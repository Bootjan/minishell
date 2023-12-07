/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bootjan <bootjan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/07 11:10:25 by tsteur            #+#    #+#             */
/*   Updated: 2023/12/07 13:32:37 by bootjan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	unset(int argc, char *argv[], char ***envp)
{
	int		i;
	
	i = 1;
	if (argc == 1)
		return (0);
	while (i < argc)
	{
		(void) argv;
		(void) envp;
		// remove(argv[i++], envp);
		i++;
	}
	return (0);
}
