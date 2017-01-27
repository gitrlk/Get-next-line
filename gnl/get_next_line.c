/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jecarol <jecarol@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/27 16:06:34 by jecarol           #+#    #+#             */
/*   Updated: 2017/01/27 21:56:03 by jecarol          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

/*int		get_next_line(const int fd, char **line)
{
	
}*/

static int		sizeton(char *str)
{
	static int i = 0;
	
	while (str[i])
	{
		if (str[i] == '\n')
			return (i);
		if (str[i] == '\0')
			return (i);
		i++;
	}
	return (0);
}

int		main(int argc, char **argv)
{
	int fd;
	int i;
	int j;
	char *tmp1;
	char buf[BUF_SIZE + 1];

	i = 0;
	j = 0;
	fd = open(argv[1], O_RDONLY);
	read(fd, buf, BUF_SIZE);
	tmp1 = (char*)malloc(sizeof(char) * (sizeton(buf) + 1));
	while (*buf)
	{
		tmp1[i] = buf[j];
		i++;
		j++;
		if (buf[j] == '\n')
		{
			tmp1[i] = '\0';
			ft_putstr(tmp1);
			ft_strdel(&tmp1);
			tmp1 = (char*)malloc(sizeof(char) * (sizeton(buf) + 1));
			i = 0;
		}
		if (buf[j] == '\0')
		{
			tmp1[i] = '\0';
			ft_putstr(tmp1);
			return (0);
		}
	}
	return(0);
}
