//---------------------------
//インクルードファイル
//---------------------------
#include "esystage02.h"
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
#include "pause.h"

//---------------------------
//グローバル変数
//---------------------------
bool g_bEs02 = true;

//---------------------------
//初期化処理
//---------------------------
HRESULT InitEsStage02(void)
{
	g_bEs02 = true;

	if (g_bEs02 == true)
	{
		InitBg();
		SetBg(D3DXVECTOR3(0.0f, 0.0f, 0.0f), SCREEN_WIDTH, SCREEN_HEIGHT, 1);

		InitPlayer();
		SetPlayer(D3DXVECTOR3(0.0f + PLAYER_X_SIZE / 2 * 1.1f, 290.0f, 0.0f), PLAYER_X_SIZE, PLAYER_Y_SIZE);

		InitBlock();
		SetBlock(D3DXVECTOR3(0.0f, 290.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), 100.0f, SCREEN_HEIGHT - 30.0f, 2.0f, 10.0f, 0);
		SetBlock(D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), SCREEN_WIDTH, 100.0f, 12.8f, 2.0f, 0);

		SetBlock(D3DXVECTOR3(400.0f, 100.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), 100.0f, 450.0f, 2.0f, 8.0f, 0);
		SetBlock(D3DXVECTOR3(400.0f, SCREEN_HEIGHT - 25.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), 100.0f, 100.0f, 2.0f, 4.0f, 0);

		SetBlock(D3DXVECTOR3(525.0f, 510.0, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), 25.0f, 25.0f, 1.0f, 1.0f, 2);

		SetBlock(D3DXVECTOR3(800.0f, 100.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), 100.0f, 250.0f, 2.0f, 7.0f, 0);
		SetBlock(D3DXVECTOR3(800.0f, 470.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), 100.0f, 250.0f, 2.0f, 7.0f, 0);

		SetBlock(D3DXVECTOR3(930.0f, 310.0, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), 25.0f, 25.0f, 1.0f, 1.0f, 2);

		SetBlock(D3DXVECTOR3(1200.0f, 100.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), 100.0f, 500.0f, 2.0f, 7.0f, 0);
		SetBlock(D3DXVECTOR3(1200.0f, SCREEN_HEIGHT - 10.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), 150.0f, 10.0f, 2.0f, 1.0f, 0);

		SetBlock(D3DXVECTOR3(1150.0f, SCREEN_HEIGHT - 150.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), 25.0f, 25.0f, 1.0f, 1.0f, 2);

		SetBlock(D3DXVECTOR3(200.0f, 500, 0.0f), D3DXVECTOR3(0.0f, -2.0f, 0.0f), 100.0f, 20.0f, 3.0f, 1.0f, 1);
		SetBlock(D3DXVECTOR3(600.0f, 500, 0.0f), D3DXVECTOR3(0.0f, -2.0f, 0.0f), 100.0f, 20.0f, 3.0f, 1.0f, 1);
		SetBlock(D3DXVECTOR3(1000.0f, 500, 0.0f), D3DXVECTOR3(0.0f, -2.0f, 0.0f), 100.0f, 20.0f, 3.0f, 1.0f, 1);

		InitEnemy();

		InitBullet();

		InitPause();
	}
	return S_OK;
}

//---------------------------
//終了処理
//---------------------------
void UninitEsStage02(void)
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
void UpdateEsStage02(void)
{
	if (GetKeyboardTrigger(DIK_E) == true || GetKeyboardTrigger(DIK_X) == true)
	{
		g_bEs02 = g_bEs02 ? false : true;
	}
	if (g_bEs02 == true)
	{
		UpdateBg();

		UpdatePlayer();

		UpdateBlock();

		UpdateEnemy();

		UpdateBullet();

		UpdateScore();

		UpdateTimer();

		UpdateLife();
	}
	else if (g_bEs02 == false)
	{
		UpdateBg();

		g_bEs02 = UpdatePause();
	}
}

//---------------------------
//描画処理
//---------------------------
void DrawEsStage02(void)
{
	if (g_bEs02 == true)
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
	else if (g_bEs02 == false)
	{
		DrawBg();

		DrawPause();
	}
}