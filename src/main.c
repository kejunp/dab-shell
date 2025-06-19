//    This file is part of DAB, a interactive and POSIX compliant shell
//    Copyright (C) 2025  Kejun Pan
//
//   This program is free software: you can redistribute it and/or modify
//    it under the terms of the GNU General Public License as published by
//    the Free Software Foundation, either version 3 of the License, or
//    (at your option) any later version.
//
//    This program is distributed in the hope that it will be useful,
//    but WITHOUT ANY WARRANTY; without even the implied warranty of
//    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
//    GNU General Public License for more details.
//
//    You should have received a copy of the GNU General Public License
//    along with this program.  If not, see <https://www.gnu.org/licenses/>.

#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <unistd.h>
#include <string.h>

#define MAX_LINE 1024
#define MAX_ARGS 128


int main() {
    char line[MAX_LINE];
    for (;;) {
        printf("$ ");
        if (!fgets(line, sizeof(line), stdin)) {
            break;
        }
        line[strcspn(line, "\n")] = 0;
        char *argv[MAX_ARGS];
        int argc = 0;
        char* token = strtok(line, " ");
        while (token && argc < MAX_ARGS - 1) {
            argv[argc++] = token;
            token = strtok(NULL, " ");
        }
        argv[argc] = NULL;
        if (argc == 0) continue;
        pid_t pid = fork();
        if (pid == 0) {
            execvp(argv[0], argv);
            fprintf(stderr, "%s: command not found\n", argv[0]);
            exit(1);
        } else if (pid > 0) {
            int status;
            waitpid(pid, &status, 0);
        } else {
            perror("fork");
        }
    }
    return EXIT_SUCCESS;
}