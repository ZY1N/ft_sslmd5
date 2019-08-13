/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sha256.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yinzhang <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/25 12:56:44 by yinzhang          #+#    #+#             */
/*   Updated: 2019/07/25 12:56:46 by yinzhang         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl.h"

unsigned int	g_k[64] = {
	0x428a2f98, 0x71374491, 0xb5c0fbcf, 0xe9b5dba5, 0x3956c25b, 0x59f111f1,
	0x923f82a4, 0xab1c5ed5, 0xd807aa98, 0x12835b01, 0x243185be, 0x550c7dc3,
	0x72be5d74, 0x80deb1fe, 0x9bdc06a7, 0xc19bf174, 0xe49b69c1, 0xefbe4786,
	0x0fc19dc6, 0x240ca1cc, 0x2de92c6f, 0x4a7484aa, 0x5cb0a9dc, 0x76f988da,
	0x983e5152, 0xa831c66d, 0xb00327c8, 0xbf597fc7, 0xc6e00bf3, 0xd5a79147,
	0x06ca6351, 0x14292967, 0x27b70a85, 0x2e1b2138, 0x4d2c6dfc, 0x53380d13,
	0x650a7354, 0x766a0abb, 0x81c2c92e, 0x92722c85, 0xa2bfe8a1, 0xa81a664b,
	0xc24b8b70, 0xc76c51a3, 0xd192e819, 0xd6990624, 0xf40e3585, 0x106aa070,
	0x19a4c116, 0x1e376c08, 0x2748774c, 0x34b0bcb5, 0x391c0cb3, 0x4ed8aa4a,
	0x5b9cca4f, 0x682e6ff3, 0x748f82ee, 0x78a5636f, 0x84c87814, 0x8cc70208,
	0x90befffa, 0xa4506ceb, 0xbef9a3f7, 0xc67178f2};

unsigned char	*g_block;

void			blockprocessing(unsigned int blocksize, unsigned char *s)
{
	unsigned int	strlen;
	long			length64;

	strlen = ft_strlen((const char *)s);
	g_block = (unsigned char *)malloc(blocksize);
	block_bezero(blocksize, g_block);
	g_block = (unsigned char *)ft_strcpy((char *)g_block, (const char *)s);
	g_block[strlen] = 128;
	length64 = strlen * 8;
	g_block[blocksize - 8] = (length64 >> 56);
	g_block[blocksize - 7] = (length64 >> 48);
	g_block[blocksize - 6] = (length64 >> 40);
	g_block[blocksize - 5] = (length64 >> 32);
	g_block[blocksize - 4] = (length64 >> 24);
	g_block[blocksize - 3] = (length64 >> 16);
	g_block[blocksize - 2] = (length64 >> 8);
	g_block[blocksize - 1] = (length64);
}

uint32_t		*loadwords(t_sha256 *sha2)
{
	int				i;
	uint32_t		s0;
	uint32_t		s1;
	uint32_t		*wrd;

	i = 16;
	wrd = malloc(sizeof(uint32_t) * 64);
	sha2->count = bigendianmemcopy(wrd, g_block, sha2->count);
	while (i < 64)
	{
		s0 = rrot(wrd[i - 15], 7) ^ rrot(wrd[i - 15], 18) ^ (wrd[i - 15] >> 3);
		s1 = rrot(wrd[i - 2], 17) ^ rrot(wrd[i - 2], 19) ^ (wrd[i - 2] >> 10);
		wrd[i] = wrd[i - 16] + s0 + wrd[i - 7] + s1;
		i++;
	}
	return (wrd);
}

void			addcompressedchunktohash(t_sha256 *sha2)
{
	sha2->h0 = sha2->h0 + sha2->a;
	sha2->h1 = sha2->h1 + sha2->b;
	sha2->h2 = sha2->h2 + sha2->c;
	sha2->h3 = sha2->h3 + sha2->d;
	sha2->h4 = sha2->h4 + sha2->e;
	sha2->h5 = sha2->h5 + sha2->f;
	sha2->h6 = sha2->h6 + sha2->g;
	sha2->h7 = sha2->h7 + sha2->h;
}

void			sha256algo(uint32_t *wrd, t_sha256 *sha2, int i, uint32_t s1)
{
	uint32_t		ch;
	uint32_t		temp1;
	uint32_t		s0;
	uint32_t		maj;
	uint32_t		temp2;

	while (i < 64)
	{
		s1 = rrot(sha2->e, 6) ^ rrot(sha2->e, 11) ^ rrot(sha2->e, 25);
		ch = (sha2->e & sha2->f) ^ ((~sha2->e) & sha2->g);
		temp1 = sha2->h + s1 + ch + g_k[i] + wrd[i];
		s0 = rrot(sha2->a, 2) ^ rrot(sha2->a, 13) ^ rrot(sha2->a, 22);
		maj = (sha2->a & sha2->b) ^ (sha2->a & sha2->c) ^ (sha2->b & sha2->c);
		temp2 = s0 + maj;
		sha2->h = sha2->g;
		sha2->g = sha2->f;
		sha2->f = sha2->e;
		sha2->e = sha2->d + temp1;
		sha2->d = sha2->c;
		sha2->c = sha2->b;
		sha2->b = sha2->a;
		sha2->a = temp1 + temp2;
		i++;
	}
	addcompressedchunktohash(sha2);
}

void			sha256(unsigned char *s, t_flags *options)
{
	unsigned int	i;
	unsigned int	blocksize;
	uint32_t		*wrd;
	t_sha256		*sha2;

	i = 0;
	sha2 = malloc(sizeof(t_sha256));
	initvariables(sha2);
	sha2->count = 0;
	blocksize = findblocksize(s);
	blockprocessing(blocksize / 8, s);
	while (blocksize / 512 > i)
	{
		multipleblockvar2series(sha2);
		wrd = loadwords(sha2);
		sha256algo(wrd, sha2, 0, 0);
		free(wrd);
		i++;
	}
	printsha256(sha2, options, s);
	free(g_block);
	free(sha2);
}
