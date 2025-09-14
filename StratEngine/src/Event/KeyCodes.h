#pragma once
#include <string>
#include <unordered_map>

#define STRAT_KEY_SPACE              32
#define STRAT_KEY_APOSTROPHE         39  /* ' */
#define STRAT_KEY_COMMA              44  /* , */
#define STRAT_KEY_MINUS              45  /* - */
#define STRAT_KEY_PERIOD             46  /* . */
#define STRAT_KEY_SLASH              47  /* / */
#define STRAT_KEY_0                  48
#define STRAT_KEY_1                  49
#define STRAT_KEY_2                  50
#define STRAT_KEY_3                  51
#define STRAT_KEY_4                  52
#define STRAT_KEY_5                  53
#define STRAT_KEY_6                  54
#define STRAT_KEY_7                  55
#define STRAT_KEY_8                  56
#define STRAT_KEY_9                  57
#define STRAT_KEY_SEMICOLON          59  /* ; */
#define STRAT_KEY_EQUAL              61  /* = */
#define STRAT_KEY_A                  65
#define STRAT_KEY_B                  66
#define STRAT_KEY_C                  67
#define STRAT_KEY_D                  68
#define STRAT_KEY_E                  69
#define STRAT_KEY_F                  70
#define STRAT_KEY_G                  71
#define STRAT_KEY_H                  72
#define STRAT_KEY_I                  73
#define STRAT_KEY_J                  74
#define STRAT_KEY_K                  75
#define STRAT_KEY_L                  76
#define STRAT_KEY_M                  77
#define STRAT_KEY_N                  78
#define STRAT_KEY_O                  79
#define STRAT_KEY_P                  80
#define STRAT_KEY_Q                  81
#define STRAT_KEY_R                  82
#define STRAT_KEY_S                  83
#define STRAT_KEY_T                  84
#define STRAT_KEY_U                  85
#define STRAT_KEY_V                  86
#define STRAT_KEY_W                  87
#define STRAT_KEY_X                  88
#define STRAT_KEY_Y                  89
#define STRAT_KEY_Z                  90
#define STRAT_KEY_LEFT_BRACKET       91  /* [ */
#define STRAT_KEY_BACKSLASH          92  /* \ */
#define STRAT_KEY_RIGHT_BRACKET      93  /* ] */
#define STRAT_KEY_GRAVE_ACCENT       96  /* ` */
#define STRAT_KEY_WORLD_1            161 /* non-US #1 */
#define STRAT_KEY_WORLD_2            162 /* non-US #2 */

/* Function keys */
#define STRAT_KEY_ESCAPE             256
#define STRAT_KEY_ENTER              257
#define STRAT_KEY_TAB                258
#define STRAT_KEY_BACKSPACE          259
#define STRAT_KEY_INSERT             260
#define STRAT_KEY_DELETE             261
#define STRAT_KEY_RIGHT              262
#define STRAT_KEY_LEFT               263
#define STRAT_KEY_DOWN               264
#define STRAT_KEY_UP                 265
#define STRAT_KEY_PAGE_UP            266
#define STRAT_KEY_PAGE_DOWN          267
#define STRAT_KEY_HOME               268
#define STRAT_KEY_END                269
#define STRAT_KEY_CAPS_LOCK          280
#define STRAT_KEY_SCROLL_LOCK        281
#define STRAT_KEY_NUM_LOCK           282
#define STRAT_KEY_PRINT_SCREEN       283
#define STRAT_KEY_PAUSE              284
#define STRAT_KEY_F1                 290
#define STRAT_KEY_F2                 291
#define STRAT_KEY_F3                 292
#define STRAT_KEY_F4                 293
#define STRAT_KEY_F5                 294
#define STRAT_KEY_F6                 295
#define STRAT_KEY_F7                 296
#define STRAT_KEY_F8                 297
#define STRAT_KEY_F9                 298
#define STRAT_KEY_F10                299
#define STRAT_KEY_F11                300
#define STRAT_KEY_F12                301
#define STRAT_KEY_F13                302
#define STRAT_KEY_F14                303
#define STRAT_KEY_F15                304
#define STRAT_KEY_F16                305
#define STRAT_KEY_F17                306
#define STRAT_KEY_F18                307
#define STRAT_KEY_F19                308
#define STRAT_KEY_F20                309
#define STRAT_KEY_F21                310
#define STRAT_KEY_F22                311
#define STRAT_KEY_F23                312
#define STRAT_KEY_F24                313
#define STRAT_KEY_F25                314
#define STRAT_KEY_KP_0               320
#define STRAT_KEY_KP_1               321
#define STRAT_KEY_KP_2               322
#define STRAT_KEY_KP_3               323
#define STRAT_KEY_KP_4               324
#define STRAT_KEY_KP_5               325
#define STRAT_KEY_KP_6               326
#define STRAT_KEY_KP_7               327
#define STRAT_KEY_KP_8               328
#define STRAT_KEY_KP_9               329
#define STRAT_KEY_KP_DECIMAL         330
#define STRAT_KEY_KP_DIVIDE          331
#define STRAT_KEY_KP_MULTIPLY        332
#define STRAT_KEY_KP_SUBTRACT        333
#define STRAT_KEY_KP_ADD             334
#define STRAT_KEY_KP_ENTER           335
#define STRAT_KEY_KP_EQUAL           336
#define STRAT_KEY_LEFT_SHIFT         340
#define STRAT_KEY_LEFT_CONTROL       341
#define STRAT_KEY_LEFT_ALT           342
#define STRAT_KEY_LEFT_SUPER         343
#define STRAT_KEY_RIGHT_SHIFT        344
#define STRAT_KEY_RIGHT_CONTROL      345
#define STRAT_KEY_RIGHT_ALT          346
#define STRAT_KEY_RIGHT_SUPER        347
#define STRAT_KEY_MENU               348

namespace StratEngine {
    const std::unordered_map<int, std::string> KeyCodeMap = {

        {STRAT_KEY_A, "A"},
        {STRAT_KEY_B, "B"},
        {STRAT_KEY_C, "C"},
        {STRAT_KEY_D, "D"},
        {STRAT_KEY_E, "E"},
        {STRAT_KEY_F, "F"},
        {STRAT_KEY_G, "G"},
        {STRAT_KEY_H, "H"},
        {STRAT_KEY_I, "I"},
        {STRAT_KEY_J, "J"},
        {STRAT_KEY_K, "K"},
        {STRAT_KEY_L, "L"},
        {STRAT_KEY_M, "M"},
        {STRAT_KEY_N, "N"},
        {STRAT_KEY_O, "O"},
        {STRAT_KEY_P, "P"},
        {STRAT_KEY_Q, "Q"},
        {STRAT_KEY_R, "R"},
        {STRAT_KEY_S, "S"},
        {STRAT_KEY_T, "T"},
        {STRAT_KEY_U, "U"},
        {STRAT_KEY_V, "V"},
        {STRAT_KEY_W, "W"},
        {STRAT_KEY_X, "X"},
        {STRAT_KEY_Y, "Y"},
        {STRAT_KEY_Z, "Z"},


        {STRAT_KEY_0, "0"},
        {STRAT_KEY_1, "1"},
        {STRAT_KEY_2, "2"},
        {STRAT_KEY_3, "3"},
        {STRAT_KEY_4, "4"},
        {STRAT_KEY_5, "5"},
        {STRAT_KEY_6, "6"},
        {STRAT_KEY_7, "7"},
        {STRAT_KEY_8, "8"},
        {STRAT_KEY_9, "9"},


        {STRAT_KEY_SPACE, "Space"},
        {STRAT_KEY_APOSTROPHE, "'"},
        {STRAT_KEY_COMMA, ","},
        {STRAT_KEY_MINUS, "-"},
        {STRAT_KEY_PERIOD, "."},
        {STRAT_KEY_SLASH, "/"},
        {STRAT_KEY_SEMICOLON, ";"},
        {STRAT_KEY_EQUAL, "="},
        {STRAT_KEY_LEFT_BRACKET, "["},
        {STRAT_KEY_BACKSLASH, "\\"},
        {STRAT_KEY_RIGHT_BRACKET, "]"},
        {STRAT_KEY_GRAVE_ACCENT, "`"},
        {STRAT_KEY_WORLD_1, "World 1"},
        {STRAT_KEY_WORLD_2, "World 2"},


        {STRAT_KEY_ESCAPE, "Escape"},
        {STRAT_KEY_ENTER, "Enter"},
        {STRAT_KEY_TAB, "Tab"},
        {STRAT_KEY_BACKSPACE, "Backspace"},
        {STRAT_KEY_INSERT, "Insert"},
        {STRAT_KEY_DELETE, "Delete"},
        {STRAT_KEY_RIGHT, "Right Arrow"},
        {STRAT_KEY_LEFT, "Left Arrow"},
        {STRAT_KEY_DOWN, "Down Arrow"},
        {STRAT_KEY_UP, "Up Arrow"},
        {STRAT_KEY_PAGE_UP, "Page Up"},
        {STRAT_KEY_PAGE_DOWN, "Page Down"},
        {STRAT_KEY_HOME, "Home"},
        {STRAT_KEY_END, "End"},
        {STRAT_KEY_CAPS_LOCK, "Caps Lock"},
        {STRAT_KEY_SCROLL_LOCK, "Scroll Lock"},
        {STRAT_KEY_NUM_LOCK, "Num Lock"},
        {STRAT_KEY_PRINT_SCREEN, "Print Screen"},
        {STRAT_KEY_PAUSE, "Pause"},


        {STRAT_KEY_F1, "F1"},
        {STRAT_KEY_F2, "F2"},
        {STRAT_KEY_F3, "F3"},
        {STRAT_KEY_F4, "F4"},
        {STRAT_KEY_F5, "F5"},
        {STRAT_KEY_F6, "F6"},
        {STRAT_KEY_F7, "F7"},
        {STRAT_KEY_F8, "F8"},
        {STRAT_KEY_F9, "F9"},
        {STRAT_KEY_F10, "F10"},
        {STRAT_KEY_F11, "F11"},
        {STRAT_KEY_F12, "F12"},
        {STRAT_KEY_F13, "F13"},
        {STRAT_KEY_F14, "F14"},
        {STRAT_KEY_F15, "F15"},
        {STRAT_KEY_F16, "F16"},
        {STRAT_KEY_F17, "F17"},
        {STRAT_KEY_F18, "F18"},
        {STRAT_KEY_F19, "F19"},
        {STRAT_KEY_F20, "F20"},
        {STRAT_KEY_F21, "F21"},
        {STRAT_KEY_F22, "F22"},
        {STRAT_KEY_F23, "F23"},
        {STRAT_KEY_F24, "F24"},
        {STRAT_KEY_F25, "F25"},


        {STRAT_KEY_KP_0, "Keypad 0"},
        {STRAT_KEY_KP_1, "Keypad 1"},
        {STRAT_KEY_KP_2, "Keypad 2"},
        {STRAT_KEY_KP_3, "Keypad 3"},
        {STRAT_KEY_KP_4, "Keypad 4"},
        {STRAT_KEY_KP_5, "Keypad 5"},
        {STRAT_KEY_KP_6, "Keypad 6"},
        {STRAT_KEY_KP_7, "Keypad 7"},
        {STRAT_KEY_KP_8, "Keypad 8"},
        {STRAT_KEY_KP_9, "Keypad 9"},
        {STRAT_KEY_KP_DECIMAL, "Keypad ."},
        {STRAT_KEY_KP_DIVIDE, "Keypad /"},
        {STRAT_KEY_KP_MULTIPLY, "Keypad *"},
        {STRAT_KEY_KP_SUBTRACT, "Keypad -"},
        {STRAT_KEY_KP_ADD, "Keypad +"},
        {STRAT_KEY_KP_ENTER, "Keypad Enter"},
        {STRAT_KEY_KP_EQUAL, "Keypad ="},


        {STRAT_KEY_LEFT_SHIFT, "Left Shift"},
        {STRAT_KEY_LEFT_CONTROL, "Left Ctrl"},
        {STRAT_KEY_LEFT_ALT, "Left Alt"},
        {STRAT_KEY_LEFT_SUPER, "Left Super"},
        {STRAT_KEY_RIGHT_SHIFT, "Right Shift"},
        {STRAT_KEY_RIGHT_CONTROL, "Right Ctrl"},
        {STRAT_KEY_RIGHT_ALT, "Right Alt"},
        {STRAT_KEY_RIGHT_SUPER, "Right Super"},
        {STRAT_KEY_MENU, "Menu"}
    };

    inline std::string KeyCodeToString(int Key) {
        auto it = KeyCodeMap.find(Key);
        if (it != KeyCodeMap.end()) {
            return it->second;
        }
        return "Unknown Key";
    }
}