/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reader.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdorner <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/04 06:42:41 by jdorner           #+#    #+#             */
/*   Updated: 2018/07/25 12:49:21 by jdorner          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

t_list	*readfile(int argc, char **argv, t_list *readcontents)
{
	int		fd;
	char	*line;

	readcontents = NULL;
	if (argc == 2)
	{
		fd = open(argv[1], O_RDONLY);
		if (fd > 0)
		{
			line = NULL;
			while ((get_next_line(fd, &line)) > 0)
			{
				ft_strcat(line, "\n");
				ft_lstadd(&readcontents, ft_lstnew(line, ft_strlen(line) + 1));
				ft_strdel(&line);
			}
		}
	}
	if (readcontents != NULL)
		close(fd);
	return (readcontents);
}

void	reverselst(t_list **lst)
{
	t_list	*prev;
	t_list	*current;
	t_list	*next;

	current = *lst;
	prev = NULL;
	next = NULL;
	while (current != NULL)
	{
		next = current->next;
		current->next = prev;
		prev = current;
		current = next;
	}
	*lst = prev;
}

int		lstcount(t_list *readcontents)
{
	int	size;

	size = 0;
	while (readcontents != NULL)
	{
		size++;
		readcontents = readcontents->next;
	}
	return (size);
}

int		legalfilewidth(char *str)
{
	char	**split;
	int		i;
	int		legalcount;

	split = ft_strsplit(str, ' ');
	i = 0;
	legalcount = 0;
	while (split[i])
	{
		i++;
		legalcount++;
	}
	cleansplit(&split);
	return (legalcount);
}

int		readmap(int argc, char **argv, t_mlx *mlx)
{
	t_list		*readcontents;
	int			width;
	int			height;

	if (!(readcontents = readfile(argc, argv, readcontents)))
		return (-1);
	reverselst(&readcontents);
	width = legalfilewidth(readcontents->content);
	height = lstcount(readcontents);
	setmap(mlx, readcontents, width, height);
	ft_lstfree(readcontents);
	return (0);
}
