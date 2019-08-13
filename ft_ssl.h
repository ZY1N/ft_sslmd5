/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ssl.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yinzhang <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/28 21:08:54 by yinzhang          #+#    #+#             */
/*   Updated: 2019/07/28 21:08:56 by yinzhang         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_SSL_H
# define FT_SSL_H

# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <fcntl.h>
# include "./ft_printf/includes/ft_printf.h"
# include "./ft_printf/includes/libft.h"
# include <limits.h>
# include <math.h>

# define USAGE "usage: ft_ssl command [command opts] [command args]\n"

typedef enum	e_algo
{
	MD5 = 0,
	SHA256,
	SHA512,
	SHA224,
	INVALID,
}				t_algo;

typedef	struct	s_flags
{
	int		p;
	int		q;
	int		r;
	int		s;
	int		tffile;
	char	*filename;
	int		fd;
	char	*text;
	char	*textwithsflag;
	char	*stdinputtext;
	char	*emptytext;
}				t_flags;

typedef	struct	s_md5
{
	unsigned int a;
	unsigned int b;
	unsigned int c;
	unsigned int d;

	unsigned int a0;
	unsigned int b0;
	unsigned int c0;
	unsigned int d0;
}				t_md5;

typedef	struct	s_sha256
{
	unsigned int	h0;
	unsigned int	h1;
	unsigned int	h2;
	unsigned int	h3;
	unsigned int	h4;
	unsigned int	h5;
	unsigned int	h6;
	unsigned int	h7;
	unsigned int	a;
	unsigned int	b;
	unsigned int	c;
	unsigned int	d;
	unsigned int	e;
	unsigned int	f;
	unsigned int	g;
	unsigned int	h;
	int				count;
}				t_sha256;

typedef	struct	s_sha512
{
	long	h0;
	long	h1;
	long	h2;
	long	h3;
	long	h4;
	long	h5;
	long	h6;
	long	h7;
	long	a;
	long	b;
	long	c;
	long	d;
	long	e;
	long	f;
	long	g;
	long	h;
	int		count;
}				t_sha512;

typedef void	t_algorithmns(unsigned char *input, t_flags *options);

void			sha224(unsigned char *s, t_flags *options);
void			sha512(unsigned char *s, t_flags *options);
int				findsize(unsigned char *s);
int				reverse(int i);
void			initconsts(t_md5 *md5);
void			setvar(t_md5 *md5);
void			findmessagedigest(t_md5 *md5);
unsigned int	findblocksize(unsigned char *s);
uint32_t		rrot(uint32_t wrd, int n);
void			initvariables(t_sha256 *sha2);
void			block_bezero(unsigned int blocksize, unsigned char *g_block);
int				bigendianmemcopy(uint32_t *wrd, unsigned char *g_block, int z);
char			*ft_strcpy(char *dst, const char *src);
char			*extractfdtext(int n);
t_algo			findalgo(char *s);
void			initflags(t_flags *options);
char			*ld_stradd(char *s, char *c, int d);
void			ifunknown(char *s, t_flags *options);
void			badflagerror(void);
void			invalidfile(char *s, t_algo algo);
int				ft_strcmp(const char *s1, const char *s2);
int				ft_strcmpmod(const char *s1, const char *s2);
void			md5(unsigned char *s, t_flags *options);
void			printmd5(t_md5 *md5, t_flags *opt, unsigned char *s);
void			printsha256(t_sha256 *sha2, t_flags *opt, unsigned char *s);
void			sha256(unsigned char *s, t_flags *options);
unsigned int	findblocksize9(unsigned char *s);
uint32_t		rrot9(uint32_t wrd, int n);
void			initvariables9(t_sha256 *sha2);
void			block_bezero9(unsigned int blocksize, unsigned char *g_block);
int				bigendian9(uint32_t *wrd, unsigned char *g_block, int z);
void			multipleblockvar2series(t_sha256 *sha2);
void			multipleblockvar5series(t_sha512 *sha5);
void			printsha224(t_sha256 *sha2, t_flags *opt, unsigned char *s);
void			printsha512(t_sha512 *sha5, t_flags *opt, unsigned char *s);
uint64_t		rrot2(uint64_t wrd, int n);
unsigned int	findblocksizesha512(unsigned char *s);
void			initvarsha5(t_sha512 *sha5);
int				bigendianmemcopy2(uint64_t *wrd, unsigned char *g_block, int z);
#endif
