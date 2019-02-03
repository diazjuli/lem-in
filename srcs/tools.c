/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdiaz <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/04 16:55:22 by jdiaz             #+#    #+#             */
/*   Updated: 2018/11/23 19:50:32 by jdiaz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <lemin.h>

int			calc_flow(t_lem *lem)
{
	t_list_p	*temp;
	int			flow;
	int			min;

	flow = 0;
	temp = lem->paths;
	while (flow < lem->num_ants)
	{
		min = temp->path.length + temp->path.flow + 1;
		while (temp)
		{
			if (flow < lem->num_ants &&
					temp->path.length + temp->path.flow < min)
			{
				temp->path.flow++;
				flow++;
			}
			temp = temp->next;
		}
		temp = lem->paths;
	}
	return (1);
}

int			add_to_queue(t_list_v **queue, t_vertex *to_add)
{
	t_list_v *temp;
	t_list_v *new;

	temp = *queue;
	new = (t_list_v *)malloc(sizeof(t_list_v));
	new->next = NULL;
	new->v = to_add;
	if (temp == NULL)
	{
		*queue = new;
	}
	else
	{
		while (temp->next)
			temp = temp->next;
		temp->next = new;
	}
	return (1);
}

t_vertex	*get_from_queue(t_list_v **queue)
{
	t_list_v	*temp;
	t_vertex	*v;

	temp = *queue;
	if (!temp)
		return (NULL);
	*queue = (*queue)->next;
	temp->next = NULL;
	v = temp->v;
	free(temp);
	return (v);
}

void		reset(t_lem *lem)
{
	t_list_v	*temp;

	temp = lem->vertices;
	while (temp)
	{
		if (temp->v->path == -1)
		{
			temp->v->marked = 0;
			temp->v->prev = NULL;
			temp->v->dis = 0;
		}
		temp = temp->next;
	}
}

void		free_split(char **split)
{
	while (*split)
	{
		free(*split);
		split++;
	}
	free(*split);
}
