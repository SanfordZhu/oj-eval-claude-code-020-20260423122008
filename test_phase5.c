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
    }

    // Free all pages
    printf("\nFreeing all pages...\n");
    void *q = p;
    for (int i = 0; i < MAXRANK0PAGE; i++, q = q + 4096) {
        return_pages(q);
    }

    // Check what the test expects
    printf("\nChecking Phase 5 expectations:\n");
    for (int pgIdx = 1; pgIdx <= 15; ++pgIdx) {
        int count = query_page_counts(pgIdx);
        printf("Rank %d: %d (expected 0) %s\n", pgIdx, count, count == 0 ? "OK" : "FAIL");
    }

    int count16 = query_page_counts(16);
    printf("Rank 16: %d (expected != 0) %s\n", count16, count16 != 0 ? "OK" : "FAIL");

    return 0;
}