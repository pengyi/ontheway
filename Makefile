SRC = $(wildcard *.c)  
objects = $(patsubst %.c, %.o, ${SRC}) 
CFLAGS = -g -Wall
exg : $(objects)
	gcc -o exg $(CFLAGS) $(objects)
$(objexts) : %.o:%.c
	gcc -c $(CFLAGS) $< -o $@
.PHONY : clean
clean :
	rm exg $(objects)
