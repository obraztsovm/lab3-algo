#ifndef TEST_RUNNER_H
#define TEST_RUNNER_H

#include <stdio.h>
#include <time.h>

typedef void (*TestFunc)();

// Примерчик макроса

static void run_test(const char *name, TestFunc func)
{
    clock_t start = clock();

    printf("\n╔════════════════════════════════════════════════════════════════════════════╗\n");
    printf(" RUNNING TEST: %s \n", name);
    printf("╠════════════════════════════════════════════════════════════════════════════╣\n");

    func(); // тест может писать в консоль

    clock_t end = clock();
    double duration = (double)(end - start) / CLOCKS_PER_SEC;

    printf("╠════════════════════════════════════════════════════════════════════════════╣\n");
    printf(" STATUS: PASSED                       \n");
    printf(" DURATION: %.6f seconds               \n", duration);
    printf("╚════════════════════════════════════════════════════════════════════════════╝\n");
}

#endif // TEST_RUNNER_H
