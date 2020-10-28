INCLDIR = ./include
CC = gcc
CFLAGS = -O2
CFLAGS += -I$(INCLDIR)

OBJDIR = obj

_DEPS = database.h
DEPS = $(patsubst %, $(INCLDIR)/%,$(_DEPS))

_OBJS = database.o main.o
OBJS = $(patsubst %,$(OBJDIR)/%,$(_OBJS))

$(OBJDIR)/%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

menuApplication: $(OBJS)
	gcc -o $@ $^ $(CFLAGS)

.PHONY: clean
clean:
	rm -f $(OBJDIR)/*.o *~ core $(INCLDIR)/*~