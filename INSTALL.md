# Installation Guide

This document describes how to install clibx on your system.

## Table of Contents

- [System Requirements](#system-requirements)
- [What You Need](#what-you-need)
- [Quick Install: Single Headers (wget/curl)](#quick-install-single-headers-wgetcurl)
- [System-wide Installation](#system-wide-installation)
- [Custom Installation Prefix](#custom-installation-prefix)
- [Manual Installation](#manual-installation)
- [Using in Your Projects](#using-in-your-projects)
- [Building Examples](#building-examples)
- [Uninstallation](#uninstallation)

## System Requirements

- **C Compiler:** GCC, Clang, or compatible (C99 or later)
- **Build Tools:** make
- **Platform:** Unix-like system (Linux, macOS, BSD)
  - POSIX path utilities for full functionality
  - x86_64 Linux for `clibx_print.h`

## What You Need

**Not all header files are required.** Choose based on your needs:

- **`clibx.h`** (core) - Main utilities: arrays, math, memory, strings, paths, hash maps, logging
  - **Always needed** if you want the library utilities
  
- **`clibx_list.h`** (optional) - Singly-linked list implementation
  - Only needed if you use linked lists
  - Requires: `clibx.h`
  
- **`clibx_print.h`** (optional) - Lightweight printf via direct syscalls
  - Only needed if you want stdio-free printing
  - **Independent module:** works standalone without `clibx.h`
  - Platform: x86_64 Linux only

## Quick Install: Single Headers (wget/curl)

Download only the headers you need:

### Option 1: Just the core library

```bash
wget https://raw.githubusercontent.com/DavidBalishyan/clibx/refs/heads/main/clibx.h
# or
curl -O https://raw.githubusercontent.com/DavidBalishyan/clibx/refs/heads/main/clibx.h
```

### Option 2: Core + Linked List

```bash
wget https://raw.githubusercontent.com/DavidBalishyan/clibx/refs/heads/main/clibx.h
wget https://raw.githubusercontent.com/DavidBalishyan/clibx/refs/heads/main/clibx_list.h
```

### Option 3: Just the printf module

```bash
wget https://raw.githubusercontent.com/DavidBalishyan/clibx/refs/heads/main/clibx_print.h
```

### Option 4: Everything

```bash
wget https://raw.githubusercontent.com/DavidBalishyan/clibx/refs/heads/main/clibx.h
wget https://raw.githubusercontent.com/DavidBalishyan/clibx/refs/heads/main/clibx_list.h
wget https://raw.githubusercontent.com/DavidBalishyan/clibx/refs/heads/main/clibx_print.h
```

Place downloaded files in your project directory or include path, then include them in your code:

```c
#include "clibx.h"        /* Always include if using core features */
#include "clibx_list.h"   /* Optional: only if using linked lists */
#include "clibx_print.h"  /* Optional: only if using syscall printf */
```

Compile with:

```bash
gcc -o myprogram myprogram.c
```

## System-wide Installation

Clone the repository and install to `/usr/local`:

```bash
git clone https://github.com/DavidBalishyan/clibx.git
cd clibx
sudo make install
```

This will:
- Copy all headers to `/usr/local/include/`
- Install manpages to `/usr/local/share/man/man3/`

> **Note:** You don't need to use all headers. See [What You Need](#what-you-need) for details.

Verify installation:

```bash
man clibx          # Main library reference
man clibx_list     # Linked list API
man clibx_print    # Lightweight printf API
```

## Custom Installation Prefix

To install to a custom location (useful for development or user-wide installation):

```bash
make install PREFIX=$HOME/.local
```

Or:

```bash
make install PREFIX=/opt/clibx
```

This allows installation without `sudo` to your personal directory.

### Adding to Your PATH

If using a custom prefix, ensure the paths are accessible:

```bash
# For header files (in your compiler search path)
export CFLAGS="-I$HOME/.local/include"

# For manpages (in your man search path)
export MANPATH="$HOME/.local/share/man:$MANPATH"
```

Add these to your shell profile (`.bashrc`, `.zshrc`, etc.) for persistence.

## Manual Installation

If you prefer to install without make, copy only the headers you need:

1. **Copy headers** (choose what you need):
   ```bash
   # Core library (always needed if using core features)
   cp clibx.h /usr/local/include/
   
   # Optional: Linked list support
   cp clibx_list.h /usr/local/include/
   
   # Optional: Standalone printf via syscalls
   cp clibx_print.h /usr/local/include/
   ```

2. **Copy manpages** (optional):
   ```bash
   cp man/man3/clibx.3 /usr/local/share/man/man3/
   cp man/man3/clibx_list.3 /usr/local/share/man/man3/
   cp man/man3/clibx_print.3 /usr/local/share/man/man3/
   ```

## Uninstallation

Remove installed files:

```bash
sudo make uninstall
```

Or with a custom prefix:

```bash
make uninstall PREFIX=$HOME/.local
```

## Using in Your Projects

### Method 1: Include Installed Headers

After system-wide installation, include only what you need:

```c
#include <clibx.h>        /* Required if using core features */
#include <clibx_list.h>   /* Optional: only if using linked lists */
#include <clibx_print.h>  /* Optional: independent syscall printf */
```

Compile normally:

```bash
gcc -o myprogram myprogram.c
```

### Method 2: Local Include (No Installation)

Copy only the headers you need to your project:

```bash
# Just the core library
cp path/to/clibx.h .

# Or add linked lists
cp path/to/clibx.h path/to/clibx_list.h .

# Or just the printf module (standalone)
cp path/to/clibx_print.h .
```

Include locally:

```c
#include "clibx.h"        /* Required for core features */
#include "clibx_list.h"   /* Optional: depends on clibx.h */
#include "clibx_print.h"  /* Optional: standalone, no dependencies */
```

Compile:

```bash
gcc -o myprogram myprogram.c
```

### Method 3: Specify Include Path

Include from a specific directory:

```bash
gcc -I/path/to/clibx/headers -o myprogram myprogram.c
```

## Building Examples

After installation, build and run the demonstration programs:

```bash
make          # Build all demos
./bin/main.demo      # Run main demo
./bin/list.demo      # Run linked list demo
./bin/print.demo     # Run print demo
```

## Installation Verification

Verify the installation by checking file locations:

```bash
# Check headers
ls -la /usr/local/include/clibx*.h

# Check manpages
ls -la /usr/local/share/man/man3/clibx*.3

# Read manpages
man clibx
man clibx_list
man clibx_print
```

## Troubleshooting

### Headers not found during compilation

Ensure headers are in a location that your compiler searches:

```bash
# Check compiler include paths
gcc -v -E - < /dev/null 2>&1 | grep include

# Or try explicit include path
gcc -I/path/to/headers -o myprogram myprogram.c
```

### Manpages not found

Update your manpage database:

```bash
# For custom prefix
export MANPATH="$HOME/.local/share/man:$MANPATH"
man clibx

# System-wide
sudo mandb
man clibx
```

### Compilation errors

Ensure you're using C99 or later:

```bash
gcc -std=c99 -o myprogram myprogram.c
```

No external libraries required.

## Upgrading

To upgrade to a new version:

```bash
cd clibx
git pull origin main
sudo make install
```

Or reinstall to custom prefix:

```bash
make install PREFIX=$HOME/.local
```

## Next Steps

After installation, read the documentation:

- Main library: `man clibx`
- Linked list: `man clibx_list`
- Print module: `man clibx_print`

Or check the [README.md](README.md) for comprehensive documentation and examples.
