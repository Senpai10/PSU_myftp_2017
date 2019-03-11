/*
** EPITECH PROJECT, 2018
** myftp
** File description:
** do commands for clients
*/

#include "myftp.h"

void remove_r_n(t_ftp *client)
{
	int i = 0;

	if (client->commands != NULL) {
		while (client->commands[i] != '\0') {
			if (client->commands[i] == '\r')
				client->commands[i] = '\0';
			i++;
		}
	}
	i = 0;
	if (client->arg != NULL) {
		while (client->arg[i] != '\0') {
			if (client->arg[i] == '\r')
				client->arg[i] = '\0';
			i++;
		}
	}
}

int check_commands(t_ftp *client)
{
	int i = 0;

	if (client->step == 2) {
		while (commands_tab[i].name != NULL) {
			if (strcmp(client->commands,
			commands_tab[i].name) == 0)
				return (commands_tab[i].fct_commands(client));
			i++;
		} if (commands_tab[i].name == NULL
		&& strcmp(client->commands, "USER") != 0
		&& strcmp(client->commands, "PASS") != 0) {
			if (write(client->fd, "500 Unknown command.\n",
			21) == -1)
				error_syscall_child(client->fd, 1);
		}
	}
	return (0);
}

int do_commands(t_ftp *client)
{
	char *line = stock_commands(client->fd);

	client->commands = strtok(line, " ");
	client->arg = strtok(NULL, " ");
	remove_r_n(client);
	if (client->commands == NULL)
		error_syscall_child(client->fd, 3);
	authentication(client);
	return (check_commands(client));
}