/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ssl.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yinzhang <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/28 21:07:50 by yinzhang          #+#    #+#             */
/*   Updated: 2019/07/28 21:07:52 by yinzhang         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl.h"

t_algorithmns *g_jumpt[4] = {
	md5,
	sha256,
	sha512,
	sha224
};

void	findinput(t_flags *options, t_algo algo)
{
	int n;

	n = 0;
	if (options->filename != NULL && options->text == NULL)
	{
		n = open(options->filename, O_RDONLY);
		if (n == -1)
			invalidfile(options->filename, algo);
		if (n != -1)
			options->text = extractfdtext(n);
	}
	if (options->filename == NULL && options->p == 0 && options->s == 0)
		options->emptytext = extractfdtext(0);
}

void	jumptable(char *input, t_flags *options, t_algo algo)
{
	g_jumpt[algo]((unsigned char *)input, options);
}

void	ifhavefile(char *s, t_flags *options, t_algo algo)
{
	options->filename = s;
	if (options->s != 1)
		findinput(options, algo);
	if (options->text != NULL)
		jumptable(options->text, options, algo);
}

void	findflags(char *s, t_flags *options, t_algo algo)
{
	if (ft_strcmp("-p", s) == 0)
	{
		options->p = 1;
		options->stdinputtext = extractfdtext(0);
		jumptable(options->stdinputtext, options, algo);
	}
	else if (ft_strcmp("-q", s) == 0)
		options->q = 1;
	else if (ft_strcmp("-r", s) == 0)
		options->r = 1;
	else if (ft_strcmp("-s", s) == 0)
	{
		if (options->s == 0)
			options->s = 1;
		else
			invalidfile(s, algo);
	}
	else if (options->s == 1 && options->textwithsflag == NULL)
	{
		options->textwithsflag = s;
		jumptable(options->textwithsflag, options, algo);
		options->s = 2;
	}
	else
		ifhavefile(s, options, algo);
}

int		main(int argc, char **argv)
{
	t_algo	algo;
	t_flags	*options;
	int		n;

	n = 1;
	options = (t_flags *)malloc(sizeof(t_flags));
	initflags(options);
	if (argc > 1)
	{
		algo = findalgo(argv[1]);
		if (algo == INVALID)
			ifunknown(argv[1], options);
		while (n++ < argc - 1)
			findflags(argv[n], options, algo);
		if (options->s == 0 && options->p == 0)
			findinput(options, algo);
		if (options->emptytext != NULL)
			jumptable(options->emptytext, options, algo);
		free(options);
	}
	else
		write(1, USAGE, 52);
}
