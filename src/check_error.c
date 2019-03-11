/*
** EPITECH PROJECT, 2018
** myftp
** File description:
** gestion erreur
*/

#include "myftp.h"

int check_path(char *path)
{
	struct stat statbuf;

	stat(path, &statbuf);
	if (!S_ISDIR(statbuf.st_mode))
		return (84);
	return (0);
}

int check_port(char *port)
{
	int i = 0;

	while (port[i] != '\0') {
		if (port[i] < '0' || port[i] > '9')
			return (84);
		i += 1;
	}
	return (0);
}

int check_error(int argc, char **argv)
{
	if (argc != 3 || check_port(argv[1]) == 84
	|| check_path(argv[2]) == 84 || atoi(argv[1]) > 65535) {
		display_usage();
		return (84);
	}
	return (0);
}