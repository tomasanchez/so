/**
 * strings.test.c
 *
 * First steps in C.
 *
 * @file This files describes the C basic practice main file.
 * @author Tomás A. Sánchez
 * @since 04.02.2021
 */

#include "str.h"
#include <string.h>
#include <assert.h>

/**
 * Assertions on str_len
 */
void TEST_STRLEN(void);

/**
 * Assertions on str_concat
 */
void TEST_STRCAT(void);

/**
 * Assertions on str_concat_dynamic
 */
void TEST_STRCAT_DYNAMIC(void);

int main(void)
{
    TEST_STRLEN();
    TEST_STRCAT();
    TEST_STRCAT_DYNAMIC();

    return 0;
}

void TEST_STRLEN()
{
    puts("Testing str_len...");
    assert(str_len("Hello") EQ 5lu);
    assert(str_len("") EQ 0lu);
    assert(str_len(NULL) EQ 0lu);
    puts("Test completed");
}

void TEST_STRCAT()
{
    // Local Variable test - the testing reference
    char *lv_test;

    puts("Testing str_cat...");
    lv_test = str_concat("", "");
    assert(strcmp(lv_test, "") EQ 0);
    free(lv_test);

    lv_test = str_concat("Hello", "World!");
    assert(strcmp(lv_test, "HelloWorld!") EQ 0);
    free(lv_test);

    puts("Test completed");
}

void TEST_STRCAT_DYNAMIC()
{
    // Local Variable test - the testing reference
    char **lv_test = malloc(sizeof(char *));
    *lv_test = malloc(sizeof(char));

    puts("Testing str_cat_dynamic...");

    str_concat_dynamic("", "", lv_test);
    assert(strcmp(*lv_test, "") EQ 0);

    str_concat_dynamic("Hello", "World!", lv_test);
    assert(strcmp(*lv_test, "HelloWorld!") EQ 0);

    if (lv_test)
    {
        if (*lv_test)
            free(*lv_test);
        free(lv_test);
    }

    puts("Test completed");
}