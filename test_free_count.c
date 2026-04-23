#include <stdio.h>
#include <stdlib.h>
#include "buddy.h"

extern int total_pages;

int main() {
    int TESTSIZE = 128;
    int MAXRANK0PAGE = TESTSIZE * 1024 / 4;
    void *p = malloc(TESTSIZE * 1024 * 1024);

    printf("Total pages: %d\n", MAXRANK0PAGE);

    init_page(p, MAXRANK0PAGE);

    // Allocate all pages
    for (int i = 0; i < MAXRANK0PAGE; i++) {
        void *r = alloc_pages(1);
    }

    // Free all pages and count
    int freed = 0;
    void *q = p;
    for (int i = 0; i < MAXRANK0PAGE; i++, q = q + 4096) {
        int ret = return_pages(q);
        if (ret == 0) freed++;
    }

    printf("Freed %d pages\n", freed);

    return 0;
}