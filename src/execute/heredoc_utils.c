/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyoyoon <hyoyoon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/23 17:57:39 by ycho2             #+#    #+#             */
/*   Updated: 2024/10/03 15:14:02 by hyoyoon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	ft_read_attach(int fd, char **pout, t_buf *buf_case);
static int	ft_read_line(int fd, t_buf *buf_case);
static int	ft_attach_nl(char **pout, t_buf *buf_case);
static char	*gnl_strjoin(char *out, t_buf *buf_case, int attach_len);

char	*get_next_line(int fd)
{
	static t_buf	buf_arr[OPEN_MAX];
	char			*out;
	int				flag;

	if (fd < 0 || fd >= OPEN_MAX || BUFFER_SIZE <= 0)
		return (NULL);
	out = (char *)malloc(sizeof(char));
	if (out == NULL)
		malloc_fail();
	out[0] = 0;
	while (1)
	{
		flag = ft_read_attach(fd, &out, &buf_arr[fd]);
		if (flag == 1 || (flag == 0 && *out != 0))
			return (out);
		else if (flag == -1 || flag == 0)
		{
			free (out);
			return (NULL);
		}
	}
}

static int	ft_read_attach(int fd, char **pout, t_buf *buf_case)
{
	int	flag;
	int	read_len;

	read_len = 1;
	if ((buf_case -> used) == 0)
	{
		buf_case -> used = 1;
		buf_case -> idx = -1;
	}
	if ((buf_case -> idx) == -1)
		read_len = ft_read_line(fd, buf_case);
	if (read_len == -1 || read_len == 0)
		return (read_len);
	else
	{
		flag = ft_attach_nl(pout, buf_case);
		return (flag);
	}
}

static int	ft_read_line(int fd, t_buf *buf_case)
{
	int	flag;

	flag = read(fd, buf_case->read_buf, BUFFER_SIZE);
	if (flag != -1)
	{
		buf_case->read_buf[flag] = 0;
		(buf_case->idx) = 0;
	}
	return (flag);
}

static int	ft_attach_nl(char **pout, t_buf *buf_case)
{
	int		i;
	char	*concat_out;

	i = 0;
	while (buf_case->read_buf[(buf_case->idx) + i])
	{
		if (buf_case->read_buf[(buf_case->idx) + i] == '\n')
		{
			concat_out = gnl_strjoin(*pout, buf_case, ++i);
			if (concat_out == NULL)
				return (-1);
			free (*pout);
			*pout = concat_out;
			(buf_case->idx) += i;
			return (1);
		}
		i++;
	}
	concat_out = gnl_strjoin(*pout, buf_case, i);
	if (concat_out == NULL)
		return (-1);
	free (*pout);
	*pout = concat_out;
	(buf_case->idx) = -1;
	return (2);
}

static char	*gnl_strjoin(char *out, t_buf *buf_case, int attach_len)
{
	int		out_len;
	char	*concat_str;

	out_len = ft_strlen(out);
	concat_str = (char *)malloc(sizeof(char) * (attach_len + out_len + 1));
	if (!concat_str)
		malloc_fail();
	concat_str[0] = 0;
	ft_strlcat(concat_str, out, out_len + 1);
	ft_strlcat(concat_str, buf_case->read_buf
		+ (buf_case->idx), out_len + attach_len + 1);
	return (concat_str);
}
