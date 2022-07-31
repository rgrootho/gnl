/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   get_next_line_utils_bonus.c                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: rgrootho <rgrootho@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/07/31 20:24:57 by rgrootho      #+#    #+#                 */
/*   Updated: 2022/07/31 20:25:16 by rgrootho      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

int	ft_strlen(char *string, char character)
{
	int	i;

	i = 0;
	while (string[i] != character && string[i] != '\0')
		i++;
	return (i);
}

char	*ft_memmove(char *src, char *dest, int len)
{
	size_t	i;

	i = 0;
	while (len > 0 && src[i])
	{
		dest[i] = src[i];
		len--;
		i++;
	}
	dest[i] = '\0';
	return (dest);
}

char	*ft_strjoin(char *last_part, char *first_part, int len_last_part)
{
	char	*new_rs;
	int		len_first_part;
	int		len_rs;

	len_first_part = ft_strlen(first_part, '\0');
	len_rs = len_first_part + len_last_part;
	new_rs = (char *)malloc((len_rs + 1) * sizeof(char));
	if (new_rs)
	{
		new_rs[len_rs] = '\0';
		ft_memmove(first_part, new_rs, len_first_part);
		ft_memmove(last_part, new_rs + len_first_part, len_last_part);
	}
	free(first_part);
	return (new_rs);
}
