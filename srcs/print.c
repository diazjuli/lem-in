/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdiaz <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/05 20:27:49 by jdiaz             #+#    #+#             */
/*   Updated: 2018/11/23 19:15:36 by jdiaz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <lemin.h>

int		print_input(t_lem *l)
{
	t_list *temp;

	while (l->input)
	{
		ft_putendl((char *)(l->input->content));
		temp = l->input->next;
		free(l->input->content);
		free(l->input);
		l->input = temp;
	}
	ft_putstr("\n");
	return (1);
}

int		get_max(t_list_p *paths)
{
	t_list_p	*tmp;
	int			max;

	max = 0;
	tmp = paths;
	while (tmp)
	{
		if (max < tmp->path.length)
			max = tmp->path.length - 1;
		tmp = tmp->next;
	}
	return (max);
}

void	print_ant(t_path path, int curr)
{
	ft_putstr("L");
	ft_putnbr(path.ants[curr]);
	ft_putchar('-');
	ft_putstr(path.rooms[curr]);
}

int		print_ants(t_lem *lem, int ants_done, int first)
{
	int			curr;
	t_list_p	*tmp;

	tmp = lem->paths;
	curr = get_max(lem->paths);
	while (curr >= 0)
	{
		while (tmp)
		{
			if (curr < tmp->path.length && tmp->path.ants[curr] != -1)
			{
				if (first++ != 0)
					ft_putstr(" ");
				print_ant(tmp->path, curr);
				if (curr + 1 == tmp->path.length)
					ants_done++;
			}
			tmp = tmp->next;
		}
		curr--;
		tmp = lem->paths;
	}
	ft_putstr("\n");
	return (ants_done);
}

int		place_ants(t_lem *l, int ants_placed)
{
	int			j;
	t_list_p	*tmp;

	tmp = l->paths;
	while (tmp)
	{
		j = tmp->path.length - 2;
		while (j >= 0)
		{
			tmp->path.ants[j + 1] = tmp->path.ants[j];
			j--;
		}
		if (tmp->path.flow > 0)
		{
			tmp->path.ants[0] = ++ants_placed;
			tmp->path.flow--;
		}
		else
			tmp->path.ants[0] = -1;
		tmp = tmp->next;
	}
	return (ants_placed);
}
