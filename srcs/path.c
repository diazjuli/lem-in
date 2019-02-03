/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdiaz <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/05 13:11:03 by jdiaz             #+#    #+#             */
/*   Updated: 2018/11/23 17:41:51 by jdiaz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <lemin.h>

void	trivial_path(t_lem *lem)
{
	t_list_p *path;
	t_list_v *adj;

	adj = get_vertex(lem, lem->start)->adj;
	while (adj)
	{
		if (ft_strequ(adj->v->name, lem->end))
		{
			path = (t_list_p *)malloc(sizeof(t_list_p));
			path->path.rooms = (char **)malloc(sizeof(char *));
			path->path.rooms[0] = lem->end;
			path->path.ants = (int *)malloc(sizeof(int));
			path->path.length = 1;
			path->path.rooms[0] = lem->end;
			path->path.ants[0] = -1;
			path->path.flow = 0;
			lem->num_paths++;
			path->next = NULL;
			lem->paths = path;
		}
		adj = adj->next;
	}
}

int		add_path(t_lem *l, t_list_p *new_path)
{
	t_list_p *temp;

	temp = l->paths;
	if (l->paths == NULL)
	{
		l->paths = new_path;
	}
	else
	{
		while (temp->next)
			temp = temp->next;
		temp->next = new_path;
	}
	return (1);
}

int		*get_int_array(int length)
{
	int		*array;
	int		i;

	i = 0;
	array = (int *)malloc(sizeof(int) * length);
	while (i < length)
	{
		array[i] = -1;
		i++;
	}
	return (array);
}

int		found_path(t_lem *l, t_vertex *curr)
{
	t_list_p	*new_path;
	int			len;

	len = curr->dis + 1;
	if ((new_path = (t_list_p *)malloc(sizeof(t_list_p))) == NULL)
		return (-1);
	new_path->path.rooms = (char **)malloc(sizeof(char *) * len);
	new_path->path.ants = get_int_array(len);
	if (!new_path->path.ants || !new_path->path.rooms)
		return (-1);
	new_path->path.length = len;
	new_path->path.rooms[len-- - 1] = l->end;
	new_path->path.flow = 0;
	while (len > 0)
	{
		new_path->path.rooms[len - 1] = curr->name;
		curr->path = l->num_paths;
		curr = curr->prev;
		len--;
	}
	l->num_paths++;
	new_path->next = NULL;
	return (add_path(l, new_path));
}

int		find_path(t_lem *l, t_vertex *curr)
{
	t_list_v	*queue;
	t_list_v	*tmp;

	queue = NULL;
	curr->marked = 1;
	add_to_queue(&queue, curr);
	while ((curr = get_from_queue(&queue)) != NULL)
	{
		tmp = curr->adj;
		while (tmp)
		{
			if (ft_strequ(tmp->v->name, l->end) &&
					!ft_strequ(curr->name, l->start))
				return (free_queue(queue, l, curr));
			if (tmp->v->marked == 0)
			{
				tmp->v->prev = curr;
				tmp->v->marked = 1;
				tmp->v->dis = curr->dis + 1;
				add_to_queue(&queue, tmp->v);
			}
			tmp = tmp->next;
		}
	}
	return (-1);
}
