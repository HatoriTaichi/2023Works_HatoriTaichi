//---------------------------
//インクルードファイル
//---------------------------
#include "enemy.h"
#include "block.h"
#include "player.h"
#include "life.h"
#include "bullet.h"
#include "sound.h"

//---------------------------
//グローバル変数
//---------------------------
LPDIRECT3DTEXTURE9		g_pTextureEnemy[MAX_ENEMY_TEX] = {};	//テクスチャへのポインタ
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffEnemy = NULL;					//頂点バッファへのポインタ
ENEMY					g_enemy[MAX_ENEMY];						//ブロックの構造体
int						g_nAnim;
int						g_nPatn;

//---------------------------
//初期化処理
//---------------------------
HRESULT InitEnemy(void)
{
	LPDIRECT3DDEVICE9	pDevice;	//デバイスへのポインタ
	VERTEX_2D			*pVtx;		//頂点情報へのポインタ

	pDevice = GetDevice();			//デバイスの取得

	//敵の数ループ
	for (int nCntEnemy = 0; nCntEnemy < MAX_ENEMY; nCntEnemy++)
	{
		g_enemy[nCntEnemy].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);		//敵の位置
		g_enemy[nCntEnemy].move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);	//敵の位置
		g_enemy[nCntEnemy].posold = D3DXVECTOR3(0.0f, 0.0f, 0.0f);	//敵の位置
		g_enemy[nCntEnemy].fWidth = 0.0f;							//敵の横幅
		g_enemy[nCntEnemy].fHeight = 0.0f;							//敵の縦幅
		g_enemy[nCntEnemy].bJump = false;							//ジャンプの状態
		g_enemy[nCntEnemy].bUse = false;							//敵の状態
		g_enemy[nCntEnemy].bDamage = true;							//敵の状態
	}
	//テクスチャの読み込み
	D3DXCreateTextureFromFile(	pDevice,
								"data/Texture/enemy00.png",	//テクスチャ
								&g_pTextureEnemy[0]);
	//テクスチャの読み込み
	D3DXCreateTextureFromFile(	pDevice,
								"data/Texture/enemy01.png",	//テクスチャ
								&g_pTextureEnemy[1]);
	//テクスチャの読み込み
	D3DXCreateTextureFromFile(	pDevice,
								"data/Texture/enemy02.png",	//テクスチャ
								&g_pTextureEnemy[2]);
	//頂点バッファの生成
	pDevice->CreateVertexBuffer(	sizeof(VERTEX_2D) * 4 * MAX_ENEMY,
									D3DUSAGE_WRITEONLY,
									FVF_VERTEX_2D,
									D3DPOOL_MANAGED,
									&g_pVtxBuffEnemy,
									NULL);

	//頂点バッファをロックし、頂点データへのポインタを取得
	g_pVtxBuffEnemy->Lock(0, 0, (void**)&pVtx, 0);

	//敵の数ループ
	for (int nCntEnemy = 0; nCntEnemy < MAX_ENEMY; nCntEnemy++)
	{
		//頂点座標の設定
		pVtx[0].pos = D3DXVECTOR3(g_enemy[nCntEnemy].pos.x - g_enemy[nCntEnemy].fWidth / 2, g_enemy[nCntEnemy].pos.y - g_enemy[nCntEnemy].fHeight, g_enemy[nCntEnemy].pos.z);
		pVtx[1].pos = D3DXVECTOR3(g_enemy[nCntEnemy].pos.x + g_enemy[nCntEnemy].fWidth / 2, g_enemy[nCntEnemy].pos.y - g_enemy[nCntEnemy].fHeight, g_enemy[nCntEnemy].pos.z);
		pVtx[2].pos = D3DXVECTOR3(g_enemy[nCntEnemy].pos.x - g_enemy[nCntEnemy].fWidth / 2, g_enemy[nCntEnemy].pos.y, g_enemy[nCntEnemy].pos.z);
		pVtx[3].pos = D3DXVECTOR3(g_enemy[nCntEnemy].pos.x + g_enemy[nCntEnemy].fWidth / 2, g_enemy[nCntEnemy].pos.y, g_enemy[nCntEnemy].pos.z);

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

		pVtx += 4;	//頂点を進める
	}

	//頂点バッファをアンロックする
	g_pVtxBuffEnemy->Unlock();

	return S_OK;
}

//---------------------------
//終了処理
//---------------------------
void UninitEnemy(void)
{
	//敵の数ループ
	for (int nCntEnemy = 0; nCntEnemy < MAX_ENEMY_TEX; nCntEnemy++)
	{
		//テクスチャの破棄
		if (g_pTextureEnemy[nCntEnemy] != NULL)
		{
			g_pTextureEnemy[nCntEnemy]->Release();
			g_pTextureEnemy[nCntEnemy] = NULL;
		}
	}

	//頂点バッファの破棄
	if (g_pVtxBuffEnemy != NULL)
	{
		g_pVtxBuffEnemy->Release();
		g_pVtxBuffEnemy = NULL;
	}
}

//---------------------------
//更新処理
//---------------------------
void UpdateEnemy(void)
{
	VERTEX_2D			*pVtx;		//頂点情報へのポインタ
	PLAYER				*pPlayer;	//プレイヤー構造体
	static int			nBullet = 0;//弾の間隔
	static int			nTimer;		//タイマー
	static int			nTimer2;	//点滅
	static int			nTimer3;	//点滅
	static int			nCol = 255;	//チカチカ

	pPlayer = GetPlayer();			//プレイヤー構造体

	for (int nCntEnemy = 0; nCntEnemy < MAX_ENEMY; nCntEnemy++)
	{
		g_enemy[nCntEnemy].posold = g_enemy[nCntEnemy].pos;	//前回の位置を保存
	}

	//頂点バッファをロックし、頂点データへのポインタを取得
	g_pVtxBuffEnemy->Lock(0, 0, (void**)&pVtx, 0);

	//敵の数ループ
	for (int nCntEnemy = 0; nCntEnemy < MAX_ENEMY; nCntEnemy++)
	{
		//使ってたら
		if (g_enemy[nCntEnemy].bUse == true)
		{
			//敵タイプ0
			if (g_enemy[nCntEnemy].nType == 0)
			{
				if (GetMode() == MODE_ES_STAGE01 || GetMode() == MODE_NO_STAGE02 || GetMode() == MODE_HD_STAGE02)
				{
					//頂点座標の設定
					pVtx[0].pos = D3DXVECTOR3(g_enemy[nCntEnemy].pos.x - g_enemy[nCntEnemy].fWidth / 2, g_enemy[nCntEnemy].pos.y - g_enemy[nCntEnemy].fHeight, g_enemy[nCntEnemy].pos.z);
					pVtx[1].pos = D3DXVECTOR3(g_enemy[nCntEnemy].pos.x + g_enemy[nCntEnemy].fWidth / 2, g_enemy[nCntEnemy].pos.y - g_enemy[nCntEnemy].fHeight, g_enemy[nCntEnemy].pos.z);
					pVtx[2].pos = D3DXVECTOR3(g_enemy[nCntEnemy].pos.x - g_enemy[nCntEnemy].fWidth / 2, g_enemy[nCntEnemy].pos.y, g_enemy[nCntEnemy].pos.z);
					pVtx[3].pos = D3DXVECTOR3(g_enemy[nCntEnemy].pos.x + g_enemy[nCntEnemy].fWidth / 2, g_enemy[nCntEnemy].pos.y, g_enemy[nCntEnemy].pos.z);

					//毎フレーム重力を＋
					g_enemy[nCntEnemy].pos.y += G_POW;
					//移動量を＋
					g_enemy[nCntEnemy].pos.y += g_enemy[nCntEnemy].move.y;

					CollisionBlock(&g_enemy[nCntEnemy].pos, &g_enemy[nCntEnemy].posold, &g_enemy[nCntEnemy].move, g_enemy[nCntEnemy].fWidth, g_enemy[nCntEnemy].fHeight, 1);

					g_enemy[nCntEnemy].pos.x += g_enemy[nCntEnemy].move.x;

					g_nAnim++;
					if (g_nAnim >= 150)
					{
						g_nPatn++;
						if (g_nPatn > 1)
						{
							g_nPatn = 0;
						}
						g_nAnim = 0;
					}
					if (g_enemy[nCntEnemy].move.x >= 0.0f)
					{
						pVtx[0].tex = D3DXVECTOR2(0.0f + 0.5 * g_nPatn, 0.5f);
						pVtx[1].tex = D3DXVECTOR2(0.5f + 0.5 * g_nPatn, 0.5f);
						pVtx[2].tex = D3DXVECTOR2(0.0f + 0.5 * g_nPatn, 1.0f);
						pVtx[3].tex = D3DXVECTOR2(0.5f + 0.5 * g_nPatn, 1.0f);
					}
					else if (g_enemy[nCntEnemy].move.x <= 0.0f)
					{
						pVtx[0].tex = D3DXVECTOR2(0.0f + 0.5 * g_nPatn, 0.0f);
						pVtx[1].tex = D3DXVECTOR2(0.5f + 0.5 * g_nPatn, 0.0f);
						pVtx[2].tex = D3DXVECTOR2(0.0f + 0.5 * g_nPatn, 0.5f);
						pVtx[3].tex = D3DXVECTOR2(0.5f + 0.5 * g_nPatn, 0.5f);
					}
				}
			}
			//敵タイプ1
			if (g_enemy[nCntEnemy].nType == 1)
			{
				if (GetMode() == MODE_ES_STAGE01)
				{
					g_enemy[nCntEnemy].pos.x += g_enemy[nCntEnemy].move.x;

					if (g_enemy[nCntEnemy].bJump == false)
					{
						g_enemy[nCntEnemy].move.y = -10.0f;
						g_enemy[nCntEnemy].bJump = true;
					}

					//頂点座標の設定
					pVtx[0].pos = D3DXVECTOR3(g_enemy[nCntEnemy].pos.x - g_enemy[nCntEnemy].fWidth / 2, g_enemy[nCntEnemy].pos.y - g_enemy[nCntEnemy].fHeight, g_enemy[nCntEnemy].pos.z);
					pVtx[1].pos = D3DXVECTOR3(g_enemy[nCntEnemy].pos.x + g_enemy[nCntEnemy].fWidth / 2, g_enemy[nCntEnemy].pos.y - g_enemy[nCntEnemy].fHeight, g_enemy[nCntEnemy].pos.z);
					pVtx[2].pos = D3DXVECTOR3(g_enemy[nCntEnemy].pos.x - g_enemy[nCntEnemy].fWidth / 2, g_enemy[nCntEnemy].pos.y, g_enemy[nCntEnemy].pos.z);
					pVtx[3].pos = D3DXVECTOR3(g_enemy[nCntEnemy].pos.x + g_enemy[nCntEnemy].fWidth / 2, g_enemy[nCntEnemy].pos.y, g_enemy[nCntEnemy].pos.z);

					//毎フレーム重力を＋
					g_enemy[nCntEnemy].move.y += G_POW;
					//移動量を＋
					g_enemy[nCntEnemy].pos.y += g_enemy[nCntEnemy].move.y;

					if (CollisionBlock(&g_enemy[nCntEnemy].pos, &g_enemy[nCntEnemy].posold, &g_enemy[nCntEnemy].move, g_enemy[nCntEnemy].fWidth, g_enemy[nCntEnemy].fHeight, 2) == true)
					{
						g_enemy[nCntEnemy].bJump = false;
					}
					//画面左端に出たら
					if (g_enemy[nCntEnemy].pos.x - ENEMY_X_SIZE <= 0)
					{
						//左端にセット
						g_enemy[nCntEnemy].pos.x = 0.0f + ENEMY_X_SIZE;
						g_enemy[nCntEnemy].move.x *= -1;
					}
				}
				else if (GetMode() == MODE_HD_STAGE01)
				{
					g_enemy[nCntEnemy].pos.x += g_enemy[nCntEnemy].move.x;

					if (g_enemy[nCntEnemy].bJump == false)
					{
						g_enemy[nCntEnemy].move.y = -10.0f;
						g_enemy[nCntEnemy].bJump = true;
					}

					//頂点座標の設定
					pVtx[0].pos = D3DXVECTOR3(g_enemy[nCntEnemy].pos.x - g_enemy[nCntEnemy].fWidth / 2, g_enemy[nCntEnemy].pos.y - g_enemy[nCntEnemy].fHeight, g_enemy[nCntEnemy].pos.z);
					pVtx[1].pos = D3DXVECTOR3(g_enemy[nCntEnemy].pos.x + g_enemy[nCntEnemy].fWidth / 2, g_enemy[nCntEnemy].pos.y - g_enemy[nCntEnemy].fHeight, g_enemy[nCntEnemy].pos.z);
					pVtx[2].pos = D3DXVECTOR3(g_enemy[nCntEnemy].pos.x - g_enemy[nCntEnemy].fWidth / 2, g_enemy[nCntEnemy].pos.y, g_enemy[nCntEnemy].pos.z);
					pVtx[3].pos = D3DXVECTOR3(g_enemy[nCntEnemy].pos.x + g_enemy[nCntEnemy].fWidth / 2, g_enemy[nCntEnemy].pos.y, g_enemy[nCntEnemy].pos.z);

					//毎フレーム重力を＋
					g_enemy[nCntEnemy].move.y += G_POW;
					//移動量を＋
					g_enemy[nCntEnemy].pos.y += g_enemy[nCntEnemy].move.y;

					if (CollisionBlock(&g_enemy[nCntEnemy].pos, &g_enemy[nCntEnemy].posold, &g_enemy[nCntEnemy].move, g_enemy[nCntEnemy].fWidth, g_enemy[nCntEnemy].fHeight, 2) == true)
					{
						g_enemy[nCntEnemy].bJump = false;
					}
				}
				else if (GetMode() == MODE_HD_STAGE03)
				{
					g_enemy[nCntEnemy].pos.x += g_enemy[nCntEnemy].move.x;

					if (g_enemy[nCntEnemy].bJump == false)
					{
						g_enemy[nCntEnemy].move.y = -10.0f;
						g_enemy[nCntEnemy].bJump = true;
					}

					//頂点座標の設定
					pVtx[0].pos = D3DXVECTOR3(g_enemy[nCntEnemy].pos.x - g_enemy[nCntEnemy].fWidth / 2, g_enemy[nCntEnemy].pos.y - g_enemy[nCntEnemy].fHeight, g_enemy[nCntEnemy].pos.z);
					pVtx[1].pos = D3DXVECTOR3(g_enemy[nCntEnemy].pos.x + g_enemy[nCntEnemy].fWidth / 2, g_enemy[nCntEnemy].pos.y - g_enemy[nCntEnemy].fHeight, g_enemy[nCntEnemy].pos.z);
					pVtx[2].pos = D3DXVECTOR3(g_enemy[nCntEnemy].pos.x - g_enemy[nCntEnemy].fWidth / 2, g_enemy[nCntEnemy].pos.y, g_enemy[nCntEnemy].pos.z);
					pVtx[3].pos = D3DXVECTOR3(g_enemy[nCntEnemy].pos.x + g_enemy[nCntEnemy].fWidth / 2, g_enemy[nCntEnemy].pos.y, g_enemy[nCntEnemy].pos.z);

					//毎フレーム重力を＋
					g_enemy[nCntEnemy].move.y += G_POW;
					//移動量を＋
					g_enemy[nCntEnemy].pos.y += g_enemy[nCntEnemy].move.y;

					if (CollisionBlock(&g_enemy[nCntEnemy].pos, &g_enemy[nCntEnemy].posold, &g_enemy[nCntEnemy].move, g_enemy[nCntEnemy].fWidth, g_enemy[nCntEnemy].fHeight, 2) == true)
					{
						g_enemy[nCntEnemy].bJump = false;
					}
					if (g_enemy[nCntEnemy].pos.x - g_enemy[nCntEnemy].fWidth / 2 <= 400)
					{
						g_enemy[nCntEnemy].move.x *= -1;
					}
				}
				if (g_enemy[nCntEnemy].move.x >= 0.0f)
				{
					pVtx[0].tex = D3DXVECTOR2(0.5f, 0.0f);
					pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
					pVtx[2].tex = D3DXVECTOR2(0.5f, 1.0f);
					pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);
				}
				else if (g_enemy[nCntEnemy].move.x <= 0.0f)
				{
					pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
					pVtx[1].tex = D3DXVECTOR2(0.5f, 0.0f);
					pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
					pVtx[3].tex = D3DXVECTOR2(0.5f, 1.0f);
				}
			}
			//敵タイプ2
			if (g_enemy[nCntEnemy].nType == 2)
			{
				if (GetMode() == MODE_ES_STAGE03)
				{
					g_enemy[nCntEnemy].pos.y += g_enemy[nCntEnemy].move.y;

					//頂点座標の設定
					pVtx[0].pos = D3DXVECTOR3(g_enemy[nCntEnemy].pos.x - g_enemy[nCntEnemy].fWidth / 2, g_enemy[nCntEnemy].pos.y - g_enemy[nCntEnemy].fHeight, g_enemy[nCntEnemy].pos.z);
					pVtx[1].pos = D3DXVECTOR3(g_enemy[nCntEnemy].pos.x + g_enemy[nCntEnemy].fWidth / 2, g_enemy[nCntEnemy].pos.y - g_enemy[nCntEnemy].fHeight, g_enemy[nCntEnemy].pos.z);
					pVtx[2].pos = D3DXVECTOR3(g_enemy[nCntEnemy].pos.x - g_enemy[nCntEnemy].fWidth / 2, g_enemy[nCntEnemy].pos.y, g_enemy[nCntEnemy].pos.z);
					pVtx[3].pos = D3DXVECTOR3(g_enemy[nCntEnemy].pos.x + g_enemy[nCntEnemy].fWidth / 2, g_enemy[nCntEnemy].pos.y, g_enemy[nCntEnemy].pos.z);

					if (CollisionBlock(&g_enemy[nCntEnemy].pos, &g_enemy[nCntEnemy].posold, &g_enemy[nCntEnemy].move, g_enemy[nCntEnemy].fWidth, g_enemy[nCntEnemy].fHeight, 4) == true)
					{

					}

					nBullet++;
					if (nBullet >= ENEMY_BULLET_SPAN)
					{
						SetBullet(D3DXVECTOR3(g_enemy[nCntEnemy].pos.x, g_enemy[nCntEnemy].pos.y - g_enemy[nCntEnemy].fHeight / 2, 0.0f), D3DXVECTOR3(-4.0f, 0.0f, 0.0f), BULLET_SIZE_X * 10, BULLET_SIZE_Y * 10, 1);
						SetBullet(D3DXVECTOR3(g_enemy[nCntEnemy].pos.x, g_enemy[nCntEnemy].pos.y - g_enemy[nCntEnemy].fHeight / 2, 0.0f), D3DXVECTOR3(-2.0f, -2.0f, 0.0f), BULLET_SIZE_X * 10, BULLET_SIZE_Y * 10, 1);
						SetBullet(D3DXVECTOR3(g_enemy[nCntEnemy].pos.x, g_enemy[nCntEnemy].pos.y - g_enemy[nCntEnemy].fHeight / 2, 0.0f), D3DXVECTOR3(-2.0f, +2.0f, 0.0f), BULLET_SIZE_X * 10, BULLET_SIZE_Y * 10, 1);
						PlaySound(SOUND_LABEL_SE001);
						nBullet = 0;
					}
				}
				else if (GetMode() == MODE_NO_STAGE04)
				{
					g_enemy[nCntEnemy].pos += g_enemy[nCntEnemy].move;

					//頂点座標の設定
					pVtx[0].pos = D3DXVECTOR3(g_enemy[nCntEnemy].pos.x - g_enemy[nCntEnemy].fWidth / 2, g_enemy[nCntEnemy].pos.y - g_enemy[nCntEnemy].fHeight, g_enemy[nCntEnemy].pos.z);
					pVtx[1].pos = D3DXVECTOR3(g_enemy[nCntEnemy].pos.x + g_enemy[nCntEnemy].fWidth / 2, g_enemy[nCntEnemy].pos.y - g_enemy[nCntEnemy].fHeight, g_enemy[nCntEnemy].pos.z);
					pVtx[2].pos = D3DXVECTOR3(g_enemy[nCntEnemy].pos.x - g_enemy[nCntEnemy].fWidth / 2, g_enemy[nCntEnemy].pos.y, g_enemy[nCntEnemy].pos.z);
					pVtx[3].pos = D3DXVECTOR3(g_enemy[nCntEnemy].pos.x + g_enemy[nCntEnemy].fWidth / 2, g_enemy[nCntEnemy].pos.y, g_enemy[nCntEnemy].pos.z);

					if (CollisionBlock(&g_enemy[nCntEnemy].pos, &g_enemy[nCntEnemy].posold, &g_enemy[nCntEnemy].move, g_enemy[nCntEnemy].fWidth, g_enemy[nCntEnemy].fHeight, 4) == true)
					{
						SetBullet(D3DXVECTOR3(g_enemy[nCntEnemy].pos.x, g_enemy[nCntEnemy].pos.y - g_enemy[nCntEnemy].fHeight / 2, 0.0f), D3DXVECTOR3(-4.0f, 4.0f, 0.0f), BULLET_SIZE_X * 5, BULLET_SIZE_Y * 5, 3);
						SetBullet(D3DXVECTOR3(g_enemy[nCntEnemy].pos.x, g_enemy[nCntEnemy].pos.y - g_enemy[nCntEnemy].fHeight / 2, 0.0f), D3DXVECTOR3(-4.0f, -4.0f, 0.0f), BULLET_SIZE_X * 5, BULLET_SIZE_Y * 5, 3);
						PlaySound(SOUND_LABEL_SE001);
					}

					nBullet++;
					if (nBullet >= ENEMY_BULLET_SPAN)
					{
						SetBullet(D3DXVECTOR3(g_enemy[nCntEnemy].pos.x, g_enemy[nCntEnemy].pos.y - g_enemy[nCntEnemy].fHeight / 2, 0.0f), D3DXVECTOR3(-2.0f, 2.0f, 0.0f), BULLET_SIZE_X * 10, BULLET_SIZE_Y * 10, 1);
						SetBullet(D3DXVECTOR3(g_enemy[nCntEnemy].pos.x, g_enemy[nCntEnemy].pos.y - g_enemy[nCntEnemy].fHeight / 2, 0.0f), D3DXVECTOR3(-2.0f, -2.0f, 0.0f), BULLET_SIZE_X * 10, BULLET_SIZE_Y * 10, 1);
						PlaySound(SOUND_LABEL_SE001);
						nBullet = 0;
					}
				}
				else if (GetMode() == MODE_HD_STAGE04)
				{
					g_enemy[nCntEnemy].pos.x += g_enemy[nCntEnemy].move.x;

					if (g_enemy[nCntEnemy].bJump == false)
					{
						g_enemy[nCntEnemy].move.y = -20.0f;
						g_enemy[nCntEnemy].bJump = true;
					}

					//頂点座標の設定
					pVtx[0].pos = D3DXVECTOR3(g_enemy[nCntEnemy].pos.x - g_enemy[nCntEnemy].fWidth / 2, g_enemy[nCntEnemy].pos.y - g_enemy[nCntEnemy].fHeight, g_enemy[nCntEnemy].pos.z);
					pVtx[1].pos = D3DXVECTOR3(g_enemy[nCntEnemy].pos.x + g_enemy[nCntEnemy].fWidth / 2, g_enemy[nCntEnemy].pos.y - g_enemy[nCntEnemy].fHeight, g_enemy[nCntEnemy].pos.z);
					pVtx[2].pos = D3DXVECTOR3(g_enemy[nCntEnemy].pos.x - g_enemy[nCntEnemy].fWidth / 2, g_enemy[nCntEnemy].pos.y, g_enemy[nCntEnemy].pos.z);
					pVtx[3].pos = D3DXVECTOR3(g_enemy[nCntEnemy].pos.x + g_enemy[nCntEnemy].fWidth / 2, g_enemy[nCntEnemy].pos.y, g_enemy[nCntEnemy].pos.z);

					//毎フレーム重力を＋
					g_enemy[nCntEnemy].move.y += G_POW;
					//移動量を＋
					g_enemy[nCntEnemy].pos.y += g_enemy[nCntEnemy].move.y;

					if (CollisionBlock(&g_enemy[nCntEnemy].pos, &g_enemy[nCntEnemy].posold, &g_enemy[nCntEnemy].move, g_enemy[nCntEnemy].fWidth, g_enemy[nCntEnemy].fHeight, 2) == true)
					{
						g_enemy[nCntEnemy].bJump = false;
					}
				}
				else if (GetMode() == MODE_HD_STAGE05)
				{
					g_enemy[nCntEnemy].pos += g_enemy[nCntEnemy].move;

					//頂点座標の設定
					pVtx[0].pos = D3DXVECTOR3(g_enemy[nCntEnemy].pos.x - g_enemy[nCntEnemy].fWidth / 2, g_enemy[nCntEnemy].pos.y - g_enemy[nCntEnemy].fHeight, g_enemy[nCntEnemy].pos.z);
					pVtx[1].pos = D3DXVECTOR3(g_enemy[nCntEnemy].pos.x + g_enemy[nCntEnemy].fWidth / 2, g_enemy[nCntEnemy].pos.y - g_enemy[nCntEnemy].fHeight, g_enemy[nCntEnemy].pos.z);
					pVtx[2].pos = D3DXVECTOR3(g_enemy[nCntEnemy].pos.x - g_enemy[nCntEnemy].fWidth / 2, g_enemy[nCntEnemy].pos.y, g_enemy[nCntEnemy].pos.z);
					pVtx[3].pos = D3DXVECTOR3(g_enemy[nCntEnemy].pos.x + g_enemy[nCntEnemy].fWidth / 2, g_enemy[nCntEnemy].pos.y, g_enemy[nCntEnemy].pos.z);

					if (CollisionBlock(&g_enemy[nCntEnemy].pos, &g_enemy[nCntEnemy].posold, &g_enemy[nCntEnemy].move, g_enemy[nCntEnemy].fWidth, g_enemy[nCntEnemy].fHeight, 4) == true)
					{
						SetBullet(D3DXVECTOR3(g_enemy[nCntEnemy].pos.x, g_enemy[nCntEnemy].pos.y - g_enemy[nCntEnemy].fHeight / 2, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), BULLET_SIZE_X * 5, BULLET_SIZE_Y * 5, 2);
						SetBullet(D3DXVECTOR3(g_enemy[nCntEnemy].pos.x, g_enemy[nCntEnemy].pos.y - g_enemy[nCntEnemy].fHeight / 2, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), BULLET_SIZE_X * 5, BULLET_SIZE_Y * 5, 2);
						PlaySound(SOUND_LABEL_SE001);
					}

					nBullet++;
					if (nBullet >= ENEMY_BULLET_SPAN)
					{
						SetBullet(D3DXVECTOR3(g_enemy[nCntEnemy].pos.x, g_enemy[nCntEnemy].pos.y - g_enemy[nCntEnemy].fHeight / 2, 0.0f), D3DXVECTOR3(-3.0f, 0.0f, 0.0f), BULLET_SIZE_X * 10, BULLET_SIZE_Y * 10, 1);
						SetBullet(D3DXVECTOR3(g_enemy[nCntEnemy].pos.x, g_enemy[nCntEnemy].pos.y - g_enemy[nCntEnemy].fHeight / 2, 0.0f), D3DXVECTOR3(-1.4f, -2.0f, 0.0f), BULLET_SIZE_X * 5, BULLET_SIZE_Y * 5, 3);
						SetBullet(D3DXVECTOR3(g_enemy[nCntEnemy].pos.x, g_enemy[nCntEnemy].pos.y - g_enemy[nCntEnemy].fHeight / 2, 0.0f), D3DXVECTOR3(-1.4f, -2.0f, 0.0f), BULLET_SIZE_X * 5, BULLET_SIZE_Y * 5, 3);
						PlaySound(SOUND_LABEL_SE001);
						nBullet = 0;
					}
					if (g_enemy[nCntEnemy].pos.x <= SCREEN_WIDTH / 2)
					{
						g_enemy[nCntEnemy].move.x *= -1;
					}
				}
			}
			//プレイヤーに触れたら
			if (pPlayer->pos.x - pPlayer->fWidth / 2 <= g_enemy[nCntEnemy].pos.x + g_enemy[nCntEnemy].fWidth / 2 &&
				pPlayer->pos.x + pPlayer->fWidth / 2 >= g_enemy[nCntEnemy].pos.x - g_enemy[nCntEnemy].fWidth / 2 &&
				pPlayer->pos.y - pPlayer->fWidth <= g_enemy[nCntEnemy].pos.y &&
				pPlayer->pos.y >= g_enemy[nCntEnemy].pos.y - g_enemy[nCntEnemy].fWidth &&
				pPlayer->bUse == true)
			{
				pPlayer->bUse = false;
				AddLife(-1);
				if (GetMode() == MODE_ES_STAGE01)
				{
					SetPlayer(D3DXVECTOR3(0.0f + pPlayer->fWidth / 2 * 1.1f, 250.0f, 0.0f), PLAYER_X_SIZE, PLAYER_Y_SIZE);
				}
				else if (GetMode() == MODE_ES_STAGE03)
				{
					SetPlayer(D3DXVECTOR3(0.0f + PLAYER_X_SIZE / 2 * 1.1f, SCREEN_HEIGHT - 10.0f, 0.0f), PLAYER_X_SIZE, PLAYER_Y_SIZE);
				}
				else if (GetMode() == MODE_NO_STAGE02)
				{
					SetPlayer(D3DXVECTOR3(0.0f + PLAYER_X_SIZE / 2 * 1.1f, 400.0f, 0.0f), PLAYER_X_SIZE, PLAYER_Y_SIZE);
				}
				else if (GetMode() == MODE_NO_STAGE04)
				{
					SetPlayer(D3DXVECTOR3(0.0f + PLAYER_X_SIZE / 2 * 1.1f, SCREEN_HEIGHT - 10.0f, 0.0f), PLAYER_X_SIZE, PLAYER_Y_SIZE);
				}
				else if (GetMode() == MODE_HD_STAGE01)
				{
					SetPlayer(D3DXVECTOR3(0.0f + PLAYER_X_SIZE / 2 * 1.1f, 250.0f, 0.0f), PLAYER_X_SIZE, PLAYER_Y_SIZE);
				}
				else if (GetMode() == MODE_HD_STAGE02)
				{
					SetPlayer(D3DXVECTOR3(0.0f + PLAYER_X_SIZE / 2 * 1.1f, 670.0f, 0.0f), PLAYER_X_SIZE, PLAYER_Y_SIZE);
				}
				else if (GetMode() == MODE_HD_STAGE03)
				{
					SetPlayer(D3DXVECTOR3(0.0f + PLAYER_X_SIZE / 2 * 1.1f, 650.0f, 0.0f), PLAYER_X_SIZE, PLAYER_Y_SIZE);
				}
				else if (GetMode() == MODE_HD_STAGE04)
				{
					SetPlayer(D3DXVECTOR3(0.0f + PLAYER_X_SIZE / 2 * 1.2f, SCREEN_HEIGHT - 11.0f, 0.0f), PLAYER_X_SIZE, PLAYER_Y_SIZE);
				}
			}
			if (g_enemy[nCntEnemy].bDamage == false)
			{
				nTimer2++;	//点滅タイミング
				nTimer3++;	//点滅タイミング
				//点滅タイミングになった
				if (nTimer3 == 10)
				{
					nTimer2 = nTimer3;	//タイミングを渡して
					nTimer3 = 0;		//0になる
				}
				//Rが255で && タイミングが来てたら
				if (nCol == 255 && nTimer2 == 10)
				{
					nCol = 0;		//透明
					nTimer2 = 0;	//タイミング初期化
					if (nCol == 0)
					{
						g_enemy[nCntEnemy].bDamage = true;
					}
				}
				//Aが0で && タイミングが来てる
				else if (nCol == 0 && nTimer2 == 10)
				{
					nCol = 255;		//見える
					nTimer2 = 0;	//タイミング初期化
				}
				pVtx[0].col = D3DCOLOR_RGBA(nCol, 0, 0, 255);
				pVtx[1].col = D3DCOLOR_RGBA(nCol, 0, 0, 255);
				pVtx[2].col = D3DCOLOR_RGBA(nCol, 0, 0, 255);
				pVtx[3].col = D3DCOLOR_RGBA(nCol, 0, 0, 255);
				if (nCol == 0)
				{
					pVtx[0].col = D3DCOLOR_RGBA(255, 255, 255, 255);
					pVtx[1].col = D3DCOLOR_RGBA(255, 255, 255, 255);
					pVtx[2].col = D3DCOLOR_RGBA(255, 255, 255, 255);
					pVtx[3].col = D3DCOLOR_RGBA(255, 255, 255, 255);
				}
			}
			//下に落ちたら
			if (g_enemy[nCntEnemy].pos.y - g_enemy[nCntEnemy].fHeight >= SCREEN_HEIGHT)
			{
				g_enemy[nCntEnemy].bUse = false;
			}
		}
		pVtx += 4;	//頂点を進める
	}
	//頂点バッファをアンロックする
	g_pVtxBuffEnemy->Unlock();
}

//---------------------------
//描画処理
//---------------------------
void DrawEnemy(void)
{
	LPDIRECT3DDEVICE9 pDevice;	//デバイスのポインタ

	//デバイスを取得する
	pDevice = GetDevice();

	//頂点バッファをデバイスのデータストリームに設定
	pDevice->SetStreamSource(	0,
								g_pVtxBuffEnemy,
								0,
								sizeof(VERTEX_2D));
	pDevice->SetFVF(FVF_VERTEX_2D);	//頂点フォーマットの設定
	//敵の数ループ
	for (int nCntEnemy = 0; nCntEnemy < MAX_ENEMY; nCntEnemy++)
	{
		//使ってたら
		if (g_enemy[nCntEnemy].bUse == true)
		{
			pDevice->SetTexture(0, g_pTextureEnemy[g_enemy[nCntEnemy].nType]);		//テクスチャの設定
			//ポリゴンの描画
			pDevice->DrawPrimitive(	D3DPT_TRIANGLESTRIP,	//プリミティブの種類
									nCntEnemy * 4,
									2);
		}
	}
}

//---------------------------
//敵のセット
//---------------------------
void SetEnemy(D3DXVECTOR3 pos, D3DXVECTOR3 move, float fWidth, float fHeight, int nType, int nLife)
{
	VERTEX_2D *pVtx; //頂点情報へのポインタ

	//頂点バッファをロックし、頂点データへのポインタを取得
	g_pVtxBuffEnemy->Lock(0, 0, (void**)&pVtx, 0);

	//敵の数ループ
	for (int nCntEnemy = 0; nCntEnemy < MAX_ENEMY; nCntEnemy++)
	{
		//使ってなかったら
		if (g_enemy[nCntEnemy].bUse == false)
		{
			g_enemy[nCntEnemy].pos = pos;			//持ってきた位置を代入
			g_enemy[nCntEnemy].move = move;			//持ってきた移動量を代入
			g_enemy[nCntEnemy].fWidth = fWidth;		//持ってきた横幅を代入
			g_enemy[nCntEnemy].fHeight = fHeight;	//持ってきた縦幅を代入
			g_enemy[nCntEnemy].nType = nType;		//持ってきた種類を代入
			g_enemy[nCntEnemy].nLife = nLife;		//持ってきた体力を代入

			//頂点座標の更新
			pVtx[0].pos = D3DXVECTOR3(g_enemy[nCntEnemy].pos.x - g_enemy[nCntEnemy].fWidth / 2, g_enemy[nCntEnemy].pos.y - g_enemy[nCntEnemy].fHeight, g_enemy[nCntEnemy].pos.z);
			pVtx[1].pos = D3DXVECTOR3(g_enemy[nCntEnemy].pos.x + g_enemy[nCntEnemy].fWidth / 2, g_enemy[nCntEnemy].pos.y - g_enemy[nCntEnemy].fHeight, g_enemy[nCntEnemy].pos.z);
			pVtx[2].pos = D3DXVECTOR3(g_enemy[nCntEnemy].pos.x - g_enemy[nCntEnemy].fWidth / 2, g_enemy[nCntEnemy].pos.y, g_enemy[nCntEnemy].pos.z);
			pVtx[3].pos = D3DXVECTOR3(g_enemy[nCntEnemy].pos.x + g_enemy[nCntEnemy].fWidth / 2, g_enemy[nCntEnemy].pos.y, g_enemy[nCntEnemy].pos.z);

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

			g_enemy[nCntEnemy].bUse = true;	//使ってる状態
			break;
		}
		pVtx += 4;	//頂点を進める
	}
	//頂点バッファをアンロックする
	g_pVtxBuffEnemy->Unlock();
}

//---------------------------
//敵の情報
//---------------------------
ENEMY *GetEnemy(void)
{
	return &g_enemy[0];
}