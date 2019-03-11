/*
** EPITECH PROJECT, 2018
** myftp
** File description:
** my strcat
*/

#include "myftp.h"

char *my_strcat(char *dest, char *src)
{
	int   y = 0;
	int   x = 0;
	char  *str;

	str = malloc(sizeof(char) * (strlen(dest) + strlen(src) + 1));
	while (dest[y] != '\0') {
		str[y] = dest[y];
		y = y + 1;
	} while (src[x] != '\0') {
		str[y] = src[x];
		y = y + 1;
		x = x + 1;
	}
	str[y] = '\0';
	return (str);
}

int check_crlf(char *commands)
{
	int i = 0;

	while (commands[i] != '\0') {
		if (commands[i] == '\r' && commands[i + 1] == '\n')
			return (1);
		i++;
	}
	return (0);
}

char *stock_commands(int client_fd)
{
	char *buffer = malloc(sizeof(char) + 1);
	char *save = "\0";
	int readed = 0;

	if (buffer == NULL)
		return (NULL);
	while (check_crlf(save) == 0) {
		readed = read(client_fd, buffer, 1);
		if (readed == -1)
			return (NULL);
		buffer[readed] = '\0';
		save = my_strcat(save, buffer);
	}
	free(buffer);
	return (save);
}