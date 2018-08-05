#include <stdio.h>
#include <getopt.h>

#include "pagesim.h"
#include "paging.h"
#include "swap.h"
#include "stats.h"

/* Simulator data structures */
uint8_t *mem;
pfn_t PTBR;
pcb_t *current_process;

/* Internal array of running processes (we only expose current_process
   to the user) */
static pcb_t *procs;

/* Constants used in parsing the trace file */
static const char *START = "START";
static const char *STOP = "STOP";

void print_help_and_exit(void);

int main(int argc, char **argv)
{
    /* Allocate some memory! */
    if (!(mem = calloc(1, MEM_SIZE))) {
        exit(1);
    }

    /* Allocate procs */
    if (!(procs = calloc(MAX_PID, sizeof(pcb_t)))) {
        exit(1);
    }

    /* Read command line options */
    FILE *fin = 0;
    int opt;
    while (-1 != (opt = getopt(argc, argv, "i:h:s"))) {
        switch (opt) {
        case 'i':
            fin = fopen(optarg, "r");

            if (!fin) {
                perror("Unable to open trace file");
                exit(1);
            }
            break;
        case 's':
            fin = stdin;
            break;
        case 'h':
        default:
            /* Print some sort of usage message and exit */
            print_help_and_exit();
        }
    }

    if (!fin) print_help_and_exit();

    /* Start the simulation */
    char rw;
    uint8_t data;
    uint32_t address;
    uint32_t pid;
    char buf[120];
    uint32_t step = 0;

    system_init();

    while ((fgets(buf, sizeof(buf), fin))) {
        /* Check if process is starting */
        if (!strncmp(buf, START, 5)) {
            /* Start scanning from the pid digits */
            int ret = sscanf(buf+6, "%" PRIu32 "\n", &pid);
            if (ret == 1) {
                /* Initialize new process */
                pcb_t *new_proc = &procs[pid];
                new_proc->pid = pid;
                proc_init(new_proc);
                printf("%8u: PID %u started\n", step, pid);
            } else {
                printf("Unable to parse trace file: Invalid START command encountered\n");
                exit(1);
            }
        } else if (!strncmp(buf, STOP, 4)) { /* Check if process is stopping */
            /* Start scanning from the pid digits */
            int ret = sscanf((buf+5), "%" PRIu32 "\n", &pid);
            if (ret == 1) {
                proc_cleanup(&procs[pid]);
                procs[pid].saved_ptbr = 0;
                printf("%8u: PID %u stopped\n", step, pid);
            } else {
                printf("Unable to parse trace file: Invalid STOP command encountered\n");
                exit(1);
            }
        } else { /* Regular access trace */
            int ret = sscanf(buf, "%u %c %x %hhu\n", &pid, &rw, &address, &data);
            if (ret == 4) {
                /* Context switch if need be */
                if (!current_process || current_process->pid != pid) {
                    context_switch(&procs[pid]);
                    current_process = &procs[pid];
                }
                uint8_t new_data = mem_access(address, rw, data);
                /* Print data for trace verification */
                if (rw == 'r') {
                    printf("%8u: %3u  r  0x%05x -> %02hhx\n", step, pid, address, new_data);
                } else {
                    printf("%8u: %3u  w  0x%05x <- %02hhx\n", step, pid, address, data);
                }

            } else {
                printf("Unable to parse trace file: Invalid memory access command encountered\n");
                exit(1);
            }
        }

        step++;                 /* Count step number for easy debugging */
    }
    fclose(fin);

    /* Cleanup and print statistics */
    free(mem);
    free(procs);
    compute_stats();

    printf("Total Accesses     : %" PRIu64 "\n", stats.accesses);
    printf("Reads              : %" PRIu64 "\n", stats.reads);
    printf("Writes             : %" PRIu64 "\n", stats.writes);
    printf("Page Faults        : %" PRIu64 "\n", stats.page_faults);
    printf("Writes to disk     : %" PRIu64 "\n", stats.writebacks);
    printf("Average Access Time: %f\n", stats.aat);
}

void print_help_and_exit() {
	printf("./vm-sim [OPTIONS] -i traces/file.trace\n");
    printf("  -i\t\tReads the trace from the specified path\n");
    printf("  -s\t\tReads the trace from standard input\n");
	printf("  -h\t\tThis helpful output\n");
	exit(0);
}
