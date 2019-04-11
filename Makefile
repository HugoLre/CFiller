
NAME = try_to_beat_me

SRCS = 	src/ai.c \
		src/game.c \
		src/main.c \
		src/map.c \
		src/print.c \
		src/utils.c

CFLAGS = -Iinclude -O3

OBJS = $(SRCS:.c=.o)

$(NAME):	$(OBJS)
			gcc $(INC) $(OBJS) -o $(NAME)

re:			fclean $(NAME)

clean:
			rm -f $(OBJS)

fclean:		clean
			rm -f $(NAME)