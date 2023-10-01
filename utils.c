/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: irgonzal <irgonzal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/06 19:51:55 by irgonzal          #+#    #+#             */
/*   Updated: 2023/10/01 17:43:39 by irgonzal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "pipex.h"

static int isseparator(char c, char *sep)
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

static int	ft_wc(char const *s, char *sep)
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
		if (isseparator(s[i], sep) == -1 && (i == 0 || isseparator(s[i - 1], sep) != -1) && quotes == 0)
			words += 1;
        if (s[i] == 39)
            quotes = 1 - quotes;
		i++;
	}
	return (words);
}

static size_t	ft_len_next(char const *s, size_t pos, char *sep)
{
	size_t	i;
    int quotes;

	i = 0;
    quotes = 0;
	while ((isseparator(s[pos + i], sep) == -1 || quotes != 0) && s[pos + i] != '\0')
    {
        //printf("car %c\n", s[pos + i]);
        if (s[pos + i] == 39)
            quotes = 1 - quotes;
		i++;
    }
    //printf("ultimo car: %c\n", s[pos + i - 1]);
	return (i);
}

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
        //printf("wc: %d\n", ft_wc(s, sep));
        while (isseparator(s[pos], sep) != -1)
			pos++;
        len = ft_len_next(s, pos, sep);
        //printf("len next: i=%d; l=%zu\n", i, len);
		arr[i] = malloc((len + 1) * sizeof(char));
		if (!arr[i])
			return (ft_out(arr, i));
		arr[i] = ft_memmove(arr[i], s + pos, len);
		arr[i][len] = '\0';
		pos += len + 1;
	}
	arr[i] = NULL;
    //printf("saliendo %s\n", arr[1]);
	return (arr);
}
