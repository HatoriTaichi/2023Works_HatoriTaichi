#pragma once
#ifndef _TIMER_H_
#define _TIMER_H_

//---------------------------
//インクルードファイル
//---------------------------
#include "main.h"

//---------------------------
//マクロ定義
//---------------------------
#define MAX_TIMER (3)			//画像を出す数
#define TIMER_SIZE_Y (25)		//Yの半径
#define TIMER_SIZE_X (25)		//Xの半径
#define ES_TIMER_SET (240)		//ES制限時間
#define NO_TIMER_SET (340)		//NO制限時間
#define HD_TIMER_SET (440)		//NO制限時間
#define DEBUG_MAXTIMER_SET (999)		//NO制限時間
#define DEBUG_MINITIMER_SET (10)		//NO制限時間

//---------------------------
//構造体の定義
//---------------------------
typedef struct
{
	D3DXVECTOR3  pos;		//ポリゴンの位置
	bool		 bUse;		//使ってるかどうか
} TIMER;

//---------------------------
//プロトタイプ宣言
//---------------------------
HRESULT InitTimer(void);
void UninitTimer(void);
void UpdateTimer(void);
void DrawTimer(void);
#endif 
