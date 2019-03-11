/*
** EPITECH PROJECT, 2018
** myftp
** File description:
** download
*/

#include "myftp.h"

void dup_close(t_ftp *client, int fd, int origin_fd)
{
	if (close(fd) == -1)
		error_syscall_child(client->fd_data, 0);
	if (dup2(origin_fd, 1) == -1)
		error_syscall_child(client->fd_data, 0);
	if (close(origin_fd) == -1)
		error_syscall_child(client->fd_data, 0);
	if (close(client->fd_data) == -1)
		error_syscall_child(client->fd, 0);
}

int open_error(t_ftp *client, int fd_file, int fd, int origin_fd)
{
	if (fd_file == -1) {
		client->pasv_actv = 0;
		if (dprintf(client->fd, "550 Failed to open file.\n") == -1)
			error_syscall_child(client->fd_data, 1);
		dup_close(client, fd, origin_fd);
		return (0);
	}
	return (1);
}

char *read_file(t_ftp *client, int fd)
{
	char *buffer = malloc(sizeof(char) + 1);
	char *save = "\0";
	int readed = 0;

	if (buffer == NULL)
		return (NULL);
	while ((readed = read(fd, buffer, 1)) > 0) {
		if (readed == -1)
			error_syscall_child(client->fd_data, 3);
		buffer[readed] = '\0';
		save = my_strcat(save, buffer);
	}
	free(buffer);
	return (save);
}

void print_download(t_ftp *client, int fd, char *content)
{
	if (content == NULL)
		error_syscall_child(client->fd_data, 3);
	if (dprintf(fd, "%s", content) == -1)
		error_syscall_child(client->fd_data, 1);
	print_code_pasv(client);
}

int download(t_ftp *client)
{
	struct sockaddr_in addr;
	int origin_fd = dup(1);
	int fd_file;
	int fd;

	if (client->pasv_actv == 1) {
		fd = accept_client(client->fd_data, &addr);
		if (fd == -1 || origin_fd == -1 || dup2(fd, 1) == -1)
			error_syscall_child(client->fd_data, 0);
		fd_file = open(client->arg, O_RDONLY);
		if (open_error(client, fd_file, fd, origin_fd) == 0)
			return (0);
		print_download(client, fd, read_file(client, fd_file));
		if (close(fd_file) == -1)
			error_syscall_child(client->fd_data, 0);
		dup_close(client, fd, origin_fd);
		client->pasv_actv = 0;
	} else
		print_error_data_transfer(client);
	return (0);
}