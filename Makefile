NAME = ircserv

CC = c++

CFLAGS = -Wall -Wextra -Werror -std=c++98 -g3

FILE = main Server Client ClientEvents Channel commandEvent
COMMAND = INVITE JOIN KICK MODE NICK PART PASS PING PRIVMSG QUIT TOPIC USER

GREEN = \033[1;32m
BLUE= \033[1;34m
RED = \033[1;31m
NC = \033[0m

FILE_DIR = ./src/
COMMAND_DIR = ./commands/
OBJ_DIR = ./obj/

FILES = $(addprefix $(FILE_DIR), $(addsuffix .cpp, $(FILE)))
OBJS = $(addprefix $(OBJ_DIR), $(addsuffix .o, $(FILE)))
COMMANDS = $(addprefix $(COMMAND_DIR), $(addsuffix .cpp, $(COMMAND)))
OBJS_COMMANDS = $(addprefix $(OBJ_DIR), $(addsuffix .o, $(COMMAND)))

all :  $(NAME)
	
$(OBJ_DIR)%.o: $(FILE_DIR)%.cpp
	@mkdir -p $(OBJ_DIR)
	@$(CC) $(CFLAGS) -pthread -c -o $@ $<
	@echo "$@ : $(GREEN)[OK]$(NC)"

$(OBJ_DIR)%.o: $(COMMAND_DIR)%.cpp
	@$(CC) $(CFLAGS) -pthread -c -o $@ $<
	@echo "$@ : $(GREEN)[OK]$(NC)"

$(NAME): $(OBJS) $(OBJS_COMMANDS)
	@$(CC) $(CFLAGS) $(OBJS) $(OBJS_COMMANDS) -o  $(NAME)
	@echo "\n$(BLUE)=============================================$(NC)\n"
	
clean :
	@clear
	@echo "$(RED)========== [ OBJECT DELETED ] ==========$(NC)"
	rm -rf $(OBJ_DIR)
	@echo "$(RED)========================================$(NC)"
	
fclean : clean
	@clear
	@echo "$(RED)========== [ OBJECT / EX DELETED ] ==========$(NC)"
	rm -f $(NAME) 
	@echo "$(RED)=============================================$(NC)"
	

re : fclean all

.PHONY : all clean fclean re libft print
