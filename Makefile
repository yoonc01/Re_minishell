NAME = minishell
cc = cc
CFLAGS = -g -Wall -Wextra -Werror
RM = rm -rf

LIB_DIR = ./lib/

LIBFT_DIR = $(LIB_DIR)libft/
LIBFT = $(LIBFT_DIR)libft.a

LIBRARIES = -lft -lreadline -L$(LIBFT_DIR)

HEADERS_DIR = ./includes/

HEADERS_LIST = minishell.h
HEADERS = $(addprefix $(HEADERS_DIR), $(HEADERS_LIST))

INCLUDES = -I$(HEADERS_DIR) -I$(LIBFT_DIR)

SRC_DIR = ./src/
SRCS_LIST = main.c\
			env_utils.c\
			error.c\
			utils.c\
			terminal.c\
			signal.c\
			env_list.c

PARSING_DIR = $(SRC_DIR)parsing
PARSING_LIST = deque.c\
			parsing.c\
			tokenize.c\
			apply_env.c\
			parsing_utils.c\
			tokenize_utils.c\
			inner_block.c\
			parsing_error.c\
			process.c

BUILTIN_DIR = $(SRC_DIR)builtin
BUILTIN_LIST = cd.c\
			echo.c\
			env.c\
			export.c\
			pwd.c\
			unset.c\
			builtin_error.c\
			exit.c

EXECUTE_DIR = $(SRC_DIR)execute
EXECUTE_LIST = make_child.c\
			make_child_util.c\
			execute_command.c\
			make_argv_envp_path.c\
			heredoc.c\
			heredoc_utils.c\
			redirect_no_fork.c\
			redirect_fork.c\
			redirect_fork_util.c\
			err_exit.c

SRCS = $(addprefix $(SRC_DIR), $(SRCS_LIST)) $(addprefix $(PARSING_DIR), $(PARSING_LIST)) $(addprefix $(BUILTIN_DIR), $(BUILTIN_LIST)) $(addprefix $(EXECUTE_DIR), $(EXECUTE_LIST))

OBJ_DIR = ./objects/
OBJ_LIST = $(SRCS_LIST:.c=.o) $(PARSING_LIST:.c=.o) $(BUILTIN_LIST:.c=.o)  $(EXECUTE_LIST:.c=.o)
OBJS = $(addprefix $(OBJ_DIR), $(OBJ_LIST))

all : $(NAME)

$(NAME) : $(LIBFT) $(OBJ_DIR) $(OBJS)
	$(cc) $(CFLAGS) $(INCLUDES) $(OBJS) $(LIBRARIES) -o $(NAME)

$(OBJ_DIR) :
	mkdir -p $(OBJ_DIR)

# SRC_DIR에 있는 .c 파일들을 처리
$(OBJ_DIR)%.o: $(SRC_DIR)%.c $(HEADERS)
	$(cc) $(CFLAGS) $(INCLUDES) -c $< -o $@

# PARSING_DIR에 있는 .c 파일들을 처리
$(OBJ_DIR)%.o: $(PARSING_DIR)/%.c $(HEADERS)
	$(cc) $(CFLAGS) $(INCLUDES) -c $< -o $@

# BUILTIN_DIR에 있는 .c 파일들을 처리
$(OBJ_DIR)%.o: $(BUILTIN_DIR)/%.c $(HEADERS)
	$(cc) $(CFLAGS) $(INCLUDES) -c $< -o $@

# EXECUTE_DIR에 있는 .c 파일들을 처리
$(OBJ_DIR)%.o: $(EXECUTE_DIR)/%.c $(HEADERS)
	$(cc) $(CFLAGS) $(INCLUDES) -c $< -o $@

$(LIBFT) :
	make -C $(LIBFT_DIR)

clean : 
	make -C $(LIBFT_DIR) clean
	$(RM) $(OBJ_DIR)

fclean : clean
	$(RM) $(LIBFT)
	$(RM) $(NAME)

re : fclean all

.PHONY: all clean fclean re

