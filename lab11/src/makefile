
PROG = lab11
PROGP = lab11Pipe
ARCH = ../lib
CC = gcc -w
INCFLG = -I $(INCDIR)

all: $(PROG) $(PROGP)
$(PROG): lab11.o 
	${CC} -o $(PROG) $^
$(PROGP): lab11Pipe.o 
	${CC} -o $(PROGP) $^
lab11.o:lab11.c 
	${CC} -c lab11.c
lab11Pipe.o:lab11Pipe.c 
	${CC} -c lab11Pipe.c
clean:
	$(RM) lab11 lab11Pipe *.o *.a
