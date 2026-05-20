#include "generic.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

GenericList *createList(size_t elem_size)
{
    GenericList *list = (GenericList *)malloc(sizeof(GenericList));

    if (!list) {
        printf("memory allocation failed\n");
        exit(EXIT_FAILURE);
    }

    list->head = NULL;
    list->elem_size = elem_size;

    return list;
}

void appendItem(GenericList *list, void *data)
{
	if (!list || !data) {
        return;
    }


    Node *newNode = (Node*)malloc(sizeof(Node));
    if (!newNode) {
        printf("Memory allocation failed for node\n");
        exit(EXIT_FAILURE);
    }


    newNode->data = malloc(list->elem_size);
    if (!newNode->data) {
        printf("Memory allocation failed for data\n");
        free(newNode);
        exit(EXIT_FAILURE);
    }

    memcpy(newNode->data, data, list->elem_size);

    newNode->next = NULL;

    if (list->head == NULL) {
        list->head = newNode;
        return;
    }

    Node *current = list->head;
    while (current->next != NULL) {
        current = current->next;
    }
    current->next = newNode;
}

int findItem(GenericList *list, void *value, EqualsFunc cmp)
{
	if (!list || !list->head || !value || !cmp) {
        return -1;
    }

    Node *current = list->head;
    int index = 0;

    while (current != NULL) {
        if (cmp(current->data, value)) {
            return index;
        }
        current = current->next;
        index++;
    }

    return -1;
}

void *popItem(GenericList *list, size_t index)
{
    if (!list || !list->head) {
        return NULL;
    }

    Node *toDelete = NULL;
    void *returnData = NULL;


    if (index == 0) {
        toDelete = list->head;
        list->head = list->head->next;
    }

    else {
        Node *prev = list->head;
        size_t currentIndex = 0;

        // Ищем узел ПЕРЕД удаляемым
        while (prev != NULL && currentIndex < index - 1) {
            prev = prev->next;
            currentIndex++;
        }

        // Если предыдущего нет или нет следующего — индекс вне диапазона
        if (!prev || !prev->next) {
            return NULL;
        }

        toDelete = prev->next;
        prev->next = toDelete->next;
    }


    returnData = malloc(list->elem_size);
    if (!returnData) {
        printf("Memory allocation failed for return data\n");
        return NULL;
    }
    memcpy(returnData, toDelete->data, list->elem_size);


    free(toDelete->data);
    free(toDelete);

	return returnData;
}

void freeList(GenericList *list)
{
    if (!list) {
        return;
    }

    Node *current = list->head;

    while (current != NULL) {
        Node *next = current->next;
        free(current->data);
        free(current);
        current = next;
    }

    free(list);
}

unsigned int listLength(GenericList *list)
{

    if (!list || !list->head) {
        return 0;
    }

    Node *current = list->head;
    unsigned int count = 0;


    while (current != NULL) {
        count++;
        current = current->next;
    }

    return count;
}
