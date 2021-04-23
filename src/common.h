/**
 * @file common.h
 * @author Santhosh Ranganathan
 * @brief Header file for common header files needed for Shell application
 */

#ifndef __COMMON_H
#define __COMMON_H

#include <stdio.h>      /* for standard i/o */
#include <string.h>     /* for string manipulation */
#include <unistd.h>     /* for pipe() */
#include <stdlib.h>     /* for exit() */
#include <sys/types.h>  /* for pid_t */
#include <sys/wait.h>   /* for waitpid() */
#include <fcntl.h>      /* for file i/o */
#include <ctype.h>      /* for isspace() */

#define TRUE  1
#define FALSE 0
typedef int bool;

/* Macro to avoid repeating same block of code */
#define EXITF_IFNEG(test, msg) if (test < 0) { perror(msg); exit(EXIT_FAILURE); }

/* Macro to define maximum number of tokens */
#define MAX_TOKENS  16

#endif
