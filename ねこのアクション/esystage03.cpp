//---------------------------
//インクルードファイル
//---------------------------
#include "esystage03.h"
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
#include "sound.h"

//---------------------------
//グローバル変数
//---------------------------
bool g_bEs03 = true;

//---------------------------
//初期化処理
//---------------------------
HRESULT InitEsStage03(void)
{
	g_bEs03 = true;

	if (g_bEs03 == true)
	{
		StopSound(SOUND_LABEL_BGM001);
		PlaySound(SOUND_LABEL_BGM004);

		InitBg();
		SetBg(D3DXVECTOR3(0.0f, 0.0f, 0.0f), SCREEN_WIDTH, SCREEN_HEIGHT, 1);

		InitPlayer();
		SetPlayer(D3DXVECTOR3(0.0f + PLAYER_X_SIZE / 2 * 1.1f, SCREEN_HEIGHT - 10.0f, 0.0f), PLAYER_X_SIZE, PLAYER_Y_SIZE);

		InitBlock();
		SetBlock(D3DXVECTOR3(0.0f, SCREEN_HEIGHT - 10.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), SCREEN_WIDTH, 10.0f, 12.8f, 1.0f, 0);
		SetBlock(D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), 10.0f, 620.0f, 1.0f, 6.0f, 0);
		SetBlock(D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), SCREEN_WIDTH, 50.0f, 12.8f, 1.0f, 0);
		SetBlock(D3DXVECTOR3(SCREEN_WIDTH - 10.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), 10.0f, SCREEN_HEIGHT, 1.0f, 6.0f, 0);

		SetBlock(D3DXVECTOR3(150.0f, SCREEN_HEIGHT - 150.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), 100.0f, 25.0f, 2.0f, 1.0f, 0);
		SetBlock(D3DXVECTOR3(350.0f, SCREEN_HEIGHT - 300.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), 100.0f, 25.0f, 2.0f, 1.0f, 0);
		SetBlock(D3DXVECTOR3(150.0f, SCREEN_HEIGHT - 450.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), 100.0f, 25.0f, 2.0f, 1.0f, 0);
		SetBlock(D3DXVECTOR3(350.0f, SCREEN_HEIGHT - 600.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), 100.0f, 25.0f, 2.0f, 1.0f, 0);

		SetBlock(D3DXVECTOR3(450.0f, SCREEN_HEIGHT - 150.0f, 0.0f), D3DXVECTOR3(0.0f, -1.5f, 0.0f), 100.0f, 25.0f, 2.0f, 1.0f, 1);

		InitEnemy();
		SetEnemy(D3DXVECTOR3(SCREEN_WIDTH - 300.0f, SCREEN_HEIGHT / 2, 0.0f), D3DXVECTOR3(0.0f, -2.0f, 0.0f), 200.0f, 200.0f, 2, 70);

		InitBullet();

		InitPause();
	}
	return S_OK;
}

//---------------------------
//終了処理
//---------------------------
void UninitEsStage03(void)
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
void UpdateEsStage03(void)
{
	if (GetKeyboardTrigger(DIK_E) == true || GetKeyboardTrigger(DIK_X) == true)
	{
		g_bEs03 = g_bEs03 ? false : true;
	}
	if (g_bEs03 == true)
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
	else if (g_bEs03 == false)
	{
		UpdateBg();

		g_bEs03 = UpdatePause();
	}
}

//---------------------------
//描画処理
//---------------------------
void DrawEsStage03(void)
{
	if (g_bEs03 == true)
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
	else if (g_bEs03 == false)
	{
		DrawBg();

		DrawPause();
	}
}