# Simple-Shell



A simple Linux shell application written in C for the Operating Systems course CSI 500 at UAlbany. Simple Shell supports multiple pipes and in the case of redirections, tries to emulate bash by ignoring all of a kind except last yet creates all the files for output redirection.


    To compile and run the application
    > bash run_simple-shell.sh


## Basic shell commands


    To display a short message about the shell
    > help

    To exit the shell
    > exit


## Examples

Commands help and exit

![](images/01_help_exit.jpg?raw=true)

Another instance of shell inside the shell

![](images/02_shell_inside_shell.jpg?raw=true)

Application inside the shell

![](images/03_app_inside_shell_a.jpg?raw=true)
![](images/03_app_inside_shell_b.jpg?raw=true)
![](images/03_app_inside_shell_c.jpg?raw=true)

Multiple pipes

![](images/04_multiple_pipes.jpg?raw=true)

Redirections and pipe (both output files created, output redirected to only test3.txt)

![](images/05_redir_pipe_a.jpg?raw=true)
![](images/05_redir_pipe_b.jpg?raw=true)
