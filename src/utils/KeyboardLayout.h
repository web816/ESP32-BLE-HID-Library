#ifndef KEYBOARD_LAYOUT_H
#define KEYBOARD_LAYOUT_H

#include <stdint.h>

namespace Keyboard {
    // HID Keyboard/Keypad Usage IDs
    enum KeyCode {
        NONE = 0x00,
        A = 0x04,
        B = 0x05,
        C = 0x06,
        // ... (other key definitions)
        UP_ARROW = 0x52,
        NUM_LOCK = 0x53
    };

    // Modifier Keys
    enum Modifier {
        NONE = 0x00,
        LEFT_CTRL = 0x01,
        LEFT_SHIFT = 0x02,
        LEFT_ALT = 0x04,
        LEFT_GUI = 0x08,
        RIGHT_CTRL = 0x10,
        RIGHT_SHIFT = 0x20,
        RIGHT_ALT = 0x40,
        RIGHT_GUI = 0x80
    };
}

#endif