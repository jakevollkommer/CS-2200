#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include "buffer.h"

/**************************************************************************\
 *                                                                        *
 * Bounded buffer.  This is the only part you need to modify.  Your       *
 * buffer should have space for up to 10 integers in it at a time.        *
 *                                                                        *
 * Add any data structures you need (globals are fine) and fill in        *
 * implementations for these three procedures:                            *
 *                                                                        *
\**************************************************************************/

typedef struct node {
	int data;
	struct node *next;
} node_t;

typedef struct linked_list {
	node_t *head;
    node_t *tail;
	int curr_size;
	int max_size;
} linked_list_t;

typedef struct array {
    int *items;
    int size;
} array_t;

// TODO: INSTANTIATE GLOBALS
pthread_mutex_t lock;
linked_list_t *buffer;
array_t* used_buffer;
pthread_cond_t full;
pthread_cond_t empty;

pthread_cond_t* in_use;


/**************************************************************************\
 *                                                                        *
 * void buffer_init(void)                                                 *
 *                                                                        *
 *      buffer_init() is called by main() at the beginning of time to     *
 *      perform any required initialization.  I.e. initialize the buffer, *
 *      any mutex/condition variables, etc.                               *
 *                                                                        *
\**************************************************************************/
void buffer_init()
{
    // TODO: IMPLEMENT METHOD
    buffer = (linked_list_t*) malloc(sizeof(linked_list_t));
    buffer -> max_size = BUFFER_MAX_SIZE;
    pthread_mutex_init(&lock, NULL);

    used_buffer = (array_t*) malloc(sizeof(array_t));
    used_buffer -> items = (int*) calloc(BUFFER_MAX_SIZE,sizeof(int));
    pthread_cond_init(&full, NULL);
    pthread_cond_init(&empty, NULL);
    in_use = (pthread_cond_t*) malloc(sizeof(pthread_cond_t) * BUFFER_MAX_SIZE);
    for (int i = 0; i < 10; i++) {
        pthread_cond_init(in_use + i, NULL);
    }
    return;
}

/**************************************************************************\
 *                                                                        *
 * void buffer_insert(int number)                                         *
 *                                                                        *
 *      buffer_insert() inserts a number into the next available slot in  *
 *      the buffer.  If no slots are available, the thread should wait    *
 *      (not spin-wait!) for an empty slot to become available.           *
 *                                                                        *
\**************************************************************************/
void buffer_insert(int number)
{
    // TODO: IMPLEMENT METHOD
    pthread_mutex_lock(&lock);

    while (buffer -> curr_size == BUFFER_MAX_SIZE) {
        pthread_cond_wait(&full,&lock);
    }
    node_t *node = (node_t*) malloc(sizeof(node_t));
    node -> data = number;
    node -> next = NULL;
    if (buffer -> curr_size == 0) {
        buffer -> head = node;
    } else {
        buffer -> tail -> next = node;
    }
    buffer -> tail = node;
    buffer -> curr_size++;

    pthread_cond_signal(&empty);

    pthread_mutex_unlock(&lock);

    return;
}

/**************************************************************************\
 *                                                                        *
 * int buffer_extract(void)                                               *
 *                                                                        *
 *      buffer_extract() removes and returns the number in the next       *
 *      available slot.  If no number is available, the thread should     *
 *      wait (not spin-wait!) for a number to become available.  Note     *
 *      that multiple consumers may call buffer_extract() simulaneously.  *
 *                                                                        *
\**************************************************************************/
int buffer_extract(void)
{
    // TODO: IMPLEMENT METHOD (NOTE: THIS METHOD MUST CALL process(int number) before returning the number)
    pthread_mutex_lock(&lock);
    while (buffer -> curr_size == 0) {
        pthread_cond_wait(&empty,&lock);
    }

    node_t *available = buffer -> head;
    buffer -> head = buffer -> head -> next;
    buffer -> curr_size--;
    if (buffer -> curr_size == 0) {
        buffer -> tail = NULL;
    }

    pthread_cond_signal(&full);

    int num = available -> data;
    if (num == 0) {
        pthread_mutex_unlock(&lock);
        return 0;
        pthread_mutex_lock(&lock);
    }

    while (used_buffer -> items[num-1]) {
        pthread_cond_wait(&in_use[num-1],&lock);
    }
    used_buffer -> items[num-1] = 1;
    pthread_mutex_unlock(&lock);

    process(available -> data);

    pthread_mutex_lock(&lock);
    used_buffer -> items[num-1] = 0;
    pthread_cond_signal(&in_use[num-1]);
    pthread_mutex_unlock(&lock);

    return num;
}

void process(int number) {
    sleep(number);
}
