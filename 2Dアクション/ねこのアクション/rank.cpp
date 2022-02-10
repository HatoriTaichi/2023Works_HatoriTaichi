//---------------------------
//インクルードファイル
//---------------------------
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include "rank.h"
#include "score.h"
#include "difficulty level.h"

//---------------------------
//グローバル変数
//---------------------------
LPDIRECT3DTEXTURE9		g_apTextureRank = NULL;				//テクスチャ
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffRank = NULL;				//頂点バッファへのポインタ
RANK					g_aRank[MAX_RANK][MAX_SCOREDIGIT];	//スコアの構造体
int						g_nRankScore[MAX_RANK + 1];			//比べるスコア
bool					g_bUse;								//一回だけ保存
int						g_nCnt;

//---------------------------
//初期化処理
//---------------------------
HRESULT InitRank(void)
{
	InitLetter();
	LPDIRECT3DDEVICE9 pDevice;  //デバイスへのポインタ
	VERTEX_2D		  *pVtx;	//頂点情報へのポインタ
	FILE			  *pFile;	//ファイル開く

	//デバイスの取得
	pDevice = GetDevice();

	//初期化
	for (int nCntRank = 0; nCntRank < MAX_RANK; nCntRank++)
	{
		for (int nCntRank2 = 0; nCntRank2 < MAX_SCOREDIGIT; nCntRank2++)
		{
			g_aRank[nCntRank][nCntRank2].pos = D3DXVECTOR3(((SCREEN_WIDTH / 2) - (RANK_X * 2)) + (RANK_X * nCntRank2), (SCREEN_HEIGHT / (7 + 1)) + ((SCREEN_HEIGHT / (7 + 1)) * nCntRank), 0.0f);
		}
		g_nRankScore[nCntRank] = 0;
	}
	g_nRankScore[MAX_RANK] = 0;
	g_bUse = true;
	//テクスチャの読み込み
	D3DXCreateTextureFromFile(	pDevice,
								"data/Texture/number000.png",
								&g_apTextureRank);
	//頂点バッファの生成
	pDevice->CreateVertexBuffer(	sizeof(VERTEX_2D) * 4 * MAX_SCOREDIGIT * MAX_RANK,
									D3DUSAGE_WRITEONLY,
									FVF_VERTEX_2D,
									D3DPOOL_MANAGED,
									&g_pVtxBuffRank,
									NULL);
	//頂点バッファをロックし、頂点データへのポインタを取得
	g_pVtxBuffRank->Lock(0, 0, (void**)&pVtx, 0);

	for (int nCntRank = 0; nCntRank < MAX_RANK; nCntRank++)
	{
		for (int nCntRank2 = 0; nCntRank2 < MAX_SCOREDIGIT; nCntRank2++)
		{
			//頂点座標
			pVtx[0].pos = D3DXVECTOR3(g_aRank[nCntRank][nCntRank2].pos.x - RANK_X / 2, g_aRank[nCntRank][nCntRank2].pos.y - RANK_X / 2, g_aRank[nCntRank][nCntRank2].pos.z);
			pVtx[1].pos = D3DXVECTOR3(g_aRank[nCntRank][nCntRank2].pos.x + RANK_X / 2, g_aRank[nCntRank][nCntRank2].pos.y - RANK_X / 2, g_aRank[nCntRank][nCntRank2].pos.z);
			pVtx[2].pos = D3DXVECTOR3(g_aRank[nCntRank][nCntRank2].pos.x - RANK_X / 2, g_aRank[nCntRank][nCntRank2].pos.y + RANK_X / 2, g_aRank[nCntRank][nCntRank2].pos.z);
			pVtx[3].pos = D3DXVECTOR3(g_aRank[nCntRank][nCntRank2].pos.x + RANK_X / 2, g_aRank[nCntRank][nCntRank2].pos.y + RANK_X / 2, g_aRank[nCntRank][nCntRank2].pos.z);

			pVtx[0].rhw = 1.0f;
			pVtx[1].rhw = 1.0f;
			pVtx[2].rhw = 1.0f;
			pVtx[3].rhw = 1.0f;

			pVtx[0].col = D3DXCOLOR(255.0f, 255.0f, 255.0f, 255.0f);
			pVtx[1].col = D3DXCOLOR(255.0f, 255.0f, 255.0f, 255.0f);
			pVtx[2].col = D3DXCOLOR(255.0f, 255.0f, 255.0f, 255.0f);
			pVtx[3].col = D3DXCOLOR(255.0f, 255.0f, 255.0f, 255.0f);

			pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
			pVtx[1].tex = D3DXVECTOR2(0.1f, 0.0f);
			pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
			pVtx[3].tex = D3DXVECTOR2(0.1f, 1.0f);

			pVtx += 4;
		}
	}
	//頂点バッファをアンロックする
	g_pVtxBuffRank->Unlock();

	if (GetMode2() == MODE_ES_STAGE03)
	{
		//ファイル開く
		pFile = fopen("es_rank.bin", "rb");
		//なんか入ってたら
		if (pFile != NULL)
		{
			for (int nCntRank = 0; nCntRank < MAX_RANK; nCntRank++)
			{
				//ランキング入手
				fscanf(pFile, "%d\n", &g_nRankScore[nCntRank]);
			}
			//閉じる
			fclose(pFile);
		}
		else
		{
			printf("読み取れないわ");
		}
		SetLetter(D3DXVECTOR3(SCREEN_WIDTH / 2, 0.0f + TETTER_Y, 0.0f), 0);
	}
	else if (GetMode2() == MODE_NO_STAGE04)
	{
		//ファイル開く
		pFile = fopen("no_rank.bin", "rb");
		//なんか入ってたら
		if (pFile != NULL)
		{
			for (int nCntRank = 0; nCntRank < MAX_RANK; nCntRank++)
			{
				//ランキング入手
				fscanf(pFile, "%d\n", &g_nRankScore[nCntRank]);
			}
			//閉じる
			fclose(pFile);
		}
		else
		{
			printf("読み取れないわ");
		}
		SetLetter(D3DXVECTOR3(SCREEN_WIDTH / 2, 0.0f + TETTER_Y, 0.0f), 1);
	}
	else if (GetMode2() == MODE_HD_STAGE05)
	{
		//ファイル開く
		pFile = fopen("hd_rank.bin", "rb");
		//なんか入ってたら
		if (pFile != NULL)
		{
			for (int nCntRank = 0; nCntRank < MAX_RANK; nCntRank++)
			{
				//ランキング入手
				fscanf(pFile, "%d\n", &g_nRankScore[nCntRank]);
			}
			//閉じる
			fclose(pFile);
		}
		else
		{
			printf("読み取れないわ");
		}
		SetLetter(D3DXVECTOR3(SCREEN_WIDTH / 2, 0.0f + TETTER_Y, 0.0f), 2);
	}
	return S_OK;
}

//---------------------------
//終了処理
//---------------------------
void UninitRank(void)
{
	UninitLetter();
	g_nCnt = 0;
	//テクスチャの破棄
	if (g_apTextureRank != NULL)
	{
		g_apTextureRank->Release();
		g_apTextureRank = NULL;
	}

	//頂点バッファの破棄
	if (g_pVtxBuffRank != NULL)
	{
		g_pVtxBuffRank->Release();
		g_pVtxBuffRank = NULL;
	}
}

//---------------------------
//更新処理
//---------------------------
void UpdateRank(void)
{
	UpdateLetter();
	VERTEX_2D	*pVtx;						//頂点情報へのポインタ
	FILE		*pFile;						//ファイル開く
	LETTER		*pLetter;					//レベル文字
	int			aNumber[MAX_SCOREDIGIT];	//スコア計算
	int			nSubdata;					//敗者

	pLetter = GetLetter();				//情報の取得

	if (g_bUse == true)
	{
		g_nRankScore[3] = GetScore();	//けつに自分のスコア
	}

	//頂点バッファをロックし、頂点データへのポインタを取得
	g_pVtxBuffRank->Lock(0, 0, (void**)&pVtx, 0);

	if (GetMode2() == MODE_TITLE)
	{
		g_nCnt++;
		if (g_nCnt <= 720 && g_nCnt >= 0)
		{
			for (int nCnt = 0; nCnt < MAX_LEVEL; nCnt++, pLetter++)
			{
				if (pLetter->nType == 2)
				{
					pLetter->nUse = false;
				}
			}
			//ファイル開く
			pFile = fopen("es_rank.bin", "rb");
			//なんか入ってたら
			if (pFile != NULL)
			{
				for (int nCntRank = 0; nCntRank < MAX_RANK; nCntRank++)
				{
					//ランキング入手
					fscanf(pFile, "%d\n", &g_nRankScore[nCntRank]);
				}
				//閉じる
				fclose(pFile);
			}
			else
			{
				printf("読み取れないわ");
			}
			SetLetter(D3DXVECTOR3(SCREEN_WIDTH / 2, 0.0f + TETTER_Y, 0.0f), 0);
		}
		else if (g_nCnt >= 720 && g_nCnt <= 1440)
		{
			for (int nCnt = 0; nCnt < MAX_LEVEL; nCnt++, pLetter++)
			{
				if (pLetter->nType == 0)
				{
					pLetter->nUse = false;
				}
			}
			pLetter -= MAX_LEVEL;
			//ファイル開く
			pFile = fopen("no_rank.bin", "rb");
			//なんか入ってたら
			if (pFile != NULL)
			{
				for (int nCntRank = 0; nCntRank < MAX_RANK; nCntRank++)
				{
					//ランキング入手
					fscanf(pFile, "%d\n", &g_nRankScore[nCntRank]);
				}
				//閉じる
				fclose(pFile);
			}
			else
			{
				printf("読み取れないわ");
			}
			SetLetter(D3DXVECTOR3(SCREEN_WIDTH / 2, 0.0f + TETTER_Y, 0.0f), 1);
		}
		else if (g_nCnt >= 1440 && g_nCnt <= 1584)
		{
			for (int nCnt = 0; nCnt < MAX_LEVEL; nCnt++, pLetter++)
			{
				if (pLetter->nType == 1)
				{
					pLetter->nUse = false;
				}
			}
			pLetter -= MAX_LEVEL;
			//ファイル開く
			pFile = fopen("hd_rank.bin", "rb");
			//なんか入ってたら
			if (pFile != NULL)
			{
				for (int nCntRank = 0; nCntRank < MAX_RANK; nCntRank++)
				{
					//ランキング入手
					fscanf(pFile, "%d\n", &g_nRankScore[nCntRank]);
				}
				//閉じる
				fclose(pFile);
			}
			else
			{
				printf("読み取れないわ");
			}
			SetLetter(D3DXVECTOR3(SCREEN_WIDTH / 2, 0.0f + TETTER_Y, 0.0f), 2);
		}
	}
	//リザルト画面
	if (GetMode() == MODE_RESULT)
	{
		for (int nRank = 0; nRank < MAX_RANK; nRank++)
		{
			for (int nRank = 0; nRank < MAX_RANK; nRank++)
			{
				if (g_nRankScore[nRank] < g_nRankScore[nRank + 1])
				{
					nSubdata = g_nRankScore[nRank];
					g_nRankScore[nRank] = g_nRankScore[nRank + 1];
					g_nRankScore[nRank + 1] = nSubdata;
				}
			}
		}
		for (int nCntRank = 0; nCntRank < MAX_RANK; nCntRank++)
		{
			//スコア計算
			aNumber[0] = g_nRankScore[nCntRank] % 100000 / 10000;
			aNumber[1] = g_nRankScore[nCntRank] % 10000 / 1000;
			aNumber[2] = g_nRankScore[nCntRank] % 1000 / 100;
			aNumber[3] = g_nRankScore[nCntRank] % 100 / 10;
			aNumber[4] = g_nRankScore[nCntRank] % 10 / 1;

			for (int nCntScore = 0; nCntScore < MAX_SCOREDIGIT; nCntScore++)
			{
				//テクスチャ座標
				pVtx[0].tex = D3DXVECTOR2((aNumber[nCntScore] * 0.1f) + 0.0f, 0.0f);
				pVtx[1].tex = D3DXVECTOR2((aNumber[nCntScore] * 0.1f) + 0.1f, 0.0f);
				pVtx[2].tex = D3DXVECTOR2((aNumber[nCntScore] * 0.1f) + 0.0f, 1.0f);
				pVtx[3].tex = D3DXVECTOR2((aNumber[nCntScore] * 0.1f) + 0.1f, 1.0f);

				pVtx += 4;
			}
		}
	}
	//頂点バッファをアンロックする
	g_pVtxBuffRank->Unlock();

	if (GetMode2() == MODE_ES_STAGE03)
	{
		if (g_bUse == true)
		{
			//ファイル開く
			pFile = fopen("es_rank.bin", "wb");
			//なんか入ってたら
			if (pFile != NULL)
			{
				for (int nCntRank = 0; nCntRank < MAX_RANK; nCntRank++)
				{
					//ランキング保存
					fprintf(pFile, "%d\n", g_nRankScore[nCntRank]);
				}
				//閉じる
				fclose(pFile);
				//一回だけ保存
				g_bUse = false;
			}
			else
			{
				printf("読み取れないわ");
			}
		}
	}
	else if (GetMode2() == MODE_NO_STAGE04)
	{
		if (g_bUse == true)
		{
			//ファイル開く
			pFile = fopen("no_rank.bin", "wb");
			//なんか入ってたら
			if (pFile != NULL)
			{
				for (int nCntRank = 0; nCntRank < MAX_RANK; nCntRank++)
				{
					//ランキング保存
					fprintf(pFile, "%d\n", g_nRankScore[nCntRank]);
				}
				//閉じる
				fclose(pFile);
				//一回だけ保存
				g_bUse = false;
			}
			else
			{
				printf("読み取れないわ");
			}
		}
	}
	else if (GetMode2() == MODE_HD_STAGE05)
	{
		if (g_bUse == true)
		{
			//ファイル開く
			pFile = fopen("hd_rank.bin", "wb");
			//なんか入ってたら
			if (pFile != NULL)
			{
				for (int nCntRank = 0; nCntRank < MAX_RANK; nCntRank++)
				{
					//ランキング保存
					fprintf(pFile, "%d\n", g_nRankScore[nCntRank]);
				}
				//閉じる
				fclose(pFile);
				//一回だけ保存
				g_bUse = false;
			}
			else
			{
				printf("読み取れないわ");
			}
		}
	}
}

//---------------------------
//描画処理
//---------------------------
void DrawRank(void)
{
	DrawLetter();
	LPDIRECT3DDEVICE9	pDevice;	//デバイスのポインタ
	int					nNum = 0;

	pDevice = GetDevice();		//デバイスを取得する
	//頂点バッファをデバイスのデータストリームに設定
	pDevice->SetStreamSource(	0,
								g_pVtxBuffRank,
								0,
								sizeof(VERTEX_2D));
	pDevice->SetFVF(FVF_VERTEX_2D); //頂点フォーマットの設定

	for (int nCntRank = 0; nCntRank < MAX_RANK; nCntRank++)
	{
		for (int nCntRank2 = 0; nCntRank2 < MAX_SCOREDIGIT; nCntRank2++)
		{
			//テクスチャ
			pDevice->SetTexture(0, g_apTextureRank);
			//ポリゴンの描画
			pDevice->DrawPrimitive(	D3DPT_TRIANGLESTRIP, //プリミティブの種類
									nNum * 4,			 //描画を開始する頂点のインデックス
									2);
			nNum++;
		}
	}
}