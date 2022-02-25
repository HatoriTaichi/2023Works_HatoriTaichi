#pragma once
#ifndef _SHADOW_H_
#define _SHADOW_H_
//---------------------------
//インクルードファイル
//---------------------------
#include "main.h"

//---------------------------
//マクロ定義
//---------------------------
#define MAX_SHADOW (256)	//影の最大数
#define SHADOW_X (1.0f)		//影のX
#define SHADOW_Z (1.0f)		//影のY

//---------------------------
//構造体
//---------------------------
typedef struct
{
	D3DXMATRIX mtxWorld;	//ワールドマトリックス
	D3DXVECTOR3 pos;		//位置
	D3DXVECTOR3 rot;		//向き
	float fWhith;			//幅
	float fHeiht;			//高さ
	float fDepht;			//奥行
	float fAlpha;			//α
	int Index;				//影の番号
	bool bUse;				//使ってるかどうか
} Shadow;

//---------------------------
//プロトタイプ宣言
//---------------------------
HRESULT InitShadow(void);
void UninitShadow(void);
void UpdateShadow(void);
void DrawShadow(void);
int SetShadow(D3DXVECTOR3 pos, float fWhith, float fDepht);	//位置、幅、高さ
void SetPointShadow(int nIdx, D3DXVECTOR3 pos, float fWhith, float fDepht, bool bUse);	//使ってる影の番号、位置
#endif