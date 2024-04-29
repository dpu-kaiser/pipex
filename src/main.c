/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkaiser <dkaiser@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/29 13:35:21 by dkaiser           #+#    #+#             */
/*   Updated: 2024/04/29 15:27:14 by dkaiser          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int main(int argc, char *argv[]) {
	if (argc != 5)
		return (1);

	// Read content of file1 (argv[1])
	// Execute cmd1 (argv[2]) with file1 on stdin
	// pipe the output of cmd1 into cmd2
	// Execute cmd2 (argv[3]) with the piped input on stdin
	// Write output of cmd2 into file2 (argv[4])
}
