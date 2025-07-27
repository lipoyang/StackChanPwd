#pragma once
#include <stdint.h>

// ボタン
#define BTN_UP      0x0001	// ↑
#define BTN_DOWN    0x0002	// ↓
#define BTN_RIGHT   0x0004	// →
#define BTN_LEFT    0x0008	// ←
#define BTN_Y       0x0010	// Y
#define BTN_A       0x0020	// A
#define BTN_B       0x0040	// B
#define BTN_X       0x0080	// X
#define BTN_R1      0x0100	// R1
#define BTN_R2      0x0200	// R2
#define BTN_L1      0x0400	// L1
#define BTN_L2      0x0800	// L2
#define BTN_ALL     0xFFFFFFFF
#define BTN_OFF     0x00000000

// Abstract class for GamePad interface
class GamePad
{
public:
    virtual void begin() = 0;           // Initialize the gamepad
    virtual bool isConnected() = 0;     // Check if the gamepad is connected
    virtual uint32_t getButton() = 0;   // Get the current button state
};
