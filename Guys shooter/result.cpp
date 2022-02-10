//---------------------------
//インクルードファイル
//---------------------------
#include "result.h"
#include "fade.h"
#include "rank.h"
#include "Picture.h"
#include "keyinput.h"
#include "mouseinput.h"
#include "sound.h"

//---------------------------
//グローバル変数
//---------------------------
bool g_bUse2 = false;

//---------------------------
//初期化処理
//---------------------------
HRESULT InitResult(void)
{
	PlaySound(SOUND_RESULT_BGN);
	InitPicture();
	SetPicture(D3DXVECTOR3((SCREEN_WIDTH / 2) - 200.0f, (SCREEN_HEIGHT / 2) - 360.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), 80.0f, 50.0f, PICTURE_TYPE_1ST);
	SetPicture(D3DXVECTOR3((SCREEN_WIDTH / 2) - 200.0f, (SCREEN_HEIGHT / 2) - 180.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), 80.0f, 50.0f, PICTURE_TYPE_2ND);
	SetPicture(D3DXVECTOR3((SCREEN_WIDTH / 2) - 200.0f, SCREEN_HEIGHT / 2, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), 80.0f, 50.0f, PICTURE_TYPE_3RD);

	InitRank();

	return S_OK;
}
//---------------------------
//終了処理
//---------------------------
void UninitResult(void)
{
	UninitPicture();

	UninitRank();
}
//---------------------------
//更新処理
//---------------------------
void UpdateResult(void)
{
	static int nCnt;	//自動繊維タイマー
	int nNum = 0;		//rando用の変数

	nCnt++;				//タイマー加算

	UpdateRank();

	//タイマーが1584になるか || エンターキー押してたか
	if (nCnt >= 1584 && GetFade() == FADE_NONE || GetKeyboardTrigger(DIK_RETURN) == true && GetFade() == FADE_NONE || MouseDowan(MOUSE_WHEEL_BOTTON) == true && GetFade() == FADE_NONE)
	{
		StopSound(SOUND_RESULT_BGN);
		PlaySound(SOUND_PUSH_SE);
		SetFade(MODE_TITLE);
		nCnt = 0;		//カウントしょきか
	}
	if (g_bUse2 == true)
	{
		nNum = 4;
	}
	else if (g_bUse2 == false)
	{
		nNum = rand() % 4;
	}

	g_bUse2 = UpdatePicture();

	switch (nNum)
	{
	case 0:
		g_bUse2 = SetPicture(D3DXVECTOR3(SCREEN_WIDTH / 2, SCREEN_HEIGHT + 250.0f, 0.0f), D3DXVECTOR3(0.0f, -2.0f, 0.0f), 500.0f, 500.0f, PICTURE_TYPE_GUYS_00);
		break;
	case 1:
		g_bUse2 = SetPicture(D3DXVECTOR3(SCREEN_WIDTH / 2, 0 - 250.0f, 0.0f), D3DXVECTOR3(0.0f, 2.0f, 0.0f), 500.0f, 500.0f, PICTURE_TYPE_GUYS_01);
		break;
	case 2:
		g_bUse2 = SetPicture(D3DXVECTOR3(SCREEN_WIDTH + 250.0f, SCREEN_HEIGHT / 2, 0.0f), D3DXVECTOR3(-2.0f, 0.0f, 0.0f), 500.0f, 500.0f, PICTURE_TYPE_GUYS_02);
		break;
	case 3:
		g_bUse2 = SetPicture(D3DXVECTOR3(0 - 250.0f, SCREEN_HEIGHT / 2, 0.0f), D3DXVECTOR3(2.0f, 0.0f, 0.0f), 500.0f, 500.0f, PICTURE_TYPE_GUYS_03);
		break;
	}
}
//---------------------------
//描画処理
//---------------------------
void DrawResult(void)
{
	DrawPicture();

	DrawRank();
}