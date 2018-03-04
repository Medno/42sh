# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: kyazdani <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/01/18 14:27:11 by kyazdani          #+#    #+#              #
#    Updated: 2018/03/02 14:30:36 by kyazdani         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = 42sh

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
STRUC_NAME = addons.c ft_environment.c main.c init_attrs.c edit_historic.c
STRUC_PATH = structure/
SRCS += $(addprefix $(PATHFS), $(addprefix $(STRUC_PATH), $(STRUC_NAME)))

### LINE EDIT ###
LINE_NAME = ft_line.c init_terms.c dblist.c move.c del_char.c add_elem.c \
			ft_pos.c move2.c completion.c dblist2.c historic.c ft_line2.c \
			ft_grab.c ft_paste.c
LINE_PATH = line_edit/
SRCS += $(addprefix $(PATHFS), $(addprefix $(LINE_PATH), $(LINE_NAME)))

### COMPLETION ###
COMP_NAME =	clean_comp.c 				\
			comp.c 						\
			comp_check_duplicate.c		\
			comp_get_dir_to_open.c		\
			comp_get_word_to_complete.c	\
			comp_sort_alphab.c			\
			comp_tools.c				\
			completion.c				\
			get_potential_cmd.c			\
			get_potential_directory.c
COMP_PATH = completion/
SRCS += $(addprefix $(PATHFS), $(addprefix $(COMP_PATH), $(COMP_NAME)))

### LEXER ###
LEXER_NAME = lexer.c init_lex.c print_lex.c is_lex.c
LEXER_PATH = lexer/
SRCS += $(addprefix $(PATHFS), $(addprefix $(LEXER_PATH), $(LEXER_NAME)))

### PARSER ###
PARSER_NAME = ast.c init_ast.c parser.c redir_ast.c edit_history.c \
			  ast_to_struct.c
PARSER_PATH = parser/
SRCS += $(addprefix $(PATHFS), $(addprefix $(PARSER_PATH), $(PARSER_NAME)))

### EXEC ###
EXEC_NAME =	fill_cmd.c		\
			init_exec.c 	\
			struct_cmd.c	\
			struct_redir.c	
EXEC_PATH = exec/
SRCS += $(addprefix $(PATHFS), $(addprefix $(EXEC_PATH), $(EXEC_NAME)))

### LIBFT ###
LIBINC = ./libft
INC += -I$(LIBINC)/includes

### 21 INCLUDES ###
INCLUDES = ./includes/ 
INC += -I$(INCLUDES)

INC += -I./logger/incs/

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
		@echo "\033[38;2;255;95;30m\c"
		@echo " [$@] > compiled\033[0m"

makelib :
		@make -C $(LIBINC) NOERR=$(NOERR) DEV=$(DEV) SAN=$(SAN)

hist :
		@/bin/rm -f ./srcs/structure/.history

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
