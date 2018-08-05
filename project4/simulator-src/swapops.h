#pragma once

#include "pagesim.h"
#include "paging.h"
#include "swap.h"
#include "types.h"

void swap_read(pte_t * entry, void *dst);
void swap_write(pte_t *entry, void * src);
void swap_free(pte_t * entry);
