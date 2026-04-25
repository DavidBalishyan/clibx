BINDIR = bin
SRCDIR = .

.PHONY: all clean build

all: $(BINDIR) build

$(BINDIR):
	@mkdir -p $(BINDIR)

clean: 
	rm -rf $(BINDIR)

build:
	@gcc main.demo.c -o $(BINDIR)/main.demo -lm
	@gcc print.demo.c -o $(BINDIR)/print.demo
