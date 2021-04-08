/**
 * strings.test.c
 *
 * First steps in C.
 *
 * @file This files describes the C basic practice main file.
 * @author Tomás A. Sánchez
 * @since 04.02.2021
 */

#include "strings.h"
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

int main(void)
{
    TEST_STRLEN();
    TEST_STRCAT();
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

    puts("Testing str_cat...");
    assert(strcmp(str_concat("", ""), "") EQ 0);
    assert(strcmp(str_concat("Hello", "World!"), "HelloWorld!") EQ 0);
    puts("Test completed");
}