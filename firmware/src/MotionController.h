#ifndef _MOTION_CONTROLLER_H_
#define _MOTION_CONTROLLER_H_

#include <stdint.h>
#include "ICS.h"

// サーボの数
#define SERVO_NUM 16

// モーションのスタックサイズ
#define MOTION_STACK_SIZE 1

// カウンタの数
#define CNT_NUM 8

// ボタン
#define BTN_UP		0x0001	// ↑
#define BTN_DOWN	0x0002	// ↓
#define BTN_RIGHT	0x0004	// →
#define BTN_LEFT	0x0008	// ←
#define BTN_Y		0x0010	// Y
#define BTN_A		0x0020	// A
#define BTN_B		0x0040	// B
#define BTN_X		0x0080	// X
#define BTN_R1		0x0100	// R1
#define BTN_R2		0x0200	// R2
#define BTN_L1		0x0400	// L1
#define BTN_L2		0x0800	// L2
#define BTN_ALL		0xFFFFFFFF
#define BTN_OFF		0x00000000

// 1フレームの時間[ms]
#define FRAME_TIME 15

// ニュートラル位置
#define NEUT_POS 7500

// コマンド
#define CMD_POS		0x00 // ポジション設定
#define CMD_SET		0x01 // パラメータ設定 (ストレッチ/スピード)
#define CMD_CNT		0x10 // カウンタ設定
#define CMD_JUMP	0x20 // ジャンプ
#define CMD_CALL	0x21 // コール
#define CMD_RET		0x22 // 復帰
#define CMD_HALT	0x23 // 停止
#define CMD_WAIT	0x30 // ウェイト

// パラメータ種別
#define SET_STRETCH	0x01 // ストレッチ
#define SET_SPEED	0x02 // スピード

// 分岐条件
#define COND_NONE		0x00 // 無条件
#define COND_LOOP		0x01 // ループ
#define COND_BTN		0x02 // ボタン(一致)
#define COND_BTN_ON		0x03 // ボタンON
#define COND_BTN_OFF	0x04 // ボタンOFF

// ポジション定数
#define POS_NO_CHANGE	0x7FFF // ポジション変更なし
#define POS_FREE		0x7000 // 脱力
#define POS_HOLD		0x7001 // 保持

// モーションデータ
struct MotionData
{
	uint8_t cmd;	// コマンド
	void* param;	// パラメータ
};

// ポジション設定命令のパラメータ
struct CmdPos
{
	uint16_t frame;			// フレーム数
	int16_t pos[SERVO_NUM];	// 各サーボのポジション
};

// パラメータ設定命令のパラメータ
struct CmdSet
{
	uint8_t type;			// パラメータ種別 (ストレッチ/スピード)
	int16_t val[SERVO_NUM];	// 各サーボのパラメータ値
};

// カウンタ設定命令のパラメータ
struct CmdCnt
{
	uint8_t  cnt;	// カウンタ番号
	uint16_t value;	// カウント値
};

// ジャンプ命令のパラメータ
struct CmdJump
{
	uint8_t  condType;	// 条件種別
	uint32_t condParam;	// 条件パラメータ 
	int8_t   dest;		// 行先
};

// コール命令のパラメータ
struct CmdCall
{
	uint8_t  condType;	// 条件種別
	uint32_t condParam;	// 条件パラメータ 
	const MotionData* dest;	// 行先
};

// ウェイト命令のパラメータ
struct CmdWait
{
	uint16_t frame;	// ウェイト時間(フレーム数)
};

// モーションコントローラ
class MotionController{
public:
	// サーボをセットする
	void setServo(IcsServo *servos);
	// トリム位置をセットする
	void setTrim(const int16_t *trims);
	// ホーム位置をセットする
	void setHome(const int16_t *pos, const uint8_t *stretch);
	// 開始する
	void begin(const MotionData* main_motion);
	// トリム位置に移動する
	void standTrim();
	// ホーム位置に移動する
	void standHome();
	// メインループから呼ぶ
	void loop();
	// ボタンフラグの値をセットする(ONする)
	void setButton(uint32_t buttonBit);
	// ボタンフラグの値をクリアする(OFFする)
	void clrButton(uint32_t buttonBit);
	// ボタンフラグの値を格納する(ON/OFFする)
	void movButton(uint32_t buttonBit);

private:
	// 各コマンド処理
	bool cmd_pos();		// ポジション設定命令
	bool cmd_set();		// パラメータ設定命令
	bool cmd_cnt();		// カウンタ設定命令
	bool cmd_jump();	// ジャンプ命令
	bool cmd_call();	// コール命令
	bool cmd_ret();		// 復帰命令
	bool cmd_halt();	// 停止命令
	bool cmd_wait();	// ウェイト命令
	// タイマ処理
	void startTimer();		// タイマー開始
	int getFrameTime();		// 経過フレーム時間取得

private:
	const MotionData *m_motion;	// 実行中のモーションデータへのポインタ
	const MotionData *m_stack[MOTION_STACK_SIZE]; // モーションデータのスタック
	int m_sp;					// モーションデータのスタック・ポインタ
	int m_pc;					// モーションデータのプログラム・カウンタ
	bool m_waiting;				// 待ち状態フラグ
	int m_cnt[CNT_NUM];			// カウンタ
	uint32_t m_button;			// ボタンフラグ
	
	IcsServo *m_servos;					// ICSサーボの配列へのポインタ
	int16_t m_trims[SERVO_NUM];			// ICSサーボのトリム位置(ニュートラル位置からのオフセット)
	int16_t m_homePos[SERVO_NUM];		// ICSサーボのホーム位置(トリム位置からのオフセット)
	uint8_t m_homeStretch[SERVO_NUM];	// ICSサーボのホームストレッチの配列
	
	uint16_t m_pos1[SERVO_NUM];			// ICSサーボの起点位置(POSコマンド移動前の位置)
	uint16_t m_pos2[SERVO_NUM];			// ICSサーボの目標位置(POSコマンド移動後の位置)
	int m_frameNum;						// フレーム数
	int m_frameCnt;						// フレーム数カウンタ
	
	uint32_t m_time_s;	// タイマ開始時刻
};

#endif
