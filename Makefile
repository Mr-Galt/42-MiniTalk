# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mheinke <mheinke@student.42abudhabi.ae>    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/12/11 21:10:48 by mheinke           #+#    #+#              #
#    Updated: 2023/12/11 21:37:04 by mheinke          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = cc
CFLAGS = -Wall -Wextra -Werror
LIBFT = ./libft/libft.a
RM = rm -rf

SERVER = server
CLIENT = client

SV_SRCS = sources/server.c
SV_OBJS = $(SV_SRCS:.c=.o)

CLIENT_SRCS = sources/client.c
CLIENT_OBJS = $(CLIENT_SRCS:.c=.o)

RESET		= $'\x1b[0m
BOLD		= $'\x1b[1m
RED			= $'\x1b[31m
GREEN		= $'\x1b[32m
YELLOW		= $'\x1b[33m

%.o: %.c
	@$(CC) $(CFLAGS) -c $< -o $@

all: $(SERVER) $(CLIENT)

$(LIBFT):
	@$(MAKE) -C ./libft

$(SERVER): $(SV_OBJS) $(LIBFT)
	@$(CC) $(CFLAGS) $(SV_OBJS) $(LIBFT) -o server
	@echo ""
	@echo "${GREEN}Libft compiled${RESET}"
	@echo "${GREEN}Server compiled${RESET}"

$(CLIENT): $(CLIENT_OBJS) $(LIBFT)
	@$(CC) $(CFLAGS) $(CLIENT_OBJS) $(LIBFT) -o client
	@echo "${GREEN}Client compiled${RESET}"
	@echo "${GREEN}${BOLD}MiniTalk completed${RESET}"
	@echo ""

clean:
	@$(MAKE) clean -C ./libft
	@$(RM) $(SV_OBJS) $(CLIENT_OBJS)
	@echo ""
	@echo "${YELLOW}Object files removed${RESET}"

fclean: clean
	@$(MAKE) fclean -C ./libft
	@$(RM) $(SERVER) $(CLIENT)
	@echo "${YELLOW}Executables removed${RESET}"
	@echo ""

re: fclean all