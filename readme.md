# marLocale Module
## Overview

This module is designed to support internationalization for C++ applications. Since the language configuration files are in JSON format, users can easily localize by editing the JSON files in their environment.

## How to Use

We recommend referring to the simple samples provided, which work on both Windows and Linux platforms.

```cpp
#include <stdio.h>
#include "marLocale.h"

int main()
{
  setLanguage("es");
  printf("%s\n", translate("Hello World").c_str());
  return 0;
}
```

### JSON File Example

Below is an example of a Spanish translation file. The actual file should be saved as lang/translations_es.json.

```json
{
  "Hello World": "Hola mundo",
  "Goodbye": "Adiós"
}
```

## Sample Programs

-    01_commandline: This is a very simple command-line program for internationalization support.
-    02_gui: A GUI program using ImGui. It uses OpenGL but focuses on translating GUI elements, making it easy to understand.

### Building the Sample Programs

Building on Windows and Linux is as simple as running the provided makefile.

```bash
make
```

## Requirements

This project depends on the **nlohmann/json** library for JSON handling. Below are the setup instructions for different operating systems:
### Windows (using MSYS2)

You can install the nlohmann/json library easily using pacman in MSYS2:

```bash
pacman -S mingw-w64-x86_64-nlohmann-json
```

### Linux Mint

For Linux Mint, you can download the library directly from the GitHub releases page and install it manually:

```bash
wget https://github.com/nlohmann/json/releases/download/v3.10.5/json.hpp -O /usr/include/nlohmann/json.hpp
```

Please ensure that you have the necessary permissions to write to the /usr/include/nlohmann/ directory or use sudo if required.


## License

This project is published under the [MIT License](LICENSE.txt).