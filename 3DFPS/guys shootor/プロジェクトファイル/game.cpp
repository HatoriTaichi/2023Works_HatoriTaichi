//---------------------------
//インクルードファイル
//---------------------------
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "game.h"
#include "keyinput.h"
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
bool g_EnemySpan;
int g_nRound;
int g_nDeth;
int g_nLife;
float g_fSpeed;
D3DXVECTOR3 g_pos[MAX_GUYS];

//---------------------------
//初期化処理
//---------------------------
HRESULT InitGame(void)
{
	PlaySound(SOUND_GAME_BGM);
	srand((unsigned int)time(NULL));

	g_EnemySpan = true;
	g_nRound = 0;
	g_nDeth = 0;
	g_nLife = 0;
	g_fSpeed = 0;

	for (int nCnt = 0; nCnt < 10; nCnt++)
	{
		g_pos[nCnt] = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	}

	InitLight();

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

	InitPlayer();
	SetPlayer(D3DXVECTOR3(0.0f, 0.0f, -100.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));

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
void UninitGame(void)
{
	UninitLight();
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
void UpdateGame(void)
{
	static int nCntPporn;
	nCntPporn++;
#ifdef _DEBUG
	if (GetKeyboardTrigger(DIK_RETURN) == true && GetFade() == FADE_NONE)
	{
		SetFade(MODE_RESULT);
	}
#endif // _DEBUG

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

	g_nDeth = GetDeth();

	if (nCntPporn > (144 * 3))
	{
		if (g_nRound <= 5 && g_EnemySpan == true)
		{
			for (int nSet = 0; nSet < 10; nSet++)
			{
				g_pos[nSet].y = float(rand() % 2);
				g_nLife = rand() % 3 + 1;
				g_fSpeed = float(rand() % 2 + 2) / 10;

				if (g_pos[nSet].y == 0)
				{
					g_pos[nSet].x = -140;
				}
				else if (g_pos[nSet].y == 1)
				{
					g_pos[nSet].x = 140;
				}

				if (g_pos[nSet].y == 0)
				{
					g_pos[nSet].z = float(rand() % 140) - float(rand() % 140);
				}
				else if (g_pos[nSet].y == 1)
				{
					g_pos[nSet].z = float(rand() % 841 + 550);
				}
				SetGuys(g_pos[nSet], D3DXVECTOR3(0.0f, 0.0f, 0.0f), g_nLife, g_fSpeed);
			}
			g_EnemySpan = false;
		}
		else if (g_nRound > 5 && g_nRound <= 10 && g_EnemySpan == true)
		{
			for (int nSet = 0; nSet < 20; nSet++)
			{
				g_pos[nSet].y = float(rand() % 2);
				g_nLife = rand() % 5 + 1;
				g_fSpeed = float(rand() % 4 + 3) / 10;

				if (g_pos[nSet].y == 0)
				{
					g_pos[nSet].x = -140;
				}
				else if (g_pos[nSet].y == 1)
				{
					g_pos[nSet].x = 140;
				}

				if (g_pos[nSet].y == 0)
				{
					g_pos[nSet].z = float(rand() % 140) - float(rand() % 140);
				}
				else if (g_pos[nSet].y == 1)
				{
					g_pos[nSet].z = float(rand() % 841 + 550);
				}
				SetGuys(g_pos[nSet], D3DXVECTOR3(0.0f, 0.0f, 0.0f), g_nLife, g_fSpeed);
			}
			g_EnemySpan = false;
		}
		nCntPporn = 0;
	}

	if (g_nRound <= 5 && g_nDeth >= 10)
	{
		AddRound(1);
		g_nRound++;
		ResetsDeth();
		g_EnemySpan = true;
	}
	else if (g_nRound > 5 && g_nRound <= 10 && g_nDeth >= 20)
	{
		AddRound(1);
		g_nRound++;
		ResetsDeth();
		g_EnemySpan = true;
	}
}

//---------------------------
//描画処理
//---------------------------
void DrawGame(void)
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