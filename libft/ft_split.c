/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kennahi <kennahi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/21 17:46:00 by kennahi           #+#    #+#             */
/*   Updated: 2021/05/05 16:46:50 by kennahi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	count_words(char const *s, char c)
{
	int		i;
	int		words;

	words = 0;
	i = 0;
	while (s[i])
	{
		if (s[i] != c && (s[i + 1] == c || s[i + 1] == '\0'))
			words++;
		i++;
	}
	return (words);
}

static int	words_len(char const *s, char c)
{
	int		i;
	int		len;

	i = 0;
	len = 0;
	while (s[i] != c && s[i] != '\0')
	{
		i++;
		len++;
	}
	return (len);
}

static void	*leak(char **sploot, int words)
{
	int		i;

	i = 0;
	while (i < words)
	{
		free(sploot[i]);
		i++;
	}
	free(sploot);
	return (NULL);
}

static char	**splooot(char const *s, int words, char c, char **sploot)
{
	int		i;
	int		j;
	int		len;

	i = -1;
	while (++i < words)
	{
		while (*s == c)
			s++;
		len = words_len(s, c);
		sploot[i] = (char *)malloc(sizeof(char) * (len + 1));
		if (!sploot[i])
			return (leak(sploot, i));
		j = 0;
		while (j < len)
			sploot[i][j++] = *s++;
		sploot[i][j] = '\0';
	}
	sploot[i] = NULL;
	return (sploot);
}

char	**ft_split(char	const *s, char c)
{
	char	**sploot;
	int		words;

	if (!s)
		return (NULL);
	words = count_words(s, c);
	sploot = (char **)malloc(sizeof(char *) * (words + 1));
	if (!sploot)
		return (NULL);
	sploot = splooot(s, words, c, sploot);
	return (sploot);
}
