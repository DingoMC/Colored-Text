# C++ Console Colored Text Library
## Overview
Colored Text library allows you to format your console output text to any color available on Windows Terminal.  
Library provides a variety of in-built functions to make coloring as easy as possible.
## Usage
### 1. Color Palette
Windows Terminal provides 16 colors:
- BLACK = 0
- DARK_BLUE = 1
- DARK_GREEN = 2
- CYAN = 3
- DARK_RED = 4
- PURPLE = 5
- ORANGE = 6
- GRAY = 7
- DARK_GRAY = 8
- BLUE = 9
- GREEN = 10
- AQUA = 11
- RED = 12
- PINK = 13
- YELLOW = 14
- WHITE = 15

You can access them via ct namespace (eg. `ct::DARK_RED`).
### 2. Color-formatted text
To manipulate text color you need to add special characters called **manipulators** to your string to create so called **formatted string**.  
There are 2 types of formatted strings:
- text color formatting only (called in functions as `CF_text`)
- text and background color formatting (called in functions as `CFB_text`)

Analogous there are 2 types of manipulators:
- text color manipulator
- text and background color manipulator

> **NOTE:** Manipulators can't be mixed in one string. In other words, when you use only text color formatting only, you cannot use background color manipulators and vice versa.

Every manipulator must start with a character called **Executor** (by default `&`). Then you type characters called **Modifiers**.  
Modifiers are hexadecimal values (Characters `0-9` and `a-f`) representing color value (`0-15`).  
For example color `PURPLE` has a value of `5`, so the modifier will be `5`.  
Color `YELLOW`, however, has a value of `14` so you need to use letters (`a = 10, b = 11, c = 12, d = 13, e = 14, f = 15`). In this case the modifier will be `e`.

Example of text color manipulation: `&bHello World!`.  
This will change color of `Hello World!` to `AQUA`.

Example of text and background color manipulation: `&1bHello World!`.  
First modifier modifies background and second text color. So this will display `Hello World!` in `AQUA` color on `DARK BLUE` background.

Each string allows multiple manipulators.  
Consider: `&bHe&allo &cWorld!`.  
This will display `He` in `AQUA`, `llo ` in `GREEN` and `World!` in `RED`.  
This feature also works for text and background color manipulation.

> **NOTE:** Library checks correction of manipulators. If you type for example `&xHello`, it will be normally displayed as a `&xHello`, because `x` is not a valid modifier. It works with text and background formatting as well (so `&0a` is correct, but `&0x`, `&x0` or `&&0` are wrong).

### 3. In-built functions
After you `#include "colored_text.h"` in your C++ file, you can access in-built functions via `ctext::` namespace.
#### `text (const std::string &text, ct::Color text_color)`
Usage: Displays string in one given color  
Arguments:
- `const std::string &text`: Text you wish to display
- `ct::Color text_color`: Color from [Color Palette](#1-color-palette)
#### `text (const std::string &CF_text)`
Usage: Displays color formatted string  
Arguments:
- `const std::string &CF_text`: Color formatted string
#### `bgtext (const std::string &text, ct::Color backgd_color, ct::Color text_color)`
Usage: Displays string in one given color on one single background 
Arguments:
- `const std::string &text`: Text you wish to display
- `ct::Color backgd_color`: Background Color from [Color Palette](#1-color-palette)
- `ct::Color text_color`: Text Color from [Color Palette](#1-color-palette)
#### `bgtext (const std::string &CFB_text)`
Usage: Displays color formatted string  
Arguments:
- `const std::string &CFB_text`: Text and Background Color formatted string
