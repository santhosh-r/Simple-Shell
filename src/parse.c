/**
 * @file parse.c
 * @author Santhosh Ranganathan
 * @brief Source file for functions which help with parsing a string for tokens
 */

#include "parse.h"

/**
 * Removes extra whitespaces and replaces any remaining
 * in between non-whitespace characters with a single
 * space character.
 * 
 * @param source  String which needs to be cleaned of extra whitespaces
 * @return String with extra whitespaces removed.
 */
char *cleanup_string(char **source)
{
    char *str = *source;
    int i, j, c;

    /* parse string and store only non-whitespace and single space characters */
    for (i=0, j=0; str[i]; i++)
        if (!(c = isspace(str[i])) || (!isspace(str[i+1]) && str[i+1]))
            str[j++] = c?' ':str[i];  /* make sure to replace newline, tab and return with plain space */ 
    /* terminate the cleaned string */
    str[j] = '\0';
    /* remove if present the space at the beginning of string */
    str = isspace(str[0]) ? str+1 : str;
    return *source = str;
}

/** 
 * Generates an array of tokens present source string seperated by the
 * given delimiter
 *
 * @param source  String containing tokens
 * @param delim   Delimiter separating tokens
 * @param len     Location to store number of tokens generated
 * @param tokens  Location of array to store tokens generated
 */
void generate_tokens(char *source, char *delim, int *len, char *tokens[])
{
    char *token;
    int n = 0;

    /* store tokens extracted using strsep() to tokens array */
    while ((token = strsep(&source, delim)) != NULL && n < MAX_TOKENS-1)
        tokens[n++] = cleanup_string(&token);
    /* terminate tokens array with NULL, useful in execvp */
    tokens[n] = (char *)NULL;
    *len = n;
}

/**
 * Removes a portion of string denoted by begin and end. Expects both
 * pointers to be valid positions within the same string with end
 * pointing to a position after begin.
 * 
 * @param begin pointer to beginning of substring
 * @param end   pointer to next position after substring end
 */
void remove_substring(char *begin, char *end)
{
    int len = strlen(end);
    int i;

    if (begin > end)
        return;
    for (i = 0; i < len; i++)
    {
        begin[i] = end[i];
        end[i] = '\0';
    }
    begin[len] = '\0';
}

/**
 * Extracts input and output files and removes them from given command string
 * 
 * @param command   String containing command eg. "ls >out.txt"
 * @param in_file   String to store input file
 * @param out_file  String to store output file
 * @return FALSE if error present while parsing command string
 */
void extract_io_files(char *command, char *in_file, char *out_file)
{
    char *begin, *redir_symbol;
    int len, fd;

    /* clean up string before parsing through it to avoid possible errors */
    cleanup_string(&command);
    /* make in_file empty, useful when no input file is present */
    in_file[0] = '\0';
    /* go through all string indices where '<' is present */
    while ((begin = strchr(command, '<')) != NULL)
    {
        /* store location where '<' was found */
        redir_symbol = begin;
        /* move begin past '<' */
        begin++;
        /* ignore all spaces */
        while (isspace(*begin) && begin < command + strlen(command))
            begin++;
        /* find string index where input filename ends */ 
        len = strcspn(begin, " ><");
        /* copy input filename into in_file */
        strncpy(in_file, begin, len);
        in_file[len] = '\0';
        /* remove input filename from command */
        remove_substring(redir_symbol, begin + len);
    }
    /* make out_file empty, useful when no output file is present */
    out_file[0] = '\0';
    /* go through all string indices where '>' is present */
    while ((begin = strchr(command, '>')) != NULL)
    {
        /* store location where '>' was found */
        redir_symbol = begin;
        /* move begin past '>' */
        begin++;
        /* ignore all spaces */
        while (isspace(*begin) && begin < command + strlen(command))
            begin++;
        /* find string index where output filename ends */ 
        len = strcspn(begin, " <>");
        /* copy output filename into out_file */
        strncpy(out_file, begin, len);
        out_file[len] = '\0';
        /* remove output filename from command */
        remove_substring(redir_symbol, begin + len);
        /* try to mimic behavior of bash, create all output files even if only last is used */
        if ((fd = creat(out_file, 0640)) < 0)
            out_file[0] = '\0';
        else
            close(fd);
    }
    /* clean up string after removal of input and output filenames */
    cleanup_string(&command);
}