NAME    := ircserv

SRCS_D  := ./src
OBJS_D  := ./build

CC      := c++
CFLAGS  := -Wall -Wextra -Werror -std=c++98 -g

HEADERS := -I ./inc

SRCS    :=	main.cpp Channel.cpp \
			client/Client.cpp commands/firstParamChannelCommand.cpp \
			commands/killCommand.cpp commands/nickCommand.cpp \
			server/killServer.cpp server/utils_server.cpp \
			commands/Command.cpp commands/joinCommand.cpp \
			commands/modeCommand.cpp commands/privmsgCommand.cpp \
			commands/inviteCommand.cpp commands/userCommand.cpp \
			commands/kickCommand.cpp commands/passCommand.cpp \
			commands/topicCommand.cpp \
			server/Server.cpp

OBJS    := $(addprefix $(OBJS_D)/, $(SRCS:.cpp=.o))

ARGS	:= 6667 pass

all: $(NAME)

$(OBJS_D)/%.o: $(SRCS_D)/%.cpp
		@mkdir -p $(dir $@)
		$(CC) $(CFLAGS) -o $@ -c $< $(HEADERS)

$(NAME): $(OBJS)
		@$(CC) $(OBJS) $(HEADERS) -o $(NAME)

gdb: all
		@gdb -tui $(NAME) -ex 'start 6667 pass'

valgrind: all
		@valgrind --show-leak-kinds=all --trace-children=yes --track-fds=yes --leak-check=full --track-origins=yes --show-reachable=yes ./$(NAME) $(ARGS)

run: all
		@./$(NAME) $(ARGS)

clean:
		rm -rf $(OBJS_D)

fclean: clean
		rm -rf $(NAME)

re: fclean all

.PHONY: all, clean, fclean, re, gdb, valgrind, run
