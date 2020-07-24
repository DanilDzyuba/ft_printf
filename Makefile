# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: clauren <marvin@42.fr>                     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/07/20 23:17:34 by clauren           #+#    #+#              #
#    Updated: 2020/07/24 14:56:05 by clauren          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

.PHONY: all clean fclean re bonus
NAME = libftprintf.a
FLAGS = -Wall -Wextra -Werror

SRC_PATH = srcs/
HDRS_PATH = includes

HEADER = includes/ft_printf.h
SRCS = 	ft_printf.c \
		ft_ltoa_base.c\
		ft_printf_sc.c\
		ft_printf_uxpd.c\
		ft_printf_utils.c

OBJS = $(SRCS:.c=.o)

all: $(NAME)

$(NAME): $(OBJS) $(HEADER)
	ar rc $(NAME) $(OBJS)
	ranlib $(NAME)

%.o: $(SRC_PATH)%.c $(HEADER)
	gcc $(CFLAGS) -I$(HDRS_PATH) -c $< -o $@

clean:
	rm -f $(OBJS)
	
fclean: clean
	rm -f $(NAME)

bonus: all

re: fclean all

