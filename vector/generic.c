#include "generic.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


static bool needToResize(Vector *vector, bool *increase)
{
    if (!vector) {
        return false;
    }


    if (vector->size >= vector->capacity) {
        *increase = true;
        return true;
    }

    if (vector->size <= vector->capacity / 4 && vector->capacity > MIN_SIZE) {
        *increase = false;
        return true;
    }

    return false;
}

static int resize(Vector *vector, bool increase)
{
    if (!vector) {
        return -1;
    }

    size_t new_capacity;

    if (increase) {
        new_capacity = vector->capacity * 2;
    } else {
        new_capacity = vector->capacity / 2;
        if (new_capacity < MIN_SIZE) {
            new_capacity = MIN_SIZE;
        }
    }


    void *new_data = realloc(vector->data, new_capacity * vector->elem_size);
    if (!new_data) {
        printf("Memory reallocation failed\n");
        return -1;
    }

    vector->data = new_data;
    vector->capacity = new_capacity;

    return 0;
}

Vector *createVector(size_t elem_size)
{

    Vector *vector = (Vector*)malloc(sizeof(Vector));
    if (!vector) {
        printf("Memory allocation failed for vector\n");
        return NULL;
    }

    vector->elem_size = elem_size;
    vector->size = 0;
    vector->capacity = MIN_SIZE;

    vector->data = malloc(vector->capacity * elem_size);
    if (!vector->data) {
        printf("Memory allocation failed for vector data\n");
        free(vector);
        return NULL;
    }

    return vector;
}

int appendVectorItem(Vector *vector, void *el)
{
    if (!vector || !el) {
        return -1;
    }

    bool increase;
    if (needToResize(vector, &increase)) {
        if (resize(vector, increase) != 0) {
            return -1;
        }
    }

    char *byte_ptr = (char*)vector->data;
    memcpy(byte_ptr + vector->size * vector->elem_size, el, vector->elem_size);

    vector->size++;

    return 0;
}

void *getVectorItem(Vector *vector, size_t index)
{
    if (!vector || !vector->data || index >= vector->size) {
        return NULL;
    }

    char *byte_ptr = (char*)vector->data;
    return byte_ptr + index * vector->elem_size;
}

int setVectorItem(Vector *vector, size_t index, void *value)
{
    if (!vector || !vector->data || !value || index >= vector->size) {
        return -1;
    }

    char *byte_ptr = (char*)vector->data;
    memcpy(byte_ptr + index * vector->elem_size, value, vector->elem_size);

    return 0;
}

void *popVectorItem(Vector *vector, size_t index)
{
    if (!vector || !vector->data || vector->size == 0 || index >= vector->size) {
        return NULL;
    }

    char *byte_ptr = (char*)vector->data;


    void *returnData = malloc(vector->elem_size);
    if (!returnData) {
        printf("Memory allocation failed for return data\n");
        return NULL;
    }
    memcpy(returnData, byte_ptr + index * vector->elem_size, vector->elem_size);

    if (index < vector->size - 1) {
        void *dest = byte_ptr + index * vector->elem_size;
        void *src = byte_ptr + (index + 1) * vector->elem_size;
        size_t bytes_to_move = (vector->size - index - 1) * vector->elem_size;
        memmove(dest, src, bytes_to_move);
    }

    vector->size--;

    bool increase;
    if (needToResize(vector, &increase) && !increase) {
        resize(vector, false);
    }

    return returnData;
}

long int findVectorItem(Vector *vector, void *value, EqualsFunc cmp)
{
    if (!vector || !vector->data || vector->size == 0 || !value || !cmp) {
        return -1;
    }

    char *byte_ptr = (char*)vector->data;

    for (size_t i = 0; i < vector->size; i++) {
        void *item = byte_ptr + i * vector->elem_size;
        if (cmp(item, value)) {
            return (long int)i;
        }
    }

    return -1;
}

int vectorFree(Vector *vector)
{
    if (!vector) {
        return -1;
    }

    if (vector->data) {
        free(vector->data);
    }

    free(vector);

    return 0;
}