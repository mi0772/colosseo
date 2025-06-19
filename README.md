# Colosseo Arena Allocator

**Colosseo** is a minimal, educational **arena allocator** written in portable C99.

This project was created for **learning purposes**, and is **not intended to replace** the many robust and battle-tested arena allocators already available. Its goal is to provide a clean and understandable implementation of region-based memory allocation, useful for studying and experimentation.

## Features

- Simple and fast memory allocation using a pre-allocated buffer
- Resettable memory model with no need to `free()` individual allocations
- Checkpoint system to temporarily roll back to a previous allocation state
- Optional aligned allocations
- Zero dependencies, fully self-contained

## Getting Started

### Build

Include `colosseo.h` and `colosseo.c` in your project. No external libraries or build systems are required.

### Example Usage

```c
#include "colosseo.h"

int main(void) {
    colosseo_t arena = colosseo_build(1024);

    char* buffer = colosseo_alloc(&arena, 64);
    if (buffer) {
        snprintf(buffer, 64, "Hello, Colosseo!");
    }

    colosseo_reset(&arena);  // Makes all allocated memory reusable
    colosseo_free(&arena);   // Releases the buffer

    return 0;
}
```

## API Overview

### Arena Lifecycle

```c
colosseo_t colosseo_build(size_t capacity);
void colosseo_free(colosseo_t* arena);
void colosseo_reset(colosseo_t* arena);
```

### Allocation

```c
char* colosseo_alloc(colosseo_t* arena, size_t size);
char* colosseo_alloc_aligned(colosseo_t* arena, size_t size, int alignment);
```

### Checkpointing

```c
char* colosseo_checkpoint(colosseo_t* arena);
void colosseo_reset_to_checkpoint(colosseo_t* arena, char* checkpoint);
```

## Internals

Colosseo uses a simple `struct` to track memory usage:

```c
typedef struct colosseo_t {
    char* memory;
    size_t offset;
    size_t capacity;
    int valid;
    char* start;
    char* end;
} colosseo_t;
```

All allocations are linear. Memory is never individually freed — instead, you reset the whole arena when you're done using it.

## Limitations

- No realloc or shrink support
- Not thread-safe
- No bounds checking beyond the initial size
- Not intended for production use

## License

This project is licensed under the MIT License.

## Author

Created by Carlo Di Giuseppe as a learning exercise. Feedback and contributions are welcome.
