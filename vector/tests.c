#include "generic.h"
#include "../comparators.h"
#include <stdio.h>
#include <stdlib.h>

int main() {
    printf("Testing Vector\n\n");


    printf("Test 1: createVector with sizeof(int)\n");

    Vector *vec = createVector(sizeof(int));

    if (vec == NULL) {
        printf("  FAILED: vector is NULL\n");
        return 1;
    }
    printf("  OK: vector is not NULL\n");

    if (vec->size != 0) {
        printf("  FAILED: size = %zu, expected 0\n", vec->size);
        return 1;
    }
    printf("  OK: size = 0\n");

    if (vec->capacity != MIN_SIZE) {
        printf("  FAILED: capacity = %zu, expected %d\n", vec->capacity, MIN_SIZE);
        return 1;
    }
    printf("  OK: capacity = %zu\n", vec->capacity);

    if (vec->elem_size != sizeof(int)) {
        printf("  FAILED: elem_size = %zu, expected %zu\n",
               vec->elem_size, sizeof(int));
        return 1;
    }
    printf("  OK: elem_size = %zu\n\n", vec->elem_size);


    printf("Test 2: appendVectorItem\n");

    Vector *vec2 = createVector(sizeof(int));

    int a = 10, b = 20, c = 30;
    appendVectorItem(vec2, &a);
    appendVectorItem(vec2, &b);
    appendVectorItem(vec2, &c);

    if (vec2->size != 3) {
        printf("  FAILED: size = %zu, expected 3\n", vec2->size);
        return 1;
    }
    printf("  OK: size = %zu\n", vec2->size);

    if (vec2->capacity < 3) {
        printf("  FAILED: capacity = %zu, should be >= 3\n", vec2->capacity);
        return 1;
    }
    printf("  OK: capacity = %zu (auto-expanded)\n", vec2->capacity);


    printf("\nTest 3: getVectorItem\n");

    int *val = (int*)getVectorItem(vec2, 0);
    if (!val || *val != 10) {
        printf("  FAILED: get index 0 = %d, expected 10\n", val ? *val : -1);
        return 1;
    }
    printf("  OK: get index 0 = %d\n", *val);

    val = (int*)getVectorItem(vec2, 2);
    if (!val || *val != 30) {
        printf("  FAILED: get index 2 = %d, expected 30\n", val ? *val : -1);
        return 1;
    }
    printf("  OK: get index 2 = %d\n", *val);


    printf("\nTest 4: setVectorItem\n");

    int new_val = 99;
    setVectorItem(vec2, 1, &new_val);

    val = (int*)getVectorItem(vec2, 1);
    if (!val || *val != 99) {
        printf("  FAILED: after set index 1 = %d, expected 99\n", val ? *val : -1);
        return 1;
    }
    printf("  OK: set index 1 to 99\n");

    printf("\nTest 5: findVectorItem\n");

    int search = 99;
    long int idx = findVectorItem(vec2, &search, intEquals);
    if (idx != 1) {
        printf("  FAILED: find 99 returned %ld, expected 1\n", idx);
        return 1;
    }
    printf("  OK: found 99 at index %ld\n", idx);

    int search2 = 999;
    idx = findVectorItem(vec2, &search2, intEquals);
    if (idx != -1) {
        printf("  FAILED: find 999 returned %ld, expected -1\n", idx);
        return 1;
    }
    printf("  OK: not found returns -1\n");


    printf("\nTest 6: popVectorItem\n");

    int *popped = (int*)popVectorItem(vec2, 1);
    if (!popped || *popped != 99) {
        printf("  FAILED: popped value = %d, expected 99\n", popped ? *popped : -1);
        return 1;
    }
    printf("  OK: popped value = %d\n", *popped);
    free(popped);

    if (vec2->size != 2) {
        printf("  FAILED: after pop size = %zu, expected 2\n", vec2->size);
        return 1;
    }
    printf("  OK: after pop size = %zu\n", vec2->size);


    val = (int*)getVectorItem(vec2, 0);
    if (!val || *val != 10) {
        printf("  FAILED: after pop index 0 = %d, expected 10\n", val ? *val : -1);
        return 1;
    }

    val = (int*)getVectorItem(vec2, 1);
    if (!val || *val != 30) {
        printf("  FAILED: after pop index 1 = %d, expected 30\n", val ? *val : -1);
        return 1;
    }
    printf("  OK: remaining elements: [10, 30]\n");

    printf("\nTest 7: vectorFree\n");

    Vector *vec3 = createVector(sizeof(double));
    double d = 3.14;
    appendVectorItem(vec3, &d);

    int result = vectorFree(vec3);
    if (result != 0) {
        printf("  FAILED: vectorFree returned %d\n", result);
        return 1;
    }
    printf("  OK: vectorFree works\n");

    printf("\nTest 8: Auto resize (capacity management)\n");

    Vector *vec4 = createVector(sizeof(int));
    printf("  Initial capacity: %zu\n", vec4->capacity);

    for (int i = 0; i < 10; i++) {
        appendVectorItem(vec4, &i);
    }
    printf("  After 10 appends: size=%zu, capacity=%zu\n", vec4->size, vec4->capacity);

    if (vec4->size != 10) {
        printf("  FAILED: size = %zu, expected 10\n", vec4->size);
        return 1;
    }

    if (vec4->capacity < 10) {
        printf("  FAILED: capacity = %zu, should be >= 10\n", vec4->capacity);
        return 1;
    }

    for (int i = 0; i < 7; i++) {
        int *p = (int*)popVectorItem(vec4, 0);
        free(p);
    }
    printf("  After 7 pops: size=%zu, capacity=%zu\n", vec4->size, vec4->capacity);

    vectorFree(vec4);
    printf("  OK: auto resize works\n");

    vectorFree(vec);
    vectorFree(vec2);

    printf("\n=== All tests passed! ===\n");
    return 0;
}