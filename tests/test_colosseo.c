#include <stdio.h>
#include <assert.h>
#include "../colosseo.h"

void test_basic_alloc() {
    colosseo_t arena = colosseo_build(128);
    assert(arena.valid);

    char* a = colosseo_alloc(&arena, 32);
    char* b = colosseo_alloc(&arena, 32);
    assert(a != NULL && b != NULL);
    assert(b == a + 32);

    colosseo_free(&arena);
}

void test_checkpoint_and_reset() {
    colosseo_t arena = colosseo_build(128);
    assert(arena.valid);

    char* mark = colosseo_checkpoint(&arena);
    char* a = colosseo_alloc(&arena, 32);
    colosseo_reset_to_checkpoint(&arena, mark);
    char* b = colosseo_alloc(&arena, 32);

    assert(a == b);

    colosseo_free(&arena);
}

void test_alloc_overflow() {
    colosseo_t arena = colosseo_build(64);
    assert(arena.valid);

    char* a = colosseo_alloc(&arena, 32);
    char* b = colosseo_alloc(&arena, 40); // should fail
    assert(a != NULL);
    assert(b == NULL);

    colosseo_free(&arena);
}

void test_aligned_alloc() {
    colosseo_t arena = colosseo_build(128);
    assert(arena.valid);

    char* a = colosseo_alloc_aligned(&arena, 32, 16);
    assert(a != NULL);
    assert(((uintptr_t)a % 16) == 0);

    colosseo_free(&arena);
}

int main() {
    test_basic_alloc();
    test_checkpoint_and_reset();
    test_alloc_overflow();
    test_aligned_alloc();

    printf("All tests passed.\n");
    return 0;
}

