# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: abutok <abutok@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/05/03 19:52:20 by abutok            #+#    #+#              #
#    Updated: 2019/05/06 16:06:06 by abutok           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = wolf3d
#	C compiler and his flags
GCC = gcc -Wall -Wextra -Werror
#	Libft linking
LINKLIBFT = -L ./libft -lft
#	Libs linking
LINKLIB = -framework OpenGL -framework AppKit /Library/Frameworks/SDL2.framework/Versions/Current/SDL2 $(LINKLIBFT)
#	Sources directoried
SRCDIR = ./src/
#	Source files
SRCFILES = main.c parse_map.c
#	Headers
INCLUDE = ./includes
#	Binaries folder
BINDIR = ./obj/
#	Binaries files
BINFILES = $(addprefix $(BINDIR), $(SRCFILES:.c=.o))
#	Libft
LIBFT = ./libft/libft.a
#	Libft headers
LIBFTINCLUDE = ./libft/includes
#	SDL Headers
SDLINCLUDE = /Library/Frameworks/SDL2.framework/Headers
#	Parallel compiling
.NOTPARALLEL = all fclean clean re $(NAME)

all: $(LIBFT) $(NAME)

$(NAME): $(BINDIR) $(BINFILES)
	$(GCC) $(LINKLIB) $(BINFILES) -I $(LIBFTINCLUDE) -I $(INCLUDE) \
		-I $(SDLINCLUDE) -o $(NAME)

$(BINDIR):
	@if [ ! -d "$(BINDIR)" ]; then mkdir $(BINDIR); fi

$(BINDIR)%.o: $(SRCDIR)%.c
	$(GCC) -c -I $(INCLUDE) -I $(LIBFTINCLUDE) -I $(SDLINCLUDE) $< -o $@

clean:
	make -C ./libft/ clean
	if [ -d "$(BINDIR)" ]; then rm -rf $(BINDIR); fi

fclean: clean
	make -C ./libft/ fclean
	if [ -f "$(NAME)" ]; then rm -rf $(NAME); fi

re: fclean all

$(LIBFT):
	make -C ./libft/
