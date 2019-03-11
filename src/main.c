/*
** EPITECH PROJECT, 2018
** myftp
** File description:
** main
*/

#include "myftp.h"

int main(int argc, char **argv)
{
	int fd;

	if (argc == 2 && strcmp(argv[1], "-help") == 0) {
		display_usage();
		return (0);
	} if (check_error(argc, argv) == 84)
		return (84);
	fd = create_socket(atoi(argv[1]));
	if (fd == -1 || communicate_server(fd, atoi(argv[1]), argv[2]) == -1)
		return (84);
	if (close(fd) == -1)
		return (84);
	return (0);
}