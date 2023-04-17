/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_format_string.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsmereka <gsmereka@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/03 18:52:37 by gsmereka          #+#    #+#             */
/*   Updated: 2023/04/04 01:57:00 by gsmereka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/ft_format_string.h"
#include <stdio.h>

static char	*ft_ptr_adr(char *word)
{
	char	*temp_w;

	temp_w = ft_strdup(word);
	free(word);
	if (temp_w[0] == '0' && ft_strlen(temp_w) == 1)
		word = ft_strdup("(nil)");
	else
	{
		word = ft_strdup("0x");
		word = ft_strjoin(word, temp_w);
	}
	free(temp_w);
	return (word);
}

static char	*ft_unsignedworks(char c, unsigned long long n)
{
	char	*word;
	int		i;

	word = NULL;
	if (c == 'x' || c == 'X')
	{
		word = ft_itohex((unsigned int)n);
		if (c == 'X')
		{
			i = 0;
			while (word[i++])
				word[i - 1] = ft_toupper(word[i - 1]);
		}
	}
	else if (c == 'p')
	{
		word = ft_itohex(n);
		word = ft_ptr_adr(word);
	}
	else if (c == 'u')
		word = ft_utoa((unsigned int)n);
	return (word);
}

static void	save_normal_word(char *str, int start, int end, t_data *data);
static void	save_special_word(char *str, va_list args, t_data *data);
static void	get_words(char *str, va_list args, t_data *data);
static char	*format_arg(char c, va_list args);

char	*ft_format_string(char *str, ...)
{
	va_list	args;
	t_data	data;
	t_word	*word;
	char	*final_word;
	int		i;
	int		j;

	data = (t_data) {0};
	if (str == 0)
		return (NULL);
	va_start(args, str);
	get_words(str, args, &data);
	va_end(args);
	final_word = malloc((data.str_size + 1) * sizeof(char));
	word = data.words;
	i = 0;
	while (word)
	{
		j = 0;
		while (word->value[j])
		{
			final_word[i] = word->value[j];
			i++;
			j++;
		}
		word = word->next;
	}
	final_word[i] = '\0';
	word_clear(&data.words);
	return (final_word);
}

// tentar so % ou %%
static void	get_words(char *str, va_list args, t_data *data)
{
	int		start;
	int		end;

	start = 0;
	end = 0;
	while (str[end])
	{
		if (str[end] == '%')
		{
			save_normal_word(str, start, end, data);
			save_special_word(&str[end + 1], args, data);
			end++;
			if (ft_strchr("cspdiuxX%", str[end]) != NULL)
				end++;
			start = end;
		}
		else
			end++;
	}
	save_normal_word(str, start, end, data);
}

static void	save_normal_word(char *str, int start, int end, t_data *data)
{
	char	*new_word;
	int		size;
	int		i;

	size = end - start;
	if (size <= 0)
		return ;
	new_word  = malloc((size + 1) * sizeof(char));
	i = 0;
	if (!new_word)
		return ;
	while (i < size)
	{
		new_word[i] = str[start + i];
		i++;
	}
	new_word[i] = '\0';
	add_word(new_word, data);
	free(new_word);
}

static void	save_special_word(char *str, va_list args, t_data *data)
{
	char	*word;

	if (!str[0])
		return ;
	if (ft_strchr("cspdiuxX%", str[0]) == NULL)
		return ;
	if (str[0] == '%')
	{
		add_word("%", data);
		return ;
	}
	word = format_arg(str[0], args);
	add_word(word, data);
	free (word);
}

static char	*format_arg(char c, va_list args)
{
	char	*word;

	if (c == 'c')
	{
		word = ft_strdup("c");
		word[0] = va_arg(args, int);
		if (word && word[0] != 0)
			return (word);
		free (word);
		word = NULL;
	}
	else if (c == 's')
	{
		word = NULL;
		word = va_arg(args, char *);
		word = ft_strdup(word);
	}
	else if (c == 'd' || c == 'i')
		word = ft_itoa(va_arg(args, int));
	else if (c == 'x' || c == 'X' || c == 'p' || c == 'u')
		word = ft_unsignedworks(c, va_arg(args, unsigned long long));
	if (!word)
		word = ft_strdup("(null)");
	return (word);
}
