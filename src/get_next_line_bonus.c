/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edesprez <edesprez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/19 16:16:43 by edesprez          #+#    #+#             */
/*   Updated: 2025/01/24 11:41:18 by edesprez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>

char	*ft_strchr(const char *str, int c)
{
	int				i;
	unsigned char	d;

	d = (unsigned char)c;
	i = 0;
	while (str[i])
	{
		if (str[i] == d)
			return ((char *)(&str[i]));
		i++;
	}
	if (!d)
		return ((char *)(&str[i]));
	return (0);
}

char	*fill_buffer(int fd, char *stash, char *buffer)
{
	int		val_read;
	char	*tmp;

	val_read = 1;
	while (val_read > 0)
	{
		val_read = read(fd, buffer, BUFFER_SIZE);
		if (val_read == -1)
		{
			free(stash);
			return (0);
		}
		else if (val_read == 0)
			break ;
		buffer[val_read] = '\0';
		if (!stash)
			stash = ft_strdup("");
		tmp = stash;
		stash = ft_strjoin(tmp, buffer);
		free(tmp);
		tmp = NULL;
		if (ft_strchr(buffer, '\n'))
			break ;
	}
	return (stash);
}

char	*fill_line(char *line_buffer)
{
	int		i;
	char	*ret_line;

	i = 0;
	while (line_buffer[i] != '\n' && line_buffer[i] != '\0')
		i++;
	if (line_buffer[i] == 0 || line_buffer[1] == 0)
		return (NULL);
	ret_line = ft_substr(line_buffer, i + 1, ft_strlen(line_buffer) - i);
	if (*ret_line == 0)
	{
		free(ret_line);
		ret_line = NULL;
	}
	line_buffer[i + 1] = '\0';
	return (ret_line);
}

char	*get_next_line(int fd)
{
	char		*buffer;
	static char	*stash[1024];
	char		*line;

	buffer = (char *)malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (!buffer)
		return (0);
	if (fd < 0 || fd > 1024 || BUFFER_SIZE < 0 || read(fd, 0, 0) < 0)
	{
		if (stash[fd])
			free(stash[fd]);
		free(buffer);
		stash[fd] = NULL;
		line = NULL;
		return (0);
	}
	line = fill_buffer(fd, stash[fd], buffer);
	free(buffer);
	buffer = NULL;
	if (!line)
		return (NULL);
	stash[fd] = fill_line(line);
	return (line);
}

/*int	main(int argc, char **argv)
{
	int	filedes;
	char *str;

	(void)argc;
	str = (char *)1;
	filedes = open(argv[1], O_RDONLY);
	while (str)
	{
		str = get_next_line(filedes);
		printf("[%s]", str);
		if (str)
			free(str);
	}
	if (str)
		free(str);
	return (0);
}*/
/*int	main(void)
{
	char *str;
	int	filedes;
	filedes = open("./test.txt", O_RDONLY);
	str = get_next_line(filedes);
	printf("[%s]", str);
	filedes = open("./test2.txt", O_RDONLY);
	str = get_next_line(filedes);
	printf("[%s]", str);
	filedes = open("./test.txt", O_RDONLY);
	str = get_next_line(filedes);
	printf("[%s]", str);
}*/
