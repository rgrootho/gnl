/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   get_next_line_bonus.c                              :+:    :+:            */
/*                                                     +:+                    */
/*   By: rgrootho <rgrootho@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/07/31 20:56:07 by rgrootho      #+#    #+#                 */
/*   Updated: 2022/07/31 20:56:09 by rgrootho      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"
#include <stdio.h>

char	*manage_rs(char *rs, char *line_to_check, int i_nl, int i_term)
{
	int	len_string_2_appent;

	if (i_nl < i_term)
		len_string_2_appent = i_nl + 1;
	else
		len_string_2_appent = i_term;
	if (!rs)
	{
		rs = (char *) malloc ((len_string_2_appent + 1) * sizeof(char));
		if (!rs)
			return (NULL);
		rs[len_string_2_appent] = '\0';
		rs = ft_memmove(line_to_check, rs, len_string_2_appent);
	}
	else
		rs = ft_strjoin(line_to_check, rs, len_string_2_appent);
	return (rs);
}

char	*check_and_move(char *save_bytes, char *rs, char *line_to_check)
{
	int	i_term;
	int	i_nl;

	i_term = ft_strlen(line_to_check, '\0');
	i_nl = ft_strlen(line_to_check, '\n');
	rs = manage_rs(rs, line_to_check, i_nl, i_term);
	if (!rs)
		return (NULL);
	if (i_term > i_nl && i_term - i_nl - 1 != 0)
		ft_memmove(&line_to_check[i_nl + 1], save_bytes, i_term - i_nl - 1);
	if (i_term > i_nl && i_term - i_nl - 1 == 0)
		save_bytes[0] = '\0';
	if (i_term == i_nl)
		save_bytes[0] = '\0';
	return (rs);
}

char	*read_file(char *save_bytes, char *rs, int fd)
{
	size_t	bytes_read;
	char	read_buffer[BUFFER_SIZE + 1];

	bytes_read = 1;
	while (bytes_read > 0)
	{
		bytes_read = read(fd, read_buffer, BUFFER_SIZE);
		read_buffer[bytes_read] = '\0';
		if (bytes_read < 0)
		{
			if (rs != NULL)
				free(rs);
			return (NULL);
		}
		if (bytes_read == 0)
			break ;
		rs = check_and_move(save_bytes, rs, read_buffer);
		if (rs == NULL)
			return (NULL);
		if (ft_strlen(rs, '\0') > ft_strlen(rs, '\n'))
			bytes_read = 0;
	}
	return (rs);
}

char	*get_next_line(int fd)
{
	static char	save_bytes[2000][BUFFER_SIZE];
	char		*rs;

	if (read(fd, save_bytes[fd], 0) == -1)
		return (NULL);
	rs = NULL;
	if (save_bytes[fd] && save_bytes[fd][0])
	{
		rs = check_and_move(save_bytes[fd], rs, save_bytes[fd]);
		if (ft_strlen(rs, '\0') > ft_strlen(rs, '\n'))
			return (rs);
	}
	rs = read_file(save_bytes[fd], rs, fd);
	return (rs);
}
