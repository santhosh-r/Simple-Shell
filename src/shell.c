/**
 * @file shell.c
 * @author Santhosh Ranganathan
 * @brief Shell application
 */

#include "common.h"
#include "execute.h"

/**
 * Prints message and reads a line from user via stdin into buffer
 * 
 * @param message String to be printed before input
 * @param buffer  Buffer in which to store input
 * @param n       Max size of input to store in buffer
 * @return line read from user which is NULL if input is
 *  EOF else same as buffer
 */
char *gets_message(const char *message, char *buffer, int n)
{
    char *line;

    printf("\n%s", message);
    /* If input is not empty, replace new line with '\0' to terminate string
     fgets() used instead of gets() due to compiler warning */
    if((line = fgets(buffer, n, stdin)) > 0)
        buffer[strcspn(buffer, "\n\r")] = '\0';
    return line;
}

/**
 * Runs my Simple Shell
 * 
 * @param prompt  String to use in prompt to the user
 */
void shell(char *prompt)
{
    /* buffer to store command line input */
    char cmdline_input[BUFSIZ];
    int status;
    
    puts("\x1B[35mSimple Shell\x1B[0m");
    /* execute input command line until user enters "exit" */
    while (gets_message(prompt, cmdline_input, BUFSIZ))
    {
        if (!strcmp(cmdline_input, "exit"))
            break;
        else if (!strcmp(cmdline_input, "help"))
        {
            puts("\x1B[35mSimple Shell\x1B[0m by Santhosh Ranganathan.");
            puts("Written for Project 1 in");
            puts("UAlbany ICSI 500 Operating Systems.");
            puts("To quit this shell, type \"exit\" and press Enter.");
        }
        else
        {
            status = execute(cmdline_input);
            /* check if child executing command line exited normally */
            if (!WIFEXITED(status))
                puts("Command terminated abnormally.");
        }
    }
}

/**
 * Entry point for Shell application
 * 
 * @return Exit status
 */
int main()
{
    shell("\r\x1B[32mprompt\x1B[0m> ");
    return 0;
}
