srctarget = src/source/list.c
dlltarget = ./list.dll

maintarget = src/source/main.c

all: build run

build:
	gcc -shared ${srctarget} -o ${dlltarget}

run:
	gcc ${maintarget} -o test ${dlltarget}
	./test