/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vertices.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdiaz <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/04 19:04:30 by jdiaz             #+#    #+#             */
/*   Updated: 2018/11/09 22:19:50 by jdiaz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <lemin.h>

t_vertex	*get_vertex(t_lem *l, char *name)
{
	t_list_v *temp;

	temp = l->vertices;
	while (temp)
	{
		if (ft_strequ(temp->v->name, name) == 1)
			return (temp->v);
		temp = temp->next;
	}
	return (NULL);
}

int			add_to_v_list(t_lem *l, t_list_v *to_add)
{
	t_list_v *temp;

	temp = l->vertices;
	if (temp == NULL)
		l->vertices = to_add;
	else
	{
		while (temp && temp->next)
		{
			if (ft_strequ(temp->v->name, to_add->v->name))
				return (-1);
			temp = temp->next;
		}
		if (ft_strequ(temp->v->name, to_add->v->name))
			return (-1);
		temp->next = to_add;
	}
	return (1);
}

int			check_int(char *n1, char *n2)
{
	int i;

	i = 0;
	while (n1[i] != '\0')
	{
		if (!ft_isdigit(n1[i]))
			return (-1);
		i++;
	}
	i = 0;
	while (n2[i] != '\0')
	{
		if (!ft_isdigit(n2[i]))
			return (-1);
		i++;
	}
	return (1);
}

int			new_vertex(t_lem *l, char *line)
{
	char		**split;
	t_list_v	*to_add;
	t_vertex	*vertex;

	split = ft_strsplit(line, ' ');
	if (split[0][0] == 'L' || check_int(split[1], split[2]) == -1)
		return (-1);
	if ((to_add = (t_list_v *)malloc(sizeof(t_list_v))) == NULL)
		return (-1);
	if ((vertex = (t_vertex *)malloc(sizeof(t_vertex))) == NULL)
		return (-1);
	vertex->prev = NULL;
	vertex->adj = NULL;
	vertex->name = ft_strdup(split[0]);
	vertex->marked = 0;
	vertex->path = -1;
	vertex->dis = 0;
	vertex->x = ft_atoi(split[1]);
	vertex->y = ft_atoi(split[2]);
	to_add->v = vertex;
	to_add->next = NULL;
	free_split(split);
	free(split);
	return (add_to_v_list(l, to_add));
}
