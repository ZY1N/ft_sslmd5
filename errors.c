/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yinzhang <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/04 00:07:04 by yinzhang          #+#    #+#             */
/*   Updated: 2019/08/04 00:07:06 by yinzhang         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl.h"

void	ifunknown(char *s, t_flags *options)
{
	ft_printf("ft_ssl: Error: '%s' is an invalid command.\n\nStandard \
	commands:\n\nMessage Digest commands:\nmd5\nsha256\n\nCipher \
	commands:\n", s);
	free(options);
	exit(-1);
}

void	badflagerror(void)
{
	ft_printf("Accepted flags: -p -q -r -s\n");
	exit(-1);
}

void	invalidfile(char *s, t_algo algo)
{
	if (algo == MD5)
		ft_printf("ft_ssl: md5: %s: No such file or directory\n", s);
	else
		ft_printf("ft_ssl: sha256: %s: No such file or directory\n", s);
}
