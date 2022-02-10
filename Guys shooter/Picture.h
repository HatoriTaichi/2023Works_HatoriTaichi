#pragma once
#ifndef _PICTURE_H_
#define _PICTURE_H_

//---------------------------
//インクルードファイル
//---------------------------
#include "main.h"

//---------------------------
//マクロ定義
//---------------------------
#define MAX_PICTURE_TEX (PICTURE_TYPE_MAX)	//テクスチャの数
#define MAX_PICTURE (64)		//画像を出す数

//---------------------------
//列挙型.モードの種類
//---------------------------
typedef enum
{
	PICTURE_TYPE_TITLE = 0,			//タイトル
	PICTURE_TYPE_ENTER,				//プッシュトゥエンター
	PICTURE_TYPE_GUYS_00,			//ガイズ00
	PICTURE_TYPE_GUYS_01,			//ガイズ01
	PICTURE_TYPE_GUYS_02,			//ガイズ02
	PICTURE_TYPE_GUYS_03,			//ガイズ03
	PICTURE_TYPE_GUNLINE_00,		//弾数の線
	PICTURE_TYPE_GUNREMAINING_00,	//最高弾数(アサルト)
	PICTURE_TYPE_RESULT,			//リザルト画面
	PICTURE_TYPE_ROUND,				//R
	PICTURE_TYPE_RETICLE_00,		//レティクル
	PICTURE_TYPE_1ST,				//ランキング
	PICTURE_TYPE_2ND,				//ランキング
	PICTURE_TYPE_3RD,				//ランキング
	PICTURE_TYPE_MAX				//リストの数
} PICTURE_TYPE;

//---------------------------
//構造体の定義
//---------------------------
typedef struct
{
	D3DXVECTOR3 pos;	//ポリゴンの位置
	D3DXVECTOR3 move;	//移動量
	float fWidth;		//幅
	float fHeight;		//高さ
	PICTURE_TYPE aType;	//種類
	bool bUse;			//使ってるかどうか
} Picture;

//---------------------------
//プロトタイプ宣言
//---------------------------
HRESULT InitPicture(void);
void UninitPicture(void);
bool UpdatePicture(void);
void DrawPicture(void);
bool SetPicture(D3DXVECTOR3 pos, D3DXVECTOR3 move, float fWigth, float fHeight, PICTURE_TYPE aType);	//位置、幅、高さ、種類
#endif 
