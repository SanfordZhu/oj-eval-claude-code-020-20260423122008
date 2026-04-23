#include <stdio.h>
#include <stdlib.h>
#include "buddy.h"

int main() {
    int TESTSIZE = 128;
    int MAXRANK0PAGE = TESTSIZE * 1024 / 4;
    void *p = malloc(TESTSIZE * 1024 * 1024);

    printf("Initializing %d pages\n", MAXRANK0PAGE);
    init_page(p, MAXRANK0PAGE);

    // Allocate all pages
    printf("Allocating all pages...\n");
    for (int i = 0; i < MAXRANK0PAGE; i++) {
        void *r = alloc_pages(1);
        if (r == NULL || r == ERR_PTR(-ENOSPC)) {
            printf("Failed to allocate page %d\n", i);
            break;
        }
    }

    // Check query_page_counts
    printf("\nAfter allocation:\n");
    for (int rank = 1; rank <= 16; rank++) {
        int count = query_page_counts(rank);
        printf("Rank %d: %d free blocks\n", rank, count);
    }

    // Free all pages
    printf("\nFreeing all pages...\n");
    void *q = p;
    for (int i = 0; i < MAXRANK0PAGE; i++, q = q + 4096) {
        return_pages(q);
    }

    // Check query_page_counts again
    printf("\nAfter freeing:\n");
    for (int rank = 1; rank <= 16; rank++) {
        int count = query_page_counts(rank);
        printf("Rank %d: %d free blocks\n", rank, count);
    }

    return 0;
}