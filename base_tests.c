#include "base_tasks.h"
#include "comparators.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main()
{
    printf("Base Tasks Tests\n\n");

    printf("Task 1: Find student with max average grade\n");

    GenericList *studentList = createList(sizeof(Student));

    Student students[] = {
        {"Ivan Ivanov", 4.5},
        {"Petr Petrov", 4.8},
        {"Sidor Sidorov", 4.2},
        {"Maria Ivanova", 4.9},
        {"Anna Kuznetsova", 4.7}
    };

    for (int i = 0; i < 5; i++)
    {
        appendItem(studentList, &students[i]);
    }

    Student *top = findMaxStudent(studentList);
    if (top)
    {
        printf("Result: %s (%.1f)\n", top->name, top->avg);
    }

    printf("\nTask 2: Find max in vector\n");

    int intArr[] = {5, 2, 9, 1, 7, 12, 3};
    Vector *intVec = createVector(sizeof(int));
    for (int i = 0; i < 7; i++)
    {
        appendVectorItem(intVec, &intArr[i]);
    }
    int *intMax = (int*)findMaxVector(intVec, intGreater);
    if (intMax)
    {
        printf("Max int: %d\n", *intMax);
        free(intMax);
    }

    long longArr[] = {100L, 500L, 300L, 800L, 200L};
    Vector *longVec = createVector(sizeof(long));
    for (int i = 0; i < 5; i++)
    {
        appendVectorItem(longVec, &longArr[i]);
    }
    long *longMax = (long*)findMaxVector(longVec, longGreater);
    if (longMax)
    {
        printf("Max long: %ld\n", *longMax);
        free(longMax);
    }

    float floatArr[] = {3.14f, 2.71f, 1.41f, 9.99f, 5.55f};
    Vector *floatVec = createVector(sizeof(float));
    for (int i = 0; i < 5; i++)
    {
        appendVectorItem(floatVec, &floatArr[i]);
    }
    float *floatMax = (float*)findMaxVector(floatVec, floatGreater);
    if (floatMax)
    {
        printf("Max float: %.2f\n", *floatMax);
        free(floatMax);
    }

    printf("\nTask 3: Remove duplicates\n");

    GenericList *strList = createList(sizeof(char[50]));
    char *words[] = {"banana", "mama", "banana", "papa", "mama", "apple", "banana"};
    for (int i = 0; i < 7; i++)
    {
        appendItem(strList, words[i]);
    }

    printf("Before: ");
    Node *curr = strList->head;
    printf("[");
    while (curr)
    {
        printf("\"%s\"", (char*)curr->data);
        curr = curr->next;
        if (curr) printf(", ");
    }
    printf("]\n");

    removeDuplicatesList(strList, stringEquals);

    printf("After:  ");
    curr = strList->head;
    printf("[");
    while (curr)
    {
        printf("\"%s\"", (char*)curr->data);
        curr = curr->next;
        if (curr) printf(", ");
    }
    printf("]\n");

    Vector *intVec2 = createVector(sizeof(int));
    int nums[] = {5, 2, 5, 1, 2, 9, 5, 1, 7};
    for (int i = 0; i < 9; i++)
    {
        appendVectorItem(intVec2, &nums[i]);
    }

    printf("\nInt vector before: ");
    printf("[");
    for (size_t i = 0; i < intVec2->size; i++)
    {
        int *val = (int*)getVectorItem(intVec2, i);
        printf("%d", *val);
        if (i < intVec2->size - 1) printf(", ");
    }
    printf("]\n");

    removeDuplicatesVector(intVec2, intEquals);

    printf("Int vector after:  ");
    printf("[");
    for (size_t i = 0; i < intVec2->size; i++)
    {
        int *val = (int*)getVectorItem(intVec2, i);
        printf("%d", *val);
        if (i < intVec2->size - 1) printf(", ");
    }
    printf("]\n");

    freeList(studentList);
    vectorFree(intVec);
    vectorFree(longVec);
    vectorFree(floatVec);
    freeList(strList);
    vectorFree(intVec2);

    printf("\n All tests completed\n");
    return 0;
}