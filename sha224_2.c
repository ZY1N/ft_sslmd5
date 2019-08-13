/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sha224_2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yinzhang <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/07 23:50:48 by yinzhang          #+#    #+#             */
/*   Updated: 2019/08/07 23:50:49 by yinzhang         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl.h"

unsigned int	findblocksize9(unsigned char *s)
{
	int i;

	i = 0;
	while (s[i])
		i++;
	return (((i + 8) / 64 * 64 + 64) * 8);
}

uint32_t		rrot9(uint32_t wrd, int n)
{
	wrd = (wrd >> n) | (wrd << (32 - n));
	return (wrd);
}

void			initvariables9(t_sha256 *sha2)
{
	sha2->h0 = 0xc1059ed8;
	sha2->h1 = 0x367cd507;
	sha2->h2 = 0x3070dd17;
	sha2->h3 = 0xf70e5939;
	sha2->h4 = 0xffc00b31;
	sha2->h5 = 0x68581511;
	sha2->h6 = 0x64f98fa7;
	sha2->h7 = 0xbefa4fa4;
	sha2->a = 0xc1059ed8;
	sha2->b = 0x367cd507;
	sha2->c = 0x3070dd17;
	sha2->d = 0xf70e5939;
	sha2->e = 0xffc00b31;
	sha2->f = 0x68581511;
	sha2->g = 0x64f98fa7;
	sha2->h = 0xbefa4fa4;
	sha2->count = 0;
}

void			block_bezero9(unsigned int blocksize, unsigned char *g_block)
{
	unsigned int i;

	i = 0;
	while (i < blocksize)
	{
		g_block[i] = '\0';
		i++;
	}
}

int				bigendian9(uint32_t *wrd, unsigned char *g_block, int z)
{
	int x;
	int y;

	x = 0;
	y = 0;
	while (x < 16)
	{
		y = 0;
		while (y < 4)
		{
			wrd[x] = wrd[x] << 8 | g_block[z];
			z++;
			y++;
		}
		x++;
	}
	return (z);
}
