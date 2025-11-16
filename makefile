srctarget = src/source/list.c
objtarget = src/obj/list.o
dlltarget = ./list.dll

maintarget = src/source/main.c

all:
	gcc -c -fPIC ${srctarget} -o ${objtarget}
	gcc -shared ${objtarget} -o ${dlltarget}
	gcc -L. ${maintarget} -o ./test -llist

create:
	touch ${objtarget}

clean:
	rm -f ${objtarget}