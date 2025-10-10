#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include "extra_tasks.h"
#include "test_runner.h"

void test_basicText()
{
    // Реализовать - для доп задания
}

void test_caseInsensitive()
{
    // Реализовать - для доп задания
}

void test_emptyText()
{
    // Реализовать - для доп задания
}

int main()
{
    printf("Running extra task tests...\n");

    run_test("Тестирование базового случая работы с текстом", test_basicText); // ну тут для удобства макрос, можете его менять как угодно или вообще не использовать
    run_test("Проверка работы со одинаковыми символами в разном регистре", test_caseInsensitive);
    run_test("Проверка ввода пустого текста", test_emptyText);

    printf("All tests passed successfully!\n");
    return 0;
}
