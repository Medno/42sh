# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: kyazdani <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2017/11/24 17:49:45 by kyazdani          #+#    #+#              #
#    Updated: 2018/03/09 11:35:07 by hlely            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libft.a
CC = gcc
AR = ar rc

### FT_PRINTF ###
PRINTF_NAME = ft_convert_str.c ft_handle_percent.c ft_flags.c ft_printf.c \
	  ft_str_parse.c ft_handle_d.c ft_handle_c.c ft_handle_base.c \
	  ft_handle_s.c ft_handle_base_2.c ft_str_join.c ft_handle_d_2.c \
	  ft_return_s.c ft_handle_binary.c ft_handle_f.c ft_flags_2.c \
	  ft_handle_c_2.c ft_colors.c ft_parse_brackets.c ft_ltoa.c \
	  ft_untoa.c ft_dtoa.c ft_ldtoa.c ft_printf_fd.c
PRINTF_PATH = ft_printf/
SRC = $(addprefix $(PRINTF_PATH), $(PRINTF_NAME))

### LISTS ###
LST_NAME = ft_lstnew.c ft_lstdelone.c ft_lstdel.c ft_lstadd.c ft_lstiter.c \
		   ft_lstmap.c ft_lst_push_back.c ft_lst_push_front.c ft_lst_count.c 
LST_PATH = ft_lst/
SRC += $(addprefix $(LST_PATH), $(LST_NAME))

### MEMS ###
MEM_NAME = ft_memset.c ft_bzero.c ft_memcpy.c ft_memccpy.c ft_memmove.c \
		   ft_memchr.c ft_memcmp.c ft_memalloc.c ft_memdel.c 
MEM_PATH = ft_mem/
SRC += $(addprefix $(MEM_PATH), $(MEM_NAME))

### IS AND TO ###
IS_NAME = ft_isalpha.c ft_isdigit.c	ft_isalnum.c ft_isascii.c ft_isprint.c \
		  ft_toupper.c ft_tolower.c 
IS_PATH = ft_is/
SRC += $(addprefix $(IS_PATH), $(IS_NAME))

### ARRAYS ###
TAB_NAME = ft_addstr_tab.c ft_freetab.c ft_tablen.c
TAB_PATH = ft_tab/
SRC += $(addprefix $(TAB_PATH), $(TAB_NAME))

### WRITES ###
WRITE_NAME = ft_inputchar.c ft_putchar.c ft_putstr.c ft_putendl.c ft_putnbr.c \
			 ft_putchar_fd.c ft_putstr_fd.c ft_putendl_fd.c ft_putnbr_fd.c 
WRITE_PATH = ft_write/
SRC += $(addprefix $(WRITE_PATH), $(WRITE_NAME))

### SPECIALS ###
SPEC_NAME = ft_getopt.c get_next_line.c
SPEC_PATH = ft_spec/
SRC += $(addprefix $(SPEC_PATH), $(SPEC_NAME))

### STRINGS ###
STR_NAME = ft_strlen.c ft_strcspn.c ft_strdup.c ft_strndup.c ft_strcpy.c \
		   ft_strncpy.c ft_strcmp.c ft_strncmp.c ft_strcat.c ft_strncat.c \
		   ft_strlcat.c ft_strchr.c ft_strrchr.c ft_strstr.c ft_strnstr.c \
		   ft_atoi.c ft_strnew.c ft_strdel.c ft_strclr.c ft_striter.c \
		   ft_striteri.c ft_strmap.c ft_strmapi.c ft_strequ.c ft_strnequ.c \
		   ft_strsub.c ft_strjoin.c ft_strtrim.c ft_strsplit.c ft_itoa.c \
		   ft_itoa_base.c ft_strstrchr.c ft_strjoindel.c ft_strjoin_infinite.c\
		   ft_strnjoindel.c
STR_PATH = ft_str/
SRC += $(addprefix $(STR_PATH), $(STR_NAME))

### PATHS OBJECTS AND SOURCE FILES ###
PATHSRC = ./srcs/
SRCS = $(addprefix $(PATHSRC), $(SRC))
OBJ = $(SRCS:.c=.o)

### INCLUDES ###
LIBINCLUDES = includes/
LIBINC = -I$(LIBINCLUDES)
LFLAGS = -Wall -Wextra

ifneq ($(NOERR),yes)
LFLAGS += -Werror
endif

ifeq ($(DEV),yes)
LFLAGS += -g
endif

ifeq ($(SAN),yes)
LFLAGS += -fsanitize=address -fno-omit-frame-pointer -fno-optimize-sibling-calls
endif

all : $(NAME)

$(NAME) : $(OBJ)
	@$(AR) $@ $^
	@ranlib $@
	@echo "\033[1;38;2;255;244;24m <<< libft -> ready >>>\033[0m"

%.o:%.c
	@$(CC) $(LFLAGS) $(LIBINC) -o $@ -c $<
	@echo "\033[1;38;2;218;154;39m>\c"

clean : 
	@/bin/rm -rf $(OBJ)


fclean : clean
	@/bin/rm -f $(NAME)

re : fclean all

.PHONY : all clean fclean re
