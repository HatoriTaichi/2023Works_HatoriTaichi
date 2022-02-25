//---------------------------
//インクルードファイル
//---------------------------
#include "result.h"
#include "bg.h"
#include "fade.h"
#include "input.h"
#include "timer.h"
#include "life.h"
#include "rank.h"
#include "score.h"
#include "player.h"
#include "block.h"
#include "sound.h"

//---------------------------
//グローバル変数
//---------------------------


//---------------------------
//初期化処理
//---------------------------
HRESULT InitResult(void)
{
	StopSound(SOUND_LABEL_BGM004);
	PlaySound(SOUND_LABEL_BGM002);

	InitBg();
	SetBg(D3DXVECTOR3(0.0f, 0.0f, 0.0f), SCREEN_WIDTH, SCREEN_HEIGHT, 4);
	SetBg(D3DXVECTOR3(SCREEN_WIDTH / 2 - 300.0f, 50.0f, 0.0f), 140.0f, 90.0f, 7);
	SetBg(D3DXVECTOR3(SCREEN_WIDTH / 2 - 300.0f, 140.0f, 0.0f), 140.0f, 90.0f, 8);
	SetBg(D3DXVECTOR3(SCREEN_WIDTH / 2 - 300.0f, 220.0f, 0.0f), 140.0f, 90.0f, 9);
	SetBg(D3DXVECTOR3(SCREEN_WIDTH / 2 - 300.0f, 400.0f, 0.0f), 140.0f, 90.0f, 10);
	SetBg(D3DXVECTOR3(SCREEN_WIDTH - 300.0f, SCREEN_HEIGHT - 50.0f, 0.0f), 300.0f, 50.0f, 5);

	InitRank();

	InitBlock();
	SetBlock(D3DXVECTOR3(0.0f, SCREEN_HEIGHT, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), SCREEN_WIDTH, 10.0f, 1.0f, 1.0f, 0);

	InitPlayer();
	SetPlayer(D3DXVECTOR3(SCREEN_WIDTH - (300.0f + PLAYER_X_SIZE), SCREEN_HEIGHT, 0.0f), PLAYER_X_SIZE, PLAYER_Y_SIZE);

	return S_OK;
}
//---------------------------
//終了処理
//---------------------------
void UninitResult(void)
{
	UninitBg();

	UninitScore();

	UninitTimer();

	UninitLife();

	UninitRank();

	UninitBlock();

	UninitPlayer();
}
//---------------------------
//更新処理
//---------------------------
void UpdateResult(void)
{
	static int nCnt;	//自動繊維タイマー

	nCnt++;				//タイマー加算

	UpdateBg();

	UpdateScore();

	UpdateRank();

	UpdatePlayer();

	UpdateBlock();
	//タイマーが700になるか && エンターキー押してたか
	if (nCnt >= 1584 && GetFade() == FADE_NONE || GetKeyboardTrigger(DIK_RETURN) == true && GetFade() == FADE_NONE)
	{
		PlaySound(SOUND_LABEL_SE000);
		SetFade(MODE_TITLE);
		nCnt = 0;		//カウントしょきか
		StopSound(SOUND_LABEL_BGM002);
	}
}
//---------------------------
//描画処理
//---------------------------
void DrawResult(void)
{
	DrawBg();

	DrawRank();

	DrawScore();

	DrawBlock();

	DrawPlayer();
}