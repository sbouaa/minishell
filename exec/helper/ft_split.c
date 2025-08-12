/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbouaa <sbouaa@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/12 17:07:33 by sbouaa            #+#    #+#             */
/*   Updated: 2025/07/29 19:51:53 by sbouaa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "helper.h"

static size_t	count_words(char const	*str, char c)
{
	int	i;
	int	off;
	int	words;

	i = 0;
	off = 1;
	words = 0;
	while (str[i] != '\0')
	{
		if (str[i] != c && off == 1)
		{
			off = 0;
			words++;
		}
		else if (str[i] == c)
			off = 1;
		i++;
	}
	return (words);
}

static char	*ft_add_word(const char *s, char c)
{
	size_t	len;
	char	*word;

	if (!s)
		return (NULL);
	len = 0;
	while (s[len] && s[len] != c)
	{
		len++;
	}
	word = g_malloc((len +1) * sizeof(char), MALLOC);
	if (word == NULL)
		return (NULL);
	len = 0;
	while (s[len] && s[len] != c)
	{
		word[len] = s[len];
		len++;
	}
	word[len] = '\0';
	return (word);
}

char	**ft_split(const char *s, char c)
{
	char	**p;
	size_t	i;
	size_t	j;
	size_t	word_count;

	if (!s)
		return (NULL);
	word_count = count_words(s, c);
	p = g_malloc((word_count + 1) * sizeof(char *), MALLOC);
	if (p == NULL)
		return (NULL);
	i = 0;
	j = -1;
	while (++j < word_count)
	{
		while (s[i] && s[i] == c)
			i++;
		p[j] = ft_add_word(&s[i], c);
		if (p[j] == NULL)
			return (NULL);
		while (s[i] && s[i] != c)
			i++;
	}
	p[word_count] = NULL;
	return (p);
}
