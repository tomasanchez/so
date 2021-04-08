/**
 * strings.c
 *
 * First steps in C.
 *
 * @file This files describes the C basic practice strings file.
 * @author Tomás A. Sánchez
 * @since 04.03.2021
 */

#include <stdlib.h>
#include "strings.h"

// ============================================================================================================
//                               ***** Public Functions Definitions *****
// ============================================================================================================

size_t str_len(const char *iv_str)
{
    return iv_str ? *iv_str == '\0' ? 0lu : str_len(iv_str + 1) + 1lu : 0lu;
}

char *str_concat(const char *iv_start, const char *iv_end)
{
    // Local Variable start_size - the size of the start string
    size_t lv_start_size = str_len(iv_start);
    // Local Variable end_size - the size of the end string
    size_t lv_end_size = str_len(iv_end);
    // Local Variable concat_size - the size of concatenation
    size_t lv_concat_size = lv_start_size + lv_end_size + 1ul;

    // Exporting  Variable concat - the concatenation of start and end
    char *ev_concat = calloc(sizeof(char), lv_concat_size);

    //Avoiding jumps on uninitialized values
    for (size_t i = 0; i <= lv_concat_size; i++)
        ev_concat[i] = '\0';

    // Copying start
    for (size_t i = 0; i <= lv_start_size; i++)
        ev_concat[i] = iv_start[i];

    // Copying end
    for (size_t i = lv_start_size, j = 0; i < lv_concat_size; i++, j++)
        ev_concat[i] = iv_end[j];

    puts(ev_concat);

    return ev_concat;
}