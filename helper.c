/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helper.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yinzhang <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/28 21:17:00 by yinzhang          #+#    #+#             */
/*   Updated: 2019/07/28 21:17:01 by yinzhang         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl.h"

char	*extractfdtext(int n)
{
	char	*s;
	char	*c;
	int		d;

	d = 0;
	s = ft_strnew(0);
	c = ft_strnew(1000);
	while ((d = read(n, c, 1000)) != 0)
		s = ld_stradd(s, c, d);
	free(c);
	return (s);
}

char	*ld_stradd(char *s, char *c, int d)
{
	char	*new;
	size_t	i;
	size_t	n;

	i = 0;
	n = ft_strlen(s);
	new = ft_strnew(n + d);
	while (i < n + d)
	{
		if (i < n)
			new[i] = s[i];
		else
			new[i] = c[i - n];
		i++;
	}
	free(s);
	return (new);
}

void	initflags(t_flags *options)
{
	options->p = 0;
	options->q = 0;
	options->r = 0;
	options->s = 0;
	options->filename = NULL;
	options->fd = 0;
	options->text = NULL;
	options->stdinputtext = NULL;
	options->textwithsflag = NULL;
	options->emptytext = NULL;
}

t_algo	findalgo(char *s)
{
	if (ft_strcmp(s, "md5") == 0)
		return (MD5);
	else if (ft_strcmp(s, "sha256") == 0)
		return (SHA256);
	else if (ft_strcmp(s, "sha512") == 0)
		return (SHA512);
	else if (ft_strcmp(s, "sha224") == 0)
		return (SHA224);
	return (INVALID);
}

char	*ft_strcpy(char *dst, const char *src)
{
	int i;

	i = 0;
	while (src[i])
	{
		dst[i] = src[i];
		i++;
	}
	dst[i] = '\0';
	return (dst);
}
