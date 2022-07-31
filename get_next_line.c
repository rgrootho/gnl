#include "get_next_line.h"
#include <stdio.h>

char *manage_rs(char *rs, char *line_to_check, int index_nl, int index_term)
{
    int len_string_2_appent;

    if (index_nl < index_term)
        len_string_2_appent = index_nl + 1;
    else
        len_string_2_appent = index_term;
    if (!rs)
    {
        rs = (char *) malloc ((len_string_2_appent + 1) * sizeof(char));
        if (!rs)
            return(NULL);
        rs[len_string_2_appent] = '\0';
        rs = ft_memmove(line_to_check, rs, len_string_2_appent);
    }
    else
        rs = ft_strjoin(line_to_check, rs, len_string_2_appent);
    return(rs);
}

char *check_and_move(char *save_bytes, char *rs, char *line_to_check)
{
    int index_term;
    int index_nl;

    index_term = ft_strlen(line_to_check, '\0');
    index_nl = ft_strlen(line_to_check, '\n');
    rs = manage_rs(rs, line_to_check, index_nl, index_term);
    if (!rs)
        return (NULL);
    if (index_term > index_nl && index_term - index_nl - 1 != 0)
        ft_memmove(&line_to_check[index_nl + 1], save_bytes, index_term - index_nl - 1);
    if (index_term > index_nl && index_term - index_nl - 1 == 0)
        save_bytes[0] = '\0';
    if (index_term == index_nl )
        save_bytes[0] = '\0';
    return(rs);
}

char *read_file(char *save_bytes, char *rs, int fd)
{
    size_t bytes_read;
    char read_buffer[BUFFER_SIZE + 1];

    bytes_read = 1;
    while(bytes_read > 0)
    {
        bytes_read = read(fd, read_buffer, BUFFER_SIZE);
        read_buffer[bytes_read] = '\0';
        if (bytes_read < 0)
        {
            if (rs != NULL)
                free(rs);
            return(NULL);
        }
        else
        {
            if (bytes_read == 0)
                break;
            rs = check_and_move(save_bytes, rs, read_buffer);
            if (rs == NULL)
                return(NULL);
            if (ft_strlen(rs, '\0') > ft_strlen(rs, '\n'))
                bytes_read = 0;
        }
    }
    return(rs);
}

char *get_next_line(int fd)
{
    static char save_bytes[BUFFER_SIZE];
    char        *rs;

    if (read(fd, save_bytes, 0 ) == -1)
        return(NULL);
    rs = NULL;
    if (save_bytes[0])
    {
        rs = check_and_move(save_bytes, rs, save_bytes);
        if (ft_strlen(rs, '\0') > ft_strlen(rs, '\n'))
            return(rs);
    }
    rs = read_file(save_bytes, rs, fd);
    return(rs);
}