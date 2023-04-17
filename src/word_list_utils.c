/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   word_list_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsmereka <gsmereka@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/03 04:17:35 by gde-mora          #+#    #+#             */
/*   Updated: 2023/04/05 16:44:44 by gsmereka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/ft_format_string.h"

t_word	*create_word(char *value)
{
	t_word	*new_node;

	new_node = (t_word *)malloc(sizeof(t_word));
	if (!new_node)
		return (NULL);
	if (value)
		new_node->size = ft_strlen(value);
	new_node->value = ft_strdup(value);
	new_node->next = NULL;
	return (new_node);
}

t_word	*word_last(t_word *word)
{
	t_word	*last_word;

	last_word = word;
	if (!word)
		return (word);
	while (last_word->next)
		last_word = last_word->next;
	return (last_word);
}

void	add_word(char *value, t_data *data)
{
	t_word	*last_node;
	t_word	*new_node;
	t_word	**words;

	words = &data->words;
	if (value)
		data->str_size += ft_strlen(value);
	if (!*words)
		*words = create_word(value);
	else
	{
		last_node = word_last(*words);
		new_node = create_word(value);
		last_node->next = new_node;
	}
}

void	word_clear(t_word **words)
{
	if (*words)
	{
		word_clear(&(*words)->next);
		free((*words)->value);
		free((*words));
		*words = NULL;
	}
}
