/*
** EPITECH PROJECT, 2018
** myftp
** File description:
** creer serveur
*/

#include "myftp.h"

int handle_clients(int fd, t_ftp *client, int port, char *path)
{
	char resolved_path[PATH_MAX + 1];
	pid_t pid = fork();

	if (pid == -1)
		return (error_syscall(fd, 4));
	else if (pid == 0) {
		client->step = 0;
		client->pasv_actv = 0;
		client->port = port;
		client->home = realpath(path, resolved_path);
		if (client->home == NULL || chdir(client->home) == -1)
			error_syscall_child(client->fd, 4);
		while (do_commands(client) == 0);
		exit(0);
	}
	return (0);
}

int accept_client(int fd, struct sockaddr_in *addr)
{
	socklen_t size = sizeof(*addr);

	return (accept(fd, (struct sockaddr *)addr, &size));
}

int communicate_server(int fd, int port, char *path)
{
	struct sockaddr_in addr_client;
	t_ftp *client = malloc(sizeof(t_ftp));

	while (1) {
		client->fd = accept_client(fd, &addr_client);
		if (client->fd == -1)
			return (error_syscall(fd, 2));
		if (write(client->fd, "220 Service ready for new user.\n",
		32) == -1)
			return (error_syscall(client->fd, 3));
		client->ip = inet_ntoa(addr_client.sin_addr);
		if (handle_clients(fd, client, port, path) == -1)
			return (-1);
	}
	free(client);
	return (0);
}

int create_socket(int port)
{
	struct protoent *proto = getprotobyname("TCP");
	int fd;
	struct sockaddr_in serv;

	if (!proto)
		return (-1);
	fd = socket(AF_INET, SOCK_STREAM, proto->p_proto);
	if (fd == - 1)
		return (-1);
	serv.sin_family = AF_INET;
	serv.sin_port = htons(port);
	serv.sin_addr.s_addr = INADDR_ANY;
	if (bind(fd, (const struct sockaddr *)&serv, sizeof(serv)) == -1
	|| listen(fd, 5) == -1)
		return (error_syscall(fd, 1));
	return (fd);
}
