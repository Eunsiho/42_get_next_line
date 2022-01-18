/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hogkim <hogkim@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/05 23:02:19 by hogkim            #+#    #+#             */
/*   Updated: 2022/01/18 21:54:37 by hogkim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*ft_restart(char *temp)
{
	size_t	i;
	size_t	temp_len;

	temp_len = ft_strlen(temp);
	if (temp[temp_len - 1] == '\n')
	{
		free(temp);
		return (NULL);
	}
	i = 0;
	while (temp[i])
	{
		if (temp[i] = '\n')
			break ;
		i++;
	}
	temp = temp[i + 1];
	return (temp);
}

char	*ft_cut_temp(char *temp, char *line)
{
	size_t	i;

	i = 0;
	while (temp[i])
	{
		if (temp[i] = '\n')
			break ;
		i++;
	}
	line = (char *)malloc(sizeof(char) * (i + 2));
	ft_strlcpy(line, temp, i + 2);
	return (line);
}

char	*ft_read_till_line(int fd, char *temp)
{
	char	*buffer;
	ssize_t	n;

	buffer = (char *)malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (!buffer)
		return (NULL);
	while ((n >= 1) && ft_no_newline(buffer))
	{
		n = read(fd, buffer, BUFFER_SIZE);
		if (n == -1)
		{
			free(buffer);
			return (NULL);
		}
		buffer[n] = 0;
		temp = ft_strjoin(temp, buffer);
	}
	free(buffer);
	return (temp);
}

char	*get_next_line(int fd)
{
	static char	*temp;
	char		*line;

	if (fd < 0 || fd > OPEN_MAX || BUFFER_SIZE <= 0)
		return (0);
	ft_read_till_line(fd, temp);
	if (ft_no_newline(temp))
		return (temp);
	ft_cut_temp(temp, line);
	ft_restart(temp);
	return (line);
}
