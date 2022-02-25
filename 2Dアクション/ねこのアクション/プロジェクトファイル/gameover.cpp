//---------------------------
//インクルードファイル
//---------------------------
#include "gameover.h"
#include "bg.h"
#include "score.h"
#include "fade.h"
#include "input.h"
#include "timer.h"
#include "life.h"
#include "sound.h"

//---------------------------
//グローバル変数
//---------------------------


//---------------------------
//初期化処理
//---------------------------
HRESULT InitGameover(void)
{
	PlaySound(SOUND_LABEL_BGM003);
	InitBg();
	SetBg(D3DXVECTOR3(0.0f, 0.0f, 0.0f), SCREEN_WIDTH, SCREEN_HEIGHT, 6);

	return S_OK;
}
//---------------------------
//終了処理
//---------------------------
void UninitGameover(void)
{
	UninitBg();

	UninitScore();

	UninitTimer();

	UninitLife();
}
//---------------------------
//更新処理
//---------------------------
void UpdateGameover(void)
{
	static int nCnt;	//自動繊維タイマー

	nCnt++;				//タイマー加算

	UpdateBg();

	//タイマーが700になるか && エンターキー押してたか
	if (nCnt >= 700 && GetFade() == FADE_NONE || GetKeyboardTrigger(DIK_RETURN) == true && GetFade() == FADE_NONE)
	{
		SetFade(MODE_TITLE);
		nCnt = 0;			//カウントしょきか
		StopSound(SOUND_LABEL_BGM003);
	}
}
//---------------------------
//描画処理
//---------------------------
void DrawGameover(void)
{
	DrawBg();
}