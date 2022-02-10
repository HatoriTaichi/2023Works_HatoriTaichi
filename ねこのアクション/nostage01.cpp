//---------------------------
//インクルードファイル
//---------------------------
#include "nostage01.h"
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
bool g_bNo01 = true;

//---------------------------
//初期化処理
//---------------------------
HRESULT InitNoStage01(void)
{
	g_bNo01 = true;

	if (g_bNo01 == true)
	{
		InitBg();
		SetBg(D3DXVECTOR3(0.0f, 0.0f, 0.0f), SCREEN_WIDTH, SCREEN_HEIGHT, 1);

		InitPlayer();
		SetPlayer(D3DXVECTOR3(0.0f + PLAYER_X_SIZE / 2 * 1.1f, SCREEN_HEIGHT - 300.0f, 0.0f), PLAYER_X_SIZE, PLAYER_Y_SIZE);

		InitBlock();
		//一番上
		SetBlock(D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), SCREEN_WIDTH, 60.0f, 12.8f, 2.0f, 0);

		//階段
		SetBlock(D3DXVECTOR3(0.0f, SCREEN_HEIGHT - 300.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), 50.0f, 300.0f, 1.0f, 6.0f, 0);
		SetBlock(D3DXVECTOR3(50.0f, SCREEN_HEIGHT - 240.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), 50.0f, 240.0f, 1.0f, 4.8f, 0);
		SetBlock(D3DXVECTOR3(100.0f, SCREEN_HEIGHT - 180.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), 50.0f, 180.0f, 1.0f, 3.6f, 0);
		SetBlock(D3DXVECTOR3(150.0f, SCREEN_HEIGHT - 120.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), 50.0f, 120.0f, 1.0f, 2.4f, 0);
		SetBlock(D3DXVECTOR3(200.0f, SCREEN_HEIGHT - 60.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), 50.0f, 60.0f, 1.0f, 1.2f, 0);

		//上からの柱
		SetBlock(D3DXVECTOR3(270.0f, 60.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), 330.0f, 400.0f, 5.0f, 4.5f, 0);

		//ゴール前
		SetBlock(D3DXVECTOR3(SCREEN_WIDTH - 430, 200.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), 100.0f, SCREEN_HEIGHT - 200.0f, 1.0f, 7.0f, 0);
		SetBlock(D3DXVECTOR3(SCREEN_WIDTH - 330, 400.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), 350.0f, SCREEN_HEIGHT - 400.0f, 4.0f, 4.0f, 0);

		//一個目動く床
		SetBlock(D3DXVECTOR3(350.0f, SCREEN_HEIGHT - 60.0f, 0.0f), D3DXVECTOR3(+2.0f, 0.0f, 0.0f), 100.0f, 25.0f, 1.0f, 0.5f, 1);
		SetBlock(D3DXVECTOR3(SCREEN_WIDTH / 2 + 100.0f, SCREEN_HEIGHT - 60.0f, 0.0f), D3DXVECTOR3(0.0f, -2.0f, 0.0f), 100.0f, 25.0f, 1.0f, 0.5f, 1);

		InitTrap();
		SetTrap(D3DXVECTOR3(600.0f, 60.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), 30.0f, 400.0f, 1.0f, 10.0f, 1);

		SetTrap(D3DXVECTOR3(630.0f, 60.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), 300.0f, 30.0f, 10.0f, 1.0f, 0);

		InitEnemy();

		InitBullet();

		InitScore();

		InitTimer();

		InitLife();

		InitPause();
	}
	return S_OK;
}

//---------------------------
//終了処理
//---------------------------
void UninitNoStage01(void)
{
	UninitBg();

	UninitPlayer();

	UninitBlock();

	UninitTrap();

	UninitEnemy();

	UninitBullet();

	UninitPause();
}

//---------------------------
//更新処理
//---------------------------
void UpdateNoStage01(void)
{
	if (GetKeyboardTrigger(DIK_E) == true || GetKeyboardTrigger(DIK_X) == true)
	{
		g_bNo01 = g_bNo01 ? false : true;
	}
	if (g_bNo01 == true)
	{
		UpdateBg();

		UpdatePlayer();

		UpdateBlock();

		UpdateTrap();

		UpdateEnemy();

		UpdateBullet();

		UpdateScore();

		UpdateTimer();

		UpdateLife();
	}
	else if (g_bNo01 == false)
	{
		UpdateBg();

		g_bNo01 = UpdatePause();
	}
}

//---------------------------
//描画処理
//---------------------------
void DrawNoStage01(void)
{
	if (g_bNo01 == true)
	{
		DrawBg();

		DrawPlayer();

		DrawBlock();

		DrawTrap();

		DrawEnemy();

		DrawBullet();

		DrawScore();

		DrawTimer();

		DrawLife();
	}
	else if (g_bNo01 == false)
	{
		DrawBg();

		DrawPause();
	}
}