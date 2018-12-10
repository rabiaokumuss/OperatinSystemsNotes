#

all: p6 p7 p8

p6: p6.c
	gcc -I../2.4.18/libfdr p6.c -o p6 -L../2.4.18/libfdr -lfdr

p7: p7.c
	gcc -I../2.4.18/libfdr p7.c -o p7 -L../2.4.18/libfdr -lfdr

p8: p8.c
	gcc -I../2.4.18/libfdr p8.c -o p8 -L../2.4.18/libfdr -lfdr
