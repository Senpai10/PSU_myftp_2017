/*
** EPITECH PROJECT, 2018
** myftp
** File description:
** file h
*/

#pragma once

#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <sys/stat.h>
#include <netdb.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <stdio.h>
#include <limits.h>
#include <dirent.h>
#include <signal.h>
#include <fcntl.h>
#include <errno.h>

typedef struct	s_ftp
{
	char *commands;
	char *arg;
	char *home;
	char *user;
	char *ip;
	int port;
	int step;
	int pasv_actv;
	int fd;
	int fd_data;
}		t_ftp;

typedef struct  s_commands
{
	char *name;
	int (*fct_commands)(t_ftp *client);
}               t_commands;

extern const t_commands commands_tab[];

int check_error(int argc, char **argv);
void display_usage(void);
int error_syscall(int, int);
void error_syscall_child(int fd, int i);
int create_socket(int port);
int communicate_server(int fd, int port, char *path);
int accept_client(int fd, struct sockaddr_in *);
int do_commands(t_ftp *client);
char *stock_commands(int client_fd);
int pwd(t_ftp *client);
int cwd(t_ftp *client);
int cdup(t_ftp *client);
int delete(t_ftp *client);
int help(t_ftp *client);
int quit(t_ftp *client);
int list(t_ftp *client);
int connect_user(t_ftp *client);
int connect_pass(t_ftp *client);
void authentication(t_ftp *client);
int pasv(t_ftp *client);
int noop(t_ftp *client);
void print_error_data_transfer(t_ftp *client);
int download(t_ftp *client);
char *my_strcat(char *dest, char *src);
int upload(t_ftp *client);
void print_code_pasv(t_ftp *client);
void dup_close(t_ftp *client, int fd, int origin_fd);
char *read_file(t_ftp *client, int fd);