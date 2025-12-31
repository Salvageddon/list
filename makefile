srctarget = src/source/list.c
objtarget = src/obj/list.o
libtarget = src/lib/liblist.a
maintarget = src/source/main.c

liblink = -Lsrc/lib -llist

all:
	gcc -c -fPIC ${srctarget} -o ${objtarget}
	gcc -shared ${objtarget} -o ${libtarget} 
	gcc ${maintarget} -o test -Isrc/include ${liblink}

create:
	touch ${objtarget}

clean:
	rm -f ${objtarget}