##
# ut-tooti
#
# @file
# @version 0.1

SRC = in-out.c user.c main.c general.c
OBJ = ${SRC:.c=.o}
CFLAGS = -Wall -Wextra -fsanitize=address

ut-tooti: ${OBJ}
	gcc ${CFLAGS} ${OBJ} -o $@


.c.o:
	gcc -c ${CFLAGS} $<

clean:
	rm -f *.o ut-tooti

# end
