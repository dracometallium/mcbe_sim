NAME=mcbe_sim

DEBUG=-Os
LFLAGS=
CFLAGS=-Wall -pipe
SOURCES= mcbe_sim.c mcbe.c
OBJECTS=$(SOURCES:.c=.o)

all: $(NAME)

$(NAME): $(OBJECTS)
	@echo LINKING
	$(CC) $(OBJECTS) $(DEBUG) $(LFLAGS) $(LIBS) $(INCPATH) -o $(NAME)

.c.o:
	@echo COMPILING $<
	$(CC) $(INCPATH) $(CFLAGS) $(DEBUG) -c $< -o $@

debug: DEBUG=-g -O0 -pg -fno-inline -D DEBUG

debug: all

clean:
	rm -rf $(OBJECTS)
	rm -f $(NAME)
