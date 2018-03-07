# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: pchadeni <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/03/06 16:40:19 by pchadeni          #+#    #+#              #
#    Updated: 2018/03/07 18:14:56 by pchadeni         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = 42sh

CC = gcc 

### PATH SRCS ### 
PATHFS = ./srcs/

### BUILTINS ###
BUI_NAME = ft_cd.c ft_cd2.c ft_cd3.c	\
		   ft_echo.c					\
		   ft_env.c						\
		   ft_set_env.c					\
		   ft_unsetenv.c				\
		   ft_history.c					\
		   ft_history2.c				\
		   ft_history3.c				\
		   ft_history4.c				\
		   ft_exit.c
BUI_PATH = builtins/
SRCS += $(addprefix $(PATHFS), $(addprefix $(BUI_PATH), $(BUI_NAME)))

### STRUCTURE ###
STRUC_NAME = addons.c			\
			 ft_environment.c	\
			 main.c				\
			 init_attrs.c		\
			 exec.c				\
			 ft_check_path.c
STRUC_PATH = structure/
SRCS += $(addprefix $(PATHFS), $(addprefix $(STRUC_PATH), $(STRUC_NAME)))

### LINE EDIT ###
LINE_NAME = ft_line.c		\
			ft_line2.c 		\
			dblist.c		\
			dblist2.c		\
			move.c			\
			move2.c			\
			add_elem.c		\
			del_char.c		\
			ft_pos.c		\
			completion.c	\
			ft_grab.c		\
			ft_paste.c		\
			control_l.c
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

### HISTORIC ###
HIST_NAME = start_histo.c			\
			edit_histo.c			\
			paste_quote_history.c	
HIST_PATH = history/
SRCS += $(addprefix $(PATHFS), $(addprefix $(HIST_PATH), $(HIST_NAME)))

### LEXER ###
LEXER_NAME = lexer.c			\
			 init_lex.c			\
			 print_lex.c		\
			 is_lex.c			\
			 categorize_token.c	\
			 first_steps.c 		\
			 last_steps.c
LEXER_PATH = lexer/
SRCS += $(addprefix $(PATHFS), $(addprefix $(LEXER_PATH), $(LEXER_NAME)))

### PARSER ###
PARSER_NAME = ast.c init_ast.c	\
			  parser.c			\
			  redir_ast.c		\
			  ast_to_struct.c	\
			  struct_redir.c	\
			  quote_esc.c		\
			  quote_remove.c	\
			  init_cmd.c		\
			  print_smtg.c
PARSER_PATH = parser/
SRCS += $(addprefix $(PATHFS), $(addprefix $(PARSER_PATH), $(PARSER_NAME)))

### REDIRECTION ###
REDIR_NAME = redirection.c		\
			 handle_redir.c		\
			 error_redir.c		\
			 setup_fd.c
REDIR_PATH = redirection/
SRCS += $(addprefix $(PATHFS), $(addprefix $(REDIR_PATH), $(REDIR_NAME)))

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

# libft.a
LIB = ./libft/libft.a

OBJ = $(SRCS:%.c=%.o)

all : makelib $(NAME)

$(NAME) : $(OBJ)
		@$(CC) $(FLAGS) $(INC) -o $@ $^ $(LIB)
		@echo "\033[K\033[35m***** done *****\033[0m"

%.o:%.c
		@$(CC) $(FLAGS) $(INC) -o $@ -c $<
		@echo "\033[38;2;255;95;30m\c"
		@echo " [$@] > compiled\033[0m\033[K\c"
		@echo "\033[70D\c"

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
