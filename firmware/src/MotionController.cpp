#include <Arduino.h>
#include "MotionController.h"

#define DEBUG
#ifdef DEBUG
#define DEBUG_PRINT(x)		Serial.print(x)
#define DEBUG_PRINTLN(x)	Serial.println(x)
#else
#define DEBUG_PRINT(x)		
#define DEBUG_PRINTLN(x)	
#endif

// サーボの応答のためのウェイト[usec] ※現状、一部に同期処理が使われているため
#define SERVO_WAIT	400

// サーボを設定する
// servos: ICSサーボの配列
void MotionController::setServo(IcsServo *servos)
{
	m_servos = servos;
}

// トリム位置を設定する
// servos: トリム位置の配列
void MotionController::setTrim(const int16_t *trims)
{
	for(int i=0;i<SERVO_NUM;i++){
		m_trims[i] = trims[i];
	}
}

// ホーム位置をセットする
void MotionController::setHome(const int16_t *pos, const uint8_t *stretch)
{
	for(int i=0;i<SERVO_NUM;i++){
		m_homePos[i]     = pos[i];
		m_homeStretch[i] = stretch[i];
	}
}

// 開始する
// main_motion: メインのモーションデータ
void MotionController::begin(const MotionData* main_motion)
{
	// 変数の初期化
	m_motion = main_motion;
	m_sp = 0;
	m_pc = 0;
	m_waiting = false;
}

// トリム位置に移動する
void MotionController::standTrim()
{
	for(int i=0;i<SERVO_NUM;i++){
		uint16_t pos = (uint16_t)(NEUT_POS + m_trims[i]);
		m_servos[i].setPosition(pos);
		m_pos1[i] = pos;
	}
}

// ホーム位置に移動する
void MotionController::standHome()
{
	// ホームストレッチの設定
	for(int i=0;i<SERVO_NUM;i++){
		m_servos[i].setStretch(m_homeStretch[i]);
	}
	// ホームポジションの計算
	for(int i=0;i<SERVO_NUM;i++){
		m_pos2[i] = (uint16_t)(NEUT_POS + m_trims[i] + m_homePos[i]);
	}

	// 現在位置の取得
	for(int i=0;i<SERVO_NUM;i++){
		uint16_t pos = 0xFFFF;
		pos = m_servos[i].getPosition();
		if((pos >= 3500) && (pos <= 11500)){
			m_pos1[i] = pos;
		}else{
			m_pos1[i] = m_pos2[i]; // 取得失敗したらホームポジション
		}
		delayMicroseconds(SERVO_WAIT);
		//Serial.print(m_pos1[i]);Serial.print(" ");
	}
	//Serial.println(" ");
	
	// 中割りして現在位置からホームポジションへ移動
	m_frameNum = 70;
	for(m_frameCnt = 0; m_frameCnt <= m_frameNum; m_frameCnt++){
		for(int i=0;i<SERVO_NUM;i++){
			int p1 = m_pos1[i];
			int p2 = m_pos2[i];
			int p = p1 + (p2 - p1) * m_frameCnt / m_frameNum;
			m_servos[i].setPosition(p);
		}
		delay(FRAME_TIME);
	}
	// ホームポジションの計算
	for(int i=0;i<SERVO_NUM;i++){
		m_pos1[i] = (uint16_t)(NEUT_POS + m_trims[i] + m_homePos[i]);
	}
}

// メインループから呼ぶ
void MotionController::loop()
{
	bool next = false; // 次の命令に進むか？
	
	// 各命令の処理
	switch (m_motion[m_pc].cmd){
		case CMD_POS:
			next = cmd_pos();
			break;
		case CMD_SET:
			next = cmd_set();
			break;
		case CMD_CNT:
			next = cmd_cnt();
			break;
		case CMD_JUMP:
			next = cmd_jump();
			break;
		case CMD_CALL:
			next = cmd_call();
			break;
		case CMD_RET:
			next = cmd_ret();
			break;
		case CMD_HALT:
			next = cmd_halt();
			break;
		case CMD_WAIT:
			next = cmd_wait();
			break;
	}
	
	// 次の命令に進むか？
	if (next)
	{
		m_pc++;
		m_waiting = false;
		//DEBUG_PRINT("PC=");
		//DEBUG_PRINTLN(m_pc);
	}
}

// ボタンフラグの値をセットする(ONする)
// buttonFlag: ボタンフラグ
void MotionController::setButton(uint32_t buttonFlag)
{
	//DEBUG_PRINT("BUTTON ON: ");
	//DEBUG_PRINTLN(buttonFlag);
	m_button |= buttonFlag;
}

// ボタンフラグの値をクリアする(OFFする)
// buttonFlag: ボタンフラグ
void MotionController::clrButton(uint32_t buttonFlag)
{
	//DEBUG_PRINT("BUTTON OFF: ");
	//DEBUG_PRINTLN(buttonFlag);
	m_button &= ~buttonFlag;
}

// ボタンフラグの値を格納する(ON/OFFする)
// buttonFlag: ボタンフラグ
void MotionController::movButton(uint32_t buttonFlag)
{
	//DEBUG_PRINT("BUTTON MOV: ");
	//DEBUG_PRINTLN(buttonFlag);
	m_button = buttonFlag;
}

// ポジション設定命令
bool MotionController::cmd_pos()
{
	// ICSコマンド送信
	if (m_waiting == false){
		m_waiting = true;
		DEBUG_PRINT("POS ");

		CmdPos *param = (CmdPos*)m_motion[m_pc].param;
		int16_t *pos = param->pos;
		m_frameNum = param->frame;
		m_frameCnt = 1;
		
		// 脱力指示のときは m_frameNum = 0 とする
		if(m_frameNum == 0){
			for (int i = 0; i < SERVO_NUM; i++){
				// 脱力
				if (pos[i] == POS_FREE){
					DEBUG_PRINT("FREE ");
					m_servos[i].setPosition(0); // 0で脱力
				}
				// 保持
				else if(pos[i] == POS_HOLD){
					DEBUG_PRINT("HOLD ");
					// 現在位置取得
					uint16_t pos = 0xFFFF;
					pos = m_servos[i].getPosition();
					if((pos >= 3500) && (pos <= 11500)){
						m_pos1[i] = pos;
					}else{
						// 失敗したらホームポジション
						m_pos1[i] = (uint16_t)(NEUT_POS + m_trims[i] + m_homePos[i]);
					}
					delayMicroseconds(SERVO_WAIT);
					
					m_servos[i].setPosition(m_pos1[i]);
					delayMicroseconds(SERVO_WAIT);
				}else{
					DEBUG_PRINT("NO_CHANGE ");
				}
			}
			DEBUG_PRINT("\n");
			return true;
		}
		
		// 各サーボの目標位置
		for (int i = 0; i < SERVO_NUM; i++){
			if (pos[i] != POS_NO_CHANGE){
				m_pos2[i] = NEUT_POS + m_trims[i] + pos[i];
				DEBUG_PRINT(pos[i]);
				DEBUG_PRINT(" ");
			}
			else{
				m_pos2[i] = POS_NO_CHANGE;
				DEBUG_PRINT("NO_CHANGE ");
			}
		}
		DEBUG_PRINT("\n");
		
		// 中割り
		for (int i = 0; i < SERVO_NUM; i++){
			if (pos[i] != POS_NO_CHANGE){
				int p1 = m_pos1[i];
				int p2 = m_pos2[i];
				int p = p1 + (p2 - p1) * m_frameCnt / m_frameNum;
				m_servos[i].requestPosition(p);
				//DEBUG_PRINT(p);
				//DEBUG_PRINT(" ");
			}
			else{
				//DEBUG_PRINT("NO_CHANGE ");
			}
		}
		//DEBUG_PRINT("\n");
		
		// タイマ開始
		startTimer();
		
		return false;
	}
	// 指定フレーム数待ち
	else{
		// 次フレームか？
		int frame = getFrameTime();
		if (frame >= m_frameCnt){
			m_frameCnt++;
			// 指定フレーム数完了か？
			if(m_frameCnt > m_frameNum){
				for (int i = 0; i < SERVO_NUM; i++){
					if (m_pos2[i] != POS_NO_CHANGE){
						m_pos1[i] = m_pos2[i];
					}
				}
				return true;
			}
			// 中割り
			else{
				for (int i = 0; i < SERVO_NUM; i++){
					if (m_pos2[i] != POS_NO_CHANGE){
						int p1 = m_pos1[i];
						int p2 = m_pos2[i];
						int p = p1 + (p2 - p1) * m_frameCnt / m_frameNum;
						m_servos[i].requestPosition(p);
						//DEBUG_PRINT(p);
						//DEBUG_PRINT(" ");
					}
					else{
						//DEBUG_PRINT("NO_CHANGE ");
					}
				}
				//DEBUG_PRINT("\n");
				return false;
			}
		}
		return false;
	}
}

// パラメータ設定命令
bool MotionController::cmd_set()
{
	// ICSコマンド送信
#if 0
	if (m_waiting == false){
		m_waiting = true;
#endif
		CmdSet *param = (CmdSet*)m_motion[m_pc].param;
		uint8_t type = param->type;
		int16_t *val = param->val;
		
		// ストレッチの設定
		if(type == SET_STRETCH){
			DEBUG_PRINT("SET STRETCH ");
			// 各サーボ
			for (int i = 0; i < SERVO_NUM; i++)
			{
				if (val[i] != -1){
					m_servos[i].setStretch((uint8_t)val[i]);
					delayMicroseconds(SERVO_WAIT);
					DEBUG_PRINT((uint8_t)val[i]);
				}else{
					DEBUG_PRINT("NO");
				}
				DEBUG_PRINT(" ");
			}
		}
		// スピードの設定
		else{
			DEBUG_PRINT("SET SPEED ");
			// 各サーボ
			for (int i = 0; i < SERVO_NUM; i++)
			{
				if (val[i] != -1){
					m_servos[i].setSpeed((uint8_t)val[i]);
					delayMicroseconds(SERVO_WAIT);
					DEBUG_PRINT(val[i]);
				}else{
					DEBUG_PRINT("NO");
				}
				DEBUG_PRINT(" ");
			}
		}
		DEBUG_PRINT("\n");
		return true; // 現状ではパラメータ設定メソッドは同期待ちのみ
#if 0
		return false;
	}
	// 通信完了待ち
	else{
		if (s_timer_flag){
			return true;
		}
		return false;
	}
#endif
}

// カウンタ設定命令
bool MotionController::cmd_cnt()
{
	CmdCnt *param = (CmdCnt*)m_motion[m_pc].param;
	int cnt = param->cnt;
	int val = param->value;
	
	DEBUG_PRINT("SET CNT ");
	if (cnt < CNT_NUM)
	{
		DEBUG_PRINT("CNT[");DEBUG_PRINT(cnt);DEBUG_PRINT("]=");DEBUG_PRINTLN(val);
		m_cnt[cnt] = val;
	}
	else
	{
		DEBUG_PRINT("BAD PARAMETER ");
		DEBUG_PRINTLN(cnt);
	}

	return true;
}

// ジャンプ命令
bool MotionController::cmd_jump()
{
	CmdJump *param = (CmdJump*)m_motion[m_pc].param;
	uint8_t condType = param->condType;
	uint32_t condParam = param->condParam;
	int8_t dest = param->dest;
	
	bool flag = false; // ジャンプするか？
	
	// 条件種別
	switch (condType)
	{
		// 無条件
		case COND_NONE:
			//DEBUG_PRINT("JUMP ");
			flag = true;
			break;
		// ループ
		case COND_LOOP:
			DEBUG_PRINT("JUMP LOOP ");
			if (condParam < CNT_NUM){
				m_cnt[condParam]--;
				DEBUG_PRINT("CNT[");DEBUG_PRINT(condParam);	DEBUG_PRINT("] = ");
				DEBUG_PRINTLN(m_cnt[condParam]);
				if (m_cnt[condParam] > 0){
					DEBUG_PRINT("JUMP LOOP ");
					DEBUG_PRINTLN(m_pc + dest);
					flag = true;
				}else{
					DEBUG_PRINTLN("LOOP END");
				}
			}else{
				DEBUG_PRINT("BAD PARAMETER ");
				DEBUG_PRINTLN(condParam);
			}
			break;
		// ボタン(一致)
		case COND_BTN:
			if (m_button == condParam){
				//DEBUG_PRINT("JUMP BTN ");
				DEBUG_PRINTLN(m_pc + dest);
				flag = true;
			}
			break;
		// ボタンON
		case COND_BTN_ON:
			if ((m_button & condParam) == condParam){
				//DEBUG_PRINT("JUMP BTN_ON ");
				DEBUG_PRINTLN(m_pc + dest);
				flag = true;
			}
			break;
		// ボタンOFF
		case COND_BTN_OFF:
			if ((m_button & condParam) == 0){
				//DEBUG_PRINT("JUMP BTN_OFF ");
				flag = true;
			}
			break;
	}
	
	// ジャンプするか？
	if (flag){
		m_pc += dest; // 行先(相対ジャンプ)
		m_waiting = false;
		return false; // ジャンプするので次の命令には進まない
	}else{
		return true; // ジャンプせず次の命令に進む
	}
}

// コール命令
bool MotionController::cmd_call()
{
	CmdCall *param = (CmdCall*)m_motion[m_pc].param;
	uint8_t condType = param->condType;
	uint32_t condParam = param->condParam;
	const MotionData *dest = param->dest;

	bool flag = false; // コールするか？
	
	// 条件種別
	switch (condType)
	{
		// 無条件
		case COND_NONE:
			DEBUG_PRINT("CALL ");
			flag = true;
			break;
		// ボタン(一致)
		case COND_BTN:
			if (m_button == condParam){
				DEBUG_PRINT("CALL BTN ");
				flag = true;
			}
			break;
		// ボタンON
		case COND_BTN_ON:
			if ((m_button & condParam) == condParam){
				DEBUG_PRINT("CALL BTN_ON ");
				flag = true;
			}
			break;
		// ボタンOFF
		case COND_BTN_OFF:
			if ((m_button & condParam) == 0){
				DEBUG_PRINT("CALL BTN_OFF ");
				flag = true;
			}
			break;
	}
	
	// コールするか？
	if (flag){
		if (m_sp < MOTION_STACK_SIZE){
			DEBUG_PRINTLN("");
			m_stack[m_sp] = m_motion;
			m_sp++;
			m_motion = param->dest; // 行先のモーションデータ
			m_pc = 0;
			m_waiting = false;
			return false; // コールするので次の命令には進まない
		}
		return true; // コールせず次の命令に進む
	}else{
		return true; // コールせず次の命令に進む
	}
}

// 復帰命令
bool MotionController::cmd_ret()
{
	if (m_sp > 0){
		DEBUG_PRINTLN("RET");
		m_sp--;
		m_motion = m_stack[m_sp]; // 戻り先のモーションデータ
		m_pc = 0;
		m_waiting = false;
	}
	return false;
}

// 停止命令
bool MotionController::cmd_halt()
{
	static bool flag = false;
	if (!flag){
		flag = true;
		DEBUG_PRINTLN("HALT");
	}

	// 何もしない
	return false;
}

// ウェイト命令
bool MotionController::cmd_wait()
{
	// ICSコマンド送信
	if (m_waiting == false){
		m_waiting = true;
		DEBUG_PRINT("WAIT\n");

		CmdPos *param = (CmdPos*)m_motion[m_pc].param;
		m_frameNum = param->frame;
		m_frameCnt = 1;
		
		// タイマ開始
		startTimer();
		
		return false;
	}
	// 指定フレーム数待ち
	else{
		// 次フレームか？
		int frame = getFrameTime();
		if (frame >= m_frameCnt){
			m_frameCnt++;
			// 指定フレーム数完了か？
			if(m_frameCnt > m_frameNum){
				return true;
			}
		}
		return false;
	}
}

// タイマー開始
void MotionController::startTimer()
{
	// 開始時刻[usec]
	m_time_s = (uint32_t)micros();
}

// 経過フレーム時間取得
int MotionController::getFrameTime()
{
	// 現在時刻[usec]
	uint32_t now = (uint32_t)micros();
	// 経過時間[usec]
	uint32_t elapsed = now - m_time_s;
	if(elapsed > UINT32_MAX/2){ // for GR-ROSE(beta)'s bug
		elapsed = 0;
	}
	// 経過フレーム
	int frame = elapsed / 1000 / FRAME_TIME;
	
	return frame;
}

