//---------------------------
//インクルードファイル
//---------------------------
#include "title.h"
#include "Picture.h"
#include "keyinput.h"
#include "fade.h"
#include "sound.h"

//---------------------------
//グローバル変数
//---------------------------
bool g_bUse = false;
bool g_bEnter = false;

//---------------------------
//初期化処理
//---------------------------
HRESULT InitTitle(void)
{
	PlaySound(SOUND_TITLE_BGM);
	InitPicture();
	SetPicture(D3DXVECTOR3(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 3, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), 500.0f, 100.0f, PICTURE_TYPE_TITLE);
	SetPicture(D3DXVECTOR3(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), 250.0f, 50.0f, PICTURE_TYPE_ENTER);

	return S_OK;
}

//---------------------------
//終了処理
//---------------------------
void UninitTitle(void)
{
	UninitPicture();
}

//---------------------------
//更新処理
//---------------------------
void UpdateTitle(void)
{
	static int nCnt;	//自動繊維タイマー
	int nNum = 0;		//rando用の変数
	
	nCnt++;	//タイマー加算

	if (GetKeyboardTrigger(DIK_RETURN) == true && GetFade() == FADE_NONE)
	{
		StopSound(SOUND_TITLE_BGM);
		PlaySound(SOUND_PUSH_SE);
		SetFade(MODE_OPERATION);
	}
	//10秒でランキング画面
	else if (nCnt >= 1440 && GetFade() == FADE_NONE)
	{
		StopSound(SOUND_TITLE_BGM);
		PlaySound(SOUND_PUSH_SE);
		SetFade(MODE_RESULT);
		nCnt = 0;
	}

	if (g_bUse == true)
	{
		nNum = 4;
	}
	else if (g_bUse == false)
	{
		nNum = rand() % 4;
	}

	g_bUse = UpdatePicture();

	switch (nNum)
	{
	case 0:
		g_bUse = SetPicture(D3DXVECTOR3(SCREEN_WIDTH / 2, SCREEN_HEIGHT + 250.0f, 0.0f), D3DXVECTOR3(0.0f, -2.0f, 0.0f), 500.0f, 500.0f, PICTURE_TYPE_GUYS_00);
		break;
	case 1:
		g_bUse = SetPicture(D3DXVECTOR3(SCREEN_WIDTH / 2, 0 - 250.0f, 0.0f), D3DXVECTOR3(0.0f, 2.0f, 0.0f), 500.0f, 500.0f, PICTURE_TYPE_GUYS_01);
		break;
	case 2:
		g_bUse = SetPicture(D3DXVECTOR3(SCREEN_WIDTH + 250.0f, SCREEN_HEIGHT / 2, 0.0f), D3DXVECTOR3(-2.0f, 0.0f, 0.0f), 500.0f, 500.0f, PICTURE_TYPE_GUYS_02);
		break;
	case 3:
		g_bUse = SetPicture(D3DXVECTOR3(0 - 250.0f, SCREEN_HEIGHT / 2, 0.0f), D3DXVECTOR3(2.0f, 0.0f, 0.0f), 500.0f, 500.0f, PICTURE_TYPE_GUYS_03);
		break;
	}
}

//---------------------------
//描画処理
//---------------------------
void DrawTitle(void)
{
	DrawPicture();
}