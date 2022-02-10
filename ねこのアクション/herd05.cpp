//---------------------------
//インクルードファイル
//---------------------------
#include "herd03.h"
#include "bullet.h"
#include "block.h"
#include "enemy.h"
#include "input.h"
#include "player.h"
#include "bg.h"
#include "score.h"
#include "timer.h"
#include "pause.h"
#include "life.h"
#include "trap.h"
#include "sound.h"

//---------------------------
//グローバル変数
//---------------------------
bool g_bHd05 = true;

//---------------------------
//初期化処理
//---------------------------
HRESULT InitHdStage05(void)
{
	g_bHd05 = true;

	if (g_bHd05 == true)
	{
		StopSound(SOUND_LABEL_BGM001);
		PlaySound(SOUND_LABEL_BGM004);

		InitBg();
		SetBg(D3DXVECTOR3(0.0f, 0.0f, 0.0f), SCREEN_WIDTH, SCREEN_HEIGHT, 1);

		InitPlayer();
		SetPlayer(D3DXVECTOR3(0.0f + PLAYER_X_SIZE / 2 * 1.2f, SCREEN_HEIGHT - 11.0f, 0.0f), PLAYER_X_SIZE, PLAYER_Y_SIZE);

		InitBlock();
		SetBlock(D3DXVECTOR3(0.0f, SCREEN_HEIGHT - 10.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), SCREEN_WIDTH, 10.0f, 12.8f, 1.0f, 0);
		SetBlock(D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), 10.0f, 620.0f, 1.0f, 6.0f, 0);
		SetBlock(D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), SCREEN_WIDTH, 50.0f, 12.8f, 1.0f, 0);
		SetBlock(D3DXVECTOR3(SCREEN_WIDTH - 10.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), 10.0f, SCREEN_HEIGHT, 1.0f, 6.0f, 0);

		SetBlock(D3DXVECTOR3(300.0f, (SCREEN_HEIGHT - 10.0f) - 100.0f, 0.0f), D3DXVECTOR3(0.0f, -2.0f, 0.0f), 100.0f, 25, 1.0f, 1.0f, 1);

		InitEnemy();
		SetEnemy(D3DXVECTOR3(SCREEN_WIDTH - 350.0f, SCREEN_HEIGHT / 2, 0.0f), D3DXVECTOR3(2.0f, -2.0f, 0.0f), 200.0f, 200.0f, 2, 110);

		InitBullet();

		InitPause();
	}
	return S_OK;
}

//---------------------------
//終了処理
//---------------------------
void UninitHdStage05(void)
{
	StopSound(SOUND_LABEL_BGM004);
	UninitBg();

	UninitPlayer();

	UninitBlock();

	UninitEnemy();

	UninitBullet();

	UninitPause();
}

//---------------------------
//更新処理
//---------------------------
void UpdateHdStage05(void)
{
	static int nCnt;

	if (GetKeyboardTrigger(DIK_E) == true || GetKeyboardTrigger(DIK_X) == true)
	{
		g_bHd05 = g_bHd05 ? false : true;
	}
	if (g_bHd05 == true)
	{
		nCnt++;

		UpdateBg();

		UpdatePlayer();

		UpdateBlock();

		UpdateEnemy();

		UpdateBullet();

		UpdateScore();

		UpdateTimer();

		UpdateLife();
	}
	else if (g_bHd05 == false)
	{
		UpdateBg();

		g_bHd05 = UpdatePause();
	}
}

//---------------------------
//描画処理
//---------------------------
void DrawHdStage05(void)
{
	if (g_bHd05 == true)
	{
		DrawBg();

		DrawPlayer();

		DrawBlock();

		DrawEnemy();

		DrawBullet();

		DrawScore();

		DrawTimer();

		DrawLife();
	}
	else if (g_bHd05 == false)
	{
		DrawBg();

		DrawPause();
	}
}