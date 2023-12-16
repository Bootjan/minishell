/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_free_str.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: bschaafs <bschaafs@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/12/10 16:19:44 by bschaafs      #+#    #+#                 */
/*   Updated: 2023/12/10 16:20:52 by bschaafs      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_free_str(char **str)
{
	if (!str || !*str)
		return ;
	free(*str);
	*str = NULL;
}
