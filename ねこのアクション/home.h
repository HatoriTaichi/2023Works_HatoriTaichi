#pragma once
#ifndef _HOME_H_
#define _HOME_H_

//---------------------------
//インクルードファイル
//---------------------------
#include "main.h"

//---------------------------
//マクロ定義
//---------------------------


//---------------------------
//構造体の定義
//---------------------------
typedef struct
{
	D3DXVECTOR3 pos;  //ポリゴンの位置
} HOME;

//---------------------------
//プロトタイプ宣言
//---------------------------
HRESULT InitHome(void);
void UninitHome(void);
void UpdateHome(void);
void DrawHome(void);
#endif 
