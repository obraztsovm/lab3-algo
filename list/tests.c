#include "generic.h"
#include "../comparators.h"
#include <stdio.h>
#include <stdlib.h>

int main() {
    printf("Testing GenericList\n\n");


    printf("Test 1: createList with sizeof(int)\n");

    GenericList *list = createList(sizeof(int));

    if (list == NULL) {
        printf("  FAILED: list is NULL\n");
        return 1;
    }
    printf("  OK: list is not NULL\n");

    if (list->head != NULL) {
        printf("  FAILED: head should be NULL\n");
        return 1;
    }
    printf("  OK: head is NULL\n");

    if (list->elem_size != sizeof(int)) {
        printf("  FAILED: elem_size = %zu, expected %zu\n",
               list->elem_size, sizeof(int));
        return 1;
    }
    printf("  OK: elem_size = %zu\n\n", list->elem_size);


    printf("Test 2: createList with sizeof(double)\n");

    GenericList *list2 = createList(sizeof(double));

    if (list2 == NULL) {
        printf("  FAILED: list2 is NULL\n");
        return 1;
    }

    if (list2->head != NULL) {
        printf("  FAILED: head should be NULL\n");
        return 1;
    }

    if (list2->elem_size != sizeof(double)) {
        printf("  FAILED: elem_size = %zu, expected %zu\n",
               list2->elem_size, sizeof(double));
        return 1;
    }
    printf("  OK: elem_size = %zu\n\n", list2->elem_size);


    printf("Test 3: appendItem\n");

    GenericList *list3 = createList(sizeof(int));

    int a = 10, b = 20, c = 30;
    appendItem(list3, &a);
    appendItem(list3, &b);
    appendItem(list3, &c);

    // Проверка: голова не NULL
    if (list3->head == NULL) {
        printf("  FAILED: head is NULL after appending\n");
        return 1;
    }
    printf("  OK: head is not NULL\n");

    // Проверка первого элемента
    if (*(int*)list3->head->data != 10) {
        printf("  FAILED: first element = %d, expected 10\n",
               *(int*)list3->head->data);
        return 1;
    }
    printf("  OK: first element = 10\n");

    // Проверка второго элемента
    if (list3->head->next == NULL) {
        printf("  FAILED: second element is NULL\n");
        return 1;
    }
    if (*(int*)list3->head->next->data != 20) {
        printf("  FAILED: second element = %d, expected 20\n",
               *(int*)list3->head->next->data);
        return 1;
    }
    printf("  OK: second element = 20\n");


    if (list3->head->next->next == NULL) {
        printf("  FAILED: third element is NULL\n");
        return 1;
    }
    if (*(int*)list3->head->next->next->data != 30) {
        printf("  FAILED: third element = %d, expected 30\n",
               *(int*)list3->head->next->next->data);
        return 1;
    }
    printf("  OK: third element = 30\n");

    printf("  OK: appendItem works!\n\n");


    printf("Test 4: appendItem with double\n");

    GenericList *list4 = createList(sizeof(double));

    double d1 = 1.5, d2 = 2.7, d3 = 3.14;
    appendItem(list4, &d1);
    appendItem(list4, &d2);
    appendItem(list4, &d3);

    if (*(double*)list4->head->data != 1.5) {
        printf("  FAILED: first double = %f, expected 1.5\n",
               *(double*)list4->head->data);
        return 1;
    }
    if (*(double*)list4->head->next->data != 2.7) {
        printf("  FAILED: second double = %f, expected 2.7\n",
               *(double*)list4->head->next->data);
        return 1;
    }
    if (*(double*)list4->head->next->next->data != 3.14) {
        printf("  FAILED: third double = %f, expected 3.14\n",
               *(double*)list4->head->next->next->data);
        return 1;
    }
    printf("  OK: appendItem with double works!\n\n");


    printf("Test 5: findItem\n");

    GenericList *list5 = createList(sizeof(int));

    int data[] = {5, 10, 15, 20, 25};
    for (int i = 0; i < 5; i++) {
        appendItem(list5, &data[i]);
    }

    // Поиск существующего элемента
    int search1 = 15;
    int idx1 = findItem(list5, &search1, intEquals);
    if (idx1 != 2) {
        printf("  FAILED: find 15 returned %d, expected 2\n", idx1);
        return 1;
    }
    printf("  OK: find 15 at index %d\n", idx1);

    // Поиск существующего элемента в начале
    int search2 = 5;
    int idx2 = findItem(list5, &search2, intEquals);
    if (idx2 != 0) {
        printf("  FAILED: find 5 returned %d, expected 0\n", idx2);
        return 1;
    }
    printf("  OK: find 5 at index %d\n", idx2);


    int search3 = 25;
    int idx3 = findItem(list5, &search3, intEquals);
    if (idx3 != 4) {
        printf("  FAILED: find 25 returned %d, expected 4\n", idx3);
        return 1;
    }
    printf("  OK: find 25 at index %d\n", idx3);


    int search4 = 99;
    int idx4 = findItem(list5, &search4, intEquals);
    if (idx4 != -1) {
        printf("  FAILED: find 99 returned %d, expected -1\n", idx4);
        return 1;
    }
    printf("  OK: find 99 returns -1 (not found)\n");


    GenericList *emptyList = createList(sizeof(int));
    int search5 = 10;
    int idx5 = findItem(emptyList, &search5, intEquals);
    if (idx5 != -1) {
        printf("  FAILED: find in empty list returned %d, expected -1\n", idx5);
        return 1;
    }
    printf("  OK: find in empty list returns -1\n\n");


    printf("Test 6: popItem\n");

    GenericList *list6 = createList(sizeof(int));


    int nums[] = {100, 200, 300, 400, 500};
    for (int i = 0; i < 5; i++) {
        appendItem(list6, &nums[i]);
    }

    // Удаляем из середины (index 2 -> значение 300)
    int *popped = (int*)popItem(list6, 2);
    if (!popped) {
        printf("  FAILED: popItem returned NULL\n");
        return 1;
    }
    if (*popped != 300) {
        printf("  FAILED: popped value = %d, expected 300\n", *popped);
        free(popped);
        return 1;
    }
    printf("  OK: popped value = %d\n", *popped);
    free(popped);


    int count = 0;
    Node *curr = list6->head;
    while (curr) {
        count++;
        curr = curr->next;
    }
    if (count != 4) {
        printf("  FAILED: after pop length = %d, expected 4\n", count);
        return 1;
    }
    printf("  OK: length = %d\n", count);


    int expected[] = {100, 200, 400, 500};
    curr = list6->head;
    for (int i = 0; i < 4; i++) {
        if (*(int*)curr->data != expected[i]) {
            printf("  FAILED: element %d = %d, expected %d\n",
                   i, *(int*)curr->data, expected[i]);
            return 1;
        }
        curr = curr->next;
    }
    printf("  OK: remaining elements: 100, 200, 400, 500\n");


    popped = (int*)popItem(list6, 0);
    if (!popped) {
        printf("  FAILED: pop head returned NULL\n");
        return 1;
    }
    if (*popped != 100) {
        printf("  FAILED: popped head = %d, expected 100\n", *popped);
        free(popped);
        return 1;
    }
    printf("  OK: popped head value = %d\n", *popped);
    free(popped);


    if (*(int*)list6->head->data != 200) {
        printf("  FAILED: new head = %d, expected 200\n", *(int*)list6->head->data);
        return 1;
    }
    printf("  OK: new head = 200\n");


    popped = (int*)popItem(list6, 2);
    if (!popped) {
        printf("  FAILED: pop last returned NULL\n");
        return 1;
    }
    if (*popped != 500) {
        printf("  FAILED: popped last = %d, expected 500\n", *popped);
        free(popped);
        return 1;
    }
    printf("  OK: popped last value = %d\n", *popped);
    free(popped);


    if (*(int*)list6->head->data != 200 || *(int*)list6->head->next->data != 400) {
        printf("  FAILED: remaining elements incorrect\n");
        return 1;
    }
    printf("  OK: remaining elements: 200, 400\n");


    GenericList *emptyList2 = createList(sizeof(int));
    popped = (int*)popItem(emptyList2, 0);
    if (popped != NULL) {
        printf("  FAILED: pop from empty list returned non-NULL\n");
        free(popped);
        return 1;
    }
    printf("  OK: pop from empty list returns NULL\n");


    popped = (int*)popItem(list6, 99);
    if (popped != NULL) {
        printf("  FAILED: pop invalid index returned non-NULL\n");
        free(popped);
        return 1;
    }
    printf("  OK: pop invalid index returns NULL\n\n");


	printf("Test 7: listLength\n");

	GenericList *list7 = createList(sizeof(int));


	if (listLength(list7) != 0) {
    	printf("  FAILED: empty list length = %u, expected 0\n", listLength(list7));
    	return 1;
	}
	printf("  OK: empty list length = 0\n");


	int x = 10, y = 20, z = 30;
	appendItem(list7, &x);
	appendItem(list7, &y);
	appendItem(list7, &z);

	if (listLength(list7) != 3) {
    	printf("  FAILED: length after 3 appends = %u, expected 3\n", listLength(list7));
    	return 1;
	}
	printf("  OK: length after 3 appends = 3\n");


	int *poppedLen = (int*)popItem(list7, 1);
	free(poppedLen);

	if (listLength(list7) != 2) {
    	printf("  FAILED: length after pop = %u, expected 2\n", listLength(list7));
    	return 1;
	}
	printf("  OK: length after pop = 2\n\n");

	freeList(list7);

    // TODO: раскомментировать после реализации freeList
    freeList(list);
    freeList(list2);
    freeList(list3);
    freeList(list4);
	freeList(list5);
	freeList(list6);
	freeList(list7);
	freeList(emptyList);
	freeList(emptyList2);

	return 0;
}