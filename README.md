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

> **NOTE** Manipulators can't be mixed in one string. In other words, when you use only text color formatting only, you cannot use background color manipulators and vice versa.

