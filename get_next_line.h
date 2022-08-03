/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   get_next_line.h                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: rgrootho <rgrootho@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/07/31 20:57:23 by rgrootho      #+#    #+#                 */
/*   Updated: 2022/08/03 13:11:32 by rgrootho      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include <unistd.h>
# include <stdlib.h>

char	*get_next_line(int fd);
char	*read_file(char *save_bytes, char *rs, int fd);
char	*check_and_move(char *save_bytes, char *rs, char *line_to_check);
char	*manage_rs(char *rs, char *line_to_check, int index_nl, int index_term);
char	*ft_memmove(char *src, char *dest, int len);
char	*ft_strjoin(char *last_part, char *first_part, int len_last_part);
int		ft_strlen(char *string, char character);

#endif