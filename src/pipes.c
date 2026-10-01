#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
#include "pipes.h"

int is_pipeline(char **tokens)
{
    if (tokens == NULL) return 0;
    for (int i = 0; tokens[i] != NULL; i++)
    {
        if (strcmp(tokens[i], "|") == 0)
        {
            return 1;
        }
    }
    return 0;
}

int execute_pipeline(char **tokens)
{
    int pipe_idx = -1;

    for (int i = 0; tokens[i] != NULL; i++)
    {
        if (strcmp(tokens[i], "|") == 0)
        {
            pipe_idx = i;
            break;
        }
    }

    if (pipe_idx == -1 || pipe_idx == 0 || tokens[pipe_idx + 1] == NULL)
    {
        fprintf(stderr, "ShellForge: Invalid pipe syntax\n");
        return 1;
    }

    tokens[pipe_idx] = NULL;
    char **cmd1 = tokens;
    char **cmd2 = &tokens[pipe_idx + 1];

    int pipefd[2];
    if (pipe(pipefd) == -1)
    {
        perror("pipe");
        return 1;
    }

    pid_t p1 = fork();
    if (p1 < 0)
    {
        perror("fork");
        close(pipefd[0]);
        close(pipefd[1]);
        return 1;
    }

    if (p1 == 0)
    {
        dup2(pipefd[1], STDOUT_FILENO);
        close(pipefd[0]);
        close(pipefd[1]);

        if (execvp(cmd1[0], cmd1) == -1)
        {
            perror("ShellForge");
            exit(EXIT_FAILURE);
        }
    }

    pid_t p2 = fork();
    if (p2 < 0)
    {
        perror("fork");
        close(pipefd[0]);
        close(pipefd[1]);
        waitpid(p1, NULL, 0);
        return 1;
    }

    if (p2 == 0)
    {
        dup2(pipefd[0], STDIN_FILENO);
        close(pipefd[0]);
        close(pipefd[1]);

        if (execvp(cmd2[0], cmd2) == -1)
        {
            perror("ShellForge");
            exit(EXIT_FAILURE);
        }
    }

    close(pipefd[0]);
    close(pipefd[1]);

    waitpid(p1, NULL, 0);
    waitpid(p2, NULL, 0);

    return 1;
}
