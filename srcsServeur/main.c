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
#include <sys/types.h>
#include <dirent.h>


void    usage(char *str)
{
    printf("Usage: %s <port>\n", str);
    exit(-1);
}

int        create_server(int port)
{
    int                    sock;
    struct protoent        *proto;
    struct sockaddr_in    sin;

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

void		ls_command(int fd)
{
    DIR *mydir;
    struct dirent *myfile;
    mydir = opendir(".");
    while((myfile = readdir(mydir)) != NULL)
    {  
        ft_putendl_fd(myfile->d_name, fd);

        ft_putendl(myfile->d_name);
    }
    closedir(mydir);

}

int        main(int argc, char *argv[])
{
    int                    port;
    int                    sock;
    int                    cs;
    unsigned int        cslen;
    struct sockaddr_in    csin;
    int                    r;
    char                buff[1024];
    pid_t               pid;
    int					count;

    if (argc != 2)
        usage(argv[0]);
    port = ft_atoi(argv[1]);
    sock = create_server(port);
    count = 0;
    
	while ((cs = accept(sock, (struct sockaddr *)&csin, &cslen)) > 0)
	{
		printf("##father ##count:%d\n",count);
		count++;
		if ((pid = fork()) == -1)
		{
			close(cs);
			continue ;
		}
		if (pid > 0)
		{
			send(cs, "Welcome to JC ~/\n", 18, 0);
		}
		else if (pid == 0)
		{
			
			printf("id:%d\n",count);
			while ((r = read(cs, buff, 1023)) > 0)
			{
				buff[r - 1] = '\0';
				printf("id:%d received %d bytes: [%s]\n", count, r, buff);
                if (!ft_strcmp(buff, "ls"))
                {
                	printf("ls received from %d\n", cs);
					ls_command(cs);					
				}
			}		
			close(cs);
			printf("count:%d\n", count);
		}

	}
	close(cs);
	close(sock);
    return (0);
}
