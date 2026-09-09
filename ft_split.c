#include "libft.h"
#include <stdlib.h>
#include <stdint.h>

/* Skip separators, count a word, then advance to the end of that word. */
static size_t	ft_count_words(const char *s, char delimiter)
{
	size_t	word_count;

	word_count = 0;
	while (*s != '\0')
	{
		while (*s != '\0' && *s == delimiter)
			s++;
		if (*s != '\0')
		{
			word_count++;
			while (*s != '\0' && *s != delimiter)
				s++;
		}
	}
	return (word_count);
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

/*
** Locate a word, measure it, copy it, then advance past it. word_index counts
** completed allocations, so cleanup never reads uninitialized pointers.
** Each word ends in a zero character; the pointer array ends in NULL.
*/
static char	**ft_fill_words(const char *s, char delimiter, char **words)
{
	size_t	word_index;
	size_t	word_length;

	word_index = 0;
	while (*s != '\0')
	{
		while (*s != '\0' && *s == delimiter)
			s++;
		if (*s == '\0')
			break ;
		word_length = 0;
		while (s[word_length] != '\0' && s[word_length] != delimiter)
			word_length++;
		words[word_index] = ft_copy_word(s, word_length);
		if (words[word_index] == NULL)
			return (ft_free_words(words, word_index));
		word_index++;
		s += word_length;
	}
	words[word_index] = NULL;
	return (words);
}

/* Count first, reserve one extra pointer for NULL, then build the words. */
char	**ft_split(char const *s, char c)
{
	char	**words;
	size_t	word_count;

	if (s == NULL)
		return (NULL);
	word_count = ft_count_words(s, c);
	if (word_count > SIZE_MAX / sizeof(char *) - 1)
		return (NULL);
	words = malloc(sizeof(char *) * (word_count + 1));
	if (words == NULL)
		return (NULL);
	return (ft_fill_words(s, c, words));
}
