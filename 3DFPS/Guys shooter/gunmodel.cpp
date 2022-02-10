//---------------------------
//インクルードファイル
//---------------------------
#include "gunmodel.h"
#include "guninfo.h"

//---------------------------
//グローバル変数
//---------------------------
LPDIRECT3DTEXTURE9		g_apTextureGunmodel[MAX_GUN_MODEL][MAX_GUN_TEX] = {};	//テクスチャのポインタ
Gunmodel				g_aGunmodel[MAX_GUN_MODEL];	//モデルの構造体
bool g_CollisionGun = true;

//---------------------------
//初期化処理
//---------------------------
HRESULT InitGunModel(void)
{
	LPDIRECT3DDEVICE9	pDevice;	//デバイスへのポインタ

	pDevice = GetDevice();			//デバイスの取得

	for (int nCntGun = 0; nCntGun < MAX_GUN_MODEL; nCntGun++)
	{
		//位置向き初期化
		g_aGunmodel[nCntGun].pos = (D3DXVECTOR3(0.0f, 0.0f, 0.0f));
		g_aGunmodel[nCntGun].rot = (D3DXVECTOR3(0.0f, 0.0f, 0.0f));
		g_aGunmodel[nCntGun].vtxMax = (D3DXVECTOR3(-1000000.0f, -1000000.0f, -1000000.0f));
		g_aGunmodel[nCntGun].vtxMin = (D3DXVECTOR3(1000000.0f, 1000000.0f, 1000000.0f));
		g_aGunmodel[nCntGun].pMesh = {};
		g_aGunmodel[nCntGun].pBuffMat = {};
		g_aGunmodel[nCntGun].bUse = false;
	}
	return S_OK;
}

//---------------------------
//終了処理
//---------------------------
void UninitGunModel(void)
{
	for (int nCntGun = 0; nCntGun < MAX_GUN_MODEL; nCntGun++)
	{
		//---------------------------
		//メッシュ破棄
		//---------------------------
		if (g_aGunmodel[nCntGun].pMesh != NULL)
		{
			g_aGunmodel[nCntGun].pMesh->Release();
			g_aGunmodel[nCntGun].pMesh = NULL;
		}

		//---------------------------
		//マテリアル破棄
		//---------------------------
		if (g_aGunmodel[nCntGun].pBuffMat != NULL)
		{
			g_aGunmodel[nCntGun].pBuffMat->Release();
			g_aGunmodel[nCntGun].pBuffMat = NULL;
		}
	}
}

//---------------------------
//更新処理
//---------------------------
void UpdateGunModel(void)
{

}

//---------------------------
//描画処理
//---------------------------
void DrawGunModel(void)
{
	LPDIRECT3DDEVICE9	pDevice;			//デバイスのポインタ

	pDevice = GetDevice();					//デバイスを取得する

	//---------------------------
	//マトリックスの設定
	//---------------------------
	D3DXMATRIX			mtxRot, mtxTrans;	//計算用マトリックス

	for (int nCntGun = 0; nCntGun < MAX_GUN_MODEL; nCntGun++)
	{
		if (g_aGunmodel[nCntGun].bUse == true)
		{
			//αテスト
			pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, TRUE);
			pDevice->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_GREATER);
			pDevice->SetRenderState(D3DRS_ALPHAREF, 0);

			D3DXMatrixIdentity(&g_aGunmodel[nCntGun].mtxWold);	//マトリックス初期化

			//向きの設定
			D3DXMatrixRotationYawPitchRoll(	&mtxRot,
											g_aGunmodel[nCntGun].rot.y,
											g_aGunmodel[nCntGun].rot.x,
											g_aGunmodel[nCntGun].rot.z);

			D3DXMatrixMultiply(	&g_aGunmodel[nCntGun].mtxWold,
								&g_aGunmodel[nCntGun].mtxWold,
								&mtxRot);
			//位置
			D3DXMatrixTranslation(	&mtxTrans,
									g_aGunmodel[nCntGun].pos.x,
									g_aGunmodel[nCntGun].pos.y,
									g_aGunmodel[nCntGun].pos.z);

			D3DXMatrixMultiply(	&g_aGunmodel[nCntGun].mtxWold,
								&g_aGunmodel[nCntGun].mtxWold,
								&mtxTrans);
			//マトリックスの設定
			pDevice->SetTransform(	D3DTS_WORLD,
									&g_aGunmodel[nCntGun].mtxWold);
			//---------------------------
			//描画処理
			//---------------------------
			D3DMATERIAL9		matDef;				//マテリアルの一時保存
			D3DXMATERIAL		*pMat;				//マテリアルデータのポインタ

			//現在のマテリアルを取得
			pDevice->GetMaterial(&matDef);

			//マテリアルデータのポインタ
			pMat = (D3DXMATERIAL*)g_aGunmodel[nCntGun].pBuffMat->GetBufferPointer();

			for (int nCntMat = 0; nCntMat < (int)g_aGunmodel[nCntGun].pnNumMat; nCntMat++)
			{
				//マテリアルの設定
				pDevice->SetMaterial(&pMat[nCntMat].MatD3D);

				//テクスチャの設定
				pDevice->SetTexture(	0,
										g_apTextureGunmodel[nCntGun][nCntMat]);

				//モデルパーツの描画
				g_aGunmodel[nCntGun].pMesh->DrawSubset(nCntMat);
			}
			//一時保存してたやつをもどす
			pDevice->SetMaterial(&matDef);

			//αテスト
			pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, FALSE);
			pDevice->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_ALWAYS);
			pDevice->SetRenderState(D3DRS_ALPHAREF, 0x00);
		}
	}
}

//---------------------------
//セット
//---------------------------
int SetGunModel(D3DXVECTOR3 pos, D3DXVECTOR3 rot, Guntype Type)
{
	LPDIRECT3DDEVICE9	pDevice;	//デバイスへのポインタ
	int nIdx = -1;

	pDevice = GetDevice();			//デバイスの取得

	for (int nCntGun = 0; nCntGun < MAX_GUN_MODEL; nCntGun++)
	{
		if (g_aGunmodel[nCntGun].bUse == false)
		{
			g_aGunmodel[nCntGun].pos = pos;
			g_aGunmodel[nCntGun].pos.y = pos.y + 15.0f;
			g_aGunmodel[nCntGun].rot = rot;
			g_aGunmodel[nCntGun].aType = Type;

			if (g_aGunmodel[nCntGun].aType == HANDGUN)
			{
				//---------------------------
				//Xファイルの読み込み
				//---------------------------
				D3DXLoadMeshFromX(	"data/Model/Gun/handgun_00.x",
									D3DXMESH_SYSTEMMEM,
									pDevice,
									NULL,
									&g_aGunmodel[nCntGun].pBuffMat,
									NULL,
									&g_aGunmodel[nCntGun].pnNumMat,
									&g_aGunmodel[nCntGun].pMesh);
			}
			else if (g_aGunmodel[nCntGun].aType == ASULTRIFLE)
			{
				//---------------------------
				//Xファイルの読み込み
				//---------------------------
				D3DXLoadMeshFromX(	"data/Model/Gun/asultrifle_00.x",
									D3DXMESH_SYSTEMMEM,
									pDevice,
									NULL,
									&g_aGunmodel[nCntGun].pBuffMat,
									NULL,
									&g_aGunmodel[nCntGun].pnNumMat,
									&g_aGunmodel[nCntGun].pMesh);
			}
			//---------------------------
			//テクスチャの抜き出し
			//---------------------------
			D3DXMATERIAL *pMat;	//マテリアルのポインタ

			//マテリアル情報のポインタ
			pMat = (D3DXMATERIAL*)g_aGunmodel[nCntGun].pBuffMat->GetBufferPointer();

			for (int nCntMat = 0; nCntMat < (int)g_aGunmodel[nCntGun].pnNumMat; nCntMat++)
			{
				if (pMat[nCntMat].pTextureFilename != NULL)
				{
					//テクスチャの読み込み
					D3DXCreateTextureFromFile(	pDevice,
												pMat[nCntMat].pTextureFilename,			//テクスチャ
												&g_apTextureGunmodel[nCntGun][nCntMat]);
				}
			}

			//---------------------------
			//頂点座標の抜き出し
			//---------------------------
			int nNumVtx;	//頂点数
			DWORD sizeFVF;	//頂点フォーマットのサイズ
			BYTE *pVtxBuff;	//頂点バッファのポインタ

			//頂点数を取得
			nNumVtx = g_aGunmodel[nCntGun].pMesh->GetNumVertices();

			//頂点フォーマットのサイズを取得
			sizeFVF = D3DXGetFVFVertexSize(g_aGunmodel[nCntGun].pMesh->GetFVF());

			//頂点バッファのロック
			g_aGunmodel[nCntGun].pMesh->LockVertexBuffer(D3DLOCK_READONLY, (void**)&pVtxBuff);

			for (int nCntVtx = 0; nCntVtx < nNumVtx; nCntVtx++)
			{
				D3DXVECTOR3 vtx = *(D3DXVECTOR3*)pVtxBuff;	//頂点座標の代入

				//頂点数を比較して最小値、最大値を抜く
				//X
				if (g_aGunmodel[nCntGun].vtxMax.x <= vtx.x)
				{
					g_aGunmodel[nCntGun].vtxMax.x = vtx.x;
				}
				if (g_aGunmodel[nCntGun].vtxMin.x >= vtx.x)
				{
					g_aGunmodel[nCntGun].vtxMin.x = vtx.x;
				}
				//Y
				if (g_aGunmodel[nCntGun].vtxMax.y <= vtx.y)
				{
					g_aGunmodel[nCntGun].vtxMax.y = vtx.y;
				}
				if (g_aGunmodel[nCntGun].vtxMin.y >= vtx.y)
				{
					g_aGunmodel[nCntGun].vtxMin.y = vtx.y;
				}
				//Z
				if (g_aGunmodel[nCntGun].vtxMax.z <= vtx.z)
				{
					g_aGunmodel[nCntGun].vtxMax.z = vtx.z;
				}
				if (g_aGunmodel[nCntGun].vtxMin.z >= vtx.z)
				{
					g_aGunmodel[nCntGun].vtxMin.z = vtx.z;
				}

				pVtxBuff += sizeFVF;	//頂点を進める
			}
			//頂点バッファをアンロック
			g_aGunmodel[nCntGun].pMesh->UnlockVertexBuffer();

			g_aGunmodel[nCntGun].bUse = true;
			nIdx = nCntGun;
			return nIdx;
			break;
		}
	}
}

//---------------------------
//セット
//---------------------------
Guntype SetPointGunModel(D3DXVECTOR3 pos, D3DXVECTOR3 rot, int nIdx)
{
	g_aGunmodel[nIdx].rot = rot;
	g_aGunmodel[nIdx].rot.x *= -1;

	if (g_aGunmodel[nIdx].aType == HANDGUN)
	{
		g_aGunmodel[nIdx].pos.x = pos.x + cosf(g_aGunmodel[nIdx].rot.y) * 20.0f;
		g_aGunmodel[nIdx].pos.y = pos.y + 15.0f;								
		g_aGunmodel[nIdx].pos.z = pos.z - sinf(g_aGunmodel[nIdx].rot.y) * 20.0f;

		g_aGunmodel[nIdx].pos.x = g_aGunmodel[nIdx].pos.x + cosf(g_aGunmodel[nIdx].rot.y - D3DX_PI / 2) * 20.0f;
		g_aGunmodel[nIdx].pos.z = g_aGunmodel[nIdx].pos.z - sinf(g_aGunmodel[nIdx].rot.y - D3DX_PI / 2) * 20.0f;

		if (g_CollisionGun == true)
		{
			SetGunType(GUNINFO_TYPE_00);
			g_CollisionGun = false;
		}
	}
	else if (g_aGunmodel[nIdx].aType == ASULTRIFLE)
	{
		g_aGunmodel[nIdx].pos.x = pos.x + cosf(g_aGunmodel[nIdx].rot.y) * 20.0f;
		g_aGunmodel[nIdx].pos.y = pos.y + 15.0f;
		g_aGunmodel[nIdx].pos.z = pos.z - sinf(g_aGunmodel[nIdx].rot.y) * 20.0f;

		g_aGunmodel[nIdx].pos.x = g_aGunmodel[nIdx].pos.x + cosf(g_aGunmodel[nIdx].rot.y - D3DX_PI / 2) * 15.0f;
		g_aGunmodel[nIdx].pos.z = g_aGunmodel[nIdx].pos.z - sinf(g_aGunmodel[nIdx].rot.y - D3DX_PI / 2) * 15.0f;

		if (g_CollisionGun == true)
		{
			SetGunType(GUNINFO_TYPE_01);
			g_CollisionGun = false;
		}
	}
	return g_aGunmodel[nIdx].aType;
}

bool CollisionGunModel(D3DXVECTOR3 *pos, D3DXVECTOR3 *posold, D3DXVECTOR3 *move, float fWidth, float fHeight, int *nIdx)
{
	int nIndx = *nIdx;
	bool bCollision = false;
	D3DXVECTOR3 posdfrc;
	D3DXVECTOR3 efectmove;
	float fAngle;
	float fSpeed = 2.5f;
	float nGuysR = 25.0f;
	float fposdfrcX;

	posdfrc = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	for (int nCntGun = 0; nCntGun < MAX_GUN_MODEL; nCntGun++)
	{
		if (g_aGunmodel[nCntGun].bUse == true)
		{
			if (nCntGun != nIndx)
			{
				g_aGunmodel[nCntGun].nCnt++;

				posdfrc.x = g_aGunmodel[nCntGun].pos.x - pos->x;
				posdfrc.z = g_aGunmodel[nCntGun].pos.z - pos->z;

				posdfrc.x = posdfrc.x * posdfrc.x;
				posdfrc.z = posdfrc.z * posdfrc.z;

				fposdfrcX = posdfrc.x + posdfrc.z;

				fposdfrcX = sqrtf(fposdfrcX);

				if (g_aGunmodel[nCntGun].pos.y <= pos->y + fHeight / 2 &&
					g_aGunmodel[nCntGun].pos.y + 5.0f >= pos->y - fHeight / 2 &&
					fposdfrcX < nGuysR)
				{
					*nIdx = nCntGun;
					g_aGunmodel[nIndx].bUse = false;
					g_CollisionGun = true;
					bCollision = true;
				}
				if (g_aGunmodel[nCntGun].nCnt > 1440)
				{
					g_aGunmodel[nCntGun].bUse = false;
					g_aGunmodel[nCntGun].nCnt = 0;
				}
			}
		}
	}
	return bCollision;
}