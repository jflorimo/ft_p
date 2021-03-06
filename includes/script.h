/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   script.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jflorimo <jflorimo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/04/22 17:38:11 by jflorimo          #+#    #+#             */
/*   Updated: 2014/04/22 17:38:13 by jflorimo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SCRIPT_H
# define SCRIPT_H

void		ft_ls(int cs);
void		empty(int fd);
void		get_pwd(int fd, int len);
void		set_cd(char *s, char *homedir, int fd);
char		*get_homedir();
void		get_file_serv(char *file, int fdf);
void		put_file_serv(char *file, int fd);

#endif
