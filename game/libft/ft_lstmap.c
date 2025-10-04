/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjouvenc <tjouvenc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/09 15:02:49 by tjouvenc          #+#    #+#             */
/*   Updated: 2024/12/10 17:54:42 by tjouvenc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static t_list	*create_list_of_same_size(t_list *lst)
{
	int		lstsize;
	int		i;
	t_list	*res;
	t_list	*cur;

	lstsize = ft_lstsize(lst);
	if (lstsize == 0)
		return (0);
	res = ft_lstnew(0);
	if (!res)
		return (0);
	i = 1;
	cur = res;
	while (i < lstsize)
	{
		cur->next = ft_lstnew(0);
		if (!cur->next)
		{
			ft_lstclear(&res, free);
			break ;
		}
		cur = cur->next;
		i++;
	}
	return (res);
}

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*res;
	t_list	*cur;

	(void)del;
	res = create_list_of_same_size(lst);
	cur = res;
	while (cur)
	{
		cur->content = f(lst->content);
		cur = cur->next;
		lst = lst->next;
	}
	return (res);
}
