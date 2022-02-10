//---------------------------
//インクルードファイル
//---------------------------
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include "player.h"
#include "input.h"
#include "block.h"
#include "bullet.h"
#include "enemy.h"
#include "fade.h"
#include "life.h"
#include "bullet.h"
#include "sound.h"

//---------------------------
//グローバル変数
//---------------------------
LPDIRECT3DTEXTURE9		g_pTexturePlayer = NULL;	//テクスチャへのポインタ
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffPlayer = NULL;	//頂点バッファへのポインタ
PLAYER					g_player;					//プレイヤーの構造体
bool					g_bLand = true;				//着地

//---------------------------
//初期化処理
//---------------------------
HRESULT InitPlayer(void)
{
	LPDIRECT3DDEVICE9	pDevice;	//デバイスへのポインタ
	VERTEX_2D			*pVtx;		//頂点情報へのポインタ
	FILE			    *pFile;		//ファイル開く

	pDevice = GetDevice();			//デバイスの取得

	g_player.pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);		//プレイヤーの初期位置
	g_player.posold = D3DXVECTOR3(0.0f, 0.0f, 0.0f);	//プレイヤーの前回位置
	g_player.move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);		//プレイヤーの移動量
	g_player.fHeight = 0;								//プレイヤーの高さ
	g_player.fWidth = 0;								//プレイヤーの幅
	g_player.bUse = true;								//プレイヤーの状態
	g_player.bJamp = false;								//ジャンプ状態
	g_player.nLevel = 0;
#ifdef _DEBUG
	g_player.nLevel = 2;
#endif

	//テクスチャの読み込み
	D3DXCreateTextureFromFile(	pDevice,
								"data/Texture/cat.png",			//テクスチャ
								&g_pTexturePlayer);
	//頂点バッファの生成
	pDevice->CreateVertexBuffer(	sizeof(VERTEX_2D) * 4,
									D3DUSAGE_WRITEONLY,
									FVF_VERTEX_2D,
									D3DPOOL_MANAGED,
									&g_pVtxBuffPlayer,
									NULL);
	//頂点バッファをロックし、頂点データへのポインタを取得
	g_pVtxBuffPlayer->Lock(0, 0, (void**)&pVtx, 0);

	//頂点座標の設定
	pVtx[0].pos = D3DXVECTOR3(g_player.pos.x - g_player.fWidth / 2, g_player.pos.y - g_player.fHeight, g_player.pos.z);
	pVtx[1].pos = D3DXVECTOR3(g_player.pos.x + g_player.fWidth / 2, g_player.pos.y - g_player.fHeight, g_player.pos.z);
	pVtx[2].pos = D3DXVECTOR3(g_player.pos.x - g_player.fWidth / 2, g_player.pos.y, g_player.pos.z);
	pVtx[3].pos = D3DXVECTOR3(g_player.pos.x + g_player.fWidth / 2, g_player.pos.y, g_player.pos.z);

	pVtx[0].rhw = 1.0f;
	pVtx[1].rhw = 1.0f;
	pVtx[2].rhw = 1.0f;
	pVtx[3].rhw = 1.0f;

	pVtx[0].col = D3DCOLOR_RGBA(255, 255, 255, 255);
	pVtx[1].col = D3DCOLOR_RGBA(255, 255, 255, 255);
	pVtx[2].col = D3DCOLOR_RGBA(255, 255, 255, 255);
	pVtx[3].col = D3DCOLOR_RGBA(255, 255, 255, 255);

	pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	pVtx[1].tex = D3DXVECTOR2(0.5f, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	pVtx[3].tex = D3DXVECTOR2(0.5f, 1.0f);

	//頂点バッファをアンロックする
	g_pVtxBuffPlayer->Unlock();

	//ファイル開く
	pFile = fopen("stat.bin", "rb");
	//なんか入ってたら
	if (pFile != NULL)
	{
		//ランキング入手
		fscanf(pFile, "%d", &g_player.nLevel);
		//閉じる
		fclose(pFile);
	}
	else
	{
		printf("読み取れないわ");
	}

	return S_OK;
}

//---------------------------
//終了処理
//---------------------------
void UninitPlayer(void)
{
	//テクスチャの破棄
	if (g_pTexturePlayer != NULL)
	{
		g_pTexturePlayer->Release();
		g_pTexturePlayer = NULL;
	}

	//頂点バッファの破棄
	if (g_pVtxBuffPlayer != NULL)
	{
		g_pVtxBuffPlayer->Release();
		g_pVtxBuffPlayer = NULL;
	}
}

//---------------------------
//更新処理
//---------------------------
void UpdatePlayer(void)
{
	LPDIRECT3DDEVICE9	pDevice;	//デバイスへのポインタ
	VERTEX_2D			*pVtx;		//頂点情報へのポインタ
	static int			nSpan;		//弾の発射クールタイム
	static int			nTimer;		//無敵時間
	static int			nTimer2;	//無敵時間
	static int			nTimer3;	//無敵時間
	static int			nCol = 255;	//チカチカ

	pDevice = GetDevice();			//デバイスの取得

	g_player.posold = g_player.pos;	//前回の位置を保存
	nSpan++;						//カウント

	//もし一回ダメージ貰ってたら
	if (g_player.bUse == false)
	{
		nTimer++;	//無敵時間カウント
		nTimer3++;	//点滅タイミング

		//無敵時間終わり
		if (nTimer >= 500)
		{
			g_player.bUse = true;	//ダメ食らってない
			nTimer = 0;				//カウント戻す
		}
		//点滅タイミングになった
		if (nTimer3 == 30)
		{
			nTimer2 = nTimer3;	//タイミングを渡して
			nTimer3 = 0;		//0になる
		}
		//Aが255で && タイミングが来てたら
		if (nCol == 255 && nTimer2 == 30)
		{
			nCol = 0;		//透明
			nTimer2 = 0;	//タイミング初期化
		}
		//Aが0で && タイミングが来てる
		else if (nCol == 0 && nTimer2 == 30)
		{
			nCol = 255;		//見える
			nTimer2 = 0;	//タイミング初期化
		}
	}
	else if (g_player.bUse == true)
	{
		nCol = 255;
	}

	//←が押されたら || A
	if (GetKeyboardPress(DIK_LEFT) == true || GetKeyboardPress(DIK_A) == true)
	{
		g_player.move.x = -MOVE_SPEED;
		g_player.pos.x += g_player.move.x;
		if (g_player.bJamp == false)
		{
			//ジャンプ状態
			g_player.bJamp = true;
			//ジャンプ
			g_player.move.y = JAMP_MOVE_POW;
		}
	}
	//→が押されたら || D
	else if (GetKeyboardPress(DIK_RIGHT) == true || GetKeyboardPress(DIK_D) == true)
	{
		g_player.move.x = MOVE_SPEED;
		g_player.pos.x += g_player.move.x;
		if (g_player.bJamp == false)
		{
			//ジャンプ状態
			g_player.bJamp = true;
			//ジャンプ
			g_player.move.y = JAMP_MOVE_POW;
		}
	}
	//操作説明 || リザルト画面
	if (GetMode() == MODE_OPERATION || GetMode() == MODE_RESULT)
	{
		g_player.move.x = -MOVE_SPEED;
		g_player.pos.x += g_player.move.x;
		if (g_player.bJamp == false)
		{
			//ジャンプ状態
			g_player.bJamp = true;
			//ジャンプ
			g_player.move.y = JAMP_MOVE_POW;
		}
	}
	//頂点バッファをロックし、頂点データへのポインタを取得
	g_pVtxBuffPlayer->Lock(0, 0, (void**)&pVtx, 0);

	//右向いてる
	if (g_player.move.x >= 0.0f)
	{
		pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
		pVtx[1].tex = D3DXVECTOR2(0.45f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(0.0f, 0.5f);
		pVtx[3].tex = D3DXVECTOR2(0.45f, 0.5f);
	}
	//左向いてる
	else if (g_player.move.x <= 0.0f)
	{
		pVtx[0].tex = D3DXVECTOR2(0.0f, 0.5f);
		pVtx[1].tex = D3DXVECTOR2(0.45f, 0.5f);
		pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
		pVtx[3].tex = D3DXVECTOR2(0.45f, 1.0f);
	}
	//頂点バッファをロックし、頂点データへのポインタを取得
	g_pVtxBuffPlayer->Lock(0, 0, (void**)&pVtx, 0);

	//リザルトとホーム以外
	if (GetMode() != MODE_OPERATION && GetMode() != MODE_RESULT)
	{
		//スペースが押されたら && ジャンプ状態じゃない
		if (GetKeyboardPress(DIK_SPACE) == true && g_player.bJamp == false)
		{
			//ジャンプ状態
			g_player.bJamp = true;
			//ジャンプ
			g_player.move.y = JAMP_POW;
		}
		//Zが押されたら
		if (GetKeyboardPress(DIK_Z) == true && nSpan > BULLET_SPAN)
		{
			PlaySound(SOUND_LABEL_SE001);
			SetBullet(D3DXVECTOR3(g_player.pos.x, g_player.pos.y - g_player.fHeight / 2, 0.0f), D3DXVECTOR3(g_player.move.x * 2, 0.0f, 0.0f), BULLET_SIZE_X * 2, BULLET_SIZE_Y * 2, 0);
			nSpan = 0;
		}
		//Fが押されたら
		else if (GetKeyboardPress(DIK_F) == true && nSpan > BULLET_SPAN)
		{
			PlaySound(SOUND_LABEL_SE001);
			SetBullet(D3DXVECTOR3(g_player.pos.x, g_player.pos.y - g_player.fHeight / 2, 0.0f), D3DXVECTOR3(g_player.move.x * 2, 0.0f, 0.0f), BULLET_SIZE_X * 2, BULLET_SIZE_Y * 2, 0);
			nSpan = 0;
		}
	}

	//頂点バッファをロックし、頂点データへのポインタを取得
	g_pVtxBuffPlayer->Lock(0, 0, (void**)&pVtx, 0);

	//頂点座標の設定
	pVtx[0].pos = D3DXVECTOR3(g_player.pos.x - g_player.fWidth / 2, g_player.pos.y - g_player.fHeight, g_player.pos.z);
	pVtx[1].pos = D3DXVECTOR3(g_player.pos.x + g_player.fWidth / 2, g_player.pos.y - g_player.fHeight, g_player.pos.z);
	pVtx[2].pos = D3DXVECTOR3(g_player.pos.x - g_player.fWidth / 2, g_player.pos.y, g_player.pos.z);
	pVtx[3].pos = D3DXVECTOR3(g_player.pos.x + g_player.fWidth / 2, g_player.pos.y, g_player.pos.z);

	if (g_player.bUse == false)
	{
		pVtx[0].col = D3DCOLOR_RGBA(255, 255, 255, nCol);
		pVtx[1].col = D3DCOLOR_RGBA(255, 255, 255, nCol);
		pVtx[2].col = D3DCOLOR_RGBA(255, 255, 255, nCol);
		pVtx[3].col = D3DCOLOR_RGBA(255, 255, 255, nCol);
	}

	if (g_player.bUse == true)
	{
		pVtx[0].col = D3DCOLOR_RGBA(255, 255, 255, 255);
		pVtx[1].col = D3DCOLOR_RGBA(255, 255, 255, 255);
		pVtx[2].col = D3DCOLOR_RGBA(255, 255, 255, 255);
		pVtx[3].col = D3DCOLOR_RGBA(255, 255, 255, 255);
	}

	//頂点バッファをアンロックする
	g_pVtxBuffPlayer->Unlock();

	//毎フレーム重力を＋
	g_player.move.y += G_POW;
	//移動量を＋
	g_player.pos.y += g_player.move.y;
	
	//ブロックに着地していたら
	if (CollisionBlock(&g_player.pos, &g_player.posold, &g_player.move, g_player.fWidth, g_player.fHeight, 0) == true)
	{
		//右向いてる
		if (g_player.move.x >= 0.0f)
		{
			pVtx[0].tex = D3DXVECTOR2(0.452f, 0.0f);
			pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
			pVtx[2].tex = D3DXVECTOR2(0.452f, 0.5f);
			pVtx[3].tex = D3DXVECTOR2(1.0f, 0.5f);
		}
		//左向いてる
		else if (g_player.move.x <= 0.0f)
		{
			pVtx[0].tex = D3DXVECTOR2(0.452f, 0.5f);
			pVtx[1].tex = D3DXVECTOR2(1.0f, 0.5f);
			pVtx[2].tex = D3DXVECTOR2(0.452f, 1.0f);
			pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);
		}
		//ジャンプ状態じゃない
		g_player.bJamp = false;
	}
	//ブロックから落ちたら
	else if (CollisionBlock(&g_player.pos, &g_player.posold, &g_player.move, g_player.fWidth, g_player.fHeight, 0) == false)
	{
		//ジャンプ状態
		g_player.bJamp = true;
	}
	//ホームにいたら
	if (GetMode() == MODE_HOME)
	{
		//画面右端に出たら
		if (g_player.pos.x + g_player.fWidth / 2 >= SCREEN_WIDTH)
		{
			//左端にセット
			g_player.pos.x = 0 + g_player.fWidth / 2;
		}
		//画面左端に出たら
		else if (g_player.pos.x - g_player.fWidth / 2 <= 0)
		{
			//右端にセット
			g_player.pos.x = SCREEN_WIDTH - g_player.fWidth / 2;
		}
	}
	//イージーのステージ1だったら
	else if (GetMode() == MODE_ES_STAGE01)
	{
		//画面左端に出たら
		if (g_player.pos.x - g_player.fWidth / 2 <= 0)
		{
			//左端にセット
			g_player.pos.x = 0.0f + g_player.fWidth / 2;
		}
		//イージーのステージ1をクリアしたら
		else if (g_player.pos.x - g_player.fWidth / 2 >= SCREEN_WIDTH && GetFade() == FADE_NONE)
		{
			AddLife(1);
			SetFade(MODE_ES_STAGE02);
		}
		//下に落ちたら
		else if (g_player.pos.y - g_player.fHeight >= SCREEN_HEIGHT)
		{
			if (GetFade() != FADE_OUT)
			{
				AddLife(-1);
			}
			g_player.bUse = false;
			SetPlayer(D3DXVECTOR3(0.0f + g_player.fWidth / 2 * 1.1f, 250.0f, 0.0f), PLAYER_X_SIZE, PLAYER_Y_SIZE);
		}
	}
	//イージーのステージ2だったら
	else if (GetMode() == MODE_ES_STAGE02)
	{
		//画面左端に出たら
		if (g_player.pos.x - g_player.fWidth / 2 <= 0)
		{
			//左端にセット
			g_player.pos.x = 0.0f + g_player.fWidth / 2;
		}
		//下に落ちたら
		else if (g_player.pos.y - g_player.fHeight >= SCREEN_HEIGHT)
		{
			if (GetFade() != FADE_OUT)
			{
				AddLife(-1);
			}
			g_player.bUse = false;
			SetPlayer(D3DXVECTOR3(0.0f + g_player.fWidth / 2 * 1.1f, 290.0f, 0.0f), PLAYER_X_SIZE, PLAYER_Y_SIZE);
		}
		//イージーのステージ2をクリアしたら
		else if (g_player.pos.x - g_player.fWidth / 2 >= SCREEN_WIDTH && GetFade() == FADE_NONE)
		{
			AddLife(1);
			SetFade(MODE_ES_STAGE03);
		}
	}
	//イージーのステージ3だったら
	else if (GetMode() == MODE_ES_STAGE03)
	{
		//画面左端に出たら
		if (g_player.pos.x - g_player.fWidth / 2 <= 0)
		{
			//左端にセット
			g_player.pos.x = 0.0f + g_player.fWidth / 2;
		}
	}
	//ノーマルのステージ1だったら
	else if (GetMode() == MODE_NO_STAGE01)
	{
		//画面左端に出たら
		if (g_player.pos.x - g_player.fWidth / 2 <= 0)
		{
			//左端にセット
			g_player.pos.x = 0.0f + g_player.fWidth / 2;
		}
		//下に落ちたら
		else if (g_player.pos.y - g_player.fHeight >= SCREEN_HEIGHT)
		{
			if (GetFade() != FADE_OUT)
			{
				AddLife(-1);
			}
			g_player.bUse = false;
			SetPlayer(D3DXVECTOR3(0.0f + PLAYER_X_SIZE / 2 * 1.1f, SCREEN_HEIGHT - 300.0f, 0.0f), PLAYER_X_SIZE, PLAYER_Y_SIZE);
		}
		//イージーのステージ2をクリアしたら
		else if (g_player.pos.x - g_player.fWidth / 2 >= SCREEN_WIDTH && GetFade() == FADE_NONE)
		{
			AddLife(1);
			SetFade(MODE_NO_STAGE02);
		}
	}
	//ノーマルのステージ2だったら
	else if (GetMode() == MODE_NO_STAGE02)
	{
		//画面左端に出たら
		if (g_player.pos.x - g_player.fWidth / 2 <= 0)
		{
			//左端にセット
			g_player.pos.x = 0.0f + g_player.fWidth / 2;
		}
		//下に落ちたら
		else if (g_player.pos.y - g_player.fHeight >= SCREEN_HEIGHT)
		{
			if (GetFade() != FADE_OUT)
			{
				AddLife(-1);
			}
			g_player.bUse = false;
			SetPlayer(D3DXVECTOR3(0.0f + PLAYER_X_SIZE / 2 * 1.1f, 400.0f, 0.0f), PLAYER_X_SIZE, PLAYER_Y_SIZE);
		}
		//イージーのステージ2をクリアしたら
		else if (g_player.pos.x - g_player.fWidth / 2 >= SCREEN_WIDTH && GetFade() == FADE_NONE)
		{
			AddLife(1);
			SetFade(MODE_NO_STAGE03);
		}
	}
	//のーまるのステージ3
	else if (GetMode() == MODE_NO_STAGE03)
	{
		//画面左端に出たら
		if (g_player.pos.x - g_player.fWidth / 2 <= 0)
		{
			//左端にセット
			g_player.pos.x = 0.0f + g_player.fWidth / 2;
		}
		//下に落ちたら
		else if (g_player.pos.y - g_player.fHeight >= SCREEN_HEIGHT)
		{
			if (GetFade() != FADE_OUT)
			{
				AddLife(-1);
			}
			g_player.bUse = false;
			SetPlayer(D3DXVECTOR3(0.0f + PLAYER_X_SIZE / 2 * 1.1f, 650.0f, 0.0f), PLAYER_X_SIZE, PLAYER_Y_SIZE);
		}
		//のーまるのステージ3をクリアしたら
		else if (g_player.pos.x - g_player.fWidth / 2 >= SCREEN_WIDTH && GetFade() == FADE_NONE)
		{
			AddLife(1);
			SetFade(MODE_NO_STAGE04);
		}
	}
	//のーまるーのステージ4だったら
	else if (GetMode() == MODE_NO_STAGE04)
	{
		//画面左端に出たら
		if (g_player.pos.x - g_player.fWidth / 2 <= 0)
		{
			//左端にセット
			g_player.pos.x = 0.0f + g_player.fWidth / 2;
		}
	}
	//はーどのステージ3だったら
	else if (GetMode() == MODE_HD_STAGE01)
	{
		//画面左端に出たら
		if (g_player.pos.x - g_player.fWidth / 2 <= 0)
		{
			//左端にセット
			g_player.pos.x = 0.0f + g_player.fWidth / 2;
		}
		//下に落ちたら
		else if (g_player.pos.y - g_player.fHeight >= SCREEN_HEIGHT)
		{
			if (GetFade() != FADE_OUT)
			{
				AddLife(-1);
			}
			g_player.bUse = false;
			SetPlayer(D3DXVECTOR3(0.0f + PLAYER_X_SIZE / 2 * 1.1f, 250.0f, 0.0f), PLAYER_X_SIZE, PLAYER_Y_SIZE);
		}
		//のーまるのステージ3をクリアしたら
		else if (g_player.pos.x - g_player.fWidth / 2 >= SCREEN_WIDTH && GetFade() == FADE_NONE)
		{
			AddLife(1);
			SetFade(MODE_HD_STAGE02);
		}
	}
	//はーどのステージ3だったら
	else if (GetMode() == MODE_HD_STAGE02)
	{
		//画面左端に出たら
		if (g_player.pos.x - g_player.fWidth / 2 <= 0)
		{
			//左端にセット
			g_player.pos.x = 0.0f + g_player.fWidth / 2;
		}
		//下に落ちたら
		else if (g_player.pos.y - g_player.fHeight >= SCREEN_HEIGHT)
		{
			if (GetFade() != FADE_OUT)
			{
				AddLife(-1);
			}
			g_player.bUse = false;
			SetPlayer(D3DXVECTOR3(0.0f + PLAYER_X_SIZE / 2 * 1.1f, 670.0f, 0.0f), PLAYER_X_SIZE, PLAYER_Y_SIZE);
		}
		//のーまるのステージ3をクリアしたら
		else if (g_player.pos.x - g_player.fWidth / 2 >= SCREEN_WIDTH && GetFade() == FADE_NONE)
		{
			AddLife(1);
			SetFade(MODE_HD_STAGE03);
		}
	}
	//はーどのステージ3だったら
	else if (GetMode() == MODE_HD_STAGE03)
	{
		//画面左端に出たら
		if (g_player.pos.x - g_player.fWidth / 2 <= 0)
		{
			//左端にセット
			g_player.pos.x = 0.0f + g_player.fWidth / 2;
		}
		//下に落ちたら
		else if (g_player.pos.y - g_player.fHeight >= SCREEN_HEIGHT)
		{
			if (GetFade() != FADE_OUT)
			{
				AddLife(-1);
				SetPlayer(D3DXVECTOR3(0.0f + PLAYER_X_SIZE / 2 * 1.1f, 650.0f, 0.0f), PLAYER_X_SIZE, PLAYER_Y_SIZE);
			}
			g_player.bUse = false;
			
		}
		//のーまるのステージ3をクリアしたら
		else if (g_player.pos.x - g_player.fWidth / 2 >= SCREEN_WIDTH && GetFade() == FADE_NONE)
		{
			AddLife(1);
			SetFade(MODE_HD_STAGE04);
		}
	}
	//はーどのステージ3だったら
	else if (GetMode() == MODE_HD_STAGE04)
	{
		//画面左端に出たら
		if (g_player.pos.x - g_player.fWidth / 2 <= 0)
		{
			//左端にセット
			g_player.pos.x = 0.0f + g_player.fWidth / 2;
		}
	}
	//はーどのステージ3だったら
	else if (GetMode() == MODE_HD_STAGE05)
	{
		//画面左端に出たら
		if (g_player.pos.x - g_player.fWidth / 2 <= 0)
		{
			//左端にセット
			g_player.pos.x = 0.0f + g_player.fWidth / 2;
		}
		//下に落ちたら
		else if (g_player.pos.y - g_player.fHeight >= SCREEN_HEIGHT)
		{
			if (GetFade() != FADE_OUT)
			{
				SetPlayer(D3DXVECTOR3(0.0f + PLAYER_X_SIZE / 2 * 1.2f, SCREEN_HEIGHT - 11.0f, 0.0f), PLAYER_X_SIZE, PLAYER_Y_SIZE);
			}
		}
	}
	//操作説明がめん || リザルト画面
	if (GetMode() == MODE_OPERATION || GetMode() == MODE_RESULT)
	{
		//下に落ちたら
		if (g_player.pos.y - g_player.fHeight >= SCREEN_HEIGHT)
		{
			SetPlayer(D3DXVECTOR3(SCREEN_WIDTH - (300.0f + PLAYER_X_SIZE), SCREEN_HEIGHT, 0.0f), PLAYER_X_SIZE, PLAYER_Y_SIZE);
		}
	}
}

//---------------------------
//描画処理
//---------------------------
void DrawPlayer(void)
{
	LPDIRECT3DDEVICE9 pDevice;	//デバイスのポインタ
	pDevice = GetDevice();		//デバイスを取得する

	//頂点バッファをデバイスのデータストリームに設定
	pDevice->SetStreamSource(	0,
								g_pVtxBuffPlayer,
								0,
								sizeof(VERTEX_2D));
	pDevice->SetFVF(FVF_VERTEX_2D);	//頂点フォーマットの設定

	pDevice->SetTexture(0, g_pTexturePlayer);		//テクスチャの設定
	//ポリゴンの描画
	pDevice->DrawPrimitive(	D3DPT_TRIANGLESTRIP,	//プリミティブの種類
							0,
							2);
}

//---------------------------
//プレイヤーのセット
//---------------------------
void SetPlayer(D3DXVECTOR3 pos, float fWidth, float fHeight)
{
	VERTEX_2D *pVtx; //頂点情報へのポインタ

	//頂点バッファをロックし、頂点データへのポインタを取得
	g_pVtxBuffPlayer->Lock(0, 0, (void**)&pVtx, 0);

	g_player.pos = pos;				//持ってきた位置を代入
	g_player.fWidth = fWidth;		//持ってきた幅を代入
	g_player.fHeight = fHeight;		//持ってきた高さを代入

	//頂点座標の設定
	pVtx[0].pos = D3DXVECTOR3(g_player.pos.x - g_player.fWidth / 2, g_player.pos.y - g_player.fHeight, g_player.pos.z);
	pVtx[1].pos = D3DXVECTOR3(g_player.pos.x + g_player.fWidth / 2, g_player.pos.y - g_player.fHeight, g_player.pos.z);
	pVtx[2].pos = D3DXVECTOR3(g_player.pos.x - g_player.fWidth / 2, g_player.pos.y, g_player.pos.z);
	pVtx[3].pos = D3DXVECTOR3(g_player.pos.x + g_player.fWidth / 2, g_player.pos.y, g_player.pos.z);

	pVtx[0].rhw = 1.0f;
	pVtx[1].rhw = 1.0f;
	pVtx[2].rhw = 1.0f;
	pVtx[3].rhw = 1.0f;

	pVtx[0].col = D3DCOLOR_RGBA(255, 255, 255, 255);
	pVtx[1].col = D3DCOLOR_RGBA(255, 255, 255, 255);
	pVtx[2].col = D3DCOLOR_RGBA(255, 255, 255, 255);
	pVtx[3].col = D3DCOLOR_RGBA(255, 255, 255, 255);

	pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	pVtx[1].tex = D3DXVECTOR2(0.45f, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	pVtx[3].tex = D3DXVECTOR2(0.45f, 1.0f);

	//頂点バッファをアンロックする
	g_pVtxBuffPlayer->Unlock();
}

//---------------------------
//プレイヤー情報の取得
//---------------------------
PLAYER *GetPlayer(void)
{
	return &g_player;
}