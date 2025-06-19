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

#include "builtins.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <stdarg.h>


static const builtin_entry builtins[] = {
    {"exit", cmd_exit, "terminates current dab shell"},
    {NULL, NULL, NULL}
};

bool is_builtin_cmd(const char* cmd) {
    for (int i = 0; builtins[i].name != NULL; ++i) {
        if (strcmp(cmd, builtins[i].name) == 0) return true;
    }
    return false;
}

int cmd_exit(int argc, char *argv[])
{
    if (argc > 1) {
        int exit_status = atoi(argv[1]);
        exit(exit_status);
    }
    exit(0);
}

static bool Printf(const char *fmt, ...) {
    va_list args;
    va_start(args, fmt);
    int ret = vprintf(fmt, args);
    va_end(args);
    return ret < 0;
}

static void print_with_escapes(const char* s) {
    for (; *s; ++s) {
        if (*s == '\\') {
            ++s;
            switch (*s) {
                case 'n': putchar('\n'); break;
                case 't': putchar('\t'); break;
                case 'r': putchar('\r'); break;
                case '\\': putchar('\\'); break;
                case 'a': putchar('\a'); break;
                case 'b': putchar('\b'); break;
                case 'v': putchar('\v'); break;
                case 'f': putchar('\f'); break;
                case '0': putchar('\0'); break;
                case '\0': return;
                default: putchar(*s); break;
            }
        } else {
            putchar(*s);
        }
    }
}

int cmd_echo(int argc, char* argv[]) {
    int start = 1;
    bool nflag = false;
    bool eflag = false;
    while (start < argc && argv[start][0] == '-' && argv[start][1] != '\0') {
        int j = 1;
        bool valid_flag = true;
        while (argv[start][j]) {
            if (argv[start][j] == 'n') {
                nflag = true;
            } else if (argv[start][j] == 'e') {
                eflag = true;
            } else if (argv[start][j] == 'E') {
                eflag = false;
            } else {
                valid_flag = false;
                break;
            }
            ++j;
        }
        if (!valid_flag) break;
        ++start;
    }
    for (int i = start; i < argc; ++i) {
        if (Printf("%s", argv[i])) return 1;
        if (i < argc - 1) {
            if (Printf(" ")) return 1;
        }
    }
    if (!nflag) {
        if (Printf("\n")) return 1;
    }
    return 0;
}
