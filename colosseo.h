//
// Created by Carlo Di Giuseppe on 19/06/25.
//

#include <stdlib.h>

#ifndef COLOSSEO_H
#define COLOSSEO_H

/**
 * Structure representing an arena allocator.
 * All allocations are done linearly from a preallocated buffer.
 */
typedef struct colosseo_t {
    char *memory;   /**< Pointer to the memory buffer */
    size_t offset;  /**< Current offset from the start for next allocation */
    size_t capacity;/**< Total capacity of the memory buffer */
    int valid;      /**< Flag indicating whether the arena is in a valid state */
    char *start;    /**< Pointer to the start of the buffer (same as memory) */
    char *end;      /**< Pointer to the end of the buffer */
} colosseo_t;



/**
 * Initializes a new arena allocator with the given capacity.
 *
 * @param capacity The size in bytes to allocate for the arena.
 * @return A colosseo_t struct with the memory initialized, or invalid if allocation failed.
 */
colosseo_t colosseo_build(size_t capacity);

/**
 * Resets the arena, making all previously allocated memory reusable.
 *
 * @param colosseo Pointer to the arena to reset.
 */
void colosseo_reset(colosseo_t *colosseo);

/**
 * Returns a checkpoint (marker) to the current position in the arena.
 *
 * @param colosseo Pointer to the arena.
 * @return A pointer that can later be passed to colosseo_reset_to_checkpoint.
 */
char* colosseo_checkpoint(colosseo_t* colosseo);

/**
 * Resets the arena to a previously saved checkpoint.
 *
 * @param colosseo Pointer to the arena.
 * @param checkpoint A pointer previously obtained from colosseo_checkpoint.
 * @return 0 on success, -1 if parameters are invalid or out of bounds.
 */
int colosseo_reset_to_checkpoint(colosseo_t* colosseo, char* checkpoint);

/**
 * Allocates a block of memory from the arena.
 *
 * @param colosseo Pointer to the arena.
 * @param size Number of bytes to allocate.
 * @return Pointer to the allocated memory, or NULL on failure.
 */
char *colosseo_alloc(colosseo_t *colosseo, size_t size);

/**
 * Allocates an aligned block of memory from the arena.
 *
 * @param colosseo Pointer to the arena.
 * @param size Number of bytes to allocate.
 * @param alignment Alignment requirement (must be a power of two).
 * @return Pointer to the allocated memory, or NULL on failure.
 */
char *colosseo_alloc_aligned(colosseo_t *colosseo, size_t size, int alignment);

/**
 * Frees the memory associated with the arena.
 *
 * @param colosseo Pointer to the arena to free.
 */
void colosseo_free(colosseo_t *colosseo);

#endif //COLOSSEO_H
