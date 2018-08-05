#include "cachesim.h"

#define TRUE 1
#define FALSE 0

/**
 * The stuct that you may use to store the metadata for each block in
 * the cache
 */
typedef struct block {
    uint64_t tag;  // The tag stored in that block
    uint8_t valid; // Valid bit
    uint8_t dirty; // Dirty bit

    // Add any metadata here to perform LRU/FIFO replacement. For LRU,
    // think about how you could use a counter variable to track the
    // oldest block in a set. For FIFO, consider how you would
    // implement a queue with only a single pointer.

    // TODO

} block_t;

/**
 * A struct for storing the configuration of the cache as passed in
 * the cache_init function.
 */
typedef struct config {
    uint64_t C;
    uint64_t B;
    uint64_t S;
    enum REPLACEMENT_POLICY policy;
} config_t;

// You may add global variables, structs, and function headers below
// this line if you need any

// TODO


/**
 * Initializes your cache with the passed in arguments.
 *
 * @param C The total size of your cache is 2^C bytes
 * @param S The total number of blocks in a line/set of your cache are 2^S
 * @param B The size of your blocks is 2^B bytes
 * @param policy The replacement policy of your cache
 */
void cache_init(uint64_t C, uint64_t B, uint64_t S, enum REPLACEMENT_POLICY policy)
{
    // Initialize the cache here. We strongly suggest using arrays for
    // the cache meta data. The block_t struct given above may be
    // useful.

    // TODO
    return NULL;
}

/**
 * Simulates one cache access at a time.
 *
 * @param rw The type of access, READ or WRITE
 * @param address The address that is being accessed
 * @param stats The struct that you are supposed to store the stats in
 * @return TRUE if the access is a hit, FALSE if not
 */
uint8_t cache_access(char rw, uint64_t address, cache_stats_t* stats)
{
    // Find the tag and index and check if it is a hit. If it is a
    // miss, then simulate getting the value from memory and putting
    // it in the cache. Make sure you track the stats along the way!

    uint8_t is_hit = FALSE;

    // TODO

    return is_hit;
}

/**
 * Frees up memory and performs any final calculations before the
 * statistics are outputed by the driver
 */
void cache_cleanup(cache_stats_t* stats)
{
    // Make sure to free any malloc'd memory here. To check if you
    // have freed up the the memory, run valgrind. For more
    // information, google how to use valgrind.

    // TODO
}

/**
 * Computes the tag of a given address based on the parameters passed
 * in
 *
 * @param address The address whose tag is to be computed
 * @param C The size of the cache (i.e. Size of cache is 2^C)
 * @param B The size of the cache block (i.e. Size of block is 2^B)
 * @param S The set associativity of the cache (i.e. Set-associativity is 2^S)
 * @return The computed tag
 */
uint64_t get_tag(uint64_t address, uint64_t C, uint64_t B, uint64_t S)
{
    // TODO
    return -1;
}

/**
 * Computes the index of a given address based on the parameters
 * passed in
 *
 * @param address The address whose tag is to be computed
 * @param C The size of the cache (i.e. Size of cache is 2^C)
 * @param B The size of the cache block (i.e. Size of block is 2^B)
 * @param S The set associativity of the cache (i.e. Set-associativity is 2^S)
 * @return The computed index
 */
uint64_t get_index(uint64_t address, uint64_t C, uint64_t B, uint64_t S)
{
    // TODO
    return -1;
}
