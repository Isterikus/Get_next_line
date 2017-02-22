/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkovalen <dkovalen@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/23 14:53:46 by dkovalen          #+#    #+#             */
/*   Updated: 2016/12/27 18:24:00 by dkovalen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include <fcntl.h>

# define BUFF_SIZE 10

int				get_next_line(const int fd, char **line);

typedef struct	s_lst
{
	int			fd;
	size_t		count;
	size_t		len;
	char		*str;
	void		*next;
}				t_lst;

#endif
