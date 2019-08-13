/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   md5.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yinzhang <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/16 19:25:04 by yinzhang          #+#    #+#             */
/*   Updated: 2019/07/16 19:25:05 by yinzhang         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl.h"

unsigned char	*g_block;

uint32_t		g_words[16];

unsigned int	g_rottable[64] = {
	0xd76aa478, 0xe8c7b756, 0x242070db, 0xc1bdceee,
	0xf57c0faf, 0x4787c62a, 0xa8304613, 0xfd469501,
	0x698098d8, 0x8b44f7af, 0xffff5bb1, 0x895cd7be,
	0x6b901122, 0xfd987193, 0xa679438e, 0x49b40821,
	0xf61e2562, 0xc040b340, 0x265e5a51, 0xe9b6c7aa,
	0xd62f105d, 0x02441453, 0xd8a1e681, 0xe7d3fbc8,
	0x21e1cde6, 0xc33707d6, 0xf4d50d87, 0x455a14ed,
	0xa9e3e905, 0xfcefa3f8, 0x676f02d9, 0x8d2a4c8a,
	0xfffa3942, 0x8771f681, 0x6d9d6122, 0xfde5380c,
	0xa4beea44, 0x4bdecfa9, 0xf6bb4b60, 0xbebfbc70,
	0x289b7ec6, 0xeaa127fa, 0xd4ef3085, 0x04881d05,
	0xd9d4d039, 0xe6db99e5, 0x1fa27cf8, 0xc4ac5665,
	0xf4292244, 0x432aff97, 0xab9423a7, 0xfc93a039,
	0x655b59c3, 0x8f0ccc92, 0xffeff47d, 0x85845dd1,
	0x6fa87e4f, 0xfe2ce6e0, 0xa3014314, 0x4e0811a1,
	0xf7537e82, 0xbd3af235, 0x2ad7d2bb, 0xeb86d391};

unsigned int	g_ctable[64] = {7, 12, 17, 22, 7, 12, 17, 22, 7,
	12, 17, 22, 7, 12, 17, 22,
	5, 9, 14, 20, 5, 9, 14, 20, 5, 9, 14, 20, 5, 9, 14, 20,
	4, 11, 16, 23, 4, 11, 16, 23, 4, 11, 16, 23, 4, 11, 16, 23,
	6, 10, 15, 21, 6, 10, 15, 21, 6, 10, 15, 21, 6, 10, 15, 21};

static int		blockprocessing(unsigned char *s)
{
	int		sizeblocks;
	long	i;
	long	x;
	long	y;

	x = 8;
	i = 0;
	sizeblocks = findsize(s);
	g_block = (unsigned char *)ft_strnew(sizeblocks);
	while (s[i])
	{
		g_block[i] = s[i];
		i++;
	}
	g_block[i] = 1 << 7;
	y = i * 8;
	while (x > 0)
	{
		g_block[sizeblocks - x] = y >> (8 * (8 - x));
		x--;
	}
	return (sizeblocks * 8);
}

static void		loadwords(int i)
{
	int x;

	x = 0;
	while (x < 16)
	{
		g_words[x] = 0;
		g_words[x] += g_block[(i - 1) * 64 + x * 4 + 0];
		g_words[x] += g_block[(i - 1) * 64 + x * 4 + 1] << 8;
		g_words[x] += g_block[(i - 1) * 64 + x * 4 + 2] << 16;
		g_words[x] += g_block[(i - 1) * 64 + x * 4 + 3] << 24;
		x++;
	}
}

uint32_t		mainmd5part2(uint32_t f, uint32_t g, int i, t_md5 *md5)
{
	f = f + md5->a + g_rottable[i] + g_words[g];
	md5->a = md5->d;
	md5->d = md5->c;
	md5->c = md5->b;
	md5->b += ((f << g_ctable[i]) | (f >> (32 - g_ctable[i])));
	return (f);
}

void			mainmd5(t_md5 *md5, int i, uint32_t f, uint32_t g)
{
	setvar(md5);
	while (i++ < 63)
	{
		if ((g = i) < 16)
			f = (md5->b & md5->c) | ((~md5->b) & md5->d);
		else if (i < 32)
		{
			f = (md5->d & md5->b) | ((~md5->d) & md5->c);
			g = (5 * i + 1) % 16;
		}
		else if (i < 48)
		{
			f = md5->b ^ md5->c ^ md5->d;
			g = (3 * i + 5) % 16;
		}
		else if (i < 64)
		{
			f = md5->c ^ (md5->b | (~md5->d));
			g = (7 * i) % 16;
		}
		f = mainmd5part2(f, g, i, md5);
	}
	findmessagedigest(md5);
}

void			md5(unsigned char *s, t_flags *options)
{
	int		i;
	int		blocksize;
	t_md5	*md5;

	md5 = malloc(sizeof(t_md5));
	i = 1;
	initconsts(md5);
	blocksize = blockprocessing(s);
	while (blocksize / i >= 512)
	{
		loadwords(i);
		mainmd5(md5, -1, 0, 0);
		i++;
	}
	md5->a0 = reverse(md5->a0);
	md5->b0 = reverse(md5->b0);
	md5->c0 = reverse(md5->c0);
	md5->d0 = reverse(md5->d0);
	printmd5(md5, options, s);
	free(g_block);
	free(md5);
}
