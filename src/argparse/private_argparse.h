/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   private_argparse.h                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmuranak <tmuranak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/07 19:30:33 by tmuranak          #+#    #+#             */
/*   Updated: 2024/11/07 19:37:07 by tmuranak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PRIVATE_ARGPARSE_H
# define PRIVATE_ARGPARSE_H

// int count_cmd_args(char *str);
// char **get_cmd(char *str);
char	***get_cmds(int argc, char *argv[]);
void	clear_cmds(int argc, char ***cmds);

#endif
