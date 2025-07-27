#include <M5Unified.h>
//#include <stdint.h>
//#include <Arduino.h>
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

// TODO
// UDP通信クラス
//UdpComm udpComm;
// UDP受信コールバック
//void udpComm_callback(char* buff);

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
//  head.setMicroMotion(true);
  	head.setMicroMotion(false);
	head.setExpression(Expression::Sleepy);

	Serial.begin(115200);
	Serial.println("StackChanPwd Start");
//	M5.Lcd.begin();
//	M5.Lcd.setTextSize(2);
//	M5.Lcd.setTextColor(TFT_WHITE, TFT_BLACK);
//	M5.Lcd.setCursor(0, 0);
//	M5.Lcd.println("StackChanPwd Start");
	delay(3000);

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

#if 1	// デバッグ用 (サーボの位置を確認)
	while(1){
		if(Serial.available() > 0){
			char c = Serial.read();
			if(c == 'b') break;
		}
		M5.update();
		if(M5.BtnA.wasPressed()){
			Serial.println("ButtonA.");
			//M5.Lcd.println("ButtonA.");
			break;
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
	// TODO
	// UDP通信の設定
//	udpComm.begin();
//	udpComm.onReceive = udpComm_callback;
	
#if 0
	// シリアル通信で's'を受信するか
	// ピン20がHIGHであれば動作開始
	//pinMode(20, INPUT_PULLUP);
	while(1)
	{
		if(Serial.available() > 0){
			char c = Serial.read();
			if(c == 's') break;
		}
		//if(digitalRead(20) == HIGH){
		//	break;
		//}
	}
#endif
	// ホームポジションに移動
	Serial.println("Stand Home position.");
	motionCtrl.standHome();

 	// ゲームパッドの初期化
	gamepad = &gamepad_ps4;
	gamepad->begin();
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
			head.setExpression(Expression::Happy, 2000);
			head.setSpeachText("ゲームパッド接続", 2000);
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
		if (!gamepad_connected) {
			Serial.println("GamePad not connected.");
			gamepad_connected = true;
			head.setExpression(Expression::Neutral, 2000);
			head.setSpeachText("ゲームパッド切断", 2000);
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
	head.loop();
}

#if 0 // TODO
/**
 * 受信したコマンドの実行
 *
 * @param buff 受信したコマンドへのポインタ
 */
void udpComm_callback(char* buff)
{
	uint16_t val;
	int sval;
	
	Serial.print("udpComm_callback:");Serial.println(buff);
	
	switch(buff[0])
	{
	/* Dコマンド(デジタルボタン)
	   書式: #Dxx$
	   xx: 0のとき停止、正のとき前進、負のとき後退。
	 */
	case 'D':
		// 値の解釈
		if( HexToUint16(&buff[1], &val, 4) != 0 ) break;
		Serial.print("D:");
		Serial.println(val);
		motionCtrl.movButton(val);
		break;
	}
}
#endif

