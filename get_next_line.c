/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hogkim <hogkim@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/05 23:02:19 by hogkim            #+#    #+#             */
/*   Updated: 2022/01/24 17:23:43hogkim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*ft_restart(char *temp)
{
	size_t	i;
	size_t	len;
	char	*str;

	len = ft_strlen(temp);
	i = 0;
	while (temp[i] && (temp[i] != '\n'))
		i++;
	if (!temp[i] || (len - i) == 1)
	{
		free(temp);
		return (NULL);
	}
	str = (char *)malloc(sizeof(char) * (len - i));
	if (!str)
		return (NULL);
	ft_strlcpy(str, &temp[i + 1], len - i);
	free(temp);
	return (str);
}

char	*ft_cut_temp(char *temp)
{
	size_t	i;
	char	*line;

	if (!temp[0])
		return (NULL);
	i = 0;
	while ((temp[i] != '\n') && temp[i])
		i++;
	if (temp[i] == '\n')
	{
		line = (char *)malloc(sizeof(char) * (i + 2));
		if (!line)
			return (NULL);
		ft_strlcpy(line, temp, i + 2);
	}
	else
	{
		line = (char *)malloc(sizeof(char) * (i + 1));
		if (!line)
			return (NULL);
		ft_strlcpy(line, temp, i + 1);
	}
	return (line);
}

char	*ft_read_till_line(int fd, char *temp)
{
	char	*buffer;
	ssize_t	n;

	buffer = (char *)malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (!buffer)
		return (NULL);
	n = 1;
	while (n && ft_no_newline(temp))
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
		return (NULL);
	temp = ft_read_till_line(fd, temp);
	if (!temp)
		return (NULL);
	line = ft_cut_temp(temp);
	temp = ft_restart(temp);
	return (line);
}
