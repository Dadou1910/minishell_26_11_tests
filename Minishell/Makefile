NAME            = Minishell

CC              = cc
CFLAGS          = -Wall -Wextra -Werror -g3
INCLUDES_DIR    = includes
BUILTINS_DIR    = builtins
PARSING_DIR     = parsing
EXEC_DIR        = exec
GNL_DIR         = Libft
OBJ_DIR         = .obj
LIBFT_DIR       = Libft
INCLUDES_H      = -I./$(INCLUDES_DIR)
DEPS            = Makefile $(INCLUDES_DIR)/minishell.h

# Liste des fichiers sources
BUILTINS_SRC    = $(BUILTINS_DIR)/builtins.c $(BUILTINS_DIR)/cd.c $(BUILTINS_DIR)/echo.c \
                  $(BUILTINS_DIR)/env.c $(BUILTINS_DIR)/export.c $(BUILTINS_DIR)/pwd.c \
                  $(BUILTINS_DIR)/unset.c
EXEC_SRC        = $(EXEC_DIR)/checks.c $(EXEC_DIR)/execute.c $(EXEC_DIR)/free.c \
                  $(EXEC_DIR)/heredoc.c $(EXEC_DIR)/main.c $(EXEC_DIR)/path.c \
                  $(EXEC_DIR)/pids.c $(EXEC_DIR)/pipe.c $(EXEC_DIR)/print_utils.c \
                  $(EXEC_DIR)/prompt_setter.c
PARSING_SRC     = $(PARSING_DIR)/env_and_ressources.c $(PARSING_DIR)/parsing_utils.c \
                  $(PARSING_DIR)/exit_code.c $(PARSING_DIR)/tokens.c $(PARSING_DIR)/handle_functions.c \
				  $(PARSING_DIR)/signaux.c \
                  $(PARSING_DIR)/quote_process.c $(PARSING_DIR)/tokens_1.c $(PARSING_DIR)/utils.c $(PARSING_DIR)/initialize.c
GNL_SRC         = $(GNL_DIR)/get_next_line.c

# Tous les fichiers sources
SOURCES         = $(BUILTINS_SRC) $(EXEC_SRC) $(PARSING_SRC) $(GNL_SRC)

# Fichiers objets, organisés dans des sous-dossiers
BUILTINS_OBJ    = $(BUILTINS_SRC:$(BUILTINS_DIR)/%.c=$(OBJ_DIR)/$(BUILTINS_DIR)/%.o)
EXEC_OBJ        = $(EXEC_SRC:$(EXEC_DIR)/%.c=$(OBJ_DIR)/$(EXEC_DIR)/%.o)
PARSING_OBJ     = $(PARSING_SRC:$(PARSING_DIR)/%.c=$(OBJ_DIR)/$(PARSING_DIR)/%.o)
GNL_OBJ         = $(GNL_SRC:$(GNL_DIR)/%.c=$(OBJ_DIR)/$(GNL_DIR)/%.o)

OBJ_FILES       = $(BUILTINS_OBJ) $(EXEC_OBJ) $(PARSING_OBJ) $(GNL_OBJ)

all: $(NAME)

$(OBJ_DIR)/%.o: %.c $(DEPS)
	@mkdir -p $(dir $@)
	@$(CC) $(CFLAGS) $(INCLUDES_H) -c -o $@ $<

$(NAME): $(OBJ_FILES)
	@make -C $(LIBFT_DIR)
	@echo "\e[36mMaking $(NAME)...\e[0m"
	@$(CC) $(CFLAGS) $(INCLUDES_H) $(OBJ_FILES) -L$(LIBFT_DIR) -lreadline -lft -o $(NAME)
	@echo "\e[32mDone !\e[0m"

clean:
	@rm -rf $(OBJ_DIR)
	@make clean -C $(LIBFT_DIR)
	@echo "\e[31mObject files removed.\e[0m"

fclean: clean
	@rm -f $(NAME)
	@make fclean -C $(LIBFT_DIR)
	@echo "\e[31m$(NAME) removed.\e[0m"

re: fclean all

.PHONY: all clean fclean re
