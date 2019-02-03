/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lemin.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdiaz <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/03 19:15:13 by jdiaz             #+#    #+#             */
/*   Updated: 2018/11/23 19:15:26 by jdiaz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEMIN_H
# define LEMIN_H

# include <libft.h>

typedef struct			s_vertex
{
	char			*name;
	struct s_list_v	*adj;
	struct s_vertex	*prev;
	int				marked;
	int				path;
	int				dis;
	int				x;
	int				y;
}						t_vertex;

typedef struct			s_list_v
{
	struct s_list_v	*next;
	t_vertex		*v;
}						t_list_v;

typedef	struct			s_path
{
	int				length;
	char			**rooms;
	int				*ants;
	int				flow;
}						t_path;

typedef struct			s_list_p
{
	struct s_list_p	*next;
	t_path			path;
}						t_list_p;

typedef struct			s_lem
{
	int				num_ants;
	int				num_paths;
	char			*start;
	char			*end;
	t_list_v		*vertices;
	t_list_p		*paths;
	t_list			*input;
	int				ants_placed;
	int				ants_done;
}						t_lem;

int						read_input(t_lem *lem);
void					free_split(char **split);
int						new_vertex(t_lem *l, char *line);
t_vertex				*get_vertex(t_lem *l, char *name);
int						get_edges(t_lem *l, char *line, int r);
int						find_path(t_lem *l, t_vertex *curr);
int						add_to_queue(t_list_v **queue, t_vertex *to_add);
t_vertex				*get_from_queue(t_list_v **queue);
void					reset(t_lem *lem);
int						place_ants(t_lem *lem, int ants_placed);
int						print_ants(t_lem *lem, int ants_printed, int first);
void					trivial_path(t_lem *lem);
int						found_path(t_lem *l, t_vertex *curr);
void					free_all(t_lem *lem);
int						free_queue(t_list_v *queue, t_lem *l, t_vertex *curr);
int						add_input(t_lem *lem, char *line);
int						print_input(t_lem *l);
int						calc_flow(t_lem *lem);

#endif
