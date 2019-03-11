/*
** EPITECH PROJECT, 2018
** myftp
** File description:
** disconnect
*/

#include "myftp.h"

int quit(t_ftp *client)
{
	if (write(client->fd,
	"221 Service closing control connection.\n", 40) == -1)
		error_syscall_child(client->fd, 1);
	if (close(client->fd) == -1)
		exit(84);
	return (1);
}