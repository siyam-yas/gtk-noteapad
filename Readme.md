# GTK Notepad

GTK Notepad is a simple cross-platform text editor built using the GTK library. It supports creating, opening, and saving text files with an integrated font selector for customizing the text view.

## Features

- **Create New Files:** Start with a blank editor.
- **Open Files:** Open text files from your filesystem.
- **Save Files:** Save your work with ease.
- **Font Selector:** Change the font style and size dynamically.


## Requirements

### Linux
- GTK 3 or newer
- Pango library

### Windows
- GTK development environment installed (MSYS2 or similar)
- Pango library

### macOS
- GTK installed via Homebrew or another package manager
- Pango library

---

## Setup Instructions

### Linux
1. Install GTK 3 and development libraries:
   ```bash
   sudo apt-get update
   sudo apt-get install libgtk-3-dev gcc make -y
   ```
2. Clone the repository:
   ```bash
   git clone https://github.com/siyam-yas/gtk-notepad.git
   cd gtk-notepad
   ```
3. Compile the application:
   ```bash
   gcc -o notepad notepad.c `pkg-config --cflags --libs gtk+-3.0`
   ```
4. Run the application:
   ```bash
   ./notepad
   ```

---

### Windows
1. Install MSYS2 from [msys2.org](https://www.msys2.org/).
2. Open MSYS2 MinGW64 and install GTK:
   ```bash
   pacman -S mingw-w64-x86_64-gtk3 mingw-w64-x86_64-gcc
   ```
3. Clone the repository:
   ```bash
   git clone https://github.com/your-username/gtk-notepad.git
   cd gtk-notepad
   ```
4. Compile the application:
   ```bash
   gcc -o notepad notepad.c `pkg-config --cflags --libs gtk+-3.0`
   ```
5. Run the application:
   ```bash
   ./notepad.exe
   ```

---

### macOS
1. Install Homebrew from [brew.sh](https://brew.sh/).
2. Install GTK and its dependencies:
   ```bash
   brew install gtk+3
   ```
3. Clone the repository:
   ```bash
   git clone https://github.com/your-username/gtk-notepad.git
   cd gtk-notepad
   ```
4. Compile the application:
   ```bash
   gcc -o notepad notepad.c `pkg-config --cflags --libs gtk+-3.0`
   ```
5. Run the application:
   ```bash
   ./notepad
   ```

---

## Troubleshooting

- **GTK not found error:** Ensure GTK is installed and `pkg-config` is properly configured.
- **Font changes not applied:** Make sure the Pango library is correctly installed.
---
