#include "types.h"
#include "pagesim.h"
#include "paging.h"
#include "swapops.h"
#include "stats.h"

pfn_t select_victim_frame(void);

/*  --------------------------------- PROBLEM 7 --------------------------------------
    Finds a free physical frame. If none are available, uses a clock sweep
    algorithm to find a used frame for eviction.

    Make sure you set the reference bits to 0 for each frame that had its
    referenced bit set.

    Return:
        The physical frame number of a free (or evictable) frame.

    HINTS: Use the global variables MEM_SIZE and PAGE_SIZE to calculate
    the number of entries in the frame table.
    ----------------------------------------------------------------------------------
*/
pfn_t select_victim_frame() {
    /* See if there are any free frames */
    for (int i = 0; i < NUM_FRAMES; i++) {
        if (!frame_table[i].mapped && !frame_table[i].protected) {
            return i;
        }
    }

    /* Implement a clock sweep algorithm here */
    for (int i = 0; i < NUM_FRAMES; i++) {
        if (frame_table[i].referenced && !frame_table[i].protected) {
            frame_table[i].referenced = 0;
        } else if (!frame_table[i].referenced && !frame_table[i].protected) {
            return i;
        }
    }

    /*
     * Cycled all the way through and all reference bits were set.
     * So loop back and return the first entry that is not protected.
     */
    for (int i = 0; i < NUM_FRAMES; i++) {
        if (!frame_table[i].protected) {
            return i;
        }
    }

    /* If every frame is protected, give up. This should never happen
       on the traces we provide you. */
    printf("System ran out of memory\n");
    exit(1);
}

/*  --------------------------------- PROBLEM 8 --------------------------------------
    Make a free frame for the system to use.

    You will first call your page replacement algorithm to identify an
    "available" frame in the system.

    In some cases, the replacement algorithm will return a frame that
    is in use by another page mapping. In these cases, you must "evict"
    the frame by using the frame table to find the original mapping and
    setting it to invalid. If the frame is dirty, write its data to swap!
 * ----------------------------------------------------------------------------------
 */
pfn_t free_frame(void) {
    pfn_t victim_pfn;

    /* Call your function to find a frame to use, either one that is
       unused or has been selected as a "victim" to take from another
       mapping. */
    victim_pfn = select_victim_frame();

    /*
     * If victim frame is currently mapped:
     *
     * 1) Look up the corresponding page table entry
     * 2) If the entry is dirty, write it to disk with swap_write()
     * 3) Mark the original page table entry as invalid
     */

    /* If the victim is in use, we must evict it first */
    fte_t* fte = &frame_table[victim_pfn];
    if (fte -> mapped) {
        pcb_t* proc = fte -> process;
        pte_t* page_table = (pte_t*) (mem + (proc -> saved_ptbr * PAGE_SIZE));
        vpn_t vpn = fte -> vpn;
        pte_t* entry = &page_table[vpn];

        if (entry -> dirty) {
            void* frame = mem + (entry -> pfn * PAGE_SIZE);
            swap_write(entry, frame);
            stats.writebacks++;
        }
        entry -> valid = 0;
    }


    /* Return the pfn */
    return victim_pfn;
}
