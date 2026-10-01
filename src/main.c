#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "shell.h"
#include "input.h"
#include "parser.h"
#include "process.h"
#include "builtin.h"
#include "signals.h"
#include "scheduler.h"
#include "pipes.h"

int main()
{
    char *line;
    char **tokens;

    initialize_signals();
    sched_init();

    printf("=====================================\n");
    printf("%s Version %s\n", SHELL_NAME, VERSION);
    printf("=====================================\n");

    while (1)
    {
        printf("myshell> ");
        line = read_line();

        if (line == NULL)
        {
            break;
        }

        tokens = parse_line(line);

        if (tokens[0] != NULL)
        {
            if (is_pipeline(tokens))
            {
                execute_pipeline(tokens);
            }
            else if (execute_builtin(tokens) == 0)
            {
                execute(tokens);
            }
        }

        free_tokens(tokens);
        free(line);
    }

    printf("Goodbye!\n");
    return 0;
}
