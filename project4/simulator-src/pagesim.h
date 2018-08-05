#pragma once

#include "types.h"

#define TRUE 1
#define FALSE 0

/* Maximum number of possible processes */
#define MAX_PID 800

/*
 * A process control block (PCB).
 *
 * PCBs hold the necessary state to facilitate switching between different
 * processes running on the system at any point in time.
 */
typedef struct process {
    uint32_t pid;
    pfn_t saved_ptbr;
} pcb_t;

/*
 * Memory parameters.
 *
 * These will be provided by the user when they run the simulator.
 */

#define PADDR_LEN 16
#define VADDR_LEN 20
#define OFFSET_LEN 12

#define PAGE_SIZE (1 << OFFSET_LEN)

#define MEM_SIZE (1 << PADDR_LEN)

#define NUM_PAGES (1 << (VADDR_LEN - OFFSET_LEN))
#define NUM_FRAMES (1 << (PADDR_LEN - OFFSET_LEN))

/*
 * Global Data Structures
 */

/* These will be provided by the simulator, but managed by the student. */

extern uint8_t *mem;            /* physical memory itself */

extern pfn_t PTBR;              /* The page table base register.

                                   The PTBR tells the paging hardware
                                   where to look to find the page table
                                   for the currently running process. */

/* This will be provided and managed by the simulator */
extern pcb_t *current_process;  /* The currently running process */

/*
 * Stats.
 *
 * Throughout the execution of your program, you should update these
 * statistics. The simulator will print them at the end of the simulation.
 */

/* The following might be helpful in computing your average access
   time (AAT) */
#define MEMORY_ACCESS_TIME      100 /* 100 ns */
#define DISK_ACCESS_TIME   10000000 /* 10 million ns = 10 ms */