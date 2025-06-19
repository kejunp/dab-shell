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

#pragma once

#include <stdbool.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef int (*builtin_func)(int argc, char* argv[]);

typedef struct {
    const char* name;
    builtin_func func;
    const char* help;
} builtin_entry;

bool is_builtin_cmd(const char* cmd);

int cmd_exit(int argc, char* argv[]);

int cmd_echo(int argc, char* argv[]);

int cmd_type(int argc, char* argv[]);

#ifdef __cplusplus
}
#endif