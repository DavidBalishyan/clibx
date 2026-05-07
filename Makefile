CC = gcc
FLAGS =
BINDIR = bin
SRCDIR = .
PREFIX ?= /usr/local
INSTALL = install
INSTALL_DIR = $(INSTALL) -d
INSTALL_FILE = $(INSTALL) -m 644
INSTALL_PROGRAM = $(INSTALL) -m 755

.PHONY: all clean build install install-headers install-man uninstall reinstall

all: $(BINDIR) build

$(BINDIR):
	@mkdir -p $(BINDIR)

clean: 
	rm -rf $(BINDIR)

build:
	$(CC) main.demo.c -o $(BINDIR)/main.demo $(FLAGS)
	$(CC) list.demo.c -o $(BINDIR)/list.demo $(FLAGS)
	$(CC) print.demo.c -o $(BINDIR)/print.demo

install: install-headers install-man
	@echo "Installation complete! Headers installed to $(PREFIX)/include/ and manpages to $(PREFIX)/share/man/man3/"

install-headers:
	$(INSTALL_DIR) $(PREFIX)/include
	$(INSTALL_FILE) clibx.h $(PREFIX)/include/
	$(INSTALL_FILE) clibx_list.h $(PREFIX)/include/
	$(INSTALL_FILE) clibx_print.h $(PREFIX)/include/
	@echo "Headers installed to $(PREFIX)/include/"

install-man:
	$(INSTALL_DIR) $(PREFIX)/share/man/man3
	$(INSTALL_FILE) man/man3/clibx.3 $(PREFIX)/share/man/man3/
	$(INSTALL_FILE) man/man3/clibx_list.3 $(PREFIX)/share/man/man3/
	$(INSTALL_FILE) man/man3/clibx_print.3 $(PREFIX)/share/man/man3/
	@echo "Manpages installed to $(PREFIX)/share/man/man3/"

uninstall:
	rm -f $(PREFIX)/include/clibx.h
	rm -f $(PREFIX)/include/clibx_list.h
	rm -f $(PREFIX)/include/clibx_print.h
	rm -f $(PREFIX)/share/man/man3/clibx.3
	rm -f $(PREFIX)/share/man/man3/clibx_list.3
	rm -f $(PREFIX)/share/man/man3/clibx_print.3
	@echo "Uninstallation complete!"

reinstall: uninstall install