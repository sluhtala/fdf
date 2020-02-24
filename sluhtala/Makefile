NAME = test

SRCS = main.c draw_line.c file_manager.c transform_move.c transform_rotate.c transform_scale.c \
	   transform_projection.c renderer.c error_manager.c matrix_multiply.c set_color.c copy_pnt.c \
	   transform_rotate_matrices.c normalize.c

all: $(NAME)

$(NAME):
	gcc $(SRCS) libft/libft.a -I /usr/X11/include -g -L /usr/X11/lib -l mlx -framework OpenGL -framework AppKit -o $(NAME)

ver2:
	gcc $(SRCS) -O libft/libft.a -o $(NAME) -I /usr/X11/include -g -l mlx -framework OpenGL -framework AppKit

clean:
	rm -f *.o

fclean: clean
	rm -f $(NAME)

re: fclean all
