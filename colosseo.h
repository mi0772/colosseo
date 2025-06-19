//
// Created by Carlo Di Giuseppe on 19/06/25.
//

#include <stdlib.h>

#ifndef COLOSSEO_H
#define COLOSSEO_H

typedef struct colosseo_t {
    char *memory;
    size_t offset;
    size_t capacity;
    int valid;
    char *start;
    char *end;
} colosseo_t;

colosseo_t colosseo_build(size_t capacity);
void colosseo_reset(colosseo_t *colosseo);
char* colosseo_checkpoint(colosseo_t* colosseo);
void colosseo_reset_to_checkpoint(colosseo_t* colosseo, char* checkpoint);
char *colosseo_alloc(colosseo_t *colosseo, size_t size);
char *colosseo_alloc_aligned(colosseo_t *colosseo, size_t size, int alignment);
void colosseo_free(colosseo_t *colosseo);

#endif //COLOSSEO_H
