/*
** EPITECH PROJECT, 2018
** myftp
** File description:
** les différentes commandes
*/

#include "myftp.h"

int delete(t_ftp *client)
{
	if (client->arg == NULL || remove(client->arg) == -1) {
		if (write(client->fd,
		"550 Permission denied.\n", 23) == -1)
			error_syscall_child(client->fd, 1);
	} else
		if (write(client->fd,
		"250 Requested file action okay, completed.\n", 43) == -1)
			error_syscall_child(client->fd, 1);
	return (0);
}

int cdup(t_ftp *client)
{
	if (chdir("../") == -1)
		error_syscall_child(client->fd, 4);
	else
		if (write(client->fd, "200 Command okay.\n", 18) == -1)
			error_syscall_child(client->fd, 1);
	return (0);
}

int cwd(t_ftp *client)
{
	if (client->arg == NULL || chdir(client->arg) == -1) {
		if (write(client->fd, "550 Failed to change directory.\n",
		32) == -1)
			error_syscall_child(client->fd, 1);
	} else
		if (write(client->fd,
		"250 Directory successfully changed.\n", 37) == -1)
			error_syscall_child(client->fd, 1);
	return (0);
}

int pwd(t_ftp *client)
{
	char pwd[1024];

	if (getcwd(pwd, sizeof(pwd)) == NULL)
		error_syscall_child(client->fd, 4);
	else
		if (write(client->fd, "257 ", 4) == -1
		|| write(client->fd, pwd, strlen(pwd)) == -1
		|| write(client->fd, " created.\n", 10)  == -1)
			error_syscall_child(client->fd, 1);
	return (0);
}