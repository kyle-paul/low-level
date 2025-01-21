#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <assert.h>

struct Arena;

typedef struct Arena {
	size_t capacity;
	size_t size;
	uint8_t *data;
	struct Arena *next;
} Arena;


Arena arena_init(size_t capacity) {
	void *data = malloc(sizeof(uint8_t) * capacity);
	if (data == NULL) {
		fprintf(stderr, "Memory allocation failed\n");
		exit(EXIT_FAILURE);
	}
	Arena arena = {
		.capacity = capacity,
		.size = 0,
		.data = data,
		.next = NULL,
	};
	return arena;
}

void *arena_alloc(Arena *arena, size_t size) {
	assert(arena->capacity >= size);
	Arena *current = arena;
	assert(current != NULL);

	while(current->size + size > current->capacity) {
		if(current->next == NULL) {
			current->next = (Arena*)malloc(sizeof(Arena));
			*current->next = arena_init(arena->capacity);
		}
		current = current->next;
	}

	void *data = &current->data[current->size];
	current->size += size;
	return data;
}

void arena_free(Arena *arena) {
	Arena *current = arena;
	while(current != NULL) {
		free(current->data);
		current->data = NULL;
		current->capacity = 0;
		current->size = 0;
		current = current->next;
	}
}

void print_arena(Arena *arena) {
	Arena *current = arena;
	while(current != NULL) {
		printf("capacity: %zu, size: %zu, data_ptr: %p\n", 
		current->capacity, current->size, current->data);
		current = current->next;
	}
}

int main() {
	Arena arena = arena_init(10);
	void *data1 = arena_alloc(&arena, sizeof(uint32_t));
	void *data2 = arena_alloc(&arena, sizeof(uint32_t));
	void *data3 = arena_alloc(&arena, sizeof(uint32_t));
	print_arena(&arena);
	arena_free(&arena);
	printf("Finished\n");
}