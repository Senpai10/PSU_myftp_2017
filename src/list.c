/*
** EPITECH PROJECT, 2018
** myftp
** File description:
** list files in the current directoy
*/

#include "myftp.h"

void print_code(t_ftp *client)
{
	if (dprintf(client->fd,
	"150 File status okay; about to open data connection.\n") == -1)
		error_syscall_child(client->fd_data, 1);
	if (dprintf(client->fd, "226 Closing data connection.\n") == -1)
		error_syscall_child(client->fd_data, 1);
}

void execution_ls(t_ftp *client, int fd)
{
	struct stat statbuf;
	char *ls[] = {"ls", "-l", ".", NULL};
	char *ls2[] = {"ls", "-l", client->arg, NULL};

	if (client->arg != NULL) {
		stat(client->arg, &statbuf);
		if (!S_ISDIR(statbuf.st_mode))
			execvp("ls", ls);
		else
			execvp("ls", ls2);
	}
	else
		execvp("ls", ls);
	if (close(fd) == -1)
		error_syscall_child(client->fd_data, 0);
	if (close(client->fd_data) == -1)
		error_syscall_child(client->fd, 0);
}

int list(t_ftp *client)
{
	struct sockaddr_in addr;
	int fd;
	pid_t pid;

	if (client->pasv_actv == 1) {
		fd = accept_client(client->fd_data, &addr);
		if (fd == -1)
			error_syscall_child(client->fd_data, 0);
		pid = fork();
		if (pid == 0) {
			dup2(fd, 1);
			execution_ls(client, fd);
			exit(0);
		}
		print_code_pasv(client);
		client->pasv_actv = 0;
	} else
		print_error_data_transfer(client);
	return (0);
}