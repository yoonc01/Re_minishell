NAME = minishell
cc = cc
CFLAGS = -g
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
			tokenize_utils.c

SRCS = $(addprefix $(SRC_DIR), $(SRCS_LIST)) $(addprefix $(PARSING_DIR), $(PARSING_LIST))

OBJ_DIR = ./objects/
OBJ_LIST = $(SRCS_LIST:.c=.o) $(PARSING_LIST:.c=.o)
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

