#pragma once
#ifndef _FLOO_H_
#define _FLOO_H_
//---------------------------
//インクルードファイル
//---------------------------
#include "main.h"

//---------------------------
//マクロ定義
//---------------------------
#define MAX_FLOO (1)//床メッシュフィールドの数
#define MAX_FLOO_TEX (1)	//テクスチャの数
#define MS_X (0.5f)	//半径X
#define MS_Y (0.5f) //半径Y
#define MS_Z (0.5f)	//半径Z

//---------------------------
//床タイプ
//---------------------------
#define FLOO_MAX_VTX_X (1)	//横ブロックの数
#define FLOO_MAX_VTX_Z (1)	//奥行ブロックの数
#define FLOO_VTX_NUM_MAX ((FLOO_MAX_VTX_X + 1) * (FLOO_MAX_VTX_Z + 1))				//全体頂点の数
#define FLOO_IDX_NUM_MAX ((FLOO_MAX_VTX_X + 1) * (FLOO_MAX_VTX_Z + 1) + (FLOO_MAX_VTX_Z - 1) * (FLOO_MAX_VTX_X + 3))	//インデックスの数
#define FLOO_POLY_NUM_MAX (2 * FLOO_MAX_VTX_X * FLOO_MAX_VTX_Z + (FLOO_MAX_VTX_Z * 4) - 4))	//△の数

//---------------------------
//構造体
//---------------------------
typedef struct
{
	D3DXVECTOR3	pos;		//位置
	D3DXVECTOR3 rot;		//向き
	D3DXMATRIX mtxWold;		//ワールドマトリックス
	float fWidth;			//幅
	float fDepht;			//奥行
	int nTex;				//テクスチャ
	bool bUse;				//使ってるか
} Field;
//---------------------------
//プロトタイプ宣言
//---------------------------
HRESULT InitFloo(void);
void UninitFloo(void);
void UpdateFloo(void);
void DrawFloo(void);
void SetFloo(D3DXVECTOR3 rot, D3DXVECTOR3 pos, float fWidth, float fDepht, int nTex);	//向き、位置、幅、奥行、テクスチャ
#endif