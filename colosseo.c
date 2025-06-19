//
// Created by Carlo Di Giuseppe on 19/06/25.
//

#include "colosseo.h"

colosseo_t colosseo_build(size_t capacity) {
    char *memory = malloc(capacity + 1);
    colosseo_t t = {
        .capacity = capacity,
        .memory = memory,
        .offset = 0,
        .valid = memory != NULL,
        .start = memory,
        .end = memory ? memory + capacity : NULL
    };
    return t;
}

void colosseo_reset(colosseo_t *colosseo) {
    if (colosseo != NULL && colosseo->valid) {
        colosseo->offset = 0;
    }
}

char *colosseo_checkpoint(colosseo_t *colosseo) {
    if (colosseo == NULL || !colosseo->valid) return NULL;
    return colosseo->start + colosseo->offset;
}

int colosseo_reset_to_checkpoint(colosseo_t *colosseo, char *checkpoint) {
    if (colosseo == NULL || !colosseo->valid) return -1;
    if (colosseo->start <= checkpoint && checkpoint <= colosseo->end) {
        colosseo->offset = checkpoint - colosseo->start;
    }
    return 0;
}

char *colosseo_alloc(colosseo_t *colosseo, size_t size) {
    if (colosseo == NULL || !colosseo->valid) return NULL;

    if (colosseo->offset + size > colosseo->capacity) return NULL;

    char *r = colosseo->start + colosseo->offset;
    colosseo->offset += size;
    return r;
}

char *colosseo_alloc_aligned(colosseo_t *colosseo, size_t size, int alignment) {
    if (colosseo == NULL || !colosseo->valid) return NULL;

    int aligned_offset = (colosseo->offset + (alignment - 1)) & ~(alignment - 1);
    if (aligned_offset + size > colosseo->capacity) return NULL;

    char *r = colosseo->start + aligned_offset;
    colosseo->offset = aligned_offset + size;

    return r;
}

void colosseo_free(colosseo_t *colosseo) {
    if (colosseo != NULL && colosseo->valid) {
        free(colosseo->start);
        colosseo->valid = 0;
        colosseo->start = NULL;
        colosseo->memory = NULL;
        colosseo->end = NULL;
        colosseo->offset = 0;
        colosseo->capacity = 0;
    }
}