/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yinzhang <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/04 20:30:50 by yinzhang          #+#    #+#             */
/*   Updated: 2019/08/04 20:30:52 by yinzhang         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl.h"

void	freestuff(t_flags *opt)
{
	if (opt->text != NULL)
		free(opt->text);
	if (opt->stdinputtext != NULL)
		free(opt->stdinputtext);
	if (opt->emptytext != NULL)
		free(opt->emptytext);
	opt->text = NULL;
	opt->textwithsflag = NULL;
	opt->stdinputtext = NULL;
	opt->emptytext = NULL;
}

void	printmd5(t_md5 *md5, t_flags *opt, unsigned char *s)
{
	if (opt->p == 1)
		ft_printf("%s", s);
	if (opt->filename != NULL && opt->r == 0 && opt->q == 0 && opt->p != 1)
	{
		ft_printf("MD5 (%s) = ", opt->filename);
	}
	if (opt->s == 1 && opt->q != 1 && opt->r != 1)
	{
		ft_printf("MD5 (\"%s\") = ", opt->textwithsflag);
	}
	ft_printf("%.8x%.8x%.8x%.8x", md5->a0, md5->b0, md5->c0, md5->d0);
	if (opt->s == 1 && opt->q != 1 && opt->r == 1)
	{
		ft_printf(" \"%s\"", opt->textwithsflag);
	}
	if (opt->r == 1 && opt->q == 0 && opt->filename != NULL && opt->p != 1)
		ft_printf(" %s", opt->filename);
	ft_printf("\n");
	if (opt->p == 1)
		opt->p = 2;
	freestuff(opt);
}

void	printsha256(t_sha256 *sha2, t_flags *opt, unsigned char *s)
{
	if (opt->p == 1)
		ft_printf("%s", s);
	if (opt->filename != NULL && opt->r == 0 && opt->q == 0 && opt->p != 1)
	{
		ft_printf("SHA256 (%s) = ", opt->filename);
	}
	if (opt->s == 1 && opt->q != 1 && opt->r != 1)
	{
		ft_printf("SHA256 (\"%s\") = ", opt->textwithsflag);
	}
	ft_printf("%.8x%.8x%.8x%.8x%.8x%.8x%.8x%.8x", sha2->h0, sha2->h1, sha2->h2,
	sha2->h3, sha2->h4, sha2->h5, sha2->h6, sha2->h7);
	if (opt->s == 1 && opt->q != 1 && opt->r == 1)
	{
		ft_printf(" \"%s\"", opt->textwithsflag);
	}
	if (opt->r == 1 && opt->q == 0 && opt->filename != NULL && opt->p != 1)
		ft_printf(" %s", opt->filename);
	ft_printf("\n");
	if (opt->p == 1)
		opt->p = 2;
	freestuff(opt);
}

void	printsha224(t_sha256 *sha2, t_flags *opt, unsigned char *s)
{
	if (opt->p == 1)
		ft_printf("%s", s);
	if (opt->filename != NULL && opt->r == 0 && opt->q == 0 && opt->p != 1)
	{
		ft_printf("SHA224 (%s) = ", opt->filename);
	}
	if (opt->s == 1 && opt->q != 1 && opt->r != 1)
	{
		ft_printf("SHA224 (\"%s\") = ", opt->textwithsflag);
	}
	ft_printf("%.8x%.8x%.8x%.8x%.8x%.8x%.8x", sha2->h0, sha2->h1, sha2->h2,
	sha2->h3, sha2->h4, sha2->h5, sha2->h6);
	if (opt->s == 1 && opt->q != 1 && opt->r == 1)
	{
		ft_printf(" \"%s\"", opt->textwithsflag);
	}
	if (opt->r == 1 && opt->q == 0 && opt->filename != NULL && opt->p != 1)
		ft_printf(" %s", opt->filename);
	ft_printf("\n");
	if (opt->p == 1)
		opt->p = 2;
	freestuff(opt);
}

void	printsha512(t_sha512 *sha5, t_flags *opt, unsigned char *s)
{
	if (opt->p == 1)
		ft_printf("%s", s);
	if (opt->filename != NULL && opt->r == 0 && opt->q == 0 && opt->p != 1)
	{
		ft_printf("SHA512 (%s) = ", opt->filename);
	}
	if (opt->s == 1 && opt->q != 1 && opt->r != 1)
	{
		ft_printf("SHA512 (\"%s\") = ", opt->textwithsflag);
	}
	ft_printf("%.8llx%.8llx%.8llx%.8llx%.8llx%.8llx%.8llx%.8llx",
	sha5->h0, sha5->h1, sha5->h2,
	sha5->h3, sha5->h4, sha5->h5, sha5->h6, sha5->h7);
	if (opt->s == 1 && opt->q != 1 && opt->r == 1)
	{
		ft_printf(" \"%s\"", opt->textwithsflag);
	}
	if (opt->r == 1 && opt->q == 0 && opt->filename != NULL && opt->p == 0)
		ft_printf(" %s", opt->filename);
	ft_printf("\n");
	if (opt->p == 1)
		opt->p = 2;
	freestuff(opt);
}
