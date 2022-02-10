#pragma once
#ifndef _MAIN_H_
#define _MAIN_H_


//---------------------------
//インクルードファイル
//---------------------------
#include <windows.h>
#include "d3dx9.h"

#define DIRECTINPUT_VERSION (0x0800) //ビルド時の警告対処用マクロ
#include "dinput.h"//入力処理に必要
#include "xaudio2.h"

//---------------------------
//ライブラリのリンク
//---------------------------
#pragma comment(lib,"d3d9.lib") //描画に必要
#pragma comment(lib,"d3dx9.lib") //[d3d9.lib]の拡張ライブラリ
#pragma comment(lib,"dxguid.lib") //DirectXコンポーネント（部品）使用に必要
#pragma comment (lib, "winmm.lib")
#pragma comment(lib,"dinput8.lib") //入力処理に必要

//---------------------------
//マクロ定義
//---------------------------
#define SCREEN_WIDTH (1280) //ウィンドウの幅
#define SCREEN_HEIGHT (720) //ウィンドウの高さ
#define FVF_VERTEX_2D (D3DFVF_XYZRHW|D3DFVF_DIFFUSE|D3DFVF_TEX1) //2Dの柔軟な頂点フォーマット

//---------------------------
//列挙型.モードの種類
//---------------------------
typedef enum
{
	MODE_TITLE = 0,		//タイトル
	MODE_OPERATION,		//操作説明
	MODE_HOME,			//ホーム
	MODE_ES_STAGE01,	//イージーのステージ01
	MODE_ES_STAGE02,	//イージーのステージ02
	MODE_ES_STAGE03,	//イージーのステージ03
	MODE_NO_STAGE01,	//ノーマルのステージ01
	MODE_NO_STAGE02,	//ノーマルのステージ02
	MODE_NO_STAGE03,	//ノーマルのステージ03
	MODE_NO_STAGE04,	//ノーマルのステージ04
	MODE_HD_STAGE01,	//ハードのステージ01
	MODE_HD_STAGE02,	//はーどのステージ02
	MODE_HD_STAGE03,	//はーどのすてーじ03
	MODE_HD_STAGE04,	//はーどのすてーじ04
	MODE_HD_STAGE05,	//はーどのすてーじ05
	MODE_RESULT,		//リザルト画面
	MODE_GAMEOVER,		//ゲームオーバー
	MODE_MAX			//リストの数
} MODE;

//---------------------------
//構造体の定義
//---------------------------
typedef struct
{
	D3DXVECTOR3 pos;	//頂点座標
	float rhw;			//1.0fで固定
	D3DCOLOR col;		//頂点カラー
	D3DXVECTOR2 tex;	//テクスチャ座標
} VERTEX_2D;

//---------------------------
//プロトタイプ宣言
//---------------------------
LPDIRECT3DDEVICE9 GetDevice(void);
void SetMode(MODE mode);
MODE GetMode(void);
MODE GetMode2(void);
#endif 