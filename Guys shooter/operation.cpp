//---------------------------
//インクルードファイル
//---------------------------
#include "operation.h"
#include "mouseinput.h"
#include "fade.h"
#include "camara.h"
#include "player.h"
#include "light.h"
#include "stage.h"
#include "shadow.h"
#include "bullet.h"
#include "Picture.h"
#include "guys.h"
#include "guninfo.h"
#include "round.h"
#include "effect.h"
#include "floo.h"
#include "worldsky.h"
#include "gunmodel.h"
#include "sound.h"

//---------------------------
//グローバル変数
//---------------------------

//---------------------------
//初期化処理
//---------------------------
HRESULT InitOperation(void)
{
	PlaySound(SOUND_OPERAT_BGM);
	InitLight();

	InitCamera();

	InitFloo();
	SetFloo(D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, -2000.0f, 0.0f), 200000.0f, 200000.0f, 0);

	InitSky();
	SetSky(D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, -100.0f, 350.0f), 1.0f, 1.0f, 0);

	InitStage();
	//38モデル
	//第一大陸
	SetStage(D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), STAGE_FLOO_00);
	SetStage(D3DXVECTOR3(100.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), STAGE_FLOO_00);
	SetStage(D3DXVECTOR3(-100.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), STAGE_FLOO_00);
	SetStage(D3DXVECTOR3(100.0f, 0.0f, 100.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), STAGE_FLOO_00);
	SetStage(D3DXVECTOR3(0.0f, 0.0f, 100.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), STAGE_FLOO_00);
	SetStage(D3DXVECTOR3(-100.0f, 0.0f, 100.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), STAGE_FLOO_00);
	SetStage(D3DXVECTOR3(100.0f, 0.0f, -100.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), STAGE_FLOO_00);
	SetStage(D3DXVECTOR3(0.0f, 0.0f, -100.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), STAGE_FLOO_00);
	SetStage(D3DXVECTOR3(-100.0f, 0.0f, -100.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), STAGE_FLOO_00);

	//反対フェンス
	SetStage(D3DXVECTOR3(0.0f, 0.0f, -150.0f), D3DXVECTOR3(0.0f, -D3DX_PI, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), STAGE_FENCE_00);
	SetStage(D3DXVECTOR3(100.0f, 0.0f, -150.0f), D3DXVECTOR3(0.0f, -D3DX_PI, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), STAGE_FENCE_00);
	SetStage(D3DXVECTOR3(-100.0f, 0.0f, -150.0f), D3DXVECTOR3(0.0f, -D3DX_PI, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), STAGE_FENCE_00);

	//左フェンス
	SetStage(D3DXVECTOR3(-150.0f, 0.0f, -100.0f), D3DXVECTOR3(0.0f, -D3DX_PI / 2, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), STAGE_FENCE_00);
	SetStage(D3DXVECTOR3(-150.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, -D3DX_PI / 2, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), STAGE_FENCE_00);
	SetStage(D3DXVECTOR3(-150.0f, 0.0f, 100.0f), D3DXVECTOR3(0.0f, -D3DX_PI / 2, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), STAGE_FENCE_00);

	//右フェンス
	SetStage(D3DXVECTOR3(150.0f, 0.0f, -100.0f), D3DXVECTOR3(0.0f, D3DX_PI / 2, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), STAGE_FENCE_00);
	SetStage(D3DXVECTOR3(150.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, D3DX_PI / 2, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), STAGE_FENCE_00);
	SetStage(D3DXVECTOR3(150.0f, 0.0f, 100.0f), D3DXVECTOR3(0.0f, D3DX_PI / 2, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), STAGE_FENCE_00);

	//第二大陸
	SetStage(D3DXVECTOR3(0.0f, 0.0f, 600.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), STAGE_FLOO_00);
	SetStage(D3DXVECTOR3(100.0f, 0.0f, 600.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), STAGE_FLOO_00);
	SetStage(D3DXVECTOR3(-100.0f, 0.0f, 600.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), STAGE_FLOO_00);
	SetStage(D3DXVECTOR3(100.0f, 0.0f, 700.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), STAGE_FLOO_00);
	SetStage(D3DXVECTOR3(0.0f, 0.0f, 700.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), STAGE_FLOO_00);
	SetStage(D3DXVECTOR3(-100.0f, 0.0f, 700.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), STAGE_FLOO_00);
	SetStage(D3DXVECTOR3(100.0f, 0.0f, 800.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), STAGE_FLOO_00);
	SetStage(D3DXVECTOR3(0.0f, 0.0f, 800.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), STAGE_FLOO_00);
	SetStage(D3DXVECTOR3(-100.0f, 0.0f, 800.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), STAGE_FLOO_00);

	//フェンス
	SetStage(D3DXVECTOR3(0.0f, 0.0f, 850.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), STAGE_FENCE_00);
	SetStage(D3DXVECTOR3(100.0f, 0.0f, 850.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), STAGE_FENCE_00);
	SetStage(D3DXVECTOR3(-100.0f, 0.0f, 850.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), STAGE_FENCE_00);

	//左フェンス
	SetStage(D3DXVECTOR3(-150.0f, 0.0f, 800.0f), D3DXVECTOR3(0.0f, -D3DX_PI / 2, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), STAGE_FENCE_00);
	SetStage(D3DXVECTOR3(-150.0f, 0.0f, 700.0f), D3DXVECTOR3(0.0f, -D3DX_PI / 2, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), STAGE_FENCE_00);
	SetStage(D3DXVECTOR3(-150.0f, 0.0f, 600.0f), D3DXVECTOR3(0.0f, -D3DX_PI / 2, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), STAGE_FENCE_00);

	//右フェンス
	SetStage(D3DXVECTOR3(150.0f, 0.0f, 800.0f), D3DXVECTOR3(0.0f, D3DX_PI / 2, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), STAGE_FENCE_00);
	SetStage(D3DXVECTOR3(150.0f, 0.0f, 700.0f), D3DXVECTOR3(0.0f, D3DX_PI / 2, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), STAGE_FENCE_00);
	SetStage(D3DXVECTOR3(150.0f, 0.0f, 600.0f), D3DXVECTOR3(0.0f, D3DX_PI / 2, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), STAGE_FENCE_00);

	//移動床
	SetStage(D3DXVECTOR3(65.0f, 0.0f, 210.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 1.0f), STAGE_MOVEFLOO_00);
	SetStage(D3DXVECTOR3(-65.0f, 0.0f, 210.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 1.0f), STAGE_MOVEFLOO_00);

	InitShadow();

	InitGunModel();

	InitGuys();
	SetGuys(D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), 1000, 0.0f);

	InitPlayer();
	SetPlayer(D3DXVECTOR3(0.0f, 100.0f, -200.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));

	InitBullet();

	InitEffect();

	InitGuninfo();

	InitRound();

	InitPicture();
	SetPicture(D3DXVECTOR3(SCREEN_WIDTH - (275 / 2), SCREEN_HEIGHT - (150 / 2), 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), 275.0f, 150.0f, PICTURE_TYPE_GUNLINE_00);;
	SetPicture(D3DXVECTOR3(0 + (60.0f / 2), SCREEN_HEIGHT - (60.0f / 2), 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), 60.0f, 60.0f, PICTURE_TYPE_ROUND);
	SetPicture(D3DXVECTOR3(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), 5.0f, 5.0f, PICTURE_TYPE_RETICLE_00);

	return S_OK;
}

//---------------------------
//終了処理
//---------------------------
void UninitOperation(void)
{
	UninitLight();
	UninitCamera();
	UninitFloo();
	UninitSky();
	UninitStage();
	UninitShadow();
	UninitGunModel();
	UninitGuys();
	UninitPlayer();
	UninitBullet();
	UninitEffect();
	UninitGuninfo();
	UninitRound();
	UninitPicture();
}

//---------------------------
//更新処理
//---------------------------
void UpdateOperation(void)
{
	if (MouseDowan(MOUSE_WHEEL_BOTTON) == true && GetFade() == FADE_NONE)
	{
		StopSound(SOUND_OPERAT_BGM);
		PlaySound(SOUND_PUSH_SE);
		SetFade(MODE_GAME);
	}

	UpdateLight();

	UpdateFloo();

	UpdateSky();

	UpdateStage();

	UpdateShadow();

	UpdateGunModel();

	UpdateGuys();

	UpdatePlayer();

	UpdateBullet();

	UpdateEffect();

	UpdateGuninfo();

	UpdateRound();

	UpdatePicture();
}

//---------------------------
//描画処理
//---------------------------
void DrawOperation(void)
{
	DrawFloo();
	DrawSky();
	DrawStage();
	DrawShadow();
	DrawGunModel();
	DrawGuys();
	DrawPlayer();
	DrawBullet();
	DrawEffect();
	DrawGuninfo();
	DrawRound();
	DrawPicture();
}