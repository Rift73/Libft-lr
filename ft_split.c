#include "libft.h"
#include <stdlib.h>

static size_t	ft_count_words(const char *s, char delimiter)
{
	size_t	count;

	count = 0;
	while (*s != '\0')
	{
		while (*s == delimiter && *s != '\0')
			s++;
		if (*s != '\0')
		{
			count++;
			while (*s != delimiter && *s != '\0')
				s++;
		}
	}
	return (count);
}

/* Only the first count word pointers own completed allocations. */
static char	**ft_free_words(char **words, size_t count)
{
	while (count > 0)
	{
		count--;
		free(words[count]);
	}
	free(words);
	return (NULL);
}

static char	*ft_copy_word(const char *s, size_t length)
{
	char	*word;

	word = malloc(length + 1);
	if (word == NULL)
		return (NULL);
	ft_memcpy(word, s, length);
	word[length] = '\0';
	return (word);
}

static char	**ft_fill_words(const char *s, char c, char **words)
{
	size_t	count;
	size_t	length;

	count = 0;
	while (*s != '\0')
	{
		while (*s == c && *s != '\0')
			s++;
		if (*s == '\0')
			break ;
		length = 0;
		while (s[length] != '\0' && s[length] != c)
			length++;
		words[count] = ft_copy_word(s, length);
		if (words[count] == NULL)
			return (ft_free_words(words, count));
		count++;
		s += length;
	}
	words[count] = NULL;
	return (words);
}

char	**ft_split(char const *s, char c)
{
	char	**words;
	size_t	count;

	if (s == NULL)
		return (NULL);
	count = ft_count_words(s, c);
	if (count > (size_t)-1 / sizeof(char *) - 1)
		return (NULL);
	words = malloc(sizeof(char *) * (count + 1));
	if (words == NULL)
		return (NULL);
	return (ft_fill_words(s, c, words));
}
