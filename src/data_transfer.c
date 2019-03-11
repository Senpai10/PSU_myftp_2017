/*
** EPITECH PROJECT, 2018
** myftp
** File description:
** data_transfer
*/

#include "myftp.h"

void print_error_data_transfer(t_ftp *client)
{
	if (dprintf(client->fd, "425 Use PORT or PASV first.\n") == -1)
		error_syscall_child(client->fd_data, 1);
}

void print_code_pasv(t_ftp *client)
{
	if (dprintf(client->fd,
	"150 File status okay; about to open data connection.\n") == -1)
		error_syscall_child(client->fd_data, 1);
	if (dprintf(client->fd, "226 Closing data connection.\n") == -1)
		error_syscall_child(client->fd_data, 1);
}

int pasv(t_ftp *client)
{
	int i = 1;

	while ((client->fd_data = create_socket(client->port + i)) == -1)
		i++;
	for (int j = 0; client->ip[j] != '\0'; j++) {
		if (client->ip[j] == '.')
			client->ip[j] = ',';
	} if (dprintf(client->fd,
	"227 Entering Passive Mode (%s,%d,%d).\n", client->ip,
	(client->port + i) / 256, (client->port + i) % 256) == -1)
		error_syscall_child(client->fd, 1);
	client->pasv_actv = 1;
	return (0);
}