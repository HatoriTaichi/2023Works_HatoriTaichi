//---------------------------
//インクルードファイル
//---------------------------
#include "home.h"
#include "block.h"
#include "bg.h"
#include "player.h"
#include "difficulty level.h"
#include "bullet.h"
#include "score.h"
#include "life.h"
#include "timer.h"
#include "pause.h"
#include "sound.h"

//---------------------------
//初期化処理
//---------------------------
HRESULT InitHome(void)
{
	PLAYER *pPlayer;

	pPlayer = GetPlayer();

	PlaySound(SOUND_LABEL_BGM001);
	InitBg();
	SetBg(D3DXVECTOR3(0.0f, 0.0f, 0.0f), SCREEN_WIDTH, SCREEN_HEIGHT, 0);

	InitLetter();
	SetLetter(D3DXVECTOR3(TETTER_POS_00_X, TETTER_POS_00_Y, 0.0f), 0);
	//イージーをクリアしてたら
	if (pPlayer->nLevel >= 1)
	{
		SetLetter(D3DXVECTOR3(TETTER_POS_02_X, TETTER_POS_02_Y, 0.0f), 1);
	}
	//ノーマルをクリアしてたら
	if (pPlayer->nLevel >= 2)
	{
		SetLetter(D3DXVECTOR3(TETTER_POS_01_X, TETTER_POS_01_Y, 0.0f), 2);
	}
	
	InitBlock();
	SetBlock(D3DXVECTOR3(100.0f, SCREEN_HEIGHT - BLOCK_Y_SIZE * 3, 0.0f), D3DXVECTOR3(0.0f, -1.0f, 0.0f), 120.0f, 30.0f, 4.0f, 1.0f, 1);
	SetBlock(D3DXVECTOR3(420.0f, SCREEN_HEIGHT - BLOCK_Y_SIZE * 3, 0.0f), D3DXVECTOR3(0.0f, -1.0f, 0.0f), 120.0f, 30.0f, 4.0f, 1.0f, 1);
	SetBlock(D3DXVECTOR3(740.0f, SCREEN_HEIGHT - BLOCK_Y_SIZE * 3, 0.0f), D3DXVECTOR3(0.0f, -1.0f, 0.0f), 120.0f, 30.0f, 4.0f, 1.0f, 1);
	SetBlock(D3DXVECTOR3(0.0f, SCREEN_HEIGHT - BLOCK_Y_SIZE * 3, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), SCREEN_WIDTH, 60.0f, 21.3f, 1.0f, 0);

	InitPlayer();
	SetPlayer(D3DXVECTOR3(0.0f + PLAYER_X_SIZE / 2 * 1.1f, SCREEN_HEIGHT - BLOCK_Y_SIZE * 3, 0.0f), PLAYER_X_SIZE, PLAYER_Y_SIZE);

	InitBullet();

	return S_OK;
}

//---------------------------
//終了処理
//---------------------------
void UninitHome(void)
{
	UninitBg();

	UninitBlock();

	UninitLetter();

	UninitPlayer();

	UninitBullet();
}

//---------------------------
//更新処理
//---------------------------
void UpdateHome(void)
{
	UpdateBg();

	UpdateBlock();

	UpdateLetter();

	UpdatePlayer();

	UpdateBullet();
}

//---------------------------
//描画処理
//---------------------------
void DrawHome(void)
{
	DrawBg();

	DrawBlock();

	DrawLetter();

	DrawPlayer();

	DrawBullet();
}