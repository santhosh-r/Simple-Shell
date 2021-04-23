/**
 * @file execute.h
 * @author Santhosh Ranganathan
 * @brief Header file for functions to execute a given command line
 */

#ifndef __EXECUTE_H
#define __EXECUTE_H

#include "parse.h"

/**
 * Executes an array of commands using multiple pipes to redirect i/o
 * 
 * @param commands  Array of commands to be piped
 * @param len       Length of the commands array
 * @return Exit status after executing all commands
 */
int execute_commands(char *commands[], int len);

/**
 * Parses and executes a string of commands with arguments and pipes
 * 
 * @param cmdline Command line string
 * @return Exit status after executing all commands
 */
int execute(char *cmdline);

#endif
