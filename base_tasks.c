#include "base_tasks.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

Student *findMaxStudent(GenericList *list)
{
    if (!list || !list->head) {
        return NULL;
    }

    Node *current = list->head;
    Student *maxStudent = (Student*)current->data;

    while (current != NULL) {
        Student *s = (Student*)current->data;
        if (s->avg > maxStudent->avg) {
            maxStudent = s;
        }
        current = current->next;
    }

    return maxStudent;
}

void *findMaxVector(Vector *vector, EqualsFunc cmp)
{
    if (!vector || vector->size == 0 || !cmp) {
        return NULL;
    }

    char *byte_ptr = (char*)vector->data;
    void *max = malloc(vector->elem_size);
    if (!max) {
        return NULL;
    }
    memcpy(max, byte_ptr, vector->elem_size);

    for (size_t i = 1; i < vector->size; i++) {
        void *current = byte_ptr + i * vector->elem_size;
        if (cmp(current, max)) {
            memcpy(max, current, vector->elem_size);
        }
    }

    return max;
}

int removeDuplicatesList(GenericList *list, EqualsFunc cmp)
{
    if (!list || !list->head || !cmp) {
        return -1;
    }

    Node *current = list->head;

    while (current != NULL) {
        Node *runner = current->next;
        Node *prev = current;

        while (runner != NULL) {
            if (cmp(current->data, runner->data)) {
                prev->next = runner->next;
                free(runner->data);
                Node *toFree = runner;
                runner = runner->next;
                free(toFree);
            } else {
                prev = runner;
                runner = runner->next;
            }
        }
        current = current->next;
    }

    return 0;
}

int removeDuplicatesVector(Vector *vector, EqualsFunc cmp)
{
    if (!vector || vector->size == 0 || !cmp) {
        return -1;
    }

    char *byte_ptr = (char*)vector->data;
    size_t newSize = 0;

    for (size_t i = 0; i < vector->size; i++) {
        void *current = byte_ptr + i * vector->elem_size;
        int isDuplicate = 0;

        for (size_t j = 0; j < newSize; j++) {
            void *existing = byte_ptr + j * vector->elem_size;
            if (cmp(current, existing)) {
                isDuplicate = 1;
                break;
            }
        }

        if (!isDuplicate) {
            if (newSize != i) {
                memcpy(byte_ptr + newSize * vector->elem_size,
                       current,
                       vector->elem_size);
            }
            newSize++;
        }
    }

    vector->size = newSize;

    return 0;
}