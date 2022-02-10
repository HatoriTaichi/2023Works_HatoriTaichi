//---------------------------
//インクルードファイル
//---------------------------
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include "bullet.h"
#include "block.h"
#include "enemy.h"
#include "player.h"
#include "score.h"
#include "life.h"
#include "fade.h"
#include "sound.h"

//---------------------------
//グローバル変数
//---------------------------
LPDIRECT3DTEXTURE9		g_pTextureBullet[MAX_TEX] = {};		//テクスチャへのポインタ
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffBullet = NULL;			//頂点バッファへのポインタ
BULLET					g_Bullet[MAX_BULLET];				//玉の構造体
int						g_nLevel;							//レベル解放の管理

//---------------------------
//初期化処理
//---------------------------
HRESULT InitBullet(void)
{
	FILE				*pFile;		//ファイル開く
	LPDIRECT3DDEVICE9	pDevice;	//デバイスへのポインタ
	VERTEX_2D			*pVtx;		//頂点情報へのポインタ

	pDevice = GetDevice();		//デバイスの取得
	//弾の初期化
	for (int nCntBullet = 0; nCntBullet < MAX_BULLET; nCntBullet++)
	{
		g_Bullet[nCntBullet].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);		//位置
		g_Bullet[nCntBullet].move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);		//移動
		g_Bullet[nCntBullet].posold = D3DXVECTOR3(0.0f, 0.0f, 0.0f);	//前回の位置
		g_Bullet[nCntBullet].fHeight = 0.0f;							//高さ
		g_Bullet[nCntBullet].fWidth = 0.0f;								//幅
		g_Bullet[nCntBullet].bUse = false;								//使ってるかどうか
		g_Bullet[nCntBullet].bRft = true;								//反射したか
	}

	//テクスチャの読み込み
	D3DXCreateTextureFromFile(	pDevice,
								"data/Texture/bullet00.png",
								&g_pTextureBullet[0]);
	//テクスチャの読み込み
	D3DXCreateTextureFromFile(	pDevice,
								"data/Texture/bullet01.png",
								&g_pTextureBullet[1]);
	//テクスチャの読み込み
	D3DXCreateTextureFromFile(	pDevice,
								"data/Texture/bullet02.png",
								&g_pTextureBullet[2]);
	//テクスチャの読み込み
	D3DXCreateTextureFromFile(	pDevice,
								"data/Texture/bullet03.png",
								&g_pTextureBullet[3]);
	//頂点バッファの生成
	pDevice->CreateVertexBuffer(	sizeof(VERTEX_2D) * 4 * MAX_BULLET,
									D3DUSAGE_WRITEONLY,
									FVF_VERTEX_2D,
									D3DPOOL_MANAGED,
									&g_pVtxBuffBullet,
									NULL);
	//頂点バッファをロックし、頂点データへのポインタを取得
	g_pVtxBuffBullet->Lock(0, 0, (void**)&pVtx, 0);

	for (int nCntBullet = 0; nCntBullet < MAX_BULLET; nCntBullet++)
	{
		//頂点座標
		pVtx[0].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		pVtx[1].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		pVtx[2].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		pVtx[3].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

		pVtx[0].rhw = 1.0f;
		pVtx[1].rhw = 1.0f;
		pVtx[2].rhw = 1.0f;
		pVtx[3].rhw = 1.0f;

		pVtx[0].col = D3DCOLOR_RGBA(255, 255, 255, 255);
		pVtx[1].col = D3DCOLOR_RGBA(255, 255, 255, 255);
		pVtx[2].col = D3DCOLOR_RGBA(255, 255, 255, 255);
		pVtx[3].col = D3DCOLOR_RGBA(255, 255, 255, 255);

		pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
		pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
		pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

		pVtx += 4;
	}
	//頂点バッファをアンロックする
	g_pVtxBuffBullet->Unlock();

	//ファイル開く
	pFile = fopen("stat.bin", "rb");
	//なんか入ってたら
	if (pFile != NULL)
	{
		//ランキング入手
		fscanf(pFile, "%d", &g_nLevel);
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
void UninitBullet(void)
{
	for (int nCntBullet = 0; nCntBullet < MAX_TEX; nCntBullet++)
	{
		//テクスチャの破棄
		if (g_pTextureBullet[nCntBullet] != NULL)
		{
			g_pTextureBullet[nCntBullet]->Release();
			g_pTextureBullet[nCntBullet] = NULL;
		}
	}

	//頂点バッファの破棄
	if (g_pVtxBuffBullet != NULL)
	{
		g_pVtxBuffBullet->Release();
		g_pVtxBuffBullet = NULL;
	}
}

//---------------------------
//更新処理
//---------------------------
void UpdateBullet(void)
{
	VERTEX_2D	*pVtx;		//頂点情報へのポインタ
	FILE		*pFile;		//ファイル開く
	ENEMY		*pEnemy;	//弾のポインタ
	PLAYER		*pPlayer;	//プレイヤーのポインタ

	pEnemy = GetEnemy();	//敵の情報を取得
	pPlayer = GetPlayer();	//プレイヤーの情報を取得

	for (int nCntBullet = 0; nCntBullet < MAX_BULLET; nCntBullet++)
	{
		//前回の位置を保存
		g_Bullet[nCntBullet].posold = g_Bullet[nCntBullet].pos;
	}
	//頂点バッファをロックし、頂点データへのポインタを取得
	g_pVtxBuffBullet->Lock(0, 0, (void**)&pVtx, 0);

	for (int nCntBullet = 0; nCntBullet < MAX_BULLET; nCntBullet++)
	{
		//弾を使ってたら
		if (g_Bullet[nCntBullet].bUse == true)
		{
			//自分の弾
			if (g_Bullet[nCntBullet].nType == 0)
			{
				//敵を数える
				for (int nCntEnemy = 0; nCntEnemy < MAX_ENEMY; nCntEnemy++, pEnemy++)
				{
					//敵を使ってたら
					if (pEnemy->bUse == true)
					{
						//敵に当たったら
						if (g_Bullet[nCntBullet].pos.x + g_Bullet[nCntBullet].fWidth / 2 >= pEnemy->pos.x - pEnemy->fWidth / 2 &&
							g_Bullet[nCntBullet].pos.x - g_Bullet[nCntBullet].fWidth / 2 <= pEnemy->pos.x + pEnemy->fWidth / 2 &&
							g_Bullet[nCntBullet].pos.y >= pEnemy->pos.y - pEnemy->fHeight &&
							g_Bullet[nCntBullet].pos.y - g_Bullet[nCntBullet].fHeight <= pEnemy->pos.y &&
							GetMode() != MODE_HOME)
						{
							PlaySound(SOUND_LABEL_SE002);
							AddScore(50);
							//敵のタイプが2
							if (pEnemy->nType == 2)
							{
								pEnemy->bDamage = false;
								AddScore(100);
								//使ってない
								g_Bullet[nCntBullet].bUse = false;	
								//敵の体力を引く
								pEnemy->nLife--;
								//体力が0になったら
								if (pEnemy->nLife <= 0)
								{
									//ESボス
									if (GetMode() == MODE_ES_STAGE03)
									{
										if (g_nLevel == 0)
										{
											g_nLevel = 1;
										}
										if (g_nLevel < 2)
										{
											//ファイル開く
											pFile = fopen("stat.bin", "wb");
											//なんか入ってたら
											if (pFile != NULL)
											{
												//ランキング保存
												fprintf(pFile, "%d", 1);
												//閉じる
												fclose(pFile);
											}
											else
											{
												printf("読み取れないわ");
											}
										}
										AddScore(200);						//スコア加算
									}
									else if (GetMode() == MODE_NO_STAGE04)
									{
										if (g_nLevel < 2)
										{
											g_nLevel = 2;
										}
										//ファイル開く
										pFile = fopen("stat.bin", "wb");
										//なんか入ってたら
										if (pFile != NULL)
										{
											//ランキング保存
											fprintf(pFile, "%d", 2);
											//閉じる
											fclose(pFile);
										}
										else
										{
											printf("読み取れないわ");
										}
										AddScore(400);						//スコア加算
									}
									else if (GetMode() == MODE_HD_STAGE04)
									{
										AddScore(500);						//スコア加算
									}
									else if (GetMode() == MODE_HD_STAGE05)
									{
										AddScore(700);						//スコア加算
									}
									g_Bullet[nCntBullet].bUse = false;	//使ってない
									pEnemy->bUse = false;				//使ってない
									if (GetFade() == FADE_NONE && GetMode() != MODE_HD_STAGE04)
									{
										SetFade(MODE_RESULT);
									}
									else if (GetFade() == FADE_NONE && GetMode() == MODE_HD_STAGE04)
									{
										SetFade(MODE_HD_STAGE05);
									}
								}
							}
							//敵のタイプが2以外
							else if (pEnemy->nType != 2)
							{
								g_Bullet[nCntBullet].bUse = false;	//使ってない
								pEnemy->bUse = false;				//使ってない
							}
						}
					}
				}
				//数えた分を引く
				pEnemy -= MAX_ENEMY;
				//頂点バッファをロックし、頂点データへのポインタを取得
				pVtx[0].pos = D3DXVECTOR3(g_Bullet[nCntBullet].pos.x - g_Bullet[nCntBullet].fWidth / 2, g_Bullet[nCntBullet].pos.y, g_Bullet[nCntBullet].pos.z);
				pVtx[1].pos = D3DXVECTOR3(g_Bullet[nCntBullet].pos.x + g_Bullet[nCntBullet].fWidth / 2, g_Bullet[nCntBullet].pos.y, g_Bullet[nCntBullet].pos.z);
				pVtx[2].pos = D3DXVECTOR3(g_Bullet[nCntBullet].pos.x - g_Bullet[nCntBullet].fWidth / 2, g_Bullet[nCntBullet].pos.y - g_Bullet[nCntBullet].fHeight, g_Bullet[nCntBullet].pos.z);
				pVtx[3].pos = D3DXVECTOR3(g_Bullet[nCntBullet].pos.x + g_Bullet[nCntBullet].fWidth / 2, g_Bullet[nCntBullet].pos.y - g_Bullet[nCntBullet].fHeight, g_Bullet[nCntBullet].pos.z);

				//移動量+
				g_Bullet[nCntBullet].pos.x += g_Bullet[nCntBullet].move.x;

				//画面外に出たら
				if (g_Bullet[nCntBullet].pos.x - BULLET_SIZE_X >= SCREEN_WIDTH)
				{
					g_Bullet[nCntBullet].bUse = false;
				}
				//壁にぶつかった
				else if (CollisionBlock(&g_Bullet[nCntBullet].pos, &g_Bullet[nCntBullet].posold, &g_Bullet[nCntBullet].move, g_Bullet[nCntBullet].fWidth, g_Bullet[nCntBullet].fHeight, 3) == true)
				{
					g_Bullet[nCntBullet].bUse = false;
				}
			}
			//敵の弾
			if (g_Bullet[nCntBullet].nType == 1)
			{
				//プレイヤーに当たったら
				if (g_Bullet[nCntBullet].pos.x + g_Bullet[nCntBullet].fWidth / 2 >= pPlayer->pos.x - pPlayer->fWidth / 2 &&
					g_Bullet[nCntBullet].pos.x - g_Bullet[nCntBullet].fWidth / 2 <= pPlayer->pos.x + pPlayer->fWidth / 2 &&
					g_Bullet[nCntBullet].pos.y >= pPlayer->pos.y - pPlayer->fHeight &&
					g_Bullet[nCntBullet].pos.y - g_Bullet[nCntBullet].fHeight <= pPlayer->pos.y &&
					pPlayer->bUse == true)
				{
					PlaySound(SOUND_LABEL_SE002);
					pPlayer->bUse = false;
					AddLife(-1);
					g_Bullet[nCntBullet].bUse = false;	//使ってない
					if (GetMode() == MODE_ES_STAGE03)
					{
						SetPlayer(D3DXVECTOR3(0.0f + PLAYER_X_SIZE / 2 * 1.1f, SCREEN_HEIGHT - 10.0f, 0.0f), PLAYER_X_SIZE, PLAYER_Y_SIZE);
					}
					else if (GetMode() == MODE_HD_STAGE05)
					{
						SetPlayer(D3DXVECTOR3(0.0f + PLAYER_X_SIZE / 2 * 1.2f, SCREEN_HEIGHT - 11.0f, 0.0f), PLAYER_X_SIZE, PLAYER_Y_SIZE);
					}
				}
				//頂点バッファをロックし、頂点データへのポインタを取得
				pVtx[0].pos = D3DXVECTOR3(g_Bullet[nCntBullet].pos.x - g_Bullet[nCntBullet].fWidth / 2, g_Bullet[nCntBullet].pos.y, g_Bullet[nCntBullet].pos.z);
				pVtx[1].pos = D3DXVECTOR3(g_Bullet[nCntBullet].pos.x + g_Bullet[nCntBullet].fWidth / 2, g_Bullet[nCntBullet].pos.y, g_Bullet[nCntBullet].pos.z);
				pVtx[2].pos = D3DXVECTOR3(g_Bullet[nCntBullet].pos.x - g_Bullet[nCntBullet].fWidth / 2, g_Bullet[nCntBullet].pos.y - g_Bullet[nCntBullet].fHeight, g_Bullet[nCntBullet].pos.z);
				pVtx[3].pos = D3DXVECTOR3(g_Bullet[nCntBullet].pos.x + g_Bullet[nCntBullet].fWidth / 2, g_Bullet[nCntBullet].pos.y - g_Bullet[nCntBullet].fHeight, g_Bullet[nCntBullet].pos.z);

				//移動量+
				g_Bullet[nCntBullet].pos += g_Bullet[nCntBullet].move;

				//画面外に出たら
				if (g_Bullet[nCntBullet].pos.x - BULLET_SIZE_X >= SCREEN_WIDTH)
				{
					g_Bullet[nCntBullet].bUse = false;
				}
				//壁にぶつかった
				else if (CollisionBlock(&g_Bullet[nCntBullet].pos, &g_Bullet[nCntBullet].posold, &g_Bullet[nCntBullet].move, g_Bullet[nCntBullet].fWidth, g_Bullet[nCntBullet].fHeight, 3) == true)
				{
					g_Bullet[nCntBullet].bUse = false;
				}
			}
			//敵の弾
			if (g_Bullet[nCntBullet].nType == 2)
			{
				//弾とプレイヤーの差分を入手
				g_Bullet[nCntBullet].posdfrc = pPlayer->posold - g_Bullet[nCntBullet].pos;

				//プレイヤーに当たったら
				if (g_Bullet[nCntBullet].pos.x + g_Bullet[nCntBullet].fWidth / 2 >= pPlayer->pos.x - pPlayer->fWidth / 2 &&
					g_Bullet[nCntBullet].pos.x - g_Bullet[nCntBullet].fWidth / 2 <= pPlayer->pos.x + pPlayer->fWidth / 2 &&
					g_Bullet[nCntBullet].pos.y >= pPlayer->pos.y - pPlayer->fHeight &&
					g_Bullet[nCntBullet].pos.y - g_Bullet[nCntBullet].fHeight <= pPlayer->pos.y &&
					pPlayer->bUse == true)
				{
					PlaySound(SOUND_LABEL_SE002);
					pPlayer->bUse = false;
					AddLife(-1);
					g_Bullet[nCntBullet].bUse = false;	//使ってない
					if (GetMode() == MODE_ES_STAGE03)
					{
						SetPlayer(D3DXVECTOR3(0.0f + PLAYER_X_SIZE / 2 * 1.1f, SCREEN_HEIGHT - 10.0f, 0.0f), PLAYER_X_SIZE, PLAYER_Y_SIZE);
					}
					else if (GetMode() == MODE_NO_STAGE04)
					{
						SetPlayer(D3DXVECTOR3(0.0f + PLAYER_X_SIZE / 2 * 1.1f, SCREEN_HEIGHT - 10.0f, 0.0f), PLAYER_X_SIZE, PLAYER_Y_SIZE);
					}
					else if (GetMode() == MODE_HD_STAGE01)
					{
						SetPlayer(D3DXVECTOR3(0.0f + PLAYER_X_SIZE / 2 * 1.1f, 250.0f, 0.0f), PLAYER_X_SIZE, PLAYER_Y_SIZE);
					}
					else if (GetMode() == MODE_HD_STAGE04)
					{
						SetPlayer(D3DXVECTOR3(0.0f + PLAYER_X_SIZE / 2 * 1.2f, SCREEN_HEIGHT - 11.0f, 0.0f), PLAYER_X_SIZE, PLAYER_Y_SIZE);
					}
					else if (GetMode() == MODE_HD_STAGE05)
					{
						SetPlayer(D3DXVECTOR3(0.0f + PLAYER_X_SIZE / 2 * 1.2f, SCREEN_HEIGHT - 11.0f, 0.0f), PLAYER_X_SIZE, PLAYER_Y_SIZE);
					}
				}
				//頂点バッファをロックし、頂点データへのポインタを取得
				pVtx[0].pos = D3DXVECTOR3(g_Bullet[nCntBullet].pos.x - g_Bullet[nCntBullet].fWidth / 2, g_Bullet[nCntBullet].pos.y, g_Bullet[nCntBullet].pos.z);
				pVtx[1].pos = D3DXVECTOR3(g_Bullet[nCntBullet].pos.x + g_Bullet[nCntBullet].fWidth / 2, g_Bullet[nCntBullet].pos.y, g_Bullet[nCntBullet].pos.z);
				pVtx[2].pos = D3DXVECTOR3(g_Bullet[nCntBullet].pos.x - g_Bullet[nCntBullet].fWidth / 2, g_Bullet[nCntBullet].pos.y - g_Bullet[nCntBullet].fHeight, g_Bullet[nCntBullet].pos.z);
				pVtx[3].pos = D3DXVECTOR3(g_Bullet[nCntBullet].pos.x + g_Bullet[nCntBullet].fWidth / 2, g_Bullet[nCntBullet].pos.y - g_Bullet[nCntBullet].fHeight, g_Bullet[nCntBullet].pos.z);

				if (GetMode() == MODE_NO_STAGE04)
				{
					if (g_Bullet[nCntBullet].posdfrc.x >= 0.0f)
					{
						g_Bullet[nCntBullet].move.x = 1.0f;
					}
					else if (g_Bullet[nCntBullet].posdfrc.x <= 0.0f)
					{
						g_Bullet[nCntBullet].move.x = -1.0f;
					}
					if (g_Bullet[nCntBullet].posdfrc.y >= 0.0f)
					{
						g_Bullet[nCntBullet].move.y = 1.0f;
					}
					else if (g_Bullet[nCntBullet].posdfrc.y <= 0.0f)
					{
						g_Bullet[nCntBullet].move.y = -1.0f;
					}
				}
				else if (GetMode() == MODE_HD_STAGE01)
				{
					if (g_Bullet[nCntBullet].posdfrc.x >= 0.0f)
					{
						g_Bullet[nCntBullet].move.x = 2.0f;
					}
					else if (g_Bullet[nCntBullet].posdfrc.x <= 0.0f)
					{
						g_Bullet[nCntBullet].move.x = -2.0f;
					}
					if (g_Bullet[nCntBullet].posdfrc.y >= 0.0f)
					{
						g_Bullet[nCntBullet].move.y = 2.0f;
					}
					else if (g_Bullet[nCntBullet].posdfrc.y <= 0.0f)
					{
						g_Bullet[nCntBullet].move.y = -2.0f;
					}
				}
				else if (GetMode() == MODE_HD_STAGE04)
				{
					if (g_Bullet[nCntBullet].posdfrc.x >= 0.0f)
					{
						g_Bullet[nCntBullet].move.x = 1.0f;
					}
					else if (g_Bullet[nCntBullet].posdfrc.x <= 0.0f)
					{
						g_Bullet[nCntBullet].move.x = -1.0f;
					}
					if (g_Bullet[nCntBullet].posdfrc.y >= 0.0f)
					{
						g_Bullet[nCntBullet].move.y = 1.0f;
					}
					else if (g_Bullet[nCntBullet].posdfrc.y <= 0.0f)
					{
						g_Bullet[nCntBullet].move.y = -1.0f;
					}
				}
				else if (GetMode() == MODE_HD_STAGE05)
				{
					if (g_Bullet[nCntBullet].posdfrc.x >= 0.0f)
					{
						g_Bullet[nCntBullet].move.x = 1.2f;
					}
					else if (g_Bullet[nCntBullet].posdfrc.x <= 0.0f)
					{
						g_Bullet[nCntBullet].move.x = -1.2f;
					}
					if (g_Bullet[nCntBullet].posdfrc.y >= 0.0f)
					{
						g_Bullet[nCntBullet].move.y = 1.2f;
					}
					else if (g_Bullet[nCntBullet].posdfrc.y <= 0.0f)
					{
						g_Bullet[nCntBullet].move.y = -1.2f;
					}
				}
				//移動量+
				g_Bullet[nCntBullet].pos += g_Bullet[nCntBullet].move;

				//画面外に出たら
				if (g_Bullet[nCntBullet].pos.x - BULLET_SIZE_X >= SCREEN_WIDTH)
				{
					g_Bullet[nCntBullet].bUse = false;
				}
				//壁にぶつかった
				else if (CollisionBlock(&g_Bullet[nCntBullet].pos, &g_Bullet[nCntBullet].posold, &g_Bullet[nCntBullet].move, g_Bullet[nCntBullet].fWidth, g_Bullet[nCntBullet].fHeight, 3) == true)
				{
					g_Bullet[nCntBullet].bUse = false;
				}
			}
			//敵の弾
			if (g_Bullet[nCntBullet].nType == 3)
			{
				//プレイヤーに当たったら
				if (g_Bullet[nCntBullet].pos.x + g_Bullet[nCntBullet].fWidth / 2 >= pPlayer->pos.x - pPlayer->fWidth / 2 &&
					g_Bullet[nCntBullet].pos.x - g_Bullet[nCntBullet].fWidth / 2 <= pPlayer->pos.x + pPlayer->fWidth / 2 &&
					g_Bullet[nCntBullet].pos.y >= pPlayer->pos.y - pPlayer->fHeight &&
					g_Bullet[nCntBullet].pos.y - g_Bullet[nCntBullet].fHeight <= pPlayer->pos.y &&
					pPlayer->bUse == true)
				{
					PlaySound(SOUND_LABEL_SE002);
					pPlayer->bUse = false;
					AddLife(-1);
					g_Bullet[nCntBullet].bUse = false;	//使ってない
					if (GetMode() == MODE_ES_STAGE03)
					{
						SetPlayer(D3DXVECTOR3(0.0f + PLAYER_X_SIZE / 2 * 1.1f, SCREEN_HEIGHT - 10.0f, 0.0f), PLAYER_X_SIZE, PLAYER_Y_SIZE);
					}
					else if (GetMode() == MODE_NO_STAGE04)
					{
						SetPlayer(D3DXVECTOR3(0.0f + PLAYER_X_SIZE / 2 * 1.1f, SCREEN_HEIGHT - 10.0f, 0.0f), PLAYER_X_SIZE, PLAYER_Y_SIZE);
					}
					else if (GetMode() == MODE_HD_STAGE05)
					{
						SetPlayer(D3DXVECTOR3(0.0f + PLAYER_X_SIZE / 2 * 1.2f, SCREEN_HEIGHT - 11.0f, 0.0f), PLAYER_X_SIZE, PLAYER_Y_SIZE);
					}
				}
				//頂点バッファをロックし、頂点データへのポインタを取得
				pVtx[0].pos = D3DXVECTOR3(g_Bullet[nCntBullet].pos.x - g_Bullet[nCntBullet].fWidth / 2, g_Bullet[nCntBullet].pos.y, g_Bullet[nCntBullet].pos.z);
				pVtx[1].pos = D3DXVECTOR3(g_Bullet[nCntBullet].pos.x + g_Bullet[nCntBullet].fWidth / 2, g_Bullet[nCntBullet].pos.y, g_Bullet[nCntBullet].pos.z);
				pVtx[2].pos = D3DXVECTOR3(g_Bullet[nCntBullet].pos.x - g_Bullet[nCntBullet].fWidth / 2, g_Bullet[nCntBullet].pos.y - g_Bullet[nCntBullet].fHeight, g_Bullet[nCntBullet].pos.z);
				pVtx[3].pos = D3DXVECTOR3(g_Bullet[nCntBullet].pos.x + g_Bullet[nCntBullet].fWidth / 2, g_Bullet[nCntBullet].pos.y - g_Bullet[nCntBullet].fHeight, g_Bullet[nCntBullet].pos.z);

				//移動量+
				g_Bullet[nCntBullet].pos += g_Bullet[nCntBullet].move;

				//画面外に出たら
				if (g_Bullet[nCntBullet].pos.x - BULLET_SIZE_X >= SCREEN_WIDTH)
				{
					g_Bullet[nCntBullet].bUse = false;
				}
				//壁にぶつかった
				else if (CollisionBlock(&g_Bullet[nCntBullet].pos, &g_Bullet[nCntBullet].posold, &g_Bullet[nCntBullet].move, g_Bullet[nCntBullet].fWidth, g_Bullet[nCntBullet].fHeight, 3) == true)
				{
					//いちはんしゃ
					if (g_Bullet[nCntBullet].bRft == true)
					{
						g_Bullet[nCntBullet].move.y *= -1;
						g_Bullet[nCntBullet].bRft = false;
					}
					//反射した玉
					else if (g_Bullet[nCntBullet].bRft == false)
					{
						g_Bullet[nCntBullet].bUse = false;
					}
				}
			}
		}
		pVtx += 4;
	}
	//頂点バッファをアンロックする
	g_pVtxBuffBullet->Unlock();
}

//---------------------------
//描画処理
//---------------------------
void DrawBullet(void)
{
	LPDIRECT3DDEVICE9 pDevice;	//デバイスのポインタ

	pDevice = GetDevice();		//デバイスを取得する
	//頂点バッファをデバイスのデータストリームに設定
	pDevice->SetStreamSource(	0,
								g_pVtxBuffBullet,
								0,
								sizeof(VERTEX_2D));
	pDevice->SetFVF(FVF_VERTEX_2D);				//頂点フォーマットの設定
	//ポリゴンの描画
	for (int nCntBullet = 0; nCntBullet < MAX_BULLET; nCntBullet++)
	{
		//使ってたら
		if (g_Bullet[nCntBullet].bUse == true)
		{
			pDevice->SetTexture(0, g_pTextureBullet[g_Bullet[nCntBullet].nType]);	//テクスチャの設定
			pDevice->DrawPrimitive(	D3DPT_TRIANGLESTRIP, //プリミティブの種類
									nCntBullet * 4,
									2);
		}
	}
}

//---------------------------
//弾のセット
//---------------------------
void SetBullet(D3DXVECTOR3 pos, D3DXVECTOR3 move, float fWidth, float fHeight, int nType)
{
	VERTEX_2D *pVtx; //頂点情報へのポインタ

	//頂点バッファをロックし、頂点データへのポインタを取得
	g_pVtxBuffBullet->Lock(0, 0, (void**)&pVtx, 0);

	for (int nCntBullet = 0; nCntBullet < MAX_BULLET; nCntBullet++)
	{
		if (g_Bullet[nCntBullet].bUse == false)
		{
			if (move.x == 0.0f)
			{
				move.x = 6.0f;
			}
			g_Bullet[nCntBullet].pos = pos;				//持ってきた位置を代入
			g_Bullet[nCntBullet].move = move;			//持ってきた移動量を代入
			g_Bullet[nCntBullet].fWidth = fWidth;		//持ってきた幅を代入
			g_Bullet[nCntBullet].fHeight = fHeight;		//持ってきた高さを代入
			g_Bullet[nCntBullet].nType = nType;			//持ってきた種類を代入
				
			//頂点バッファをロックし、頂点データへのポインタを取得
			pVtx[0].pos = D3DXVECTOR3(g_Bullet[nCntBullet].pos.x - g_Bullet[nCntBullet].fWidth / 2, g_Bullet[nCntBullet].pos.y, g_Bullet[nCntBullet].pos.z);
			pVtx[1].pos = D3DXVECTOR3(g_Bullet[nCntBullet].pos.x + g_Bullet[nCntBullet].fWidth / 2, g_Bullet[nCntBullet].pos.y, g_Bullet[nCntBullet].pos.z);
			pVtx[2].pos = D3DXVECTOR3(g_Bullet[nCntBullet].pos.x - g_Bullet[nCntBullet].fWidth / 2, g_Bullet[nCntBullet].pos.y - g_Bullet[nCntBullet].fHeight, g_Bullet[nCntBullet].pos.z);
			pVtx[3].pos = D3DXVECTOR3(g_Bullet[nCntBullet].pos.x + g_Bullet[nCntBullet].fWidth / 2, g_Bullet[nCntBullet].pos.y - g_Bullet[nCntBullet].fHeight, g_Bullet[nCntBullet].pos.z);

			pVtx[0].rhw = 1.0f;
			pVtx[1].rhw = 1.0f;
			pVtx[2].rhw = 1.0f;
			pVtx[3].rhw = 1.0f;

			pVtx[0].col = D3DCOLOR_RGBA(255, 255, 255, 255);
			pVtx[1].col = D3DCOLOR_RGBA(255, 255, 255, 255);
			pVtx[2].col = D3DCOLOR_RGBA(255, 255, 255, 255);
			pVtx[3].col = D3DCOLOR_RGBA(255, 255, 255, 255);

			pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
			pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
			pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
			pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

			g_Bullet[nCntBullet].bUse = true;
			g_Bullet[nCntBullet].bRft = true;
			break;
		}
		pVtx += 4;
	}
	//頂点バッファをアンロックする
	g_pVtxBuffBullet->Unlock();
}

//---------------------------
//弾の情報を取得
//---------------------------
BULLET *GetBullet(void)
{
	return &g_Bullet[0];
}