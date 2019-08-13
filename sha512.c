/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sha512.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yinzhang <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/08 00:33:36 by yinzhang          #+#    #+#             */
/*   Updated: 2019/08/08 00:33:37 by yinzhang         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl.h"

static long	g_k[80] = {0x428a2f98d728ae22, 0x7137449123ef65cd,
	0xb5c0fbcfec4d3b2f, 0xe9b5dba58189dbbc, 0x3956c25bf348b538,
	0x59f111f1b605d019, 0x923f82a4af194f9b, 0xab1c5ed5da6d8118,
	0xd807aa98a3030242, 0x12835b0145706fbe, 0x243185be4ee4b28c,
	0x550c7dc3d5ffb4e2, 0x72be5d74f27b896f, 0x80deb1fe3b1696b1,
	0x9bdc06a725c71235, 0xc19bf174cf692694, 0xe49b69c19ef14ad2,
	0xefbe4786384f25e3, 0x0fc19dc68b8cd5b5, 0x240ca1cc77ac9c65,
	0x2de92c6f592b0275, 0x4a7484aa6ea6e483, 0x5cb0a9dcbd41fbd4,
	0x76f988da831153b5, 0x983e5152ee66dfab, 0xa831c66d2db43210,
	0xb00327c898fb213f, 0xbf597fc7beef0ee4, 0xc6e00bf33da88fc2,
	0xd5a79147930aa725, 0x06ca6351e003826f, 0x142929670a0e6e70,
	0x27b70a8546d22ffc, 0x2e1b21385c26c926, 0x4d2c6dfc5ac42aed,
	0x53380d139d95b3df, 0x650a73548baf63de, 0x766a0abb3c77b2a8,
	0x81c2c92e47edaee6, 0x92722c851482353b, 0xa2bfe8a14cf10364,
	0xa81a664bbc423001, 0xc24b8b70d0f89791, 0xc76c51a30654be30,
	0xd192e819d6ef5218, 0xd69906245565a910, 0xf40e35855771202a,
	0x106aa07032bbd1b8, 0x19a4c116b8d2d0c8, 0x1e376c085141ab53,
	0x2748774cdf8eeb99, 0x34b0bcb5e19b48a8, 0x391c0cb3c5c95a63,
	0x4ed8aa4ae3418acb, 0x5b9cca4f7763e373, 0x682e6ff3d6b2b8a3,
	0x748f82ee5defb2fc, 0x78a5636f43172f60, 0x84c87814a1f0ab72,
	0x8cc702081a6439ec, 0x90befffa23631e28, 0xa4506cebde82bde9,
	0xbef9a3f7b2c67915, 0xc67178f2e372532b, 0xca273eceea26619c,
	0xd186b8c721c0c207, 0xeada7dd6cde0eb1e, 0xf57d4f7fee6ed178,
	0x06f067aa72176fba, 0x0a637dc5a2c898a6, 0x113f9804bef90dae,
	0x1b710b35131c471b, 0x28db77f523047d84, 0x32caab7b40c72493,
	0x3c9ebe0a15c9bebc, 0x431d67c49c100d4c, 0x4cc5d4becb3e42b6,
	0x597f299cfc657e2a, 0x5fcb6fab3ad6faec, 0x6c44198c4a475817};

unsigned char	*g_block;

static void			blockprocessing(unsigned int blocksize, unsigned char *s)
{
	unsigned int	strlen;
	__uint128_t		length128;
	int				x;

	x = 16;
	strlen = ft_strlen((const char *)s);
	g_block = (unsigned char *)malloc(blocksize);
	block_bezero(blocksize, g_block);
	g_block = (unsigned char *)ft_strcpy((char *)g_block, (const char *)s);
	g_block[strlen] = 128;
	length128 = strlen * 8;
	while (x > 0)
	{
		g_block[blocksize - x] = length128 >> (8 * (x - 1));
		x--;
	}
}

static uint64_t		*loadwords(t_sha512 *sha5)
{
	int				i;
	uint64_t		s0;
	uint64_t		s1;
	uint64_t		*wrd;

	i = 16;
	wrd = malloc(sizeof(uint64_t) * 80);
	sha5->count = bigendianmemcopy2(wrd, g_block, sha5->count);
	while (i < 80)
	{
		s0 = rrot2(wrd[i - 15], 1) ^ rrot2(wrd[i - 15], 8) ^ (wrd[i - 15] >> 7);
		s1 = rrot2(wrd[i - 2], 19) ^ rrot2(wrd[i - 2], 61) ^ (wrd[i - 2] >> 6);
		wrd[i] = wrd[i - 16] + s0 + wrd[i - 7] + s1;
		i++;
	}
	return (wrd);
}

static void			addcompressedchunktohash(t_sha512 *sha5)
{
	sha5->h0 = sha5->h0 + sha5->a;
	sha5->h1 = sha5->h1 + sha5->b;
	sha5->h2 = sha5->h2 + sha5->c;
	sha5->h3 = sha5->h3 + sha5->d;
	sha5->h4 = sha5->h4 + sha5->e;
	sha5->h5 = sha5->h5 + sha5->f;
	sha5->h6 = sha5->h6 + sha5->g;
	sha5->h7 = sha5->h7 + sha5->h;
}

void				sha556algo(uint64_t *w, t_sha512 *sha5, int i, uint64_t s1)
{
	uint64_t		ch;
	uint64_t		temp1;
	uint64_t		s0;
	uint64_t		maj;
	uint64_t		temp2;

	while (i < 80)
	{
		s1 = rrot2(sha5->e, 14) ^ rrot2(sha5->e, 18) ^ rrot2(sha5->e, 41);
		ch = (sha5->e & sha5->f) ^ ((~sha5->e) & sha5->g);
		temp1 = sha5->h + s1 + ch + g_k[i] + w[i];
		s0 = rrot2(sha5->a, 28) ^ rrot2(sha5->a, 34) ^ rrot2(sha5->a, 39);
		maj = (sha5->a & sha5->b) ^ (sha5->a & sha5->c) ^ (sha5->b & sha5->c);
		temp2 = s0 + maj;
		sha5->h = sha5->g;
		sha5->g = sha5->f;
		sha5->f = sha5->e;
		sha5->e = sha5->d + temp1;
		sha5->d = sha5->c;
		sha5->c = sha5->b;
		sha5->b = sha5->a;
		sha5->a = temp1 + temp2;
		i++;
	}
	addcompressedchunktohash(sha5);
}

void				sha512(unsigned char *s, t_flags *options)
{
	unsigned int	i;
	unsigned int	blocksize;
	uint64_t		*wrd;
	t_sha512		*sha5;

	i = 0;
	sha5 = malloc(sizeof(t_sha512));
	initvarsha5(sha5);
	blocksize = findblocksizesha512(s);
	blockprocessing(blocksize / 8, s);
	sha5->count = 0;
	while (blocksize / 1024 > i)
	{
		multipleblockvar5series(sha5);
		wrd = loadwords(sha5);
		sha556algo(wrd, sha5, 0, 0);
		free(wrd);
		i++;
	}
	printsha512(sha5, options, s);
	free(g_block);
	free(sha5);
}
