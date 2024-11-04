CC			=	cc
CFLAGS		=	-Wall -Wextra -Werror -O3
SRC_LIT		=	main.c fractals.c window_utils.c movement.c complex_math.c
SRC_DIR		=	src
SRCS		=	$(addprefix $(SRC_DIR)/,$(SRC_LIT))
OBJS		=	$(SRCS:.c=.o)
LIBFT		=	libft/libft.a
LIBMLX		=	libmlx/libmlx.a
LIBOTHER	=	-lX11 -lXext -lm
LIBS		=	$(LIBFT) $(LIBMLX) $(LIBOTHER)
INCL		=	-I ./include -I ./libft/include -I ./libmlx
NAME		=	fract_ol.out

all			:	$(NAME)

$(NAME)		:	$(OBJS) createlibs
			$(CC) $(CFLAGS) $(INCL) $(OBJS) $(LIBS) -o $@

%.o			:	%.c
			$(CC) $(CFLAGS) -o $@ -c $^ $(INCL)

createlibs	:
			make -C ./libft
			make -C ./libmlx

fclean		:	clean
			make fclean -C ./libft
			make clean -C ./libmlx
			rm -f $(NAME)

clean		:
			make clean -C ./libft
			make clean -C ./libmlx
			rm -f $(OBJS)

re			:	fclean all

.PHONY		:	fclean clean all re createlibs
