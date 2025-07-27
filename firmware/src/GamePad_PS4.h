#pragma once

#include "GamePad.h"

// PS4 GamePad class
class GamePad_PS4 : public GamePad
{
public:
    void begin() override;
    bool isConnected() override;
    uint32_t getButton() override;
private:
    uint8_t _btmac[6];
};