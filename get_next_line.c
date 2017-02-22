/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkovalen <dkovalen@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/23 15:06:25 by dkovalen          #+#    #+#             */
/*   Updated: 2016/12/27 18:22:57 by dkovalen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include "libft.h"

char	**ft_split_again(char *str)
{
	int		i;
	int		j;
	int		end;
	char	**rez;

	i = -1;
	j = 1;
	while (str[++i] != '\0')
		if (str[i] == '\n' && str[i + 1] != '\0')
			j++;
	rez = (char **)malloc(sizeof(char *) * (j + 1));
	rez[j--] = NULL;
	end = i;
	if (str[i - 1] == '\n')
		end = i - 1;
	while (i--)
	{
		if (i == 0 || str[i - 1] == '\n')
		{
			if ((rez[j--] = ft_strsub(str, i, end - i)) == 0)
				return (NULL);
			end = i - 1;
		}
	}
	return (rez);
}

char	*ft_realloc(char *eternal, int sz)
{
	char	*copy;
	size_t	i;
	size_t	size;

	if (eternal == NULL)
	{
		eternal = (char *)malloc(sizeof(char) * (sz + 1));
		return (eternal);
	}
	size = ft_strlen(eternal);
	copy = (char *)malloc(sizeof(char) * (size + sz));
	if (copy == NULL)
		return (NULL);
	i = 0;
	while (i < size)
	{
		copy[i] = eternal[i];
		i++;
	}
	copy[i] = '\0';
	return (copy);
}

int		create(t_lst **temp, const int fd)
{
	t_lst	*new;
	char	*test;
	int		rd;

	test = (char *)malloc(sizeof(char) * (BUFF_SIZE));
	new = (t_lst *)malloc(sizeof(t_lst));
	new->str = (char *)malloc(sizeof(char) * BUFF_SIZE);
	while ((rd = read(fd, test, BUFF_SIZE)) > 0)
	{
		new->str = ft_realloc(new->str, rd);
		ft_strncat(new->str, test, rd);
		ft_bzero(test, BUFF_SIZE);
	}
	if (new->str == NULL || rd < 0)
		return (-1);
	new->count = 0;
	new->fd = fd;
	new->len = ft_strlen(new->str);
	new->next = NULL;
	if (*temp != NULL)
		(*temp)->next = new;
	else
		(*temp) = new;
	return (1);
}

int		rez(t_lst *elem, char **line)
{
	*(line) = NULL;
	if (elem->str[elem->len] != '\0')
		elem->str[elem->len] = '\0';
	if (ft_split_again(elem->str)[elem->count])
		*(line) = ft_split_again(elem->str)[elem->count];
	else
	{
		*(line) = ft_strnew(0);
		return (0);
	}
	elem->count++;
	return (1);
}

int		get_next_line(const int fd, char **line)
{
	static t_lst	*beg;
	t_lst			*temp;
	int				ret;

	if (beg == NULL)
	{
		if ((ret = create(&beg, fd)) <= 0)
			return (ret);
	}
	else
	{
		temp = beg;
		while (temp)
		{
			if (temp->fd == fd)
				return (rez(temp, line));
			if (temp->next == NULL)
				break ;
			temp = temp->next;
		}
		if ((ret = create(&temp, fd)) <= 0)
			return (ret);
		return (rez(temp->next, line));
	}
	return (rez(beg, line));
}
