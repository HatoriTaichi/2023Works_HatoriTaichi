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

//---------------------------
//グローバル変数
//---------------------------
bool g_bHd04 = true;

//---------------------------
//初期化処理
//---------------------------
HRESULT InitHdStage04(void)
{
	g_bHd04 = true;

	if (g_bHd04 == true)
	{
		InitBg();
		SetBg(D3DXVECTOR3(0.0f, 0.0f, 0.0f), SCREEN_WIDTH, SCREEN_HEIGHT, 1);

		InitPlayer();
		SetPlayer(D3DXVECTOR3(0.0f + PLAYER_X_SIZE / 2 * 1.2f, SCREEN_HEIGHT - 11.0f, 0.0f), PLAYER_X_SIZE, PLAYER_Y_SIZE);

		InitBlock();
		SetBlock(D3DXVECTOR3(0.0f, SCREEN_HEIGHT - 10.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), SCREEN_WIDTH, 10.0f, 12.8f, 1.0f, 0);
		SetBlock(D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), 10.0f, 620.0f, 1.0f, 6.0f, 0);
		SetBlock(D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), SCREEN_WIDTH, 50.0f, 12.8f, 1.0f, 0);
		SetBlock(D3DXVECTOR3(SCREEN_WIDTH - 10.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), 10.0f, SCREEN_HEIGHT, 1.0f, 6.0f, 0);

		SetBlock(D3DXVECTOR3(320.0f, SCREEN_HEIGHT - 180, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), 100.0f, 180, 1.0f, 2.5f, 0);
		SetBlock(D3DXVECTOR3(640, SCREEN_HEIGHT - 180, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), 100.0f, 180, 1.0f, 2.5f, 0);
		SetBlock(D3DXVECTOR3(960, SCREEN_HEIGHT - 180, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), 100.0f, 180, 1.0f, 2.5f, 0);

		InitEnemy();
		SetEnemy(D3DXVECTOR3(SCREEN_WIDTH - 150.0f, SCREEN_HEIGHT - 20.0f, 0.0f), D3DXVECTOR3(1.5f, 0.0f, 0.0f), 100.0f, 100.0f, 2, 50);

		InitBullet();

		InitPause();
	}
	return S_OK;
}

//---------------------------
//終了処理
//---------------------------
void UninitHdStage04(void)
{
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
void UpdateHdStage04(void)
{
	static int nCnt;

	if (GetKeyboardTrigger(DIK_E) == true || GetKeyboardTrigger(DIK_X) == true)
	{
		g_bHd04 = g_bHd04 ? false : true;
	}
	if (g_bHd04 == true)
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
		if (nCnt >= 1440)
		{
			SetBullet(D3DXVECTOR3(20.0f, 20, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), BULLET_SIZE_X * 5, BULLET_SIZE_Y * 5, 2);
			SetBullet(D3DXVECTOR3(SCREEN_WIDTH - 20.0f, 20.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), BULLET_SIZE_X * 5, BULLET_SIZE_Y * 5, 2);
			SetBullet(D3DXVECTOR3(20.0f, SCREEN_HEIGHT - 20.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), BULLET_SIZE_X * 5, BULLET_SIZE_Y * 5, 2);
			SetBullet(D3DXVECTOR3(SCREEN_WIDTH - 20.0f, SCREEN_HEIGHT - 20.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), BULLET_SIZE_X * 5, BULLET_SIZE_Y * 5, 2);
			nCnt = 0;
		}
	}
	else if (g_bHd04 == false)
	{
		UpdateBg();

		g_bHd04 = UpdatePause();
	}
}

//---------------------------
//描画処理
//---------------------------
void DrawHdStage04(void)
{
	if (g_bHd04 == true)
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
	else if (g_bHd04 == false)
	{
		DrawBg();

		DrawPause();
	}
}