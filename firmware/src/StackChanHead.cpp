// スタックチャン頭部クラス

#include "StackChanHead.h"
#include "RcServo.h"

#define SERVO_CH_X 0
#define SERVO_CH_Y 1

using namespace m5avatar;

static StackChanHead *head;
static Avatar avatar;
static RcServo servos; // PCA9685サーボドライバ

// サーボの向きとゼロ点オフセット
static const int SERVO_POLARITY[]= { 1,  1 };
static const int SERVO_OFFSET[]  = { -3,  0 };

// 首のサーボの初期化
static void servo_setup()
{
    servos.begin();
    for(int i=0;i<2;i++){
        servos.setPolarity(SERVO_CH_X+i, SERVO_POLARITY[i]);
        servos.setOffset  (SERVO_CH_X+i, SERVO_OFFSET[i]);
    }
    servos.setInitialPosition(SERVO_CH_X, 0);
    servos.setInitialPosition(SERVO_CH_Y, 0);
}

// 首のサーボのタスク
static void task_servo(void *args)
{
  float gazeX, gazeY;
  DriveContext *ctx = (DriveContext *)args;
  Avatar *avatar = ctx->getAvatar();
  for (;;)
  {
    if(head->isMicroMotionEnabled())
    {
      avatar->getGaze(&gazeY, &gazeX);
      servos.setTargetPosition(SERVO_CH_X, (int)(15.0 * gazeX));
      if(gazeY < 0) {
        int tmp = (int)(10.0 * gazeY);
        if(tmp > 10) tmp = 10;
        servos.setTargetPosition(SERVO_CH_Y, tmp);
      } else {
        servos.setTargetPosition(SERVO_CH_Y, (int)(10.0 * gazeY));
      }
    }
    servos.control(SERVO_CH_X);
    servos.control(SERVO_CH_Y);
    
    delay(50);
  }
}

// スタックチャン頭部の初期化
void StackChanHead::begin()
{
    head = this;

    servo_setup();
    delay(1000);

    avatar.init();
    avatar.addTask(task_servo, "servo");
    avatar.setSpeechFont(&fonts::efontJA_16);
    avatar.setSpeechText("こんにちは");
    delay(2000);
    avatar.setSpeechText("");
}

// スタックチャン頭部のループ処理
void StackChanHead::loop()
{
    uint32_t now = millis();

    if (T_expression > 0 && (now - t0_expression) >= T_expression) {
        avatar.setExpression(baseExpression);
        T_expression = 0;
    }

    if (T_speech > 0 && (now - t0_speech) >= T_speech) {
        avatar.setSpeechText("");
        T_speech = 0;
    }
}

// スタックチャンの表情を設定
void StackChanHead::setExpression(Expression expression, int duration_ms)
{
    avatar.setExpression(expression);
    if (duration_ms > 0) {
        t0_expression = millis();
        T_expression = duration_ms;
    }
}

// スタックチャンのセリフを設定
void StackChanHead::setSpeachText(const char *text, int duration_ms)
{
    avatar.setSpeechText(text);
    if (duration_ms > 0) {
        t0_speech = millis();
        T_speech = duration_ms;
    }
}

// スタックチャンのセリフをクリア
void StackChanHead::clearSpeachText()
{
    avatar.setSpeechText("");
}

// スタックチャンの首サーボ角度を設定
void StackChanHead::setPosition(int x, int y)
{
    isMicroMotion = false;
    servos.setPosition(SERVO_CH_X, x);
    servos.setPosition(SERVO_CH_Y, y);
}

// スタックチャンの首サーボの不随意運動の有効/無効を設定
void StackChanHead::setMicroMotion(bool enable)
{
    isMicroMotion = enable;
    if (enable) {
        servos.setTargetPosition(SERVO_CH_X, 0);
        servos.setTargetPosition(SERVO_CH_Y, 0);
    }
}

// スタックチャンの視線を設定
void StackChanHead::setGaze(float x, float y)
{
    avatar.setGaze(y, x); // Note: y is vertical, x is horizontal
}