# -----------------------------  PROJECT ------------------------------------------------------#
NAME = minishell

# -----------------------------  DIRECTORIES  ------------------------------------------------------#
CC          := cc
CFLAGS      := -Wall -Wextra -Werror -g -Iincludes
LDFLAGS     := -lreadline -lpthread
LIBFT       := libft/libft.a

DIR_SRCS    := src
BN_DIR_SRCS := bonus
DIR_OBJS    := .objs
DIR_INCS    := includes

SRCS =  main.c \
		parsing/expend_vars.c \
		parsing/frees.c \
		parsing/handle_quote.c \
		parsing/parsing.c \
		parsing/tokens.c \
		parsing/token_utils.c \
		parsing/inits.c \
		lexing/lexing.c \
		lexing/lexing_utils.c \
		lexing/accesses.c \
		lexing/get_paths.c \
		errors/errors.c \
		builtin/echo.c \
		builtin/builtin_utils.c \
		exec/exec.c \
		exec/exec_utils.c \
		exec/sigs_strat.c \
		exec/do_heredoc.c \
		builtin/env.c \
		builtin/cd.c \
		builtin/pwd.c \
		builtin/unset.c \
		builtin/export.c \
		builtin/exit.c \
		exec/heredocs.c \
		exec/handle_redirections.c \
		signals/signals.c \
		exec/exec_loop.c \
		exec/exec_loop_utils.c \
		phoenix/phoenix.c \
		phoenix/find.c \
		phoenix/extract.c \
		phoenix/true_phoenix.c \
		phoenix/extract_utils.c \

OBJS   := $(addprefix $(DIR_OBJS)/, $(SRCS:.c=.o))
INCS   := $(addprefix $(DIR_INCS)/, minishell.h)

# Couleurs et symboles
BLUE        := \033[34m
YELLOW      := \033[33m
GREEN       := \033[32m
CYAN        := \033[36m
RED         := \033[31m
END         := \033[0m
CHECK       := ✅
CROSS       := ❌
WARN        := ⚠️
INFO        := ℹ️

MINI =  "\n"\
		"           ▄▄▄▄███▄▄▄     ▄█   ▄█▄▄▄▄    ▄█     ▄████████▀  ▄█    █▄     ▄███████▄  ▄█        ▄█       \n"\
		"        ▄██▀▀▀███▀▀▀██  ▄██  ▄██▀▀▀██▄ ▄██    ███    ███  ███    ███    ███    ██▀ ███       ███       \n"\
		"       ███   ███   ███ ███▌ ███   ███ ███▌   ███    █▀   ███    ███    ███    █▀  ███       ███       \n"\
		"      ███   ███   ███ ███▌ ███   ███ ███▌   ███      ▄▄▄███▄▄▄▄███▄▄▄▄███▄▄▄▄▄▄▄ ███       ███       \n"\
		"     ███   ███   ███ ███▌ ███   ███ ███▌  ▀▀██████████████▀▀▀▀███▀▀▀▀███▀▀▀▀▀▀  ███       ███       \n"\
		"    ███   ███   ███ ███  ███   ███ ███           ███  ███    ███    ███    █▄  ███       ███       \n"\
		"   ███   ███   ██▀ ██▀  ███   ██▀ ██▀    ▄█     ███  ███    ███     ███▄   ███ ███▌    ▄ ███▌    ▄ \n"\
		"   ▀█   ███   █▀  █▀    ▀█   █▀  █▀    ▄████████▀   █▀     █▀       ▀███████▀ █████▄▄██ █████▄▄██ \n"\
		"                                                                               ▀         ▀         \n"\

all: $(LIBFT) $(NAME)
	@echo "$(GREEN)$(CHECK) $(NAME) is ready!$(END)"
	@echo $(MINI)

# Compilation des fichiers objets
$(DIR_OBJS)/%.o: $(DIR_SRCS)/%.c $(INCS) Makefile $(LIBFT)
	@mkdir -p $(dir $@)
	@printf "$(BLUE)$(INFO) Compiling: $(END)$(CYAN)$<$(END)\r"
	@$(CC) $(CFLAGS) -c $< -o $@
	@printf "\r\033[K$(GREEN)$(CHECK) Compiled: $(END)$(CYAN)$<$(END)\n"

$(NAME): $(OBJS)
	@$(CC) $(CFLAGS) $(OBJS) $(LIBFT) $(LDFLAGS) -o $@
	@echo "$(GREEN)$(CHECK) $(NAME) created!$(END)"

$(LIBFT):
	@make -C libft --no-print-directory
	@echo "$(GREEN)$(CHECK) $(LIBFT) compiled!$(END)"

clean:
	@rm -rf $(DIR_OBJS)
	@make clean -C libft --no-print-directory
	@echo "$(CYAN)$(WARN) Object files cleaned!$(END)"

fclean: clean
	@rm -f $(NAME)
	@make fclean -C libft --no-print-directory
	@echo "$(RED)$(CROSS) Full clean completed!$(END)"

# Recompilation
re: fclean all
	@echo "$(GREEN)$(CHECK) Project recompiled!$(END)"

.PHONY: all clean fclean re
