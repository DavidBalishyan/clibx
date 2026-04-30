CC = gcc
FLAGS = -lm
BINDIR = bin
SRCDIR = .

.PHONY: all clean build

all: $(BINDIR) build

$(BINDIR):
	@mkdir -p $(BINDIR)

clean: 
	rm -rf $(BINDIR)

build:
	$(CC) main.demo.c -o $(BINDIR)/main.demo $(FLAGS)
	$(CC) print.demo.c -o $(BINDIR)/print.demo
