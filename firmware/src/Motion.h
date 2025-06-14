#include "MotionController.h"

// このモーションは近藤科学KXR-L2用サンプルプロジェクトV1.1をもとにしています。
// Copyright (C) 2013 Kondo Kagaku co.,ltd. All Rights Reserved.

// ↑: 歩行前
namespace M001{
    const CmdSet ServoParam1={SET_STRETCH,{ -1, -1, -1, -1, -1, -1, 60, 60, 60, 60, 60, 60, 60, 60, 60, 60}};
    const CmdPos Pos1={  5,{  400, -400,    0,    0,-1200,-1200,    0,    0,  150,  250,  300,  500,  150,  250, -200, -150}};
    const CmdPos Pos2={ 12,{    0,    0,    0,    0,-1200,-1200,    0,    0,  600,   50, 1200,    0,  800,  150,    0, -300}};
    const CmdPos Pos4={  4,{  400,  400,    0,    0,-1200,-1200,  -50,    0,  500, -200, 1000,  -30,  500,  200,    0, -200}};
    const CmdPos Pos5={  3,{  400,  400,    0,    0,-1200,-1200,  -50,    0,  500, -400,  600,  -50,  100,  350,    0, -200}};
    const CmdSet ServoParam2={SET_STRETCH,{ -1, -1, -1, -1, -1, -1, 90, 40,100, 40,100, 40,100, 40, 90, 40}};
    const CmdPos Pos6={  8,{  400,  400,    0,    0,-1200,-1200,    0,    0,  800, -400, 1100,    0,  400,  400,  200,  200}};
    const CmdJump CmpButton1={COND_BTN_OFF, BTN_UP, +9};
    const CmdPos Pos7={ 10,{    0,    0,    0,    0,-1200,-1200,    0,   50,   50,  600,    0, 1200,  120,  550,  250,    0}};
    const CmdPos Pos8={  4,{ -400, -400,    0,    0,-1200,-1200,    0,   50, -200,  500,  -30, 1000,  200,  500,  200,    0}};
    const CmdPos Pos9={  3,{ -400, -400,    0,    0,-1200,-1200,    0,   50, -400,  500,  -50,  600,  350,  100,  200,    0}};
    const CmdSet ServoParam3={SET_STRETCH,{ -1, -1, -1, -1, -1, -1, 60, 90, 40,100, 40,100, 40,100, 60, 90}};
    const CmdPos Pos10={  8,{ -400, -400,    0,    0,-1200,-1200,    0,    0, -400,  800,    0, 1100,  400,  400, -200, -200}};
    const CmdJump CmpButton2={COND_BTN_OFF, BTN_UP, +3};
    const CmdPos Pos3={ 10,{    0,    0,    0,    0,-1200,-1200,  -50,    0,  600,   50, 1200,    0,  550,  120,    0, -250}};
    const CmdJump Jump1={COND_NONE, 0, -12};
    const CmdSet HomeStretch={SET_STRETCH,{ 20, 20, 20, 20, 65, 65, 65, 65, 65, 65, 65, 65, 65, 65, 65, 65}};
    const CmdPos HomePos={ 10,{  400, -400,    0,    0,-1200,-1200,    0,    0,  150,  150,  300,  300,  150,  150,    0,    0}};
    
    const MotionData motion[] = {
        { CMD_SET, (void*)&ServoParam1 },
        { CMD_POS, (void*)&Pos1 },
        { CMD_POS, (void*)&Pos2 },
        { CMD_POS, (void*)&Pos4 },
        { CMD_POS, (void*)&Pos5 },
        { CMD_SET, (void*)&ServoParam2 },
        { CMD_POS, (void*)&Pos6 },
        { CMD_JUMP,(void*)&CmpButton1 },
        { CMD_POS, (void*)&Pos7 },
        { CMD_POS, (void*)&Pos8 },
        { CMD_POS, (void*)&Pos9 },
        { CMD_SET, (void*)&ServoParam3 },
        { CMD_POS, (void*)&Pos10 },
        { CMD_JUMP,(void*)&CmpButton2 },
        { CMD_POS, (void*)&Pos3 },
        { CMD_JUMP,(void*)&Jump1 },
        { CMD_SET, (void*)&HomeStretch },
        { CMD_POS, (void*)&HomePos },
        { CMD_RET, NULL }
    };
}

// ↓: 歩行後
namespace M002{
    const CmdSet ServoParam1={SET_STRETCH,{ -1, -1, -1, -1, -1, -1, 60, 60, 60, 60, 60, 60, 60, 60, 60, 60}};
    const CmdPos Pos1={  5,{  400, -400,    0,    0,-1200,-1200,    0,    0,  150,  250,  300,  500,  150,  250, -200, -150}};
    const CmdPos Pos2={ 12,{    0,    0,    0,    0,-1200,-1200,    0,    0,  600,   50, 1200,    0,  800,    0,    0, -300}};
    const CmdJump CmpButton1={COND_BTN_OFF, BTN_DOWN, +11};
    const CmdPos Pos7={ 10,{ -400, -400,    0,    0,-1200,-1200,    0,    0, -400,  600,    0,  750,  400,  150,    0, -300}};
    const CmdPos Pos8={  6,{ -400, -400,    0,    0,-1200,-1200,    0,    0, -400,  200,    0,  200,  200,  100,  200,  200}};
    const CmdPos Pos9={  6,{ -400, -400,    0,    0,-1200,-1200,    0,    0, -200,  500,    0, 1000,  100,  300,  300,    0}};
    const CmdPos Pos10={  8,{    0,    0,    0,    0,-1200,-1200,    0,    0,   50,  600,    0, 1200,  -50,  400,  300,    0}};
    const CmdJump CmpButton2={COND_BTN_OFF, BTN_DOWN, +6};
    const CmdPos Pos3={ 10,{  400,  400,    0,    0,-1200,-1200,    0,    0,  600, -400,  750,    0,  150,  400,    0,  300}};
    const CmdPos Pos4={  6,{  400,  400,    0,    0,-1200,-1200,    0,    0,  200, -400,  200,    0,  100,  200, -200, -200}};
    const CmdPos Pos5={  6,{  400,  400,    0,    0,-1200,-1200,    0,    0,  500, -200, 1000,    0,  300,  100,    0, -300}};
    const CmdPos Pos6={  8,{    0,    0,    0,    0,-1200,-1200,    0,    0,  600,   50, 1200,    0,  400,  -50,    0, -300}};
    const CmdJump Jump1={COND_NONE, 0, -10};
    const CmdSet HomeStretch={SET_STRETCH,{ 20, 20, 20, 20, 65, 65, 65, 65, 65, 65, 65, 65, 65, 65, 65, 65}};
    const CmdPos HomePos={ 10,{  400, -400,    0,    0,-1200,-1200,    0,    0,  150,  150,  300,  300,  150,  150,    0,    0}};
    const MotionData motion[] = {
        { CMD_SET, (void*)&ServoParam1 },
        { CMD_POS, (void*)&Pos1 },
        { CMD_POS, (void*)&Pos2 },
        { CMD_JUMP,(void*)&CmpButton1 },
        { CMD_POS, (void*)&Pos7 },
        { CMD_POS, (void*)&Pos8 },
        { CMD_POS, (void*)&Pos9 },
        { CMD_POS, (void*)&Pos10 },
        { CMD_JUMP,(void*)&CmpButton2 },
        { CMD_POS, (void*)&Pos3 },
        { CMD_POS, (void*)&Pos4 },
        { CMD_POS, (void*)&Pos5 },
        { CMD_POS, (void*)&Pos6 },
        { CMD_JUMP,(void*)&Jump1 },
        { CMD_SET, (void*)&HomeStretch },
        { CMD_POS, (void*)&HomePos },
        { CMD_RET, NULL }
    };
}

// ←: 歩行左
namespace M003{
    const CmdPos Pos1={  4,{  400, -400,    0,    0,-1200,-1200,    0,    0,  150,    0,  300,    0,  150,    0,  200,  400}};
    const CmdPos Pos2={ 10,{  400, -400,    0,    0,-1200,-1200,    0,    0,    0,  500,  -50, 1000,    0,  500,  400,    0}};
    const CmdPos Pos3={  3,{  400, -400,    0,    0,-1200,-1200, -300,  500,    0,  500,  -50, 1000,    0,  500,    0,  300}};
    const CmdPos Pos4={  6,{  400, -400,    0,    0,-1200,-1200, -500,  500,    0,  500,  -50, 1000,    0,  500, -200,  300}};
    const CmdPos Pos5={ 10,{  400, -400,    0,    0,-1200,-1200,    0,    0,  150,  150,  300,  300,  150,  150,    0, -200}};
    const CmdJump CmpButton1={COND_BTN, BTN_LEFT, -5};
    const CmdPos HomePos={ 10,{  400, -400,    0,    0,-1200,-1200,    0,    0,  150,  150,  300,  300,  150,  150,    0,    0}};
    const MotionData motion[] = {
        { CMD_POS, (void*)&Pos1 },
        { CMD_POS, (void*)&Pos2 },
        { CMD_POS, (void*)&Pos3 },
        { CMD_POS, (void*)&Pos4 },
        { CMD_POS, (void*)&Pos5 },
        { CMD_JUMP,(void*)&CmpButton1 },
        { CMD_POS, (void*)&HomePos },
        { CMD_RET, NULL }
    };
}

// →: 歩行右
namespace M004{
    const CmdPos Pos1={  4,{  400, -400,    0,    0,-1200,-1200,    0,    0,    0,  150,    0,  300,    0,  150, -400, -200}};
    const CmdPos Pos2={ 10,{  400, -400,    0,    0,-1200,-1200,    0,    0,  500,    0, 1000,  -50,  500,    0,    0, -400}};
    const CmdPos Pos3={  3,{  400, -400,    0,    0,-1200,-1200, -500,  300,  500,    0, 1000,  -50,  500,    0, -300,    0}};
    const CmdPos Pos4={  6,{  400, -400,    0,    0,-1200,-1200, -500,  500,  500,    0, 1000,  -50,  500,    0, -300,  200}};
    const CmdPos Pos5={ 10,{  400, -390,    0,    0,-1200,-1200,    0,    0,  150,  150,  300,  300,  150,  150,  200,    0}};
    const CmdJump CmpButton1={COND_BTN, BTN_RIGHT, -5};
    const CmdPos HomePos={ 10,{  400, -400,    0,    0,-1200,-1200,    0,    0,  150,  150,  300,  300,  150,  150,    0,    0}};
    const MotionData motion[] = {
        { CMD_POS, (void*)&Pos1 },
        { CMD_POS, (void*)&Pos2 },
        { CMD_POS, (void*)&Pos3 },
        { CMD_POS, (void*)&Pos4 },
        { CMD_POS, (void*)&Pos5 },
        { CMD_JUMP,(void*)&CmpButton1 },
        { CMD_POS, (void*)&HomePos },
        { CMD_RET, NULL }
    };
}

// X+↑: 歩行少し前
namespace M011{
    const CmdSet ServoParam1={SET_STRETCH,{ -1, -1, -1, -1, -1, -1, 60, 60, 60, 60, 60, 60, 60, 60, 60, 60}};
    const CmdPos Pos1={  5,{  400, -400,    0,    0,-1200,-1200,    0,    0,  150,  250,  300,  500,  150,  250, -200, -150}};
    const CmdPos Pos2={  6,{    0,    0,    0,    0,-1200,-1200,    0,    0,  400,   50,  800,    0,  400,   50,    0, -200}};
    const CmdPos Pos4={  3,{  400,  400,    0,    0,-1200,-1200,    0,    0,  500, -200, 1000,    0,  550,  200,    0, -200}};
    const CmdPos Pos5={  2,{  200,  200,    0,    0,-1200,-1200,    0,    0,  150, -300,  300,    0,  150,  300,    0, -100}};
    const CmdPos Pos6={  5,{  200,  200,    0,    0,-1200,-1200,    0,    0,  150, -300,  300,    0,  150,  300,  100,  150}};
    const CmdJump CmpButton1={COND_BTN_OFF, BTN_UP, +8};
    const CmdPos Pos7={  6,{    0,    0,    0,    0,-1200,-1200,    0,    0,   50,  400,    0,  800,   50,  400,  300,    0}};
    const CmdPos Pos8={  3,{ -400, -400,    0,    0,-1200,-1200,    0,    0, -200,  500,    0, 1000,  200,  550,  200,    0}};
    const CmdPos Pos9={  2,{ -200, -200,    0,    0,-1200,-1200,    0,    0, -300,  150,    0,  300,  300,  150,  100,    0}};
    const CmdPos Pos10={  5,{ -200, -200,    0,    0,-1200,-1200,    0,    0, -300,  150,    0,  300,  300,  150, -150, -100}};
    const CmdJump CmpButton2={COND_BTN_OFF, BTN_UP, +3};
    const CmdPos Pos3={  6,{    0,    0,    0,    0,-1200,-1200,    0,    0,  400,   50,  800,    0,  400,   50,    0, -150}};
    const CmdJump Jump1={COND_NONE, 0, -10};
    const CmdSet HomeStretch={SET_STRETCH,{ 20, 20, 20, 20, 65, 65, 65, 65, 65, 65, 65, 65, 65, 65, 65, 65}};
    const CmdPos HomePos={ 10,{  400, -400,    0,    0,-1200,-1200,    0,    0,  150,  150,  300,  300,  150,  150,    0,    0}};
    const MotionData motion[] = {
        { CMD_SET, (void*)&ServoParam1 },
        { CMD_POS, (void*)&Pos1 },
        { CMD_POS, (void*)&Pos2 },
        { CMD_POS, (void*)&Pos4 },
        { CMD_POS, (void*)&Pos5 },
        { CMD_POS, (void*)&Pos6 },
        { CMD_JUMP,(void*)&CmpButton1 },
        { CMD_POS, (void*)&Pos7 },
        { CMD_POS, (void*)&Pos8 },
        { CMD_POS, (void*)&Pos9 },
        { CMD_POS, (void*)&Pos10 },
        { CMD_JUMP,(void*)&CmpButton2 },
        { CMD_POS, (void*)&Pos3 },
        { CMD_JUMP,(void*)&Jump1 },
        { CMD_SET, (void*)&HomeStretch },
        { CMD_POS, (void*)&HomePos },
        { CMD_RET, NULL }
    };
}

// X+↓: 歩行少し後
namespace M012{
    const CmdSet ServoParam1={SET_STRETCH,{ -1, -1, -1, -1, -1, -1, 60, 60, 60, 60, 60, 60, 60, 60, 60, 60}};
    const CmdPos Pos1={  5,{  400, -400,    0,    0,-1200,-1200,    0,    0,  150,  250,  300,  500,  150,  250, -200, -150}};
    const CmdPos Pos2={  6,{    0,    0,    0,    0,-1200,-1200,    0,    0,  400,   50,  800,    0,  400,   50,    0, -200}};
    const CmdJump CmpButton1={COND_BTN_OFF, BTN_DOWN, +11};
    const CmdPos Pos7={  4,{ -200, -200,    0,    0,-1200,-1200,    0,    0, -300,  150,    0,  300,  300,  100, -100, -100}};
    const CmdPos Pos8={  2,{ -200, -200,    0,    0,-1200,-1200,    0,    0, -300,  150,    0,  300,  300,  100,  100,    0}};
    const CmdPos Pos9={  3,{ -400, -400,    0,    0,-1200,-1200,    0,    0, -200,  500,    0, 1000,  150,  500,  200,    0}};
    const CmdPos Pos10={  6,{    0,    0,    0,    0,-1200,-1200,    0,    0,   50,  400,    0,  800,   50,  400,  300,    0}};
    const CmdJump CmpButton2={COND_BTN_OFF, BTN_DOWN, +6};
    const CmdPos Pos3={  4,{  200,  200,    0,    0,-1200,-1200,    0,    0,  150, -300,  300,    0,  100,  300,  100,  100}};
    const CmdPos Pos4={  2,{  200,  200,    0,    0,-1200,-1200,    0,    0,  150, -300,  300,    0,  100,  300,    0, -100}};
    const CmdPos Pos5={  3,{  400,  400,    0,    0,-1200,-1200,    0,    0,  500, -200, 1000,    0,  500,  150,    0, -200}};
    const CmdPos Pos6={  6,{    0,    0,    0,    0,-1200,-1200,    0,    0,  400,   50,  800,    0,  400,   50,    0, -150}};
    const CmdJump Jump1={COND_NONE, 0, -10};
    const CmdSet HomeStretch={SET_STRETCH,{ 20, 20, 20, 20, 65, 65, 65, 65, 65, 65, 65, 65, 65, 65, 65, 65}};
    const CmdPos HomePos={ 10,{  400, -400,    0,    0,-1200,-1200,    0,    0,  150,  150,  300,  300,  150,  150,    0,    0}};
    const MotionData motion[] = {
        { CMD_SET, (void*)&ServoParam1 },
        { CMD_POS, (void*)&Pos1 },
        { CMD_POS, (void*)&Pos2 },
        { CMD_JUMP,(void*)&CmpButton1 },
        { CMD_POS, (void*)&Pos7 },
        { CMD_POS, (void*)&Pos8 },
        { CMD_POS, (void*)&Pos9 },
        { CMD_POS, (void*)&Pos10 },
        { CMD_JUMP,(void*)&CmpButton2 },
        { CMD_POS, (void*)&Pos3 },
        { CMD_POS, (void*)&Pos4 },
        { CMD_POS, (void*)&Pos5 },
        { CMD_POS, (void*)&Pos6 },
        { CMD_JUMP,(void*)&Jump1 },
        { CMD_SET, (void*)&HomeStretch },
        { CMD_POS, (void*)&HomePos },
        { CMD_RET, NULL }
    };
}

// X+←: 歩行少し左
namespace M013{
    const CmdPos Pos1={ 10,{  400, -400,    0,    0,-1200,-1200,    0,    0,    0,  500,  -50, 1000,    0,  500,  150,    0}};
    const CmdPos Pos2={  3,{  400, -400,    0,    0,-1200,-1200, -100,  200,    0,  500,  -50, 1000,    0,  500,    0,  150}};
    const CmdPos Pos3={  6,{  400, -400,    0,    0,-1200,-1200, -200,  200,    0,  500,  -50, 1000,    0,  500, -100,  100}};
    const CmdPos Pos4={ 10,{  400, -400,    0,    0,-1200,-1200,    0,    0,  150,  150,  300,  300,  150,  150,    0, -200}};
    const CmdPos Pos5={  4,{  400, -400,    0,    0,-1200,-1200,    0,    0,  150,    0,  300,    0,  150,    0,  100,  200}};
    const CmdJump CmpButton1={COND_BTN, BTN_L1|BTN_LEFT, -5};
    const CmdPos HomePos={ 10,{  400, -400,    0,    0,-1200,-1200,    0,    0,  150,  150,  300,  300,  150,  150,    0,    0}};
    const MotionData motion[] = {
        { CMD_POS, (void*)&Pos1 },
        { CMD_POS, (void*)&Pos2 },
        { CMD_POS, (void*)&Pos3 },
        { CMD_POS, (void*)&Pos4 },
        { CMD_POS, (void*)&Pos5 },
        { CMD_JUMP,(void*)&CmpButton1 },
        { CMD_POS, (void*)&HomePos },
        { CMD_RET, NULL }
    };
}

// X+→: 歩行少し右
namespace M014{
    const CmdPos Pos1={ 10,{  400, -400,    0,    0,-1200,-1200,    0,    0,  500,    0, 1000,  -50,  500,    0,    0, -150}};
    const CmdPos Pos2={  3,{  400, -400,    0,    0,-1200,-1200, -200,  100,  500,    0, 1000,  -50,  500,    0, -150,    0}};
    const CmdPos Pos3={  6,{  400, -400,    0,    0,-1200,-1200, -200,  200,  500,    0, 1000,  -50,  500,    0, -100,  100}};
    const CmdPos Pos4={ 10,{  400, -390,    0,    0,-1200,-1200,    0,    0,  150,  150,  300,  300,  150,  150,  200,    0}};
    const CmdPos Pos5={  4,{  400, -390,    0,    0,-1200,-1200,    0,    0,    0,  150,    0,  300,    0,  150, -200, -100}};
    const CmdJump CmpButton1={COND_BTN, BTN_L1|BTN_RIGHT, -5};
    const CmdPos HomePos={ 10,{  400, -400,    0,    0,-1200,-1200,    0,    0,  150,  150,  300,  300,  150,  150,    0,    0}};
    const MotionData motion[] = {
        { CMD_POS, (void*)&Pos1 },
        { CMD_POS, (void*)&Pos2 },
        { CMD_POS, (void*)&Pos3 },
        { CMD_POS, (void*)&Pos4 },
        { CMD_POS, (void*)&Pos5 },
        { CMD_JUMP,(void*)&CmpButton1 },
        { CMD_POS, (void*)&HomePos },
        { CMD_RET, NULL }
    };
}

// L2: 歩行左旋回
namespace M021{
    const CmdPos Pos1={  3,{  400, -400,    0,    0,-1200,-1200, -120,  120,  650, -500,  300,  200, -400,  650, -300,  300}};
    const CmdPos Pos2={  5,{  400, -400,    0,    0,-1200,-1200, -200,  200,  650, -500,  300,  200, -400,  650, -300,  300}};
    const CmdPos Pos3={ 20,{  400, -400,    0,    0,-1200,-1200,    0,    0,  150,  150,  300,  300,  150,  150,    0,    0}};
    const CmdJump CmpButton1={COND_BTN, BTN_L2, -3};
    const CmdPos HomePos={ 10,{  400, -400,    0,    0,-1200,-1200,    0,    0,  150,  150,  300,  300,  150,  150,    0,    0}};
    const MotionData motion[] = {
        { CMD_POS, (void*)&Pos1 },
        { CMD_POS, (void*)&Pos2 },
        { CMD_POS, (void*)&Pos3 },
        { CMD_JUMP,(void*)&CmpButton1 },
        { CMD_POS, (void*)&HomePos },
        { CMD_RET, NULL }
    };
}

// R2: 歩行右旋回
namespace M022{
    const CmdPos Pos1={  3,{  400, -400,    0,    0,-1200,-1200, -120,  120, -500,  650,  200,  300,  650, -400, -300,  300}};
    const CmdPos Pos2={  5,{  400, -400,    0,    0,-1200,-1200, -200,  200, -500,  650,  200,  300,  650, -400, -300,  300}};
    const CmdPos Pos3={ 20,{  400, -400,    0,    0,-1200,-1200,    0,    0,  150,  150,  300,  300,  150,  150,    0,    0}};
    const CmdJump CmpButton1={COND_BTN, BTN_R2, -3};
    const CmdPos HomePos={ 10,{  400, -400,    0,    0,-1200,-1200,    0,    0,  150,  150,  300,  300,  150,  150,    0,    0}};
    const MotionData motion[] = {
        { CMD_POS, (void*)&Pos1 },
        { CMD_POS, (void*)&Pos2 },
        { CMD_POS, (void*)&Pos3 },
        { CMD_JUMP,(void*)&CmpButton1 },
        { CMD_POS, (void*)&HomePos },
        { CMD_RET, NULL }
    };
}

// B+↑: 起き上がり(仰向け)
namespace M101{
    const CmdSet ServoParam1={SET_STRETCH,{127,127, -1, -1, -1, -1, -1, -1,127,127,127,127,127,127, -1, -1}};
    const CmdPos Pos1={ 10,{    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0}};
    const CmdPos Pos2={ 40,{ 3700,-3700,    0,    0,-2800,-2800,    0,    0,  800,  800,    0,    0,    0,    0,    0,    0}};
    const CmdPos Pos3={ 30,{ 1800,-1800,    0,    0,    0,    0,    0,    0, 2500, 2500,    0,    0,    0,    0,    0,    0}};
    const CmdPos Pos4={ 30,{ 1800,-1800,    0,    0,    0,    0,    0,    0, 2500, 2500, 3650, 3650, 1600, 1600,    0,    0}};
    const CmdPos Pos5={ 15,{ 2000,-2000,    0,    0, -360, -360,    0,    0,    0,    0, 2500, 2500,  600,  600,    0,    0}};
    const CmdPos Pos6={ 15,{ 2000,-2000,    0,    0, -360, -360,    0,    0, -700, -700, 2700, 2700, 1600, 1600,    0,    0}};
    const CmdPos Pos7={ 50,{  298, -270,    0,    0, -360, -360,    0,    0,  800,  800, 2700, 2700, 1850, 1850,    0,    0}};
    const CmdPos Pos8={ 80,{    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,  200,  200,    0,    0}};
    const CmdSet HomeStretch={SET_STRETCH,{ 20, 20, 20, 20, 65, 65, 65, 65, 65, 65, 65, 65, 65, 65, 65, 65}};
    const CmdPos HomePos={ 10,{  400, -400,    0,    0,-1200,-1200,    0,    0,  150,  150,  300,  300,  150,  150,    0,    0}};
    const MotionData motion[] = {
        { CMD_SET, (void*)&ServoParam1 },
        { CMD_POS, (void*)&Pos1 },
        { CMD_POS, (void*)&Pos2 },
        { CMD_POS, (void*)&Pos3 },
        { CMD_POS, (void*)&Pos4 },
        { CMD_POS, (void*)&Pos5 },
        { CMD_POS, (void*)&Pos6 },
        { CMD_POS, (void*)&Pos7 },
        { CMD_POS, (void*)&Pos8 },
        { CMD_SET, (void*)&HomeStretch },
        { CMD_POS, (void*)&HomePos },
        { CMD_RET, NULL }
    };
}

// B+↓: 起き上がり(うつ伏せ)
namespace M102{
    const CmdSet ServoParam1={SET_SPEED,{ -1, -1, -1, -1, -1, -1, -1, -1,127,127,127,127,127,127, -1, -1}};
    const CmdPos Pos1={ 10,{    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0}};
    const CmdPos Pos2={ 30,{    0,    0, 2500, 2500,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0}};
    const CmdPos Pos3={ 30,{-5400, 5400, 2500, 2500,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0}};
    const CmdPos Pos4={ 20,{-5400, 5400,    0,    0,-2500,-2500,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0}};
    const CmdPos Pos5={  5,{-2700, 2700,    0,    0,-2500,-2500,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0}};
    const CmdPos Pos6={ 10,{-2700, 2700,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0, 1500, 1500,    0,    0}};
    const CmdPos Pos7={ 30,{-2300, 2300,    0,    0,    0,    0,    0,    0, 3500, 3500, 3820, 3820, 1500, 1500,    0,    0}};
    const CmdPos Pos8={ 20,{    0,    0,    0,    0,    0,    0,    0,    0, 1800, 1800, 3600, 3600, 1800, 1800,    0,    0}};
    const CmdPos Pos9={ 40,{-1500, 1500,    0,    0,    0,    0,    0,    0, 2000, 2000, 2900, 2900, 1500, 1500,    0,    0}};
    const CmdPos Pos10={ 30,{-1500, 1500,    0,    0,    0,    0,    0,    0, 1500, 1500, 2000, 2000, 1000, 1000,    0,    0}};
    const CmdPos Pos11={ 50,{    0,    0,    0,    0,    0,    0,    0,    0,  500,  500,    0,    0,    0,    0,    0,    0}};
    const CmdSet HomeStretch={SET_STRETCH,{ 20, 20, 20, 20, 65, 65, 65, 65, 65, 65, 65, 65, 65, 65, 65, 65}};
    const CmdPos HomePos={ 10,{  400, -400,    0,    0,-1200,-1200,    0,    0,  150,  150,  300,  300,  150,  150,    0,    0}};
    const MotionData motion[] = {
        { CMD_SET, (void*)&ServoParam1 },
        { CMD_POS, (void*)&Pos1 },
        { CMD_POS, (void*)&Pos2 },
        { CMD_POS, (void*)&Pos3 },
        { CMD_POS, (void*)&Pos4 },
        { CMD_POS, (void*)&Pos5 },
        { CMD_POS, (void*)&Pos6 },
        { CMD_POS, (void*)&Pos7 },
        { CMD_POS, (void*)&Pos8 },
        { CMD_POS, (void*)&Pos9 },
        { CMD_POS, (void*)&Pos10 },
        { CMD_POS, (void*)&Pos11 },
        { CMD_SET, (void*)&HomeStretch },
        { CMD_POS, (void*)&HomePos },
        { CMD_RET, NULL }
    };
}

// L1: パンチ左ストレート
namespace M201{
    const CmdPos Pos1={ 20,{ 1200, -668,    0,  561,-3400,-2675, -605,  452, 1800,  -60, 1300,  800, -280, 1221, -485,  612}};
    const CmdPos Pos2={  3,{ 1196, 2839,    4,  589,-3391, -400, -605,  452, 1800,  -60, 1300,  800, -280, 1221, -485,  612}};
    const CmdJump CmpButton1={COND_BTN, BTN_L1, -1};
    const CmdPos HomePos={ 10,{  400, -400,    0,    0,-1200,-1200,    0,    0,  150,  150,  300,  300,  150,  150,    0,    0}};
    const MotionData motion[] = {
        { CMD_POS, (void*)&Pos1 },
        { CMD_POS, (void*)&Pos2 },
        { CMD_JUMP,(void*)&CmpButton1 },
        { CMD_POS, (void*)&HomePos },
        { CMD_RET, NULL }
    };
}

// R1: パンチ右ストレート
namespace M202{
    const CmdSet ServoParam1={SET_SPEED,{127,127, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1}};
    const CmdSet ServoParam2={SET_STRETCH,{127,127, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1}};
    const CmdPos Pos1={ 20,{  668,-1200,  561,    4,-2675,-3400, -452,  605,  -60, 1800,  800, 1300, 1221, -280, -612,  485}};
    const CmdPos Pos2={  1,{-2839,-1200,  589,    0, -400,-3400, -452,  605,  -60, 1800,  800, 1300, 1221, -280, -612,  485}};
    const CmdJump CmpButton1={COND_BTN, BTN_R1, -1};
    const CmdPos HomePos={ 10,{  400, -400,    0,    0,-1200,-1200,    0,    0,  150,  150,  300,  300,  150,  150,    0,    0}};
    const MotionData motion[] = {
        { CMD_SET, (void*)&ServoParam1 },
        { CMD_SET, (void*)&ServoParam2 },
        { CMD_POS, (void*)&Pos1 },
        { CMD_POS, (void*)&Pos2 },
        { CMD_JUMP,(void*)&CmpButton1 },
        { CMD_POS, (void*)&HomePos },
        { CMD_RET, NULL }
    };
}

// A+←: パンチ左裏拳
namespace M211{
    const CmdPos Pos1={  5,{  400,-1500,    0,  700,-1200,-3000,    0,    0,  150,  150,  300,  300,  150,  150,    0,    0}};
    const CmdPos Pos2={  3,{ -400,  937,  360, 2811,-1200, -505, -827,  415,  -22,  741,   56, 1246,  173,  649, -541,  405}};
    const CmdJump CmpButton1={COND_BTN, BTN_A|BTN_LEFT, -1};
    const CmdPos HomePos={ 10,{  400, -400,    0,    0,-1200,-1200,    0,    0,  150,  150,  300,  300,  150,  150,    0,    0}};
    const MotionData motion[] = {
        { CMD_POS, (void*)&Pos1 },
        { CMD_POS, (void*)&Pos2 },
        { CMD_JUMP,(void*)&CmpButton1 },
        { CMD_POS, (void*)&HomePos },
        { CMD_RET, NULL }
    };
}

// A+→: パンチ右裏拳
namespace M212{
    const CmdPos Pos1={  5,{ 1500, -400,  700,    0,-3400,-1200,    0,    0,  150,  150,  300,  300,  150,  150,    0,    0}};
    const CmdPos Pos2={  3,{ -649, -400, 2811,  360, -505,-1200, -415,  827,  250,   -9,  800,  195,  500,  247, -541,  733}};
    const CmdJump CmpButton1={COND_BTN, BTN_A|BTN_RIGHT, -1};
    const CmdPos HomePos={ 10,{  400, -400,    0,    0,-1200,-1200,    0,    0,  150,  150,  300,  300,  150,  150,    0,    0}};
    const MotionData motion[] = {
        { CMD_POS, (void*)&Pos1 },
        { CMD_POS, (void*)&Pos2 },
        { CMD_JUMP,(void*)&CmpButton1 },
        { CMD_POS, (void*)&HomePos },
        { CMD_RET, NULL }
    };
}

// A+↓: 防御
namespace M220{
    const CmdPos Pos1={ 10,{  400, -400,    0,    0,-1200,-1200,    0,    0, 1360, 1360, 1800, 1800, 1080, 1080,    0,    0}};
    const CmdPos Pos2={ 25,{-1700, 1700, -200, -200,-3300,-3300,    0,    0, 1900, 2952, 3800, 3580, 1900,  681,    0,  -10}};
    const CmdPos Free1={  0,{0x7FFF,0x7FFF,0x7FFF,0x7FFF,0x7FFF,0x7FFF,0x7FFF,0x7FFF,0x7000,0x7000,0x7000,0x7000,0x7000,0x7000,0x7FFF,0x7FFF}};
    const CmdJump CmpButton1={COND_BTN, BTN_A|BTN_DOWN, 0};
    const CmdPos Hold1={  0,{0x7FFF,0x7FFF,0x7FFF,0x7FFF,0x7FFF,0x7FFF,0x7FFF,0x7FFF,0x7001,0x7001,0x7001,0x7001,0x7001,0x7001,0x7FFF,0x7FFF}};
    const CmdPos Pos3={ 10,{    0,    0,    0,    0,-1200,-1200,    0,    0, 1800, 1800, 3600, 3600, 1800, 1800,    0,    0}};
    const CmdPos Pos4={ 20,{ -300,  300,    0,    0,-1200,-1200,    0,    0, 1600, 1600, 2900, 2900, 1500, 1500,    0,    0}};
    const CmdPos Pos5={ 15,{    0,    0,    0,    0,-1200,-1200,    0,    0, 1500, 1500, 2000, 2000, 1000, 1000,    0,    0}};
    const CmdPos Pos6={ 15,{    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0}};
    const CmdPos HomePos={ 10,{  400, -400,    0,    0,-1200,-1200,    0,    0,  150,  150,  300,  300,  150,  150,    0,    0}};
    const MotionData motion[] = {
        { CMD_POS, (void*)&Pos1 },
        { CMD_POS, (void*)&Pos2 },
        { CMD_POS, (void*)&Free1 },
        { CMD_JUMP,(void*)&CmpButton1 },
        { CMD_POS, (void*)&Hold1 },
        { CMD_POS, (void*)&Pos3 },
        { CMD_POS, (void*)&Pos4 },
        { CMD_POS, (void*)&Pos5 },
        { CMD_POS, (void*)&Pos6 },
        { CMD_POS, (void*)&HomePos },
        { CMD_RET, NULL }
    };
}

// Y+↑: あいさつ
namespace M301{
    const CmdPos Pos0={ 10,{  400, -400,    0,    0,-1200,-1200,    0,    0,  150,  150,  300,  300,  150,  150,    0,    0}};
    const CmdPos Pos1={ 10,{  400, -400,    0,    0,-1200,-1200,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0}};
    const CmdPos Pos2={100,{  400, -400,    0,    0,-1200,-1200,    0,    0, 1500, 1500,    0,    0,    0,    0,    0,    0}};
    const CmdPos Pos3={ 50,{  400, -400,    0,    0,-1200,-1200,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0}};
    const CmdPos HomePos={ 10,{  400, -400,    0,    0,-1200,-1200,    0,    0,  150,  150,  300,  300,  150,  150,    0,    0}};
    const MotionData motion[] = {
        { CMD_POS, (void*)&Pos0 },
        { CMD_POS, (void*)&Pos1 },
        { CMD_POS, (void*)&Pos2 },
        { CMD_POS, (void*)&Pos3 },
        { CMD_POS, (void*)&HomePos },
        { CMD_RET, NULL }
    };
}

// Y+↓: 手を振る
namespace M302{
    const CmdCnt SetCnt={ 0, 3};
    const CmdPos Pos1={ 40,{-3800, -400,    0,    0,-1200,-1200,    0,    0,  150,  150,  300,  300,  150,  150,    0,    0}};
    const CmdPos Pos2={ 40,{-3800, -400, -400,    0,-1200,-1200,    0,    0,  350,  150,  700,  300,  350,  150,  150,  150}};
    const CmdPos Pos3={ 40,{-3800, -400,  800,    0,-1200,-1200,    0,    0,  350,  150,  700,  300,  350,  150,  150,  150}};
    const CmdPos Pos4={ 40,{-3800, -400, -400,    0,-1200,-1200,    0,    0,  150,  350,  300,  700,  150,  350, -150, -150}};
    const CmdPos Pos5={ 40,{-3800, -400,  800,    0,-1200,-1200,    0,    0,  150,  350,  300,  700,  150,  350, -150, -150}};
    const CmdJump Loop={COND_LOOP, 0, -4};
    const CmdPos HomePos={ 40,{  400, -400,    0,    0,-1200,-1200,    0,    0,  150,  150,  300,  300,  150,  150,    0,    0}};
    const MotionData motion[] = {
        { CMD_CNT, (void*)&SetCnt },
        { CMD_POS, (void*)&Pos1 },
        { CMD_POS, (void*)&Pos2 },
        { CMD_POS, (void*)&Pos3 },
        { CMD_POS, (void*)&Pos4 },
        { CMD_POS, (void*)&Pos5 },
        { CMD_JUMP,(void*)&Loop },
        { CMD_POS, (void*)&HomePos },
        { CMD_RET, NULL }
    };
}

// Y+←: 腕立て
namespace M401{
    const CmdCnt SetCnt={ 0, 4};
    const CmdPos Pos1={ 50,{    0,    0,    0,   10, -800, -800,    0,    0, 1900, 1900, 3800, 3800, 1900, 1900,    0,    0}};
    const CmdPos Pos2={ 20,{-1300, 1300,    0,   10, -800, -800,    0,    0, 3100, 3100, 3800, 3800, 1900, 1900,    0,    0}};
    const CmdPos Pos3={ 30,{-2100, 2100,    0,   10, -800, -800,    0,    0, 3100, 3100, 2800, 2800, 1900, 1900,    0,    0}};
    const CmdPos Pos4={ 30,{-2000, 2000,    0,   10, -800, -800,    0,    0, 1600, 1600, 2500, 2500, 1900, 1900,    0,    0}};
    const CmdPos Pos5={ 30,{-2000, 2000,    0,    0, -800, -800,    0,    0,  500,  500,  600,  600,   70,   70,    0,    0}};
    const CmdWait Wait1={33};
    const CmdPos Pos6={ 40,{-2000, 2000,    0,    0, -800, -800,    0,    0,  500,  500,  600,  600,   70,   70,    0,    0}};
    const CmdPos Pos7={ 15,{ -900,  900,    0,    0,-2400,-2400,    0,    0,  500,  500,  600,  600,   70,   70,    0,    0}};
    const CmdJump Loop={COND_LOOP, 0, -2};
    const CmdPos Pos8={ 30,{-2300, 2300,    0,    0,    0,    0,    0,    0, 3500, 3500, 3820, 3820, 1500, 1500,    0,    0}};
    const CmdPos Pos9={ 20,{    0,    0,    0,    0,    0,    0,    0,    0, 1800, 1800, 3600, 3600, 1800, 1800,    0,    0}};
    const CmdPos Pos10={ 40,{-1500, 1500,    0,    0,    0,    0,    0,    0, 2000, 2000, 2900, 2900, 1500, 1500,    0,    0}};
    const CmdPos Pos11={ 30,{-1500, 1500,    0,    0,    0,    0,    0,    0, 1500, 1500, 2000, 2000, 1000, 1000,    0,    0}};
    const CmdPos Pos12={ 50,{    0,    0,    0,    0,    0,    0,    0,    0,  500,  500,    0,    0,    0,    0,    0,    0}};
    const CmdPos HomePos={ 10,{  400, -400,    0,    0,-1200,-1200,    0,    0,  150,  150,  300,  300,  150,  150,    0,    0}};
    const MotionData motion[] = {
        { CMD_CNT, (void*)&SetCnt },
        { CMD_POS, (void*)&Pos1 },
        { CMD_POS, (void*)&Pos2 },
        { CMD_POS, (void*)&Pos3 },
        { CMD_POS, (void*)&Pos4 },
        { CMD_POS, (void*)&Pos5 },
        { CMD_WAIT, (void*)&Wait1 },
        { CMD_POS, (void*)&Pos6 },
        { CMD_POS, (void*)&Pos7 },
        { CMD_JUMP,(void*)&Loop },
        { CMD_POS, (void*)&Pos8 },
        { CMD_POS, (void*)&Pos9 },
        { CMD_POS, (void*)&Pos10 },
        { CMD_POS, (void*)&Pos11 },
        { CMD_POS, (void*)&Pos12 },
        { CMD_POS, (void*)&HomePos },
        { CMD_RET, NULL }
    };
}

// Y+→: 前転
namespace M402{
    const CmdSet ServoParam1={SET_STRETCH,{127,127, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1}};
    const CmdPos Pos1={ 50,{    0,    0,    0,   10, -800, -800,    0,    0, 1900, 1900, 3800, 3800, 1900, 1900,    0,    0}};
    const CmdPos Pos2={ 20,{-1300, 1300,    0,   10, -800, -800,    0,    0, 3100, 3100, 3800, 3800, 1900, 1900,    0,    0}};
    const CmdPos Pos3={ 30,{-2100, 2100,    0,   10, -800, -800,    0,    0, 3100, 3100, 2800, 2800, 1900, 1900,    0,    0}};
    const CmdPos Pos4={ 20,{-3093, 2984,  -72,   14,-3709,-3718,    4,  -18, 3355, -768, -811, 2246, 2234,  401,    4,    4}};
    const CmdWait Wait1={33};
    const CmdPos Pos5={100,{-4829, 4800,  -72,   14,-3709,-3718,    4,  -18, 3355, -768, -811, 2246, 2234,  401,    4,    4}};
    const CmdPos Pos6={100,{-4500, 4500,  -72,   14,-3709,-3718,    0,    0, -800, -800, 2400, 2400,  200,  200,    0,    0}};
    const CmdPos Pos7={ 60,{-5000, 5000,  -72,   14,-3709,-3718,    0,    0,    0,    0, 2000, 2000, -650, -650,    0,    0}};
    const CmdPos Pos12={ 30,{  400, -400,    0,    0,-1200,-1200,    0,    0,  150,  150,  300,  300,  150,  150,    0,    0}};
    const CmdPos Pos8={ 10,{    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0}};
    const CmdPos Pos9={ 40,{ 3700,-3700,    0,    0,-2800,-2800,    0,    0,  800,  800,    0,    0,    0,    0,    0,    0}};
    const CmdPos Pos10={ 30,{ 1800,-1800,    0,    0,    0,    0,    0,    0, 2500, 2500,    0,    0,    0,    0,    0,    0}};
    const CmdPos Pos11={ 30,{ 1800,-1800,    0,    0,    0,    0,    0,    0, 2500, 2500, 3650, 3650, 1600, 1600,    0,    0}};
    const CmdPos Pos13={ 15,{ 2000,-2000,    0,    0, -360, -360,    0,    0,    0,    0, 2500, 2500,  600,  600,    0,    0}};
    const CmdPos Pos14={ 15,{ 2000,-2000,    0,    0, -360, -360,    0,    0, -700, -700, 2700, 2700, 1600, 1600,    0,    0}};
    const CmdPos Pos15={ 50,{  298, -270,    0,    0, -360, -360,    0,    0,  800,  800, 2700, 2700, 1850, 1850,    0,    0}};
    const CmdPos Pos16={ 80,{    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,  200,  200,    0,    0}};
    const CmdSet HomeStretch={SET_STRETCH,{ 20, 20, 20, 20, 65, 65, 65, 65, 65, 65, 65, 65, 65, 65, 65, 65}};
    const CmdPos HomePos={ 10,{  400, -400,    0,    0,-1200,-1200,    0,    0,  150,  150,  300,  300,  150,  150,    0,    0}};
    const MotionData motion[] = {
        { CMD_SET, (void*)&ServoParam1 },
        { CMD_POS, (void*)&Pos1 },
        { CMD_POS, (void*)&Pos2 },
        { CMD_POS, (void*)&Pos3 },
        { CMD_POS, (void*)&Pos4 },
        { CMD_WAIT, (void*)&Wait1 },
        { CMD_POS, (void*)&Pos5 },
        { CMD_POS, (void*)&Pos6 },
        { CMD_POS, (void*)&Pos7 },
        { CMD_POS, (void*)&Pos12 },
        { CMD_POS, (void*)&Pos8 },
        { CMD_POS, (void*)&Pos9 },
        { CMD_POS, (void*)&Pos10 },
        { CMD_POS, (void*)&Pos11 },
        { CMD_POS, (void*)&Pos13 },
        { CMD_POS, (void*)&Pos14 },
        { CMD_POS, (void*)&Pos15 },
        { CMD_POS, (void*)&Pos16 },
        { CMD_SET, (void*)&HomeStretch },
        { CMD_POS, (void*)&HomePos },
        { CMD_RET, NULL }
    };
}

// A+L1+L2: 全脱力
namespace M500{
    const CmdPos Free1={  0,{0x7000,0x7000,0x7000,0x7000,0x7000,0x7000,0x7000,0x7000,0x7000,0x7000,0x7000,0x7000,0x7000,0x7000,0x7000,0x7000}};
    const CmdJump CmpButton1={COND_BTN_OFF, BTN_B, 0};
    const CmdPos Hold1={  0,{0x7001,0x7001,0x7001,0x7001,0x7001,0x7001,0x7001,0x7001,0x7001,0x7001,0x7001,0x7001,0x7001,0x7001,0x7001,0x7001}};
    const CmdPos HomePos={ 70,{  400, -400,    0,    0,-1200,-1200,    0,    0,  150,  150,  300,  300,  150,  150,    0,    0}};
    const MotionData motion[] = {
        { CMD_POS, (void*)&Free1 },
        { CMD_JUMP,(void*)&CmpButton1 },
        { CMD_POS, (void*)&Hold1 },
        { CMD_POS, (void*)&HomePos },
        { CMD_RET, NULL }
    };
}

// メインモーション
namespace M000{
    const CmdSet ServoParam1={SET_SPEED,  {127,127,127,127,127,127,127,127,127,127,127,127,127,127,127,127}};
    const CmdSet ServoParam2={SET_STRETCH,{ 20, 20, 20, 20, 65, 65, 65, 65, 65, 65, 65, 65, 65, 65, 65, 65}};
    const CmdPos Pos1={ 10,{  400, -400,    0,    0,-1200,-1200,    0,    0,  150,  150,  300,  300,  150,  150,    0,    0}};
    const CmdJump Wait = { COND_BTN_OFF, BTN_ALL, 0 };
    const CmdCall CallM001 ={COND_BTN, BTN_UP,           M001::motion}; // ↑: 歩行前
    const CmdCall CallM002 ={COND_BTN, BTN_DOWN,         M002::motion}; // ↓: 歩行後
    const CmdCall CallM003 ={COND_BTN, BTN_LEFT,         M003::motion}; // ←: 歩行左
    const CmdCall CallM004 ={COND_BTN, BTN_RIGHT,        M004::motion}; // →: 歩行右
    const CmdCall CallM011 ={COND_BTN, BTN_X|BTN_UP,     M011::motion}; // X+↑: 歩行少し前
    const CmdCall CallM012 ={COND_BTN, BTN_X|BTN_DOWN,   M012::motion}; // X+↓: 歩行少し後
    const CmdCall CallM013 ={COND_BTN, BTN_X|BTN_LEFT,   M013::motion}; // X+←: 歩行少し左
    const CmdCall CallM014 ={COND_BTN, BTN_X|BTN_RIGHT,  M014::motion}; // X+→: 歩行少し右
    const CmdCall CallM021 ={COND_BTN, BTN_L2,           M021::motion}; // L2: 歩行左旋回
    const CmdCall CallM022 ={COND_BTN, BTN_R2,           M022::motion}; // R2: 歩行右旋回
    const CmdCall CallM201 ={COND_BTN, BTN_L1,           M201::motion}; // L1: パンチ左ストレート
    const CmdCall CallM202 ={COND_BTN, BTN_R1,           M202::motion}; // R1: パンチ右ストレート
    const CmdCall CallM220 ={COND_BTN, BTN_A|BTN_DOWN,   M220::motion}; // A+↓: 防御
    const CmdCall CallM211 ={COND_BTN, BTN_A|BTN_LEFT,   M211::motion}; // A+←: パンチ左裏拳
    const CmdCall CallM212 ={COND_BTN, BTN_A|BTN_RIGHT,  M212::motion}; // A+→: パンチ右裏拳
    const CmdCall CallM101 ={COND_BTN, BTN_B|BTN_UP,     M101::motion}; // B+↑: 起き上がり(仰向け)
    const CmdCall CallM102 ={COND_BTN, BTN_B|BTN_DOWN,   M102::motion}; // B+↓: 起き上がり(うつ伏せ)
    const CmdCall CallM301 ={COND_BTN, BTN_Y|BTN_UP,     M301::motion}; // Y+↑: あいさつ
    const CmdCall CallM302 ={COND_BTN, BTN_Y|BTN_DOWN,   M302::motion}; // Y+↓: 手を振る
    const CmdCall CallM401 ={COND_BTN, BTN_Y|BTN_LEFT,   M401::motion}; // Y+←: 腕立て
    const CmdCall CallM402 ={COND_BTN, BTN_Y|BTN_RIGHT,  M402::motion}; // Y+→: 前転
    const CmdCall CallM500 ={COND_BTN, BTN_A|BTN_L1|BTN_L2, M500::motion}; // A+L1+L2: 全脱力
    const CmdJump Jump1 ={COND_NONE, 0, -23};
    
    const MotionData motion[] = {
        { CMD_SET, (void*)&ServoParam1 },
        { CMD_SET, (void*)&ServoParam2 },
        { CMD_POS, (void*)&Pos1 },
        { CMD_JUMP, (void*)&Wait },
        { CMD_CALL, (void*)&CallM001 },
        { CMD_CALL, (void*)&CallM002 },
        { CMD_CALL, (void*)&CallM003 },
        { CMD_CALL, (void*)&CallM004 },
        { CMD_CALL, (void*)&CallM011 },
        { CMD_CALL, (void*)&CallM012 },
        { CMD_CALL, (void*)&CallM013 },
        { CMD_CALL, (void*)&CallM014 },
        { CMD_CALL, (void*)&CallM021 },
        { CMD_CALL, (void*)&CallM022 },
        { CMD_CALL, (void*)&CallM101 },
        { CMD_CALL, (void*)&CallM102 },
        { CMD_CALL, (void*)&CallM201 },
        { CMD_CALL, (void*)&CallM202 },
        { CMD_CALL, (void*)&CallM211 },
        { CMD_CALL, (void*)&CallM212 },
        { CMD_CALL, (void*)&CallM220 },
        { CMD_CALL, (void*)&CallM301 },
        { CMD_CALL, (void*)&CallM302 },
        { CMD_CALL, (void*)&CallM401 },
        { CMD_CALL, (void*)&CallM402 },
        { CMD_CALL, (void*)&CallM500 },
        { CMD_JUMP, (void*)&Jump1 }
    };
}
