NAME = fdf

SRCS = srcs/main.c srcs/draw_line.c srcs/file_manager.c srcs/transform_move.c \
	srcs/transform_rotate.c srcs/transform_scale.c \
	srcs/transform_projection.c srcs/renderer.c srcs/error_manager.c \
	srcs/matrix_multiply.c srcs/set_color.c srcs/copy_pnt.c \
	srcs/transform_rotate_matrices.c srcs/normalize.c

all: $(NAME)

$(NAME):
	@make -C libft
	@echo compiling ..
	@gcc $(SRCS) -O libft/libft.a -o $(NAME) -I /usr/X11/include -I includes -g -l mlx -framework OpenGL -framework AppKit
	@echo $(NAME) created

cata:
	@make -C libft
	@echo compiling ..
	@gcc $(SRCS) libft/libft.a -I /usr/X11/include -I includes -g -L /usr/X11/lib -l mlx -framework OpenGL -framework AppKit -o $(NAME)
	@echo $(NAME) created

clean:
	rm -f *.o

fclean: clean
	rm -f $(NAME)

re: fclean all
