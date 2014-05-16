/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jflorimo <jflorimo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/04/22 16:41:36 by jflorimo          #+#    #+#             */
/*   Updated: 2014/04/22 16:41:37 by jflorimo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <sys/socket.h>
#include <netdb.h>
#include <unistd.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <libft.h>
#include <stdio.h>
#include "script.h"

void					usage(char *str)
{
	printf("Usage: %s <port>\n", str);
	exit(-1);
}

int						create_server(int port)
{
	int					sock;
	struct protoent		*proto;
	struct sockaddr_in	sin;

	proto = getprotobyname("tcp");
	if (proto == 0)
		return (-1);
	sock = socket(PF_INET, SOCK_STREAM, proto->p_proto);
	sin.sin_family = AF_INET;
	sin.sin_port = htons(port);
	sin.sin_addr.s_addr = htonl(INADDR_ANY);
	if (bind(sock, (const struct sockaddr *)&sin, sizeof(sin)) == -1)
	{
		printf("Bind error\n");
		exit(-42);
	}
	listen(sock, 42);
	return (sock);
}

int						main(int argc, char *argv[])
{
	int                    port;
	int                    sock;
	int                    cs;
	unsigned int        cslen;
	struct sockaddr_in    csin;
	int                 r;
	char                buff[1024];
	pid_t               pid;
	int					count;
	char				*homedir;

	if (argc != 2)
	    usage(argv[0]);
	port = ft_atoi(argv[1]);
	sock = create_server(port);
	count = 0;
	if (getcwd(buff, sizeof(buff)) != NULL)
	{
		homedir = ft_strdup(buff);
	}
	ft_putstr("HOME: ");
	ft_putendl(homedir);
	while ((cs = accept(sock, (struct sockaddr *)&csin, &cslen)) > 0)
	{
		if ((pid = fork()) == -1)
		{
			close(cs);
			continue ;
		}
		else if (pid > 0)
		{
			close(cs);
			count++;
			continue ;
		}
		else if (pid == 0)
		{
			count++;
		}
		while ((r = read(cs, buff, 1023)) > 0)
		{
			buff[r - 1] = '\0';
			printf("received %d bytes: [%s] from client N%d\n", r, buff, count);
			if (ft_strncmp("ls", buff, 2) == 0)
				ft_ls(cs);
			if (ft_strncmp("pwd", buff, 3) == 0)
				get_pwd(cs, homedir);
			if (ft_strncmp("cd", buff, 2) == 0)
				set_cd(&buff[3], homedir);
		}
	}
	return (0);
}
