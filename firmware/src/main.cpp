#include <M5Unified.h>
#include "StackChanHead.h"
#include "GamePad_PS4.h"
#include "ICS.h"
#include "MotionController.h"
#include "Motion.h"
#include "common.h"

// シリアルポートのピン割り当て
#define PIN_RXD1 27
#define PIN_TXD1 19
#define PIN_RXD2 13
#define PIN_TXD2 14

// ICSサーボ
IcsController ics1(Serial1, PIN_RXD1, PIN_TXD1); // 右半身系統
IcsController ics2(Serial2, PIN_RXD2, PIN_TXD2); // 左半身系統
IcsServo servos[SERVO_NUM];

// モーションコントローラ
MotionController motionCtrl;

// トリム位置
const int16_t TRIM_POS[SERVO_NUM]={
//  肩P(右,左) 肩R         肘          腿R         腿P         膝           足首P       足首R
    1350,-1350,-2700,-2700,    0,    0,    0,    0, -250, -250,-2000,-2000,  520,  520,    0,    0
};

// ホームポジション
const int16_t HOME_POS[SERVO_NUM]={
//  肩P(右,左) 肩R         肘          腿R         腿P         膝           足首P       足首R
     400, -400,    0,    0,-1200,-1200,    0,    0,  150,  150,  300,  300,  150,  150,    0,    0
};

// ホームストレッチ
const uint8_t HOME_STRETCH[SERVO_NUM]={
//  肩P(右,左) 肩R         肘          腿R         腿P         膝           足首P       足首R
      20,   20,   20,   20,   65,   65,   65,   65,   65,   65,   65,   65,   65,   65,   65,   65
};

// 送信バッファ
static char txbuff[256];

// ゲームパッド (PS4コントローラ)
GamePad *gamepad;
GamePad_PS4 gamepad_ps4;
bool gamepad_connected = false;

// スタックチャン
using namespace m5avatar;
StackChanHead head;

// 初期化
void setup()
{
	auto cfg = M5.config();
  	M5.begin(cfg);

  	// スタックチャンの初期化
	head.begin();
  	head.setMicroMotion(false);

	Serial.begin(115200);
	Serial.println("StackChanPwd Start");
	
	// MACアドレスの確認用
  	uint8_t btmac[6];
  	esp_read_mac(btmac, ESP_MAC_BT);
  	Serial.printf("[Bluetooth] Mac Address = %02X:%02X:%02X:%02X:%02X:%02X\n", 
    	btmac[0], btmac[1], btmac[2], btmac[3], btmac[4], btmac[5]);

	// ICSサーボの初期化
	ics1.begin();
	ics2.begin();
	for(int i=0; i<(SERVO_NUM/2); i++){
		servos[i*2  ].attach(ics1, 1+i); // 右半身のサーボ
		servos[i*2+1].attach(ics2, 1+i); // 左半身のサーボ
	}
	
	// モーションコントローラの初期化
	motionCtrl.setServo(servos);
	motionCtrl.setTrim(TRIM_POS);
	motionCtrl.setHome(HOME_POS, HOME_STRETCH);
	motionCtrl.begin(M000::motion);

#if 0	// デバッグ用 (サーボの位置を確認)
	while(1){
		if(Serial.available() > 0){
			char c = Serial.read();
			if(c == 's') break;
		}
		for(int i=0;i<SERVO_NUM;i++){
			uint16_t pos = servos[i].getPosition();
			Serial.print(pos);Serial.print(" ");
		}
		Serial.println(" ");
		delay(1000);
	}
	Serial.println("Servo position check finished.");
#endif

	// ホームポジションに移動
	Serial.println("Stand Home position.");
	motionCtrl.standHome();

 	// ゲームパッドの初期化
	gamepad = &gamepad_ps4;
	gamepad->begin();

	// スタックチャンを居眠り状態に
	head.setBaseExpression(Expression::Sleepy);
	head.setExpression(Expression::Sleepy);
}

// メインループ
void loop()
{
	motionCtrl.loop();
	ics1.loop();
	ics2.loop();
	
	// ゲームパッド
  	if (gamepad->isConnected()) {
		if (!gamepad_connected) {
			Serial.println("GamePad connected.");
			gamepad_connected = true;
			head.setBaseExpression(Expression::Neutral);
			head.setExpression(Expression::Happy, 2000);
			head.setSpeachText("ゲームパッド接続", 2000);
			head.setMicroMotion(true);
		}
		// ゲームパッドのボタン状態を取得
		static uint32_t buttonFlag_prev = 0xFFFFFFFF;
    	uint32_t buttonFlag = gamepad->getButton();
		// ボタンフラグをモーションコントローラにセット
		motionCtrl.movButton(buttonFlag);
		if(buttonFlag != buttonFlag_prev) {
    		Serial.printf("Button Flag: 0x%08X\n", buttonFlag);
			//M5.Lcd.printf("Button Flag: 0x%08X\n", buttonFlag);
		}
		buttonFlag_prev = buttonFlag;

  	}else{
		if (gamepad_connected) {
			Serial.println("GamePad disconnected.");
			gamepad_connected = false;
			head.setBaseExpression(Expression::Sleepy);
			head.setExpression(Expression::Neutral, 2000);
			head.setSpeachText("ゲームパッド切断", 2000);
			head.setMicroMotion(false);
		}
	}

	// 開発用 (シリアル通信でのボタン入力)
	if(Serial.available() > 0){
		char c = Serial.read();
		if(c == '1') motionCtrl.setButton(BTN_L1);
		if(c == '2') motionCtrl.setButton(BTN_L2);
		if(c == '3') motionCtrl.setButton(BTN_R1);
		if(c == '4') motionCtrl.setButton(BTN_R2);
		if(c == 'a') motionCtrl.setButton(BTN_LEFT);
		if(c == 's') motionCtrl.setButton(BTN_DOWN);
		if(c == 'd') motionCtrl.setButton(BTN_UP);
		if(c == 'f') motionCtrl.setButton(BTN_RIGHT);
		if(c == 'h') motionCtrl.setButton(BTN_X);
		if(c == 'j') motionCtrl.setButton(BTN_A);
		if(c == 'k') motionCtrl.setButton(BTN_Y);
		if(c == 'l') motionCtrl.setButton(BTN_B);
		if(c == ' ') motionCtrl.clrButton(BTN_ALL);
	}
	
	// スタックチャン
	static const MotionData *motion_prev = M000::motion;
	const MotionData *motion = motionCtrl.getPresentMotion();
	if(motion != motion_prev) {
		motion_prev = motion;

		// モーションに応じてスタックチャンの表情を変える
		if((motion == M201::motion) || // パンチ左ストレート
		   (motion == M202::motion) || // パンチ右ストレート
		   (motion == M211::motion) || // A+←: パンチ左裏拳
		   (motion == M212::motion) || // A+→: パンチ右裏拳
		   (motion == M220::motion)    // A+↓: 防御
		){
			head.setExpression(Expression::Angry);
		}else{
			head.setExpression(Expression::Neutral);
		}
		// モーションに応じてスタックチャンの顔の向きを変える
		if       (motion == M003::motion) { // ←: 歩行左
			head.setPosition( 50, 0);
		} else if(motion == M004::motion) { // →: 歩行右
			head.setPosition(-50, 0);
		} else if(motion == M201::motion) {	// パンチ左ストレート
			head.setPosition( 25, 0);
		} else if(motion == M202::motion) {	// パンチ右ストレート
			head.setPosition(-25, 0);
		} else if(motion == M211::motion) { // A+←: パンチ左裏拳
			head.setPosition( 50, 0);
		} else if(motion == M212::motion) { // A+→: パンチ右裏拳
			head.setPosition(-50, 0);
		} else if(motion == M220::motion) { // A+↓: 防御
			head.setPosition(  0, -25);
		} else {
			head.setPosition(  0, 0);
		}
		// モーションに応じてスタックチャンの不随意運動を有効/無効にする
		if(motion == M000::motion){
			head.setMicroMotion(true);
		}else{
			head.setMicroMotion(false);
		}
	}
	head.loop();
}
