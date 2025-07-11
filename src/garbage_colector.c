/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   garbage_colector.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pdrettas <pdrettas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/04 18:26:35 by itsiros           #+#    #+#             */
/*   Updated: 2025/06/11 11:20:10 by itsiros          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cube3d.h"

void	gc_mark_all(t_gc *gc)
{
	void	*root_ptr;
	t_gcobj	*cur;
	int		i;

	i = -1;
	while (++i < gc->root_count)
	{
		root_ptr = *gc->roots[i];
		cur = gc->objects;
		while (cur)
		{
			if (cur->ptr == root_ptr)
			{
				cur->marked = 1;
				break ;
			}
			cur = cur->next;
		}
	}
}

void	gc_sweep(t_gc *gc)
{
	t_gcobj	**cur;
	t_gcobj	*unreached;

	if (gc->objects == NULL)
		return ;
	cur = &gc->objects;
	while (*cur)
	{
		if (!(*cur)->marked)
		{
			if ((*cur)->ptr)
			{
				free((*cur)->ptr);
				(*cur)->ptr = NULL;
				unreached = *cur;
				*cur = unreached->next;
				free(unreached);
			}
		}
		else
		{
			(*cur)->marked = 0;
			cur = &(*cur)->next;
		}
	}
}

void	gc_collect(t_gc *gc)
{
	gc_mark_all(gc);
	gc_sweep(gc);
}

t_gc	gc_new(void)
{
	t_gc	gc;

	gc = (t_gc){0};
	return (gc);
}

void	gc_destroy(t_gc *gc)
{
	t_gcobj	*cur;
	t_gcobj	*next;

	cur = gc->objects;
	while (cur)
	{
		free(cur->ptr);
		next = cur->next;
		free(cur);
		cur = next;
	}
}
