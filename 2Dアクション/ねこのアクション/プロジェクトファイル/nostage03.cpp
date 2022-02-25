//---------------------------
//インクルードファイル
//---------------------------
#include "nostage03.h"
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
bool g_bNo03 = true;
bool g_bPlayer = true;
bool g_bPlayer2 = true;

//---------------------------
//初期化処理
//---------------------------
HRESULT InitNoStage03(void)
{
	g_bNo03 = true;
	g_bPlayer = true;
	g_bPlayer2 = true;

	if (g_bNo03 == true)
	{
		InitBg();
		SetBg(D3DXVECTOR3(0.0f, 0.0f, 0.0f), SCREEN_WIDTH, SCREEN_HEIGHT, 1);

		InitPlayer();
		SetPlayer(D3DXVECTOR3(0.0f + PLAYER_X_SIZE / 2 * 1.1f, 650.0f, 0.0f), PLAYER_X_SIZE, PLAYER_Y_SIZE);

		InitBlock();
		//初期地面
		SetBlock(D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), SCREEN_WIDTH, 100.0f, 12.8f, 2.0f, 0);
		SetBlock(D3DXVECTOR3(0.0f, 650.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), 100.0f, 100.0f, 1.0f, 1.0f, 0);

		//さんまた床
		SetBlock(D3DXVECTOR3(250.0f, 250.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), 600.0f, 50.0f, 5.0f, 1.0f, 0);
		SetBlock(D3DXVECTOR3(250.0f, 450.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), 600.0f, 50.0f, 5.0f, 1.0f, 0);
		SetBlock(D3DXVECTOR3(250.0f, 650.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), 600.0f, 50.0f, 5.0f, 1.0f, 0);

		//邪魔
		SetBlock(D3DXVECTOR3(350.0f, 425.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), 25.0f, 25.0f, 1.0f, 1.0f, 0);
		SetBlock(D3DXVECTOR3(350.0f, 625.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), 25.0f, 25.0f, 1.0f, 1.0f, 0);

		//移動床縦
		SetBlock(D3DXVECTOR3(100.0f, 650.0f, 0.0f), D3DXVECTOR3(0.0f, -1.0f, 0.0f), 100.0f, 25.0f, 1.0f, 1.0f, 1);
		SetBlock(D3DXVECTOR3(950.0f, 450.0f, 0.0f), D3DXVECTOR3(0.0f, -1.5f, 0.0f), 100.0f, 25.0f, 1.0f, 1.0f, 1);

		//最後
		SetBlock(D3DXVECTOR3(1100.0f, SCREEN_HEIGHT - 10.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), 2000.0f, 50.0f, 4.0f, 1.0f, 0);

		InitTrap();
		
		InitEnemy();
		
		InitBullet();

		InitPause();
	}
	return S_OK;
}

//---------------------------
//終了処理
//---------------------------
void UninitNoStage03(void)
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
void UpdateNoStage03(void)
{
	PLAYER			*pPlayer;

	pPlayer = GetPlayer();

	if (GetKeyboardTrigger(DIK_E) == true || GetKeyboardTrigger(DIK_X) == true)
	{
		g_bNo03 = g_bNo03 ? false : true;
	}
	if (g_bNo03 == true)
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
		if (pPlayer->pos.x + pPlayer->fWidth / 2 >= 650 &&
			pPlayer->pos.y >= 500.0f &&
			g_bPlayer == true && 
			pPlayer->bUse == true)
		{
			SetTrap(D3DXVECTOR3(700.0f, 500.0f, 0.0f), D3DXVECTOR3(-0.5f, 0.0f, 0.0f), 50.0f, 150.0f, 1.0f, 4.0f, 2);

			SetBlock(D3DXVECTOR3(375.0f, 535.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), 50.0f, 25.0f, 1.0f, 2.0f, 2);

			g_bPlayer = false;
		}
		else if (pPlayer->pos.x + pPlayer->fWidth / 2 >= 650 &&
				 pPlayer->pos.y >= 450 &&
				 pPlayer->pos.y <= 500 &&
				 g_bPlayer2 == true &&
				 pPlayer->bUse == true)
		{
			SetTrap(D3DXVECTOR3(700.0f, 300.0f, 0.0f), D3DXVECTOR3(-0.5f, 0.0f, 0.0f), 50.0f, 150.0f, 1.0f, 4.0f, 2);

			SetBlock(D3DXVECTOR3(375.0f, 335.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), 50.0f, 25.0f, 1.0f, 2.0f, 2);

			g_bPlayer2 = false;
		}
		if (pPlayer->bUse == false)
		{
			g_bPlayer = true;
			g_bPlayer2 = true;
		}
	}
	else if (g_bNo03 == false)
	{
		UpdateBg();

		g_bNo03 = UpdatePause();
	}
}

//---------------------------
//描画処理
//---------------------------
void DrawNoStage03(void)
{
	if (g_bNo03 == true)
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
	else if (g_bNo03 == false)
	{
		DrawBg();

		DrawPause();
	}
}