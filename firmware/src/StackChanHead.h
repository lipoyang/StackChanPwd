#pragma once

#include <M5Unified.h>
#include <Avatar.h>

// スタックチャン頭部クラス
class StackChanHead
{
public:
    void begin();
    void loop();
    void setExpression(m5avatar::Expression expression, int duration_ms = 0);
    void setSpeachText(const char *text, int duration_ms = 0);
    void clearSpeachText();
    void setPosition(int x, int y);
    void setGaze(float x, float y);
    void setMicroMotion(bool enable);
    bool isMicroMotionEnabled() const { return isMicroMotion; }

private:
    bool isMicroMotion = false;
    uint32_t t0_expression;
    uint32_t t0_speech;
    uint32_t T_expression = 0;
    uint32_t T_speech = 0;
};