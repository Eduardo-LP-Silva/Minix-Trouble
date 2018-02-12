# Makefile for the project

COMPILER_TYPE= gnu

CC=gcc

PROG= proj
SRCS= main.c video_gr.c timer_kbd_reusable.c Graphics_reusable.c vbe.c Bitmap.c Mouse_reusable.c server.c menu.c movement.c ASM.S M_IH.S
CFLAGS= -Wall

DPADD+= ${LIBDRIVER} ${LIBSYS}
LDADD+= -llm -ldriver -lsys

LDFLAGS+= -L .

MAN=

BINDIR?= /usr/sbin

.include <bsd.prog.mk>
.include <bsd.gcc.mk>
