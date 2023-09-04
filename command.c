/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: irgonzal <irgonzal@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/30 17:35:31 by irgonzal          #+#    #+#             */
/*   Updated: 2023/09/02 17:17:11 by irgonzal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "pipex.h"

static int	ft_isspace(char c)
{
	if (c == 32 || (c < 14 && c > 8))
		return (1);
	return (0);
}

static size_t len_first_word(char *s)
{
    size_t pos;
    size_t len;

    pos = 0;
    len = 0;
    while (ft_isspace(s[pos]) == 1)
        pos++;
    while (ft_isspace(s[pos + len]) != 1 && s[pos + len] != '\0')
        len++;
    return(len);
}

static size_t len_second_word(char *s)
{
    size_t pos;
    size_t len;

    pos = 0;
    len = 0;
    while (ft_isspace(s[pos]) == 1)
        pos++;
    while (ft_isspace(s[pos]) == 0 && s[pos] != '\0')
        pos++;
    while (ft_isspace(s[pos]) == 1)
        pos++;
    //printf("pos: %zu\n", pos);
    while (s[pos + len] != '\0')
    {
        //printf("caracter: %c\n", s[pos + len]);
        len++;
    }
    return (len);
}

static void    get_second_word(char *s, char *arr_s, size_t len)
{
    size_t  pos;
    
    pos = 0;
    while (ft_isspace(s[pos]) == 1)
        pos++;
    while (ft_isspace(s[pos]) != 1 && s[pos] != '\0')
        pos++;
    while (ft_isspace(s[pos]) == 1)
        pos++;
    ft_memmove(arr_s, s + pos, len);
    arr_s[len] = '\0';
}

static void    get_first_word(char *s, char *arr_s, size_t len)
{
    size_t  pos;
    
    pos = 0;
    while (ft_isspace(s[pos]) == 1)
        pos++;
    ft_memmove(arr_s, s + pos, len);
    arr_s[len] = '\0';
}

int    get_command(char *s, char *arr[3])
{
    size_t  len;
    
    len = len_first_word(s);
    //printf("len first word: [%ld]\n", len);
    arr[0] = malloc((len + 1) * sizeof(char));
    if (!arr[0])
        return (1);
    get_first_word(s, arr[0], len);
    //printf("first command\n");
    len = len_second_word(s);
    //printf("len2 %zu\n", len);
    if (len != 0)
    {
        arr[1] = malloc((len + 1) * sizeof(char));
        if (!arr[1])
        {
            free(arr[0]);
            return (1);
        }
        get_second_word(s, arr[1], len);
        //printf("second word\n");
    }
    else
        arr[1] = NULL;
    arr[2] = NULL;
    //printf("exiting\n");
    return (0);
}
