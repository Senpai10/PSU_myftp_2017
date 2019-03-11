/*
** EPITECH PROJECT, 2018
** myftp
** File description:
** upload file
*/

#include "myftp.h"

void transfer_file(t_ftp *client, int fd)
{
	int fd_file;
	char *content;

	if (client->arg == NULL) {
		if (dprintf(client->fd, "550 Permission denied.\n") == -1)
			error_syscall_child(client->fd_data, 1);
		return ;
	}
	fd_file = open(client->arg, O_CREAT | O_WRONLY, 0777);
	content = read_file(client, fd);
	if (fd_file == -1 || content == NULL)
		error_syscall_child(client->fd_data, 4);
	if (write(fd_file, content, strlen(content)) == -1)
		error_syscall_child(client->fd_data, 1);
	print_code_pasv(client);
	if (close(fd_file) == -1)
		error_syscall_child(client->fd_data, 0);
	free(content);
}

int upload(t_ftp *client)
{
	struct sockaddr_in addr;
	int origin_fd = dup(1);
	int fd;

	if (client->pasv_actv == 1) {
		fd = accept_client(client->fd_data, &addr);
		if (fd == -1 || origin_fd == -1)
			error_syscall_child(client->fd_data, 0);
		if (dup2(fd, 1) == -1)
			error_syscall_child(client->fd_data, 0);
		transfer_file(client, fd);
		dup_close(client, fd, origin_fd);
		client->pasv_actv = 0;
	} else
		print_error_data_transfer(client);
	return (0);
}