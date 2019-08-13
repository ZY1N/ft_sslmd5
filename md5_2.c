/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   md5_2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yinzhang <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/04 01:31:33 by yinzhang          #+#    #+#             */
/*   Updated: 2019/08/04 01:31:35 by yinzhang         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl.h"

void	findmessagedigest(t_md5 *md5)
{
	md5->a0 = md5->a0 + md5->a;
	md5->b0 = md5->b0 + md5->b;
	md5->c0 = md5->c0 + md5->c;
	md5->d0 = md5->d0 + md5->d;
}

void	setvar(t_md5 *md5)
{
	md5->a = md5->a0;
	md5->b = md5->b0;
	md5->c = md5->c0;
	md5->d = md5->d0;
}

int		findsize(unsigned char *s)
{
	int i;
	int x;

	x = 0;
	i = 0;
	while (s[i])
		i++;
	x = ((i + 8) / 64) * 64 + 64;
	return (x);
}

int		reverse(int i)
{
	int new;

	new = 0;
	new += i << 24 & 0xff000000;
	new += i << 8 & 0xff0000;
	new += i >> 8 & 0xff00;
	new += i >> 24 & 0xff;
	return (new);
}

void	initconsts(t_md5 *md5)
{
	md5->a = 0x67452301;
	md5->b = 0xefcdab89;
	md5->c = 0x98badcfe;
	md5->d = 0x10325476;
	md5->a0 = 0x67452301;
	md5->b0 = 0xefcdab89;
	md5->c0 = 0x98badcfe;
	md5->d0 = 0x10325476;
}
