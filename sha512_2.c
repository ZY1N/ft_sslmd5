/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sha512_2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yinzhang <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/08 00:53:34 by yinzhang          #+#    #+#             */
/*   Updated: 2019/08/08 00:53:36 by yinzhang         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl.h"

uint64_t		rrot2(uint64_t wrd, int n)
{
	wrd = (wrd >> n) | (wrd << (64 - n));
	return (wrd);
}

unsigned int	findblocksizesha512(unsigned char *s)
{
	int i;

	i = 0;
	while (s[i])
		i++;
	return (((i + 16) / 128 * 128 + 128) * 8);
}

void			initvarsha5(t_sha512 *sha5)
{
	sha5->h0 = 0x6a09e667f3bcc908;
	sha5->h1 = 0xbb67ae8584caa73b;
	sha5->h2 = 0x3c6ef372fe94f82b;
	sha5->h3 = 0xa54ff53a5f1d36f1;
	sha5->h4 = 0x510e527fade682d1;
	sha5->h5 = 0x9b05688c2b3e6c1f;
	sha5->h6 = 0x1f83d9abfb41bd6b;
	sha5->h7 = 0x5be0cd19137e2179;
	sha5->a = 0x6a09e667f3bcc908;
	sha5->b = 0xbb67ae8584caa73b;
	sha5->c = 0x3c6ef372fe94f82b;
	sha5->d = 0xa54ff53a5f1d36f1;
	sha5->e = 0x510e527fade682d1;
	sha5->f = 0x9b05688c2b3e6c1f;
	sha5->g = 0x1f83d9abfb41bd6b;
	sha5->h = 0x5be0cd19137e2179;
}

int				bigendianmemcopy2(uint64_t *wrd, unsigned char *g_block, int z)
{
	int x;
	int y;

	x = 0;
	y = 0;
	while (x < 16)
	{
		y = 0;
		while (y < 8)
		{
			wrd[x] = wrd[x] << 8 | g_block[z];
			z++;
			y++;
		}
		x++;
	}
	return (z);
}
