# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: kyazdani <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/01/18 14:27:11 by kyazdani          #+#    #+#              #
#    Updated: 2018/02/07 15:16:45 by kyazdani         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = 21sh

CC = gcc 

SRC_NAME = main.c

### PATH SRCS ### 
PATHFS = ./srcs/

### BUILTINS ###
BUI_NAME = ft_cd.c ft_cd2.c ft_cd3.c \
		   ft_echo.c \
		   ft_env.c \
		   ft_set_env.c \
		   ft_unsetenv.c
BUI_PATH = builtins/
SRCS += $(addprefix $(PATHFS), $(addprefix $(BUI_PATH), $(BUI_NAME)))

### STRUCTURE ###
STRUC_NAME = addons.c ft_environment.c main.c init_attrs.c
STRUC_PATH = structure/
SRCS += $(addprefix $(PATHFS), $(addprefix $(STRUC_PATH), $(STRUC_NAME)))

### LINE EDIT ###
LINE_NAME = ft_line.c init_terms.c chain_db.c move.c del_char.c add_elem.c
LINE_PATH = line_edit/
SRCS += $(addprefix $(PATHFS), $(addprefix $(LINE_PATH), $(LINE_NAME)))

### LIBFT ###
LIBINC = ./libft
INC += -I$(LIBINC)/includes

### 21 INCLUDES ###
INCLUDES = ./includes/ 
INC += -I$(INCLUDES)


# flags
FLAGS = -Wall -Wextra

ifneq ($(NOERR),yes)
FLAGS += -Werror
endif

ifeq ($(DEV),yes)
FLAGS += -g
endif

ifeq ($(SAN),yes)
FLAGS += -fsanitize=address -fno-omit-frame-pointer -fno-optimize-sibling-calls
endif

# termcap linker
TERMS = -ltermcap

# libft.a
LIB = ./libft/libft.a

OBJ = $(SRCS:%.c=%.o)

all : makelib $(NAME)

$(NAME) : $(OBJ)
		@$(CC) $(FLAGS) $(INC) -o $@ $^ $(LIB) $(TERMS)
		@echo "\033[35m***** done *****\033[0m"

%.o:%.c
		@$(CC) $(FLAGS) $(INC) -o $@ -c $<
		@echo "\x1b[38;2;255;95;30m"
		@echo " [$@] > compiled\033[0m"

makelib :
		@make -C $(LIBINC) NOERR=$(NOERR) DEV=$(DEV) SAN=$(SAN)

clean : cleanlib
		@/bin/rm -rf $(OBJ)
		@echo "\033[31m--== objects trashed ==--\033[0m"

cleanlib :
		@make clean -C ./libft

fclean : fcleanlib clean
		@/bin/rm -f $(NAME)
		@echo "\033[033m--== binary trashed ==--\033[0m"

fcleanlib :
		@make fclean -C ./libft

re : fclean all

.PHONY : all clean fclean re
