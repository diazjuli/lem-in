/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdiaz <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/03 20:41:55 by jdiaz             #+#    #+#             */
/*   Updated: 2018/11/23 20:26:37 by jdiaz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <lemin.h>

int		print_error(void)
{
	ft_putstr("ERROR\n");
	return (-1);
}

int		init(t_lem *lem)
{
	lem->num_ants = 0;
	lem->num_paths = 0;
	lem->start = NULL;
	lem->end = NULL;
	lem->paths = NULL;
	lem->input = NULL;
	lem->ants_placed = 0;
	lem->ants_done = 0;
	return (1);
}

int		main(void)
{
	t_lem	lem;

	init(&lem);
	if (read_input(&lem) == -1)
		return (print_error());
	trivial_path(&lem);
	while (lem.num_paths < lem.num_ants)
	{
		if (find_path(&lem, get_vertex(&lem, lem.start)) == -1)
			break ;
		reset(&lem);
	}
	if (lem.num_paths == 0)
		return (print_error());
	print_input(&lem);
	calc_flow(&lem);
	while (lem.ants_done < lem.num_ants)
	{
		lem.ants_placed = place_ants(&lem, lem.ants_placed);
		lem.ants_done = print_ants(&lem, lem.ants_done, 0);
	}
	free_all(&lem);
	return (1);
}
