
CC=gcc
CFLAGS= -Wall -Wextra -Wpedantic -Werror

send: send.c
sock: sock.c

clean:
	rm -f sock send
