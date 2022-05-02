/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: romee <romee@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/18 17:44:41 by romee             #+#    #+#             */
/*   Updated: 2022/05/02 18:06:15 by romee            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>

#ifndef BUFFER_SIZE
	BUFFER_SIZE=1;
#endif

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	size_t	i;

	i = 0;
	if (dst == NULL && src == NULL)
	{
		return (NULL);
	}
	if (dst > src)
	{
		while (len > 0)
		{
			*(char *)(dst + (len - 1)) = *(char *)(src + (len - 1));
			len--;
		}
	}
	else
	{
		while (i < len)
		{
			*(char *)(dst + i) = *(char *)(src + i);
			i++;
		}
	}
	return (dst);
}

size_t	ft_strlcpy(char *dst, const char *src, size_t dstsize)
{
	size_t	i;

	i = 0;
	if (!src || !dst)
		return (0);
	if (dstsize > 0)
	{
		while (src[i] != '\0' && i < (dstsize - 1))
		{
			dst[i] = src[i];
			i++;
		}
		dst[i] = '\0';
	}
	while (src[i] != '\0')
		i++;
	return (i);
}

size_t	ft_strlen(const char *str, char character)
{
	size_t	index;
	
	index = 0;
	if(!str)
		return(0);
	while (str[index] && str[index] != character)
		index++;
	return (index);
}

char	*ft_strjoin(char const *s1, char const *s2, char character)
{
	char	*concat;
	size_t	lens1;
	size_t	lens2;
	size_t	totlen;


	if (!s1 || !s2)
		return (0);
	lens1 = ft_strlen(s1, '\0');
	lens2 = ft_strlen(s2, character);
	totlen = lens1 + lens2;
	if(character == '\n')
	{
		totlen++;
		lens2++;
	}
	concat = (char *)malloc((totlen + 1) * sizeof(char));
	if (concat == 0)
		return (0);
	ft_strlcpy(concat, s1, (lens1 + 1));
	ft_strlcpy(concat + lens1, s2, (lens2 + 1));
	// printf("%s\n",concat);
	return (concat);
}
///////////////////////////////////////////////////////////////////////

char	*save_buffer(char *save_buff, size_t index_save_buff)
{
	size_t len_save_buff;

	len_save_buff = ft_strlen(&save_buff[index_save_buff - 1], '\0');
	save_buff = ft_memmove(save_buff, &save_buff[index_save_buff], len_save_buff);
	save_buff[len_save_buff] = '\0';
	return(save_buff);
}

char	*check_for_nl(char *return_string, char *buffer)
{
	size_t len_retstr;
	size_t end_string;

	end_string = ft_strlen(buffer, '\0');
	len_retstr = ft_strlen(buffer, '\n');
	if (len_retstr < end_string)
		len_retstr++;
	if (return_string == NULL)
	{
		return_string = (char*) malloc ((len_retstr + 1) * sizeof(char));
		if (!return_string)
			return(NULL);
		return_string[len_retstr] = '\0';
		return_string = ft_memmove(return_string, buffer, len_retstr);
		if(ft_strlen(buffer, '\n') < end_string)
			buffer = save_buffer(buffer, len_retstr);
	}
	else if (ft_strlen(buffer, '\n') < end_string)
	{
		return_string = ft_strjoin(return_string, buffer, '\n');
		buffer = save_buffer(buffer, len_retstr);
	}
	else
		return_string = ft_strjoin(return_string, buffer, '\0');
	return(return_string);
}

char *read_and_check(char *return_string, char *buffer, int fd)
{
	while(ft_strlen(return_string, '\n') == ft_strlen(return_string, '\0'))
	{
		size_t bytes_read;

		bytes_read = read(fd, buffer, BUFFER_SIZE);
		if (bytes_read == 0 && return_string[0] != '\0')
		{
			buffer[0] = '\0';
			return(return_string);
		}
		if(bytes_read <= 0 && return_string[0] == '\0')
		{
			free(return_string);
			return(NULL);
		}
		buffer[bytes_read] = '\0';
		return_string = check_for_nl(return_string, buffer);
		if (return_string == NULL)
			return(NULL);
		if (ft_strlen(return_string, '\n') < ft_strlen(return_string, '\0'))
			break;
	}
	return(return_string);
}

char *get_next_line(int fd)
{
	static char	*save_buff;
	char *return_string;

	return_string = NULL;
	if(!save_buff)
	{
		save_buff = (char *) malloc ((BUFFER_SIZE + 1) * sizeof(char));
		if (!save_buff)
			return(NULL);
		save_buff[BUFFER_SIZE] = '\0';
	}
	else
	{
		return_string = check_for_nl(return_string, save_buff);
		if (return_string == NULL)
			return(NULL);
		if(ft_strlen(return_string, '\n') < ft_strlen(return_string, '\0'))
			return(return_string);
	}
		return_string = read_and_check(return_string, save_buff, fd);
		if (return_string == NULL)
			return(NULL);
	return(return_string);
}

int main(void)
{
	int fd;
	char gid[] = "even test";
	char *string;
	int i = 0;

	string = gid;
	fd = open ("lees.txt", O_RDONLY);
	while(string != NULL)
	{
		string = get_next_line(fd);
		printf("dit is string main line %d: %s", i + 1, string);
		free(string);
		i++;
	}
	free(string);
	close(fd);
	//system("leaks a.out");

	return (0);
}
//gcc -Wall -Wextra -Werror -D BUFFER_SIZE=42 <files>.c

// char *get_next_line(int fd)
// {
// 	static *char 
// 	size_t		bytes_read;
// 	char		*string_from_file;

// 	#ifndef BUFFER_SIZE
// 		BUFFER_SIZE=1;
// 	#endif
// 	string_from_file = (char*) malloc (BUFFER_SIZE * sizeof(char));
// 	bytes_read = read(fd, string_from_file, BUFFER_SIZE);
// 	if (bytes_read <= 0)
// 		return (NULL);
// 	printf("dit is string_from_file: %s\n", string_from_file);
// 	printf("dit is bytes_read: %zu\n", bytes_read);
// 	return(string_from_file);
// }