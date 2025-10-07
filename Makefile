# **************************************************************************** #
#	  #
#	 :::	  ::::::::	#
#	Makefile	   :+:	  :+:	:+:	#
#	 +:+ +:+	 +:+	  #
#	By: alborges <alborges@student.42.fr>	  +#+  +:+	   +#+	 #
#	 +#+#+#+#+#+   +#+	#
#	Created: 2025/07/15 00:00:00 by alborges	  #+#	#+#	  #
#	Updated: 2025/07/15 19:25:05 by alborges	 ###   ########.fr	#
#	  #
# **************************************************************************** #

# Variables
NAME = fdf
CC = gcc
CFLAGS = -Wall -Wextra -Werror -g
INCLUDES = -I./includes -I./libft -I./minilibx-linux -I./get_next_line

# Chemins
SRCDIR = srcs
OBJDIR = obj
LIBFT_DIR = libft
MLX_DIR = minilibx-linux

MY_SRCS = $(SRCDIR)/main.c $(SRCDIR)/events.c $(SRCDIR)/parsing.c $(SRCDIR)/render.c $(SRCDIR)/render2.c $(SRCDIR)/utils.c $(SRCDIR)/bounds.c 
GNL_SRCS = get_next_line/get_next_line.c get_next_line/get_next_line_utils.c
SRCS = $(MY_SRCS) $(GNL_SRCS)

MY_OBJS = $(MY_SRCS:$(SRCDIR)/%.c=$(OBJDIR)/%.o)
GNL_OBJS = $(GNL_SRCS:get_next_line/%.c=$(OBJDIR)/%.o)
OBJS = $(MY_OBJS) $(GNL_OBJS)

# Bibliothèques
LIBFT = $(LIBFT_DIR)/libft.a
MLX = $(MLX_DIR)/libmlx.a
LIBS = -L$(LIBFT_DIR) -lft -L$(MLX_DIR) -lmlx -lX11 -lXext -lm

# Règles
all: $(NAME)

$(NAME): $(OBJDIR) $(LIBFT) $(MLX) $(OBJS)
	$(CC) $(OBJS) $(LIBS) -o $(NAME)

$(OBJDIR)/%.o: $(SRCDIR)/%.c
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

$(OBJDIR)/%.o: get_next_line/%.c
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

$(OBJDIR):
	mkdir -p $(OBJDIR)

$(LIBFT):
	make -C $(LIBFT_DIR)

$(MLX):
	make -C $(MLX_DIR)

clean:
	rm -rf $(OBJDIR)
	make clean -C $(LIBFT_DIR)
	make clean -C $(MLX_DIR)

fclean: clean
	rm -f $(NAME)
	make fclean -C $(LIBFT_DIR)

re: fclean all

.PHONY: all clean fclean re
