/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdiaz <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/09 20:55:36 by jdiaz             #+#    #+#             */
/*   Updated: 2018/11/09 22:20:18 by jdiaz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <lemin.h>

void	free_vertex(t_vertex *v)
{
	t_list_v *tmp;

	free(v->name);
	while (v->adj)
	{
		tmp = v->adj->next;
		free(v->adj);
		v->adj = tmp;
	}
	free(v);
}

void	free_vertices(t_list_v *vertices)
{
	t_list_v *tmp;

	while (vertices)
	{
		free_vertex(vertices->v);
		tmp = vertices->next;
		free(vertices);
		vertices = tmp;
	}
}

void	free_paths(t_list_p *paths)
{
	t_list_p *tmp;

	while (paths)
	{
		tmp = paths->next;
		free(paths->path.rooms);
		free(paths->path.ants);
		free(paths);
		paths = tmp;
	}
}

void	free_all(t_lem *lem)
{
	free(lem->start);
	free(lem->end);
	free_vertices(lem->vertices);
	free_paths(lem->paths);
}

int		free_queue(t_list_v *queue, t_lem *l, t_vertex *curr)
{
	t_list_v *temp;

	while (queue)
	{
		temp = queue->next;
		free(queue);
		queue = temp;
	}
	return (found_path(l, curr));
}
