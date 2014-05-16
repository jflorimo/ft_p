/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jflorimo <jflorimo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/05/13 14:57:17 by jflorimo          #+#    #+#             */
/*   Updated: 2014/05/13 14:57:18 by jflorimo         ###   ########.fr       */
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

void					usage(char *str)
{
	ft_putstr("Usage: ");
	ft_putstr(str);
	ft_putstr(" <port>\n");
	exit(-1);
}

int						create_client(char *addr, int port)
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
	sin.sin_addr.s_addr = inet_addr(addr);
	if (connect(sock, (const struct sockaddr *)&sin, sizeof(sin)) == -1)
	{
		ft_putstr("Connect error\n");
		exit(-42);
	}
	return (sock);
}

int						main(int argc, char *argv[])
{
	int					port;
	int					sock;
	int					r;
	int					r2;
	char				buff[1024];

	if (argc != 3)
	usage(argv[0]);
	port = ft_atoi(argv[2]);
	sock = create_client(argv[1], port);
	ft_putstr("JC% ");
	while ((r = read(0, buff, 1023)) > 0)
	{
		buff[r - 1] = '\0';
		write(sock, buff, r);
		if (ft_strncmp("ls", buff, 2) == 0)
		{
			while ((r2 = read(sock, buff, 1)) > 0 && buff[0] != '\0')
			{
				buff[r2] = '\0';
				write(1, buff, r2);
			}
		}
		ft_putstr("JC% ");
	}
	close(sock);
	return (0);
}
