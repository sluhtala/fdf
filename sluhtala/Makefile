NAME = fdf

SRCS = srcs/main.c srcs/draw_line.c srcs/file_manager.c srcs/transform_move.c \
	srcs/transform_rotate.c srcs/transform_scale.c \
	srcs/transform_projection.c srcs/renderer.c srcs/error_manager.c \
	srcs/matrix_multiply.c srcs/set_color.c srcs/copy_pnt.c \
	srcs/transform_rotate_matrices.c srcs/normalize.c srcs/transformation_init.c

OFILES = main.o draw_line.o file_manager.o transform_move.o \
	transform_rotate.o transform_scale.o \
	transform_projection.o renderer.o error_manager.o \
	matrix_multiply.o set_color.o copy_pnt.o \
	transform_rotate_matrices.o normalize.o transformation_init.o

all: $(NAME)

$(NAME):
	@make -C libft
	@echo compiling ..
	@gcc $(SRCS) libft/libft.a -o $(NAME) -I includes -g -l mlx -framework OpenGL -framework AppKit -Wall -Wextra -Werror
	@echo $(NAME) created

cata:
	@make -C libft
	@echo compiling ..
	@gcc $(SRCS) libft/libft.a -I /usr/X11/include -I includes -g -L /usr/X11/lib -l mlx -framework OpenGL -framework AppKit -o $(NAME)
	@echo $(NAME) created

clean:
	rm -f $(OFILES)
	@make clean -C libft

fclean: clean
	rm -f $(NAME)
	rm -rf $(NAME).dSYM
	@make fclean -C libft

re: fclean all
