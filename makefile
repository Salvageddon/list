srctarget = src/source/list.c
objtarget = src/obj/list.o
dlltarget = ./list.dll

maintarget = src/source/main.c

all: build run

build:
	gcc -c -fPIC ${srctarget} -o ${objtarget}
	gcc -shared ${objtarget} -o ${dlltarget}

run:
	gcc ${maintarget} -o test ${dlltarget}
	./test