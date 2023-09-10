/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: irgonzal <irgonzal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/06 19:51:55 by irgonzal          #+#    #+#             */
/*   Updated: 2023/09/10 10:47:33 by irgonzal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "pipex.h"

static int ft_is_separator(char c, char *sep)
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
    //printf("No separator %c\n", c);
    return (-1);
}

static int	ft_wc(char const *s, char *sep)
{
	int	i;
	int	words;

	if (!s)
		return (0);
	i = 0;
	words = 0;
	while (s[i] != '\0')
	{
		if (ft_is_separator(s[i], sep) == -1 && (i == 0 || ft_is_separator(s[i - 1], sep) != -1))
			words += 1;
		i++;
	}
	return (words);
}

static size_t	ft_len_next(char const *s, size_t pos, char *sep)
{
	size_t	i;

	i = 0;
	while (ft_is_separator(s[pos + i], sep) == -1 && s[pos + i] != '\0')
    {
        //printf("i, c, pos + i %zu %c %zu\n", i , s[pos + i], pos + i);
		i++;
    }
    //printf("len next %zu %c\n", i, s[pos + i]);
	return (i);
}

static	char	**ft_out(char **arr, int i)
{
	int	j;

	j = 0;
	while (j <= i)
	{
		free(arr[j]);
		j++;
	}
	free(arr);
	return (NULL);
}

char	**ft_super_split(char const *s, char *sep)
{
	char	**arr;
	int		i;
	size_t	pos;
	size_t	len;

	arr = malloc((ft_wc(s, sep) + 1) * sizeof(char *));
	if (!arr)
		return (NULL);
	i = -1;
	pos = 0;
	while (++i < ft_wc(s, sep))
	{
        //printf("pos a %zu\n", pos);
		while (ft_is_separator(s[pos], sep) != -1)
			pos++;
        //printf("pos b %zu\n", pos);
		len = ft_len_next(s, pos, sep);
		arr[i] = malloc((len + 1) * sizeof(char));
		if (!arr[i])
			return (ft_out(arr, i));
		arr[i] = ft_memmove(arr[i], s + pos, len);
		arr[i][len] = '\0';
		pos += len + 1;
	}
	arr[i] = NULL;
	return (arr);
}
