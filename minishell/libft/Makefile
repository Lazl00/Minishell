NAME		:=	libft.a
BUFFER_SIZE	:=	4096

CC			:=	clang
FLAGS		:= -Wall -Werror -Wextra

DIR_SRCS	:=	srcs
DIR_OBJS	:=	.objs
DIR_INCS	:=	include

LST_SRCS	:=	ft_atoi.c \
				ft_bzero.c \
				ft_calloc.c \
				ft_isalnum.c \
				ft_isalpha.c \
				ft_isascii.c \
				ft_isdigit.c \
				ft_isprint.c \
				ft_itoa.c \
				ft_memchr.c \
				ft_memcmp.c \
				ft_memcpy.c \
				ft_memmove.c \
				ft_memset.c \
				ft_putchar_fd.c \
				ft_putendl_fd.c \
				ft_putnbr_fd.c \
				ft_putstr_fd.c \
				ft_split.c \
				ft_strchr.c \
				ft_strdup.c \
				ft_striteri.c \
				ft_strjoin.c \
				ft_strlcat.c \
				ft_strlcpy.c \
				ft_strlen.c \
				ft_strmapi.c \
				ft_strncmp.c \
				ft_strnstr.c \
				ft_strrchr.c \
				ft_strtok.c \
				ft_strcmp.c \
				ft_strtrim.c \
				ft_substr.c \
				ft_tolower.c \
				ft_toupper.c \
				ft_lstadd_back_bonus.c \
				ft_lstadd_front_bonus.c \
				ft_lstclear_bonus.c \
				ft_lstdelone_bonus.c \
				ft_lstiter_bonus.c \
				ft_lstlast_bonus.c \
				ft_lstmap_bonus.c \
				ft_lstnew_bonus.c \
				ft_lstsize_bonus.c \
				printf/ft_hexa.c \
				printf/ft_print_adresse.c \
				printf/ft_print_unsigned.c \
				printf/ft_printf_untils.c \
				printf/ft_printf.c \
				printf/ft_putnbrbase.c \
				gnl/get_next_line.c \
				gnl/get_next_line_bonus.c \
				gnl/get_next_line_utils_bonus.c \
				gnl/get_next_line_utils.c \

LST_OBJS	:=	$(LST_SRCS:.c=.o)
LST_INCS	:=	libft.h ft_printf.h get_next_line.h get_next_line_bonus.h

SRCS		:=	$(addprefix $(DIR_SRCS)/,$(LST_SRCS))
OBJS		:=	$(addprefix $(DIR_OBJS)/,$(LST_OBJS))
INCS		:=	$(addprefix $(DIR_INCS)/,$(LST_INCS))

ERASE		=	\033[2K\r
BLUE		=	\033[34m
YELLOW		=	\033[33m
GREEN		=	\033[32m
END			=	\033[0m

$(DIR_OBJS)/%.o: $(DIR_SRCS)/%.c $(INCS) Makefile
	@mkdir -p $(DIR_OBJS)
	@mkdir -p $(DIR_OBJS)/printf
	@mkdir -p $(DIR_OBJS)/gnl
	@printf "$(ERASE)$(BLUE) > Compilation :$(END) $<"
	@$(CC) $(FLAGS) -D BUFFER_SIZE=${BUFFER_SIZE} -I $(DIR_INCS) -c $< -o $@
	@printf "\r\033[K"

all:	$(NAME)

$(NAME):	$(OBJS)
	@ar rcs $@ $^

clean:
	@rm -rf $(DIR_OBJS)

fclean:		clean
	@rm -rdf	$(NAME)

re:			fclean all

.PHONY:	all clean fclean re
