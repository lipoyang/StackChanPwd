// PS4 GamePad class

#include <Arduino.h>
#include <PS4Controller.h>

#include "GamePad_PS4.h"

// initialize GamePad
void GamePad_PS4::begin()
{
    esp_read_mac(_btmac, ESP_MAC_BT);
    Serial.printf("[Bluetooth] Mac Address = %02X:%02X:%02X:%02X:%02X:%02X\n", 
        _btmac[0], _btmac[1], _btmac[2], _btmac[3], _btmac[4], _btmac[5]);

    PS4.begin();
};

// check if GamePad is connected
bool GamePad_PS4::isConnected()
{
    return PS4.isConnected();
}

// get button state from GamePad
uint32_t GamePad_PS4::getButton()
{
    uint32_t buttonFlag = 0;
    ps4_button_t button = PS4.getButton();
    if (button.down)     buttonFlag |= BTN_DOWN;
    if (button.left)     buttonFlag |= BTN_LEFT;
    if (button.right)    buttonFlag |= BTN_RIGHT;
    if (button.up)       buttonFlag |= BTN_UP;
    if (button.cross)    buttonFlag |= BTN_A;
    if (button.circle)   buttonFlag |= BTN_B;
    if (button.square)   buttonFlag |= BTN_X;
    if (button.triangle) buttonFlag |= BTN_Y;
    if (button.l1)       buttonFlag |= BTN_L1;
    if (button.r1)       buttonFlag |= BTN_R1;
    if (button.l2)       buttonFlag |= BTN_L2;
    if (button.r2)       buttonFlag |= BTN_R2;

    return buttonFlag;
}