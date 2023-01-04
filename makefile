##
# ut-tooti
#
# @file
# @version 0.1

output: in-out.o struct.o main.o
	gcc -Wall -fsanitize=address -Wextra main.o struct.o in-out.o -o main.out
in-out.o:
	gcc -c in-out.c
struct.o:
	gcc -c struct.c
main.o:
	gcc -c main.c
clean:
	rm *.o
	rm main.out

# end
