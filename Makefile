NAME    := ircserv

SRCS_D  := ./src
OBJS_D  := ./build

CC      := clang++
CFLAGS  := -Wall -Wextra -Werror -std=c++98 -g

HEADERS := -I ./inc

SRCS    := main.cpp Server.cpp utils.cpp

OBJS    := $(addprefix $(OBJS_D)/, $(SRCS:.cpp=.o))

GREEN   := \033[1;32m

ARGS	:= 6667 pass

all: $(NAME)

$(OBJS_D)/%.o: $(SRCS_D)/%.cpp
		@test -d $(OBJS_D) || mkdir $(OBJS_D)
		@$(CC) $(CFLAGS) -o $@ -c $< $(HEADERS) && printf "$(GREEN)✔️ $(notdir $<) compiled\n"

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