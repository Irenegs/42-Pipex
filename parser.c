/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: irgonzal <irgonzal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/13 15:23:01 by irgonzal          #+#    #+#             */
/*   Updated: 2023/10/13 18:41:58 by irgonzal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "pipex.h"

char	**ft_out(char **arr, int i)
{
	int	j;

	j = 0;
	while (j <= i && arr[j])
	{
		free(arr[j]);
		j++;
	}
	free(arr);
	return (NULL);
}

static int is_separator(char c, char *sep)
{
    int i;

    if (sep)
    {
        i = 0;
        while (c != sep[i] && sep[i] != '\0')
            i++;
        if (sep[i] != '\0')
            return (i);
    }
    return (-1);
}

static int is_escaped(char const *s, int i)
{
    if (s[i - 1] == '\\')
        return (1);
    return (0);
}

static int  new_word(char const *s, char *sep, int i, int quotes)
{
    if (s && sep)
    {
        if (is_separator(s[i], sep) == -1 && quotes == 0)
        {
            if (i == 0)
                return (1);
            if (is_separator(s[i - 1], sep) != -1 && is_escaped(s, i - 1) == 0)
                return (1);
        }
        return (0);
    }
    return (1);
}

int	ft_wc(char const *s, char *sep)
{
	int	i;
	int	words;
    int quotes;

	if (!s)
		return (0);
	i = 0;
	words = 0;
    quotes = 0;
	while (s[i] != '\0')
	{
		if (new_word(s, sep, i, quotes) == 1)
        {
            //printf("nw:%c\n", s[i]);
			words += 1;
        }
        if (s[i] == '\'' && is_escaped(s, i) == 0)
            quotes = 1 - quotes;
		i++;
	}
	return (words);
}

int end_word(char const *s, char *sep, int i, int quotes)
{
    if (s && sep && s[i] != '\0')
    {
        if (quotes == 1 || is_separator(s[i], sep) == -1 || is_escaped(s, i) == 1)
        {
            //printf("nll:%c\n", s[i]);
            return (0);
        }
    }
    //printf("ll:%c\n", s[i]);
    return (1);
}

int ch_to_print(char const *s, int i)
{
    if (s[i] == '\\' || s[i] == '\'')
    {
        if (is_escaped(s, i) == 0)
            return (0);
    }
    return (1);
}

int len_next_word(char const *s, char *sep, int pos)
{
    int len;
    int i;
    int quotes;

    i = 0;
    len = 0;
    quotes = 0;
    while (end_word(s, sep, pos + i, quotes) == 0)
    {
        if (ch_to_print(s, pos + i) == 1)
        {
            //printf("c:%c\n", s[pos + i]);
            len++;
        }
        else if (s[pos + i] == '\'')
            quotes = 1 - quotes;
        i++;
    }
    //printf("ew:%c\n", s[pos + i]);
    return(len);
}

int copy_return_nonprint(char *dst, char const *s, int len)
{
    int i;
    int nonprintable;

    i = 0;
    nonprintable = 0;
    if (dst && s)
    {
        while (i < len)
        {
            //printf("eval %c\n", s[i+nonprintable]);
            if (ch_to_print(s, i + nonprintable) == 1)
            {
                dst[i] = s[i + nonprintable];
                //printf("copied %i: %c\n", i, dst[i]);
                i++;
            }
            else
            {
                nonprintable++;
                //printf("non %i: %c\n", i, s[i + nonprintable -1]);
            }
        }
        dst[len] = '\0';
        return (nonprintable);
    }
    return (-1);
}

char	**ft_super_split(char const *s, char *sep)
{
	char	**arr;
	int		i;
	int	pos;
	int	len;

	arr = malloc((ft_wc(s, sep) + 1) * sizeof(char *));
	if (!arr)
		return (NULL);
	i = -1;
	pos = 0;
	while (++i < ft_wc(s, sep))
	{
        //printf("wc: %d\n", ft_wc(s, sep));
        //printf("pos01 %d\n", pos);
        while (new_word(s, sep, pos, 0) == 0)
        {
            //printf("s %c\n", s[pos]);
			pos++;
        }
        //printf("pos1 %d\n", pos);
        //printf("c %c\n", s[pos]);
        len = len_next_word(s, sep, pos);
        //printf("len next: i=%d; l=%d; c=%c\n", i, len, s[pos]);
		arr[i] = malloc((len + 1) * sizeof(char));
		if (!arr[i])
			return (ft_out(arr, i));
        //printf("pos %d\n", pos);
		pos = pos + len + copy_return_nonprint(arr[i], s + pos, len);
	}
	arr[i] = NULL;
    //printf("saliendo %s\n", arr[1]);
	return (arr);
}

