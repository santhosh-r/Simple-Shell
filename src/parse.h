/**
 * @file parse.h
 * @author Santhosh Ranganathan
 * @brief Header file for functions which help with parsing a string for tokens
 */

#ifndef __PARSE_H
#define __PARSE_H

#include "common.h"

/**
 * Removes extra whitespaces and replaces any remaining
 * in between non-whitespace characters with a single
 * space character.
 * 
 * @param source  String which needs to be cleaned of extra whitespaces
 * @return String with extra whitespaces removed.
 */
char *cleanup_string(char **source);

/** 
 * Generates an array of tokens present source string seperated by the
 * given delimiter
 *
 * @param source  String containing tokens
 * @param delim   Delimiter separating tokens
 * @param len     Location to store number of tokens generated
 * @param tokens  Location of array to store tokens generated
 */
void generate_tokens(char *source, char *delim, int *len, char *tokens[]);

/**
 * Extracts input and output files and removes them from given command string
 * 
 * @param command   String containing command eg. "ls >out.txt"
 * @param in_file   String to store input file
 * @param out_file  String to store output file
 */
void extract_io_files(char *command, char *in_file, char *out_file);

#endif
