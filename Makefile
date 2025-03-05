NAME    := ircserv

SRCS_D  := ./src
OBJS_D  := ./build

CC      := clang++
CFLAGS  := -Wall -Wextra -Werror -std=c++98 -g

HEADERS := -I ./inc

SRCS    := main.cpp commands/Command.cpp commands/QuitCommand.cpp \
			 server/Server.cpp server/utils_server.cpp client/Client.cpp \
			 Channel.cpp

OBJS    := $(addprefix $(OBJS_D)/, $(SRCS:.cpp=.o))

GREEN   := \033[1;32m
RESET   := \033[0m

ARGS	:= 6667 pass

all: $(NAME)

$(OBJS_D)/%.o: $(SRCS_D)/%.cpp
		@test -d $(OBJS_D) || mkdir $(OBJS_D)
		@test -d $(OBJS_D)/commands || mkdir $(OBJS_D)/commands
		@test -d $(OBJS_D)/server || mkdir $(OBJS_D)/server
		@test -d $(OBJS_D)/client || mkdir $(OBJS_D)/client
		@$(CC) $(CFLAGS) -o $@ -c $< $(HEADERS) && printf "$(GREEN)✔️ $(notdir $<) compiled\n$(RESET)"

$(NAME): $(OBJS)
		@$(CC) $(OBJS) $(HEADERS) -o $(NAME)

gdb: all
		@gdb -tui $(NAME) -ex 'start 6667 pass'

valgrind: all
		@valgrind --show-leak-kinds=all --trace-children=yes --track-fds=yes --leak-check=full --track-origins=yes --show-reachable=yes ./$(NAME) $(ARGS)

run: all
		@./$(NAME) $(ARGS)

clean:
		@rm -rf $(OBJS_D)

fclean: clean
		@rm -rf $(NAME)

re: clean all

.PHONY: all, clean, fclean, re, gdb, valgrind, run
