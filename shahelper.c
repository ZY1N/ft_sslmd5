/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shahelper.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yinzhang <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/08 00:19:10 by yinzhang          #+#    #+#             */
/*   Updated: 2019/08/08 00:19:11 by yinzhang         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl.h"

void	multipleblockvar2series(t_sha256 *sha2)
{
	sha2->a = sha2->h0;
	sha2->b = sha2->h1;
	sha2->c = sha2->h2;
	sha2->d = sha2->h3;
	sha2->e = sha2->h4;
	sha2->f = sha2->h5;
	sha2->g = sha2->h6;
	sha2->h = sha2->h7;
}

void	multipleblockvar5series(t_sha512 *sha5)
{
	sha5->a = sha5->h0;
	sha5->b = sha5->h1;
	sha5->c = sha5->h2;
	sha5->d = sha5->h3;
	sha5->e = sha5->h4;
	sha5->f = sha5->h5;
	sha5->g = sha5->h6;
	sha5->h = sha5->h7;
}
