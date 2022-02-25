#pragma once
#ifndef _CAMERA_H_
#define _CAMERA_H_

//---------------------------
//インクルードファイル
//---------------------------
#include "main.h"

//---------------------------
//マクロ定義
//---------------------------
#define MAX_CAMERA (2)				//カメラの最大数
#define CAMERA_MOVE_SPEED (1.0f)	//プレイヤーの移動量
#define CAMERA_DESTAANCE (200)		//プレイヤーと注視点の距離

//---------------------------
//構造体
//---------------------------
typedef struct
{
	D3DXVECTOR3 PosV;			//視点
	D3DXVECTOR3 PosR;			//注視点
	D3DXVECTOR3 Rot;			//カメラの向き
	POINT Pointer;				//マウスの位置
	POINT Poimove;				//マウスの移動量
	D3DXVECTOR3 VecU;			//上方向ベクトル
	D3DXMATRIX mtxProjection;	//プロジェクションマトリックス
	D3DXMATRIX mtxView;			//ビューマトリックス
	D3DVIEWPORT9 viewport;		//ビューポート
	float Long;					//幅
	bool bUse;					//使ってるか
} Camera;

//---------------------------
//プロトタイプ宣言
//---------------------------
HRESULT InitCamera(void);
void UninitCamera(void);
void UpdateCamera(void);
void SetCamera(int nIdx);
Camera *GetCamera(void);
#endif