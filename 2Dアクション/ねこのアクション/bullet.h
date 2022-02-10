#pragma once
#ifndef _BULLET_H_
#define _BULLET_H_

//---------------------------
//インクルードファイル
//---------------------------
#include "main.h"

//---------------------------
//マクロ定義
//---------------------------
#define BULLET_SIZE_X (5.0f)	//玉サイズX半径
#define BULLET_SIZE_Y (5.0f)	//玉サイズY半径
#define MAX_BULLET (256)		//玉の最大数
#define BULLET_SPAN (10)		//弾のクールタイム
#define ENEMY_BULLET_SPAN (150)	//弾のクールタイム
#define MAX_TEX (4)				//テクスチャの数

//---------------------------
//構造体の定義
//---------------------------
typedef struct
{
	D3DXVECTOR3 pos;		//ポリゴンの位置
	D3DXVECTOR3 posold;		//前回の位置
	D3DXVECTOR3 posdfrc;	//差分
	D3DXVECTOR3 move;		//移動量
	float fWidth;			//幅
	float fHeight;			//高さ
	int nType;				//種類
	bool bRft;				//反射
	bool bUse;				//使ってるかどうか
} BULLET;
//---------------------------
//プロトタイプ宣言
//---------------------------
HRESULT InitBullet(void);
void UninitBullet(void);
void UpdateBullet(void);	//クリア時間
void DrawBullet(void);
void SetBullet(D3DXVECTOR3 pos, D3DXVECTOR3 move, float fWidth, float fHeight, int nType);	//位置、移動量、幅、高さ、種類
BULLET *GetBullet(void);
#endif 
