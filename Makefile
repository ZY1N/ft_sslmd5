# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: yinzhang <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/06/14 16:26:00 by yinzhang          #+#    #+#              #
#    Updated: 2019/06/14 16:26:02 by yinzhang         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #
NAME		= ft_ssl

CFLAGS		= -Wall -Werror -Wextra

INCLUDE		= ft_ssl.h\

PRINTFDIR	= ft_printf/

FILES		= ft_ssl.c helper.c md5.c print.c sha256.c errors.c md5_2.c\
			sha256_2.c sha512.c sha224.c sha224_2.c shahelper.c sha512_2.c\

PRINTFSRC 	= ./ft_printf/libftprintf.a\

OBJ = $(FILES:.c=.o)

all: $(NAME)

$(NAME):
	@make re -C $(PRINTFDIR)
	@gcc $(CFLAGS) $(FILES) -o $(NAME) -I $(INCLUDE) $(PRINTFSRC)

clean:
	@rm -f $(OBJ)
	@make clean -C $(PRINTFDIR)

fclean: clean
	@rm -f $(OBJ)
	@rm -f $(NAME)
	@make fclean -C $(PRINTFDIR)

re: fclean all