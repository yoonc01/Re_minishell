/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ycho2 <ycho2@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/27 20:14:29 by ycho2             #+#    #+#             */
/*   Updated: 2024/04/22 13:52:05 by ycho2            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H

# include <stdlib.h>
# include <unistd.h>
# include <stdio.h>
# include <stdarg.h>

typedef struct s_list
{
	void			*content;
	struct s_list	*next;
}t_list;

int		ft_isalpha(int c);
int		ft_isdigit(int c);
int		ft_isalnum(int c);
int		ft_isascii(int c);
int		ft_isprint(int c);

size_t	ft_strlen(const char *str);
void	*ft_memset(void *ptr, int value, size_t num);
void	ft_bzero(void *ptr, size_t size);
void	*ft_memcpy(void *dest, const void *src, size_t size);
void	*ft_memmove(void *dst, const void *src, size_t len);
size_t	ft_strlcpy(char *dest, const char *src, size_t size);
size_t	ft_strlcat(char *dest, const char *src, size_t size);
int		ft_strncmp(const char *s1, const char *s2, size_t n);

int		ft_toupper(int c);
int		ft_tolower(int c);
char	*ft_strchr(const char *str, int val);
char	*ft_strrchr(const char *str, int val);

void	*ft_memchr(const void *ptr, int val, size_t num);
int		ft_memcmp(const void *ptr1, const void *ptr2, size_t num);
char	*ft_strnstr(const char *str, const char *find, size_t len);
int		ft_atoi(const char *str);
int		ft_atoi16(const char *str);

void	*ft_calloc(size_t count, size_t size);
char	*ft_strdup(const char *s1);

char	*ft_substr(char const *s, unsigned int start, size_t len);
char	*ft_strjoin(char const *s1, char const *s2);
char	*ft_strtrim(char const *s1, char const *set);
char	**ft_split(char const *s, char c);
void	split_free(char **split);
char	*ft_itoa(int n);
char	*ft_strmapi(char const *s, char (*f)(unsigned int, char));
void	ft_striteri(char *s, void (*f)(unsigned int, char*));
void	ft_putchar_fd(char c, int fd);
void	ft_putstr_fd(char *s, int fd);
void	ft_putendl_fd(char *s, int fd);
void	ft_putnbr_fd(int n, int fd);

t_list	*ft_lstnew(void *content);
void	ft_lstadd_front(t_list **lst, t_list *new);
int		ft_lstsize(t_list *lst);
t_list	*ft_lstlast(t_list *lst);
void	ft_lstadd_back(t_list **lst, t_list *new);
void	ft_lstdelone(t_list *lst, void (*del)(void *));
void	ft_lstclear(t_list **lst, void (*del)(void *));
void	ft_lstiter(t_list *lst, void (*f)(void *));
t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *));

void	ft_malloc_err(void);

int		ft_conversion(char c, va_list ap);

int		ft_printf_char(va_list ap);
int		ft_printf_str(va_list ap);
int		ft_printf_addr(va_list ap);
int		ft_printf_dec(va_list ap);
int		ft_printf_u_dec(va_list ap);
int		ft_printf_hex(char c, va_list ap);

char	*ft_uitoa(unsigned int n);

int		ft_printf(const char *string, ...);

#endif
