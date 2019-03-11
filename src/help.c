/*
** EPITECH PROJECT, 2018
** myftp
** File description:
** list les commands disponibles
*/

#include "myftp.h"

int help(t_ftp *client)
{
	if (write(client->fd, "214-The following commands are recognized.\n",
	43) == -1)
		error_syscall_child(client->fd, 1);
	if (write(client->fd, " USER PASS CWD CDUP QUIT DELE ", 30) == -1
	|| write(client->fd, "PWD PASV PORT HELP NOOP RETR ", 28) == -1
	|| write(client->fd, "STOR LIST\n", 10) == -1
	|| write(client->fd, "214 Help message.\n", 18) == -1)
		error_syscall_child(client->fd, 1);
	return (0);
}