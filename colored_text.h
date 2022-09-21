#ifndef COLORED_TEXT_H
#define COLORED_TEXT_H
#include <iostream>
#include <string>
#include <vector>
#include <random>
#include <windows.h>
// Namespace of Colored Text
namespace ct {
    // Handle to Console
    HANDLE ConsoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);
    // CT Color Executor
    const char Executor = '&';
    // Color Palette
    enum Color {BLACK = 0, DARK_BLUE = 1, DARK_GREEN = 2, CYAN = 3, DARK_RED = 4, PURPLE = 5, ORANGE = 6, GRAY = 7, DARK_GRAY = 8,
                BLUE = 9, GREEN = 10, AQUA = 11, RED = 12, PINK = 13, YELLOW = 14, WHITE = 15};
    // CT Modifiers List
    const std::vector <char> Modifiers = {'0', '1', '2', '3', '4', '5', '6', '7', '8', '9', 'a', 'b', 'c', 'd', 'e', 'f'};
    // Rainbow Sequence Colors List
    const std::vector <WORD> RainbowSequence = {0x04, 0x0c, 0x06, 0x0e, 0x0a, 0x02, 0x03, 0x0b, 0x09, 0x05};
    // Rainbow Sequence Colors List (with colored background)
    const std::vector <WORD> BgRainbowSequence = {0xc4, 0x4c, 0xe6, 0x6e, 0x2a, 0xa2, 0xb3, 0x3b, 0x19, 0xd5};
}
// Colored Text Class
class ctext {
    public:
        // Displays colored text (Argument: Color formatted string)
        static void text (const std::string &CF_text) {
            for (unsigned int i = 0; i < CF_text.length(); i++) {
                if (CheckCTExecutor(CF_text, i)) {
                    SetConsoleTextAttribute(ct::ConsoleHandle, ConvertModifierToColor(CF_text.at(i+1)));
                    i++;
                }
                else std::cout<<CF_text.at(i);
            }
        }
        // Displays single-colored text (Arguments: Plain string, Text color)
        static void text (const std::string &text, ct::Color text_color) {
            SetConsoleTextAttribute(ct::ConsoleHandle, text_color);
            std::cout<<text;
        }
        // Displays colored text with background (Argument: Color + background formatted string)
        static void bgtext (const std::string &CFB_text) {
            for (unsigned int i = 0; i < CFB_text.length(); i++) {
                if (CheckCTBExecutor(CFB_text, i)) {
                    SetConsoleTextAttribute(ct::ConsoleHandle, ConvertModifierToColor(CFB_text.at(i+1), CFB_text.at(i+2)));
                    i+=2;
                }
                else std::cout<<CFB_text.at(i);
            }
        }
        // Displays single-colored text + background (Arguments: Plain string, Background color, Text color)
        static void bgtext (const std::string &text, ct::Color backgd_color, ct::Color text_color) {
            SetConsoleTextAttribute(ct::ConsoleHandle, backgd_color*16+text_color);
            std::cout<<text;
        }
        static void rainbow (const std::string &text) {
            unsigned int size = text.length();
            std::vector <int> Sequencer;
            SetFullRainbowSequencer(Sequencer, size, text);
            for (unsigned int i = 0; i < text.length(); i++) {
                SetConsoleTextAttribute(ct::ConsoleHandle, ct::RainbowSequence[Sequencer[i]]);
                std::cout<<text.at(i);
            }
        }
        static void rainbow_bg (const std::string &text) {
            unsigned int size = text.length();
            std::vector <int> Sequencer;
            SetFullRainbowSequencer(Sequencer, size, text);
            for (unsigned int i = 0; i < text.length(); i++) {
                SetConsoleTextAttribute(ct::ConsoleHandle, ct::BgRainbowSequence[Sequencer[i]]);
                std::cout<<text.at(i);
            }
        }
        // Displays rainbow cycling text
        static void rainbow_cycle (const std::string &text) {
            // Rainbow Index Sequencer
            std::vector <int> Sequencer;
            unsigned int size = text.length() > 10 ? 10 : text.length();
            if (text.at(text.length()-1) == '\n' && text.length() > 1 && text.length() <= 10) size--;
            Sequencer.resize(size);
            SetRainbowSequencer(Sequencer, size);
            for (unsigned int i = 0; i < text.length(); i++) {
                SetConsoleTextAttribute(ct::ConsoleHandle, ct::RainbowSequence[Sequencer[i%size]]);
                std::cout<<text.at(i);
            }
        }
        // Displays rainbow cycling text (with colored background)
        static void rainbow_bg_cycle (const std::string &text) {
            // Rainbow Index Sequencer
            std::vector <int> Sequencer;
            unsigned int size = text.length() > 10 ? 10 : text.length();
            if (text.at(text.length()-1) == '\n' && text.length() > 1 && text.length() <= 10) size--;
            Sequencer.resize(size);
            SetRainbowSequencer(Sequencer, size);
            for (unsigned int i = 0; i < text.length(); i++) {
                SetConsoleTextAttribute(ct::ConsoleHandle, ct::BgRainbowSequence[Sequencer[i%size]]);
                std::cout<<text.at(i);
            }
        }
    private:
        // Checks if there is a modifier after executor sign
        static bool CheckCTExecutor (const std::string &CT_text, unsigned int iter_at) {
            if (CT_text.at(iter_at) != ct::Executor) return false;
            if (iter_at >= CT_text.length() - 1) return false;
            for (unsigned int i = 0; i < 16; i++) if (CT_text.at(iter_at+1) == ct::Modifiers[i]) return true;
            return false;
        }
        // Checks if there are 2 modifiers after executor sign
        static bool CheckCTBExecutor (const std::string &CTB_text, unsigned int iter_at) {
            if (CTB_text.at(iter_at) != ct::Executor) return false;
            if (iter_at >= CTB_text.length() - 2) return false;
            bool t_modifier_ok = false;
            for (unsigned int i = 0; i < 16; i++) {
                if (CTB_text.at(iter_at+1) == ct::Modifiers[i]) {
                    t_modifier_ok = true;
                    break;
                }
            }
            if (t_modifier_ok) for (unsigned int i = 0; i < 16; i++) if (CTB_text.at(iter_at+2) == ct::Modifiers[i]) return true;
            return false;
        }
        // Converts Modfier to Text Color
        static WORD ConvertModifierToColor (char t_modifier) {
            if (t_modifier >= 48 && t_modifier <= 57) return (int) t_modifier - 48;
            if (t_modifier >= 97 && t_modifier <= 102) return (int) t_modifier - 87;
            return 0x00;
        }
        // Converts Modifiers to Background Color + Text Color
        static WORD ConvertModifierToColor (char b_modifier, char t_modifier) {
            WORD value = 0x00;
            if (b_modifier >= 48 && b_modifier <= 57) value += 16 * ((int) b_modifier - 48);
            if (b_modifier >= 97 && b_modifier <= 102) value += 16 * ((int) b_modifier - 87);
            if (t_modifier >= 48 && t_modifier <= 57) value += (int) t_modifier - 48;
            if (t_modifier >= 97 && t_modifier <= 102) value += (int) t_modifier - 87;
            return value;
        }
        // Set rainbow cycle sequencer
        static void SetRainbowSequencer (std::vector <int> &Sequencer, unsigned int size) {
            switch (size) {
                case 1: {Sequencer = {0}; break;}
                case 2: {Sequencer = {0, 9}; break;}
                case 3: {Sequencer = {0, 5, 9}; break;}
                case 4: {Sequencer = {0, 3, 6, 9}; break;}
                case 5: {Sequencer = {0, 2, 4, 6, 9}; break;}
                case 6: {Sequencer = {0, 2, 4, 6, 7, 9}; break;}
                case 7: {Sequencer = {0, 1, 2, 4, 6, 7, 9}; break;}
                case 8: {Sequencer = {0, 1, 2, 4, 5, 6, 7, 9}; break;}
                case 9: {Sequencer = {0, 1, 2, 3, 4, 5, 6, 7, 9}; break;}
                default: {Sequencer = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9}; break;}
            }
        }
        static void SetFullRainbowSequencer (std::vector <int> &Sequencer, unsigned int size, const std::string &text) {
            Sequencer.resize(size);
            unsigned int c_size = size;
            if (text.at(text.length()-1) == '\n') c_size--;
            if (c_size < 11) SetRainbowSequencer(Sequencer, c_size);
            else {
                unsigned int rep = c_size / 10;
                unsigned int rem = c_size % 10;
                unsigned int c = 0;
                unsigned int i = 0;
                do {
                    for (unsigned r = 0; r < rep; r++) {
                        Sequencer[i] = c;
                        i++;
                    }
                    if (rem > 0) {
                        Sequencer[i] = c;
                        rem--;
                        i++;
                    }
                    c++;
                } while (i < size);
                for (i = c_size; i < size; i++) Sequencer[i] = 9;
            }
        }
};
#endif // !COLORED_TEXT_H