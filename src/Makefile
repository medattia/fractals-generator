BINNAME= binary

LNKFLAGS= -lstdc++ -lm -I../include `pkg-config --cflags --libs opencv`

# Sources
SRCS= spirals.cpp 
OBJS= $(shell echo $(SRCS) | sed "s/\.cpp/.o/g" |sed "s/\.c/.o/g")

all: $(SRCS) $(BINNAME)

$(BINNAME): $(OBJS)
	gcc $(OBJS) -o $(BINNAME) $(LNKFLAGS)

.c.o:
	gcc $(CFLAGS) -o $@ -c $?

.cpp.o:
	gcc $(CFLAGS) -o $@ -c $?

clean:
	rm -f $(OBJS) $(BINNAME)
