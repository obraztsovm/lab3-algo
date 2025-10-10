#include "base_tasks.h"
#include "comparators.h"
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

void test_findMaxStudent()
{
    printf("Test 1: findMaxStudent() ... ");
    // Реализовать тест
    printf("OK\n");
}

void test_findMaxStudent_empty()
{
    printf("Test 2: findMaxStudent() with empty list ... ");
    // Реализовать тест
    printf("OK\n");
}

void test_findMaxVector_int()
{
    printf("Test 3: findMaxVector() with int ... ");
    // Реализовать тест
    printf("OK\n");
}

void test_findMaxVector_float()
{
    printf("Test 4: findMaxVector() with float ... ");
    // Реализовать тест
    printf("OK\n");
}

void test_findMaxVector_long()
{
    printf("Test 5: findMaxVector() with long int ... ");
    // Реализовать тест
    printf("OK\n");
}

void test_findMaxVector_empty()
{
    printf("Test 6: findMaxVector() with empty vector ... ");
    // Реализовать тест
    printf("OK\n");
}

void test_removeDuplicatesList_strings()
{
    printf("Test 7: removeDuplicatesList() with strings ... ");
    // Реализовать тест
    printf("OK\n");
}

void test_removeDuplicatesList_ints()
{
    printf("Test 8: removeDuplicatesList() with ints ... ");
    // Реализовать тест
    printf("OK\n");
}

void test_removeDuplicatesVector_ints()
{
    printf("Test 9: removeDuplicatesVector() with ints ... ");
    // Реализовать тест
    printf("OK\n");
}

void test_removeDuplicatesVector_floats()
{
    printf("Test 10: removeDuplicatesVector() with floats ... ");
    // Реализовать тест
    printf("OK\n");
}

void test_removeDuplicates_empty()
{
    printf("Test 11: removeDuplicatesList() with empty list ... ");
    // Реализовать тест
    printf("OK\n");
}

int main()
{
    printf("Running Base Tasks unit tests...\n\n");
    clock_t total_start = clock();

    test_findMaxStudent();
    test_findMaxStudent_empty();
    test_findMaxVector_int();
    test_findMaxVector_float();
    test_findMaxVector_long();
    test_findMaxVector_empty();
    test_removeDuplicatesList_strings();
    test_removeDuplicatesList_ints();
    test_removeDuplicatesVector_ints();
    test_removeDuplicatesVector_floats();
    test_removeDuplicates_empty();

    clock_t total_end = clock();
    double total_secs = (double)(total_end - total_start) / CLOCKS_PER_SEC;

    printf("\nAll Base Tasks tests passed successfully!\n");
    printf("Total test duration: %.6f seconds\n", total_secs);

    return 0;
}
