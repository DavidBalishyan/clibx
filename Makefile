CC = gcc
BINDIR = bin
SRCDIR = .
PREFIX ?= /usr/local
INSTALL = install
INSTALL_DIR = $(INSTALL) -d
INSTALL_FILE = $(INSTALL) -m 644
INSTALL_PROGRAM = $(INSTALL) -m 755

.PHONY: all clean build install install-headers install-man uninstall

all: help

help:
	@echo "Usage: make <target>"
	@echo ""
	@echo "Targets:"
	@echo "  all              Default target (shows this help message)"
	@echo "  help             Show this help message"
	@echo "  build            Build demo binaries into $(BINDIR)/"
	@echo "  clean            Remove build directory"
	@echo "  install          Install headers and manpages"
	@echo "  reinstall        Reinstall headers and manpages"
	@echo "  install-headers  Install header files to $(PREFIX)/include/"
	@echo "  install-man      Install manpages to $(PREFIX)/share/man/man3/"
	@echo "  uninstall        Remove installed headers and manpages"
	@echo ""
	@echo "Variables:"
	@echo "  PREFIX=$(PREFIX)"
	@echo ""
	@echo "Examples:"
	@echo "  make build"
	@echo "  sudo make install"
	@echo "  make PREFIX=/usr install"

$(BINDIR):
	@mkdir -p $(BINDIR)

clean: 
	rm -rf $(BINDIR)

build: $(BINDIR)
	$(CC) main.demo.c -o $(BINDIR)/main.demo
	$(CC) list.demo.c -o $(BINDIR)/list.demo
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
