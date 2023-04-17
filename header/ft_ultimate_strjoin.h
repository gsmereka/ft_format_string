/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_format_string.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsmereka <gsmereka@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/30 22:56:31 by lbiasuz           #+#    #+#             */
/*   Updated: 2022/07/26 20:19:18 by gsmereka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_FORMAT_STRING_H
# define FT_FORMAT_STRING_H
# include <stdarg.h>
# include <unistd.h>
# include <stdlib.h>

typedef struct s_word
{
	char			*value;
	int				size;
	struct s_word	*next;
}	t_word;

typedef struct s_data
{
	t_word	*words;
	int		str_size;
}	t_data;

char	*ft_format_string(char *str, ...);
char	*ft_strchr(const char *s, int c);
char	*ft_strdup(const char *s);
char	*ft_strjoin(char *s1, char *s2);
char	*ft_itoa(int n);
char	*ft_utoa(unsigned int n);
char	*ft_itohex(unsigned long long n);
void	ft_putchar_fd(char c, int fd);
void	ft_putstr_fd(char *s, int fd);
size_t	ft_strlen(const char *s);
int		ft_toupper(int c);
int		ft_isdigit(int c);

// words_utils
t_word	*create_word(char *value);
t_word	*word_last(t_word *word);
void	add_word(char *value, t_data *data);
void	word_clear(t_word **words);

#endif