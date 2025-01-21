#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <assert.h>

typedef struct {
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
	};
	return arena;
}

void *arena_alloc(Arena *arena, size_t size) {
	assert(arena->capacity >= size);
	Arena *current = arena;
	assert(current != NULL);

	// whether left space in each arena is sufficient
	while(current->size + size > current->capacity) {
		// if this is the last node
		if(current->next == NULL) {
			Arena next = arena_init(arena->capacity);
			current->next = &next;
		}
		// traverse next if this not the last node
		current = current->next;   
	}

	// found one arena have valid left space
	void *data = &arena->data[arena->size];
	arena->size += size;
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
	printf("capacity: %zu, size: %zu, data_ptr: %p\n", 
			arena->capacity, arena->size, arena->data);
}

int main() {
	Arena arena = arena_init(1024);
	void *head = arena_alloc(&arena, sizeof(uint32_t));
	print_arena(&arena);
	arena_free(&arena);
	printf("Finished\n");
}