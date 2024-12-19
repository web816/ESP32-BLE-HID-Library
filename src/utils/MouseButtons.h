#ifndef MOUSE_BUTTONS_H
#define MOUSE_BUTTONS_H

#include <stdint.h>

namespace Mouse {
    enum Button {
        NONE = 0x00,
        LEFT = 0x01,
        RIGHT = 0x02,
        MIDDLE = 0x04
    };
}

#endif