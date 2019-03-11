/*
** EPITECH PROJECT, 2018
** myftp
** File description:
** le flag help
*/

#include "myftp.h"

void error_syscall_child(int fd, int i)
{
	if (close(fd) == -1) {
		fprintf(stderr, "Error : Cannot close the fd client\n");
		exit(84);
	} switch (i) {
		case 1:
			fprintf(stderr, "Error : Cannot write\n");
			break;
		case 2:
			fprintf(stderr, "Error : Cannot find PWD\n");
			break;
		case 3:
			fprintf(stderr, "Error : Cannot malloc or read\n");
			break;
		case 4:
			fprintf(stderr,
			"Error : Cannot change, open or retrieve directory\n");
			break;
	}
	exit(84);
}

int error_syscall(int fd, int i)
{
	if (close(fd) == -1) {
		fprintf(stderr, "Error : Cannot close the fd\n");
		return (84);
	} switch (i) {
		case 1:
			fprintf(stderr, "Error : Cannot bind or listen\n");
			break;
		case 2:
			fprintf(stderr, "Error : Cannot accept\n");
			break;
		case 3:
			fprintf(stderr, "Error : Cannot write\n");
			break;
		case 4:
			fprintf(stderr, "Error : Cannot fork\n");
			break;
	}
	return (-1);
}

void display_usage(void)
{
	printf("USAGE: ./server port path\n");
	printf("\tport is the port number on which the server socket ");
	printf("listens\n");
	printf("\tpath is the path to the home directory for the ");
	printf("Anonymous user\n");
}

int noop(t_ftp *client)
{
	(void)client;
	if (write(client->fd, "200 Command okay.\n", 18) == -1)
		error_syscall_child(client->fd, 1);
	return (0);
}