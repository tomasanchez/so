/**
 * strings.h
 *
 * First steps in C. Hand-made string functions
 *
 * @file This files describes the exporting methods for Strings treatment.
 * @author Tomás A. Sánchez
 * @since 04.02.2021
 */

#pragma once

#include <stdio.h>
#include <stdlib.h>

// Equals
#define EQ ==
// Not Equals
#define NE !=
// Error
#define ERROR -1

/**
 * 
 * Joins two strings.
 * 
 * @public
 * @param iv_start the first part of string to concatenate
 * @param iv_end the ending of the concatenation
 * @returns a concatenated string startend.
 */
char *str_concat(const char *, const char *);

/**
 * 
 * Tells the length of a string.
 * 
 * @public
 * @param iv_str the string itself.
 * @returns the length of a string.
 */
size_t str_len(const char *);