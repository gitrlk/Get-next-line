#include "get_next_line.h"

int		stock_checker(t_list **stock_data, char **line, char **str)
{
	int			i;

	i = 0;
	if (*stock_data && ft_strlen((*stock_data)->content))
	{
		*str = ft_strdup((*stock_data)->content);
		free((*stock_data)->content);
		if (ft_strchr(*str, '\n'))
		{
			while ((*str)[i] != '\n')
				i++;
			*line = ft_strsub(*str, 0, i);
			(*stock_data)->content = ft_strdup(ft_strchr(*str, '\n') + 1);
			free(*str);
			return (1);
		}
	}
	if (!(*str))
		*str = ft_strnew(0);
	return (0);
}

void	found_newline(t_list **stock_data, char **line, char *buf, char **str)
{
	int i;

	i = 0;
	(*stock_data)->content = ft_strdup(ft_strchr(buf, '\n') + 1);
	while (buf[i] != '\n')
		i++;
	*line = ft_strjoin(*str, ft_strsub(buf, 0, i));
	free(*str);
}

int		str_not_empty(t_list **stock_data, char **str, char **line)
{
	int i;

	i = 0;
	if (*str && ft_strlen(*str))
	{
		*line = ft_strdup(*str);
		free(str);
		free((*stock_data)->content);
		free(stock_data);
		stock_data = NULL;
		return (1);
	}
	else
		return (0);
}

int		get_next_line(const int fd, char **line)
{
	int					i;
	char				*str;
	char				buf[BUF_SIZE + 1];
	static t_list		*stock_data = NULL;

	str = NULL;
	if (stock_checker(&stock_data, line, &str))
		return (1);
	while ((i = read(fd, buf, BUF_SIZE)) > 0)
	{
		if (!stock_data)
			stock_data = ft_lstnew((void *)buf, ft_strlen(buf));
		buf[i] = '\0';
		if (ft_strchr(buf, '\n'))
		{
			found_newline(&stock_data, line, buf, &str);
			return (1);
		}
		else if (i < BUF_SIZE)
		{
			*line = ft_strjoin(str, buf);
			ft_strdel(&str);
			stock_data = NULL;
		}
		if (i < BUF_SIZE || ft_strchr(buf, '\n'))
			return (1);
		str = ft_strjoin(str, buf);
	}
	if (i < 0)
		return (-1);
	return (str_not_empty(&stock_data, &str, line));
}
