/**
 * @file execute.c
 * @author Santhosh Ranganathan
 * @brief Source file for functions to execute a given command line
 */

#include "execute.h"

/**
 * Executes an array of commands using multiple pipes to redirect i/o
 * 
 * @param commands  Array of commands to be piped
 * @param len       Length of the commands array
 * @return Exit status after executing all commands
 */
int execute_commands(char *commands[], int len)
{
    int pipe_in[2], pipe_out[2], i, l, pid_count = 0, status = 0;
    pid_t pid, child_pids[MAX_TOKENS];
    char *args[MAX_TOKENS], in_file[64], out_file[64];
    int in_file_fd, out_file_fd;
    
    for (i = 0; i < len; i++)
    {
        extract_io_files(commands[i], in_file, out_file);
        generate_tokens(commands[i], " ", &l, args);

        /* create pipes only inbetween two processes */
        if (i < len-1)
            EXITF_IFNEG(pipe(pipe_out), "pipe() failed");
        EXITF_IFNEG((pid = fork()), "fork() failed");
        if (pid == 0)
        {
            /* if input file present and this is first command, redirect file to stdin */
            /* beyond first command, pipe takes precedence, input file is ignored */
            if (i == 0 && in_file[0] != '\0')
            {
                EXITF_IFNEG((in_file_fd = open(in_file, O_RDONLY)), "open() failed.");
                EXITF_IFNEG(dup2(in_file_fd, STDIN_FILENO), "dup2() failed");
                close(in_file_fd);
            }
            /* if output file present, redirect stdout to file */
            if (out_file[0] != '\0')
            {
                EXITF_IFNEG((out_file_fd = creat(out_file, 0640)), "creat() failed.");
                EXITF_IFNEG(dup2(out_file_fd, STDOUT_FILENO), "dup2() failed");
                close(out_file_fd);
            }
            /* with more than one command, redirect previous pipe in to stdin before execvp() */
            if (i > 0)
            {
                close(pipe_in[1]);
                EXITF_IFNEG(dup2(pipe_in[0], STDIN_FILENO), "dup2() failed");
                close(pipe_in[0]);
            }
            /* until penultimate command, redirect current pipe out to stdout before execvp() */
            if (i < len-1)
            {
                close(pipe_out[0]);
                /* avoid that if output file present */
                if (out_file[0] == '\0')
                    EXITF_IFNEG(dup2(pipe_out[1], STDOUT_FILENO), "dup2() failed");
                close(pipe_out[1]);
            }
            EXITF_IFNEG(execvp(args[0], args), "execvp() failed");
        }
        /* store child pids */
        child_pids[pid_count++] = pid;
        /* close previous pipe */
        if (i > 0)
        {
            close(pipe_in[1]);
            close(pipe_in[0]);
        }
        /* assign current pipe to previous pipe */
        pipe_in[0] = pipe_out[0];
        pipe_in[1] = pipe_out[1];
    }
    /* wait for all children */
    for (i=0; i < pid_count; i++)
        waitpid(child_pids[i], &status, 0);
    return status;
}

/**
 * Parses and executes a string of commands with arguments and pipes
 * 
 * @param cmdline Command line string
 * @return Exit status after executing all commands
 */
int execute(char *cmdline)
{
    int pid, status, len;
    bool background;
    char *commands[MAX_TOKENS];

    /* Stop if cmdline is NULL or string is empty */
    if (!cmdline || !cmdline[0])
        return 0;
    cleanup_string(&cmdline);
    len = strlen(cmdline);
    /* check if give command line is to be executed in background */
    if ((background = cmdline[len - 1] == '&') == TRUE)
        cmdline[--len] = '\0';
    generate_tokens(cmdline, "|", &len, commands);
    /* if to be backgrounded, execute command line in a child without waiting for it to finish */
    if (background)
    {
        EXITF_IFNEG((pid = fork()), "fork() failed");
        if (pid == 0)
        {
            status = execute_commands(commands, len);
            puts("\nJob has ended");
            exit(status);
        }
        return 0;
    }
    return execute_commands(commands, len);
}
