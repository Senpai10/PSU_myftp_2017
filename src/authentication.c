/*
** EPITECH PROJECT, 2018
** myftp
** File description:
** authentification
*/

#include "myftp.h"

int connect_pass(t_ftp *client)
{
	if (client->step == 0 && strcmp(client->commands, "PASS") == 0) {
		if (dprintf(client->fd, "503 Login with USER first.\n") == -1)
			error_syscall_child(client->fd, 1);
		return (503);
	} if (client->step == 2
	&& strcmp(client->commands, "PASS") == 0) {
		if (write(client->fd, "230 Already logged in.\n", 23) == -1)
			error_syscall_child(client->fd, 1);
		return (230);
	} if (strcmp(client->user, "Anonymous") != 0) {
		if (write(client->fd, "530 Login incorrect.\n", 21) == -1)
			error_syscall_child(client->fd, 1);
		return (530);
	} if (write(client->fd, "230 User logged in, proceed.\n", 29) == -1)
		error_syscall_child(client->fd, 1);
	return (230);
}

int connect_user(t_ftp *client)
{
	if (client->step == 2) {
		if (write(client->fd, "530 Can't change from guest user.\n",
		34) == -1)
			error_syscall_child(client->fd, 1);
		return (530);
	} if (client->arg == NULL) {
		if (write(client->fd, "530 Permission denied.\n", 23) == -1)
			error_syscall_child(client->fd, 1);
		return (530);
	}
	client->user = strdup(client->arg);
	if (write(client->fd, "331 User name okay, need password.\n",
	35) == -1)
			error_syscall_child(client->fd, 1);
	return (331);
}

void authentication(t_ftp *client)
{
	int ret;

	if (client->step != 2
	&& (strcmp(client->commands, "USER") != 0
	&& strcmp(client->commands, "PASS") != 0))
		if (write(client->fd,
		"530 Please login with USER and PASS.\n", 37) == -1)
			error_syscall_child(client->fd, 1);
	if (strcmp(client->commands, "USER") == 0) {
		ret = connect_user(client);
		if (ret == 331)
			client->step = 1;
	} if (strcmp(client->commands, "PASS") == 0) {
		ret = connect_pass(client);
		if (ret == 230)
			client->step = 2;
	}
}