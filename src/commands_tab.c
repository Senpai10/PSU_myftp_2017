/*
** EPITECH PROJECT, 2018
** myftp
** File description:
** tableau de command
*/

#include "myftp.h"

const t_commands commands_tab[] =
{
	{"PWD", &pwd},
	{"CWD", &cwd},
	{"CDUP", &cdup},
	{"DELE", &delete},
	{"HELP", &help},
	{"QUIT", &quit},
	{"PASV", &pasv},
	{"NOOP", &noop},
	{"LIST", &list},
	{"RETR", &download},
	{"STOR", &upload},
	{NULL, NULL}
};
