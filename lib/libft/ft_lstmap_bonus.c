/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ycho2 <ycho2@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/31 20:10:41 by ycho2             #+#    #+#             */
/*   Updated: 2023/11/04 18:48:06 by ycho2            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*node;
	t_list	*temp_node;
	void	*temp_content;

	temp_node = NULL;
	node = NULL;
	while (lst)
	{
		temp_content = f(lst->content);
		temp_node = ft_lstnew(temp_content);
		if (temp_node == 0)
		{
			del(temp_content);
			ft_lstclear(&node, del);
			return (0);
		}
		ft_lstadd_back(&node, temp_node);
		lst = lst->next;
	}
	temp_node = 0;
	return (node);
}
