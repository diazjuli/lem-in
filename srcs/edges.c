/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   edges.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdiaz <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/04 20:12:47 by jdiaz             #+#    #+#             */
/*   Updated: 2018/11/23 20:52:28 by jdiaz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <lemin.h>

int		add_edge(t_vertex *v1, t_vertex *add)
{
	t_list_v *node;
	t_list_v *tmp;

	if ((node = (t_list_v *)malloc(sizeof(t_list_v))) == NULL)
		return (-1);
	node->v = add;
	node->next = NULL;
	if (v1->adj == NULL)
		v1->adj = node;
	else
	{
		tmp = v1->adj;
		while (tmp)
		{
			if (!tmp->next || tmp->v->name == add->name)
				break ;
			tmp = tmp->next;
		}
		if (tmp->v->name != add->name)
			tmp->next = node;
		else
			free(node);
	}
	return (1);
}

int		check_edge(char **split)
{
	int i;

	i = 0;
	while (split[i])
		i++;
	return (i == 2);
}

int		get_edges(t_lem *l, char *line, int r)
{
	char		**split;
	t_vertex	*v1;
	t_vertex	*v2;

	while (r > 0)
	{
		if (line[0] != '#')
		{
			split = ft_strsplit(line, '-');
			if (check_edge(split) != 1)
				return (-1);
			v1 = get_vertex(l, split[0]);
			v2 = get_vertex(l, split[1]);
			if (!v1 || !v2 || add_edge(v1, v2) == -1 || add_edge(v2, v1) == -1)
				return (-1);
			free_split(split);
			free(split);
		}
		add_input(l, line);
		r = get_next_line(0, &line);
	}
	return (r);
}
