#pragma once
#ifndef _GUNINFO_H_
#define _GUNINFO_H_

//---------------------------
//インクルードファイル
//---------------------------
#include "main.h"

//---------------------------
//マクロ定義
//---------------------------
#define MAX_GUNINFO_TEX (1)	//テクスチャの数
#define MAX_GUNDIGIT (2)	//残段数の桁数
#define GUN_X (30)			//X
#define GUN_Y (30)			//Y

//---------------------------
//列挙型.モードの種類
//---------------------------
typedef enum
{
	GUNINFO_TYPE_00 = 0,//ハンドガン
	GUNINFO_TYPE_01,	//アサルト
	GUNINFO_MAX,
} GUNINFO_TYPE;

//---------------------------
//構造体の定義
//---------------------------
typedef struct
{
	D3DXVECTOR3 pos;	//ポリゴンの位置
	float fWidth;		//幅
	float fHeight;		//高さ
	int nRemaining;		//断層
} Guninfo;

//---------------------------
//プロトタイプ宣言
//---------------------------
HRESULT InitGuninfo(void);
void UninitGuninfo(void);
void UpdateGuninfo(void);
void DrawGuninfo(void);
void AddRemaining(int nShoot);
void SetGunType(GUNINFO_TYPE aType);
int GetRemaining(void);
#endif 
