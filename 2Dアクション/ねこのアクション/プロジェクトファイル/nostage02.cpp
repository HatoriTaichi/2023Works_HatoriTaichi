//---------------------------
//インクルードファイル
//---------------------------
#include "nostage02.h"
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
bool g_bNo02 = true;

//---------------------------
//初期化処理
//---------------------------
HRESULT InitNoStage02(void)
{
	g_bNo02 = true;

	if (g_bNo02 == true)
	{
		InitBg();
		SetBg(D3DXVECTOR3(0.0f, 0.0f, 0.0f), SCREEN_WIDTH, SCREEN_HEIGHT, 1);

		InitPlayer();
		SetPlayer(D3DXVECTOR3(0.0f + PLAYER_X_SIZE / 2 * 1.1f, 400.0f, 0.0f), PLAYER_X_SIZE, PLAYER_Y_SIZE);

		InitBlock();
		//初期地面
		SetBlock(D3DXVECTOR3(0.0f, 400.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), 100.0f, SCREEN_HEIGHT - 400.0f, 1.0f, 4.0f, 0);
		SetBlock(D3DXVECTOR3(100.0f, 300.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), 100.0f, SCREEN_HEIGHT - 300.0f, 1.0f, 5.0f, 0);
		SetBlock(D3DXVECTOR3(200.0f, 200.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), 100.0f, SCREEN_HEIGHT - 200.0f, 1.0f, 6.0f, 0);

		//とげ地面
		SetBlock(D3DXVECTOR3(300.0f, 250.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), SCREEN_HEIGHT - 80.0f, 50.0f, 7.0f, 1.0f, 0);
		SetBlock(D3DXVECTOR3(300.0f, 450.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), SCREEN_HEIGHT - 80.0f, 50.0f, 7.0f, 1.0f, 0);
		SetBlock(D3DXVECTOR3(300.0f, 650.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), SCREEN_HEIGHT - 30.0f, 50.0f, 7.0f, 1.0f, 0);

		//さいごじめｗん
		SetBlock(D3DXVECTOR3(1170.0f, 650.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), SCREEN_HEIGHT - 30.0f, 50.0f, 7.0f, 1.0f, 0);
		SetBlock(D3DXVECTOR3(1170.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), SCREEN_HEIGHT - 30.0f, 450.0f, 7.0f, 6.0f, 0);

		//動く床
		SetBlock(D3DXVECTOR3(330.0f, 170.0f, 0.0f), D3DXVECTOR3(2.0f, 0.0f, 0.0f), 100.0f, 25, 2.0f, 1.0f, 1);
		SetBlock(D3DXVECTOR3(500.0f, 370.0f, 0.0f), D3DXVECTOR3(2.5f, 0.0f, 0.0f), 100.0f, 25, 2.0f, 1.0f, 1);

		InitTrap();
		SetTrap(D3DXVECTOR3(300.0f, 240.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), SCREEN_HEIGHT - 80.0f, 10.0f, 20.0f, 1.0f, 3);

		SetTrap(D3DXVECTOR3(300.0f, 440.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), SCREEN_HEIGHT - 80.0f, 10.0f, 20.0f, 1.0f, 3);

		InitEnemy();
		SetEnemy(D3DXVECTOR3(650, 650, 0.0f), D3DXVECTOR3(-1.0f, 0.0f, 0.0f), 50.0f, 50.0f, 0, 1);
		SetEnemy(D3DXVECTOR3(650, 650, 0.0f), D3DXVECTOR3(1.0f, 0.0f, 0.0f), 50.0f, 50.0f, 0, 1);

		InitBullet();

		InitPause();
	}
	return S_OK;
}

//---------------------------
//終了処理
//---------------------------
void UninitNoStage02(void)
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
void UpdateNoStage02(void)
{
	if (GetKeyboardTrigger(DIK_E) == true || GetKeyboardTrigger(DIK_X) == true)
	{
		g_bNo02 = g_bNo02 ? false : true;
	}
	if (g_bNo02 == true)
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
	else if (g_bNo02 == false)
	{
		UpdateBg();

		g_bNo02 = UpdatePause();
	}
}

//---------------------------
//描画処理
//---------------------------
void DrawNoStage02(void)
{
	if (g_bNo02 == true)
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
	else if (g_bNo02 == false)
	{
		DrawBg();

		DrawPause();
	}
}