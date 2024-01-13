#include "sh.h"

// valid var_name-> a-zA-Z0-9_
int isvalid_var_name_char(int c)
{
	if (!ft_isalnum(c) && c != 95)
	{
		return (0);
	}
	return (1);
}

static unsigned int	ft_words(char const *s, char c)
{
	unsigned int	nb;

	nb = 0;
	while (*s)
	{
		if (*s != c)
			nb++;
		while (*s && *s != c)
			s++;
		while (*s && *s == c)
			s++;
	}
	return (nb);
}

static char	*ft_wordalloc(char const *s, char c)
{
	char	*str;
	size_t	i;
	size_t	len;

	i = 0;
	while ((char)s[i] && (char)s[i] != c)
		i++;
	len = i;
	str = (char *)malloc(sizeof(char) * (len + 1));
	if (!str)
		return (NULL);
	i = 0;
	while (i < len)
	{
		str[i] = (char)s[i];
		i++;
	}
	str[i] = '\0';
	return (str);
}

char	**ft_split(char const *s, char c)
{
	char			**str_new;
	unsigned int	num_words;
	size_t			i;

	num_words = ft_words(s, c);
	str_new = (char **)malloc(sizeof(char *) * (num_words + 1));
	if (!str_new)
		return (NULL);
	i = 0;
	while (i < num_words)
	{
		while (*s == c && *s)
			s++;
		if (*s != c && *s)
		{
			str_new[i] = ft_wordalloc(s, c);
			if (!str_new[i])
				return (str_new);
		}
		while (*s != c && *s)
			s++;
		i++;
	}
	str_new[i] = NULL;
	return (str_new);
}