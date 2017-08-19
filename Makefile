NAME = ft_ls

CPP = clang

CFLAGS = -O3 -g3 -fsanitize=address

HEADER = includes -L libft -I libft/includes/

SOURCES = main.c \
			parsing.c \
			misc.c

DIR_O = obj

DIR_S = srcs

SRCS = $(addprefix $(DIR_S)/,$(SOURCES))
OBJS = $(addprefix $(DIR_O)/,$(SOURCES:.c=.o))

all: obj $(NAME)

${NAME}: $(OBJS)
	${CPP} $(CFLAGS) -o $@ $^ libft/libft.a

$(DIR_O)/%.o: $(DIR_S)/%.c
	$(CPP) $(CFLAGS) -I $(HEADER) -c -o $@ $<

obj:
	mkdir -p obj

clean:	
	rm -rf obj

.PHONY: all $(NAME)
