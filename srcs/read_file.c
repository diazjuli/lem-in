/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_file.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdiaz <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/04 12:54:47 by jdiaz             #+#    #+#             */
/*   Updated: 2018/11/24 18:36:15 by jdiaz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <lemin.h>

int		add_input(t_lem *lem, char *line)
{
	t_list	*add;
	t_list	*temp;

	add = (t_list *)malloc(sizeof(t_list));
	add->next = NULL;
	add->content = (void *)line;
	add->content_size = sizeof(line);
	temp = lem->input;
	if (temp == NULL)
		lem->input = add;
	else
	{
		while (temp->next)
			temp = temp->next;
		temp->next = add;
	}
	return (1);
}

int		get_start(t_lem *l, char *line, char type)
{
	char	**split;
	int		r;

	if ((line[2] == 's' && l->start) || (line[2] == 'e' && l->end))
		return (-1);
	add_input(l, line);
	r = get_next_line(0, &line);
	while (r > 0 && line[0] == '#')
	{
		if (ft_strnequ(line, "##start", 7) || ft_strnequ(line, "##end", 5))
			return (-1);
		add_input(l, line);
		r = get_next_line(0, &line);
	}
	if (r < 1 || ft_num_words(line) != 3 || new_vertex(l, line) == -1)
		return (-1);
	split = ft_strsplit(line, ' ');
	l->end = type == 'e' ? ft_strdup(split[0]) : l->end;
	l->start = type == 's' ? ft_strdup(split[0]) : l->start;
	add_input(l, line);
	free_split(split);
	free(split);
	return (1);
}

char	*read_vertices(t_lem *l, char *line, int r)
{
	while ((r = get_next_line(0, &line)) > 0)
	{
		while (r > 0 && line[0] == '#')
		{
			if (ft_strnequ(line, "##start", 6) || ft_strnequ(line, "##end", 4))
			{
				if (get_start(l, line, line[2]) == -1)
					return (NULL);
			}
			else
				add_input(l, line);
			r = get_next_line(0, &line);
		}
		if (r < 1 || ft_num_words(line) != 3)
			break ;
		if (new_vertex(l, line) == -1)
			return (NULL);
		add_input(l, line);
	}
	if (r < 1 || !l->start || !l->end)
		return (NULL);
	return (line);
}

int		read_input(t_lem *lem)
{
	char	*line;
	int		r;

	r = get_next_line(0, &line);
	while (r > 0 && line[0] == '#')
	{
		add_input(lem, line);
		r = get_next_line(0, &line);
	}
	if (r < 1 || (lem->num_ants = ft_atoi(line)) < 1)
		return (-1);
	add_input(lem, line);
	if ((line = read_vertices(lem, line, 1)) == NULL)
		return (-1);
	if (get_edges(lem, line, 1) == -1)
		return (-1);
	return (1);
}
