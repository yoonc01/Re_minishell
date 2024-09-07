/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyoyoon <hyoyoon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/07 14:17:28 by hyoyoon           #+#    #+#             */
/*   Updated: 2024/09/07 15:05:31 by hyoyoon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <unistd.h>
# include <stdlib.h>

typedef struct  s_node
{
    char            *str;
    struct s_node   *next;
    struct s_node   *prev;
}   t_node;

typedef struct s_deque
{
    t_node  *front;
    t_node  *rear;
    int     size;
}   t_deque;

t_deque *create_deque(void);
void    insert_front(t_deque *dq, char *str);
void    insert_rear(t_deque *dq, char *str);
void    delete_front(t_deque *dq);
void    delete_rear(t_deque *dq);

#endif