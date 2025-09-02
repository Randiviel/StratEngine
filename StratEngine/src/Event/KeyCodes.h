#pragma once
#include <string>
#include <unordered_map>

#define STRAT_KEY_A 65
#define STRAT_KEY_B 66
#define STRAT_KEY_C 67
#define STRAT_KEY_D 68
#define STRAT_KEY_E 69
#define STRAT_KEY_F 70
#define STRAT_KEY_G 71
#define STRAT_KEY_H 72
#define STRAT_KEY_I 73
#define STRAT_KEY_J 74
#define STRAT_KEY_K 75
#define STRAT_KEY_L 76
#define STRAT_KEY_M 77
#define STRAT_KEY_N 78
#define STRAT_KEY_O 79
#define STRAT_KEY_P 80
#define STRAT_KEY_Q 81
#define STRAT_KEY_R 82
#define STRAT_KEY_S 83
#define STRAT_KEY_T 84
#define STRAT_KEY_U 85
#define STRAT_KEY_V 86
#define STRAT_KEY_W 87
#define STRAT_KEY_X 88
#define STRAT_KEY_Y 89
#define STRAT_KEY_Z 90

#define STRAT_KEY_0 48
#define STRAT_KEY_1 49
#define STRAT_KEY_2 50
#define STRAT_KEY_3 51
#define STRAT_KEY_4 52
#define STRAT_KEY_5 53
#define STRAT_KEY_6 54
#define STRAT_KEY_7 55
#define STRAT_KEY_8 56
#define STRAT_KEY_9 57

#define STRAT_KEY_ESCAPE 0
#define STRAT_KEY_ENTER 1
#define STRAT_KEY_TAB 2
#define STRAT_KEY_BACKSPACE 3
#define STRAT_KEY_INSERT 4
#define STRAT_KEY_DELETE 5

#define STRAT_KEY_RIGHT 6
#define STRAT_KEY_LEFT 7
#define STRAT_KEY_DOWN 8
#define STRAT_KEY_UP 9

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

        {STRAT_KEY_ESCAPE, "Escape"},
        {STRAT_KEY_ENTER, "Enter"},
        {STRAT_KEY_TAB, "Tab"},
        {STRAT_KEY_BACKSPACE, "Backspace"},
        {STRAT_KEY_INSERT, "Insert"},
        {STRAT_KEY_DELETE, "Delete"},

        {STRAT_KEY_RIGHT, "Right Arrow"},
        {STRAT_KEY_LEFT, "Left Arrow"},
        {STRAT_KEY_DOWN, "Down Arrow"},
        {STRAT_KEY_UP, "Up Arrow"}
    };

    inline std::string KeyCodeToString(int Key) {
        auto it = KeyCodeMap.find(Key);
        if (it != KeyCodeMap.end()) {
            return it->second;
        }
        return "Unknown Key";
    }
}