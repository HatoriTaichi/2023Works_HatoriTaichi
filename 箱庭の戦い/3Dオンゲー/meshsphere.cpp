//=============================================================================
//
// 3Dポリゴン処理 [floo.cpp]
// Author : 羽鳥太一
//
//=============================================================================
#include "meshsphere.h"
#include "manager.h"
#include "renderer.h"

//=============================================================================
// 静的メンバ変数宣言
//=============================================================================

//=============================================================================
// デフォルトコンストラクタ
//=============================================================================
CMeshsphere::CMeshsphere()
{
	int m_nXPoly = 0;
	int m_nZPoly = 0;
	int m_nXRadius = 0;
	D3DXMatrixIdentity(&m_mtxWorld);
}

//=============================================================================
// デストラクタ
//=============================================================================
CMeshsphere::~CMeshsphere()
{

}

//=============================================================================
// 初期化処理
//=============================================================================
HRESULT CMeshsphere::Init(void)
{
	LPDIRECT3DDEVICE9 pDevice; //デバイスのポインタ
	pDevice = CManager::GetRenderer()->GetDevice();	//デバイスを取得する

													//テクスチャの設定
	SetTexture(m_Type);

	//頂点バッファの取得
	LPDIRECT3DVERTEXBUFFER9* ppVtxBuff = GetVtxBuff();

	int nNumVtx = GetNumVtx();	//頂点数の取得
	int nNumIdx = GetNumIdx();	//インデックス数の取得

								//頂点バッファの生成
	if (*ppVtxBuff == NULL)
	{
		pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * nNumVtx,
									D3DUSAGE_WRITEONLY,
									FVF_VERTEX_3D,
									D3DPOOL_MANAGED,
									ppVtxBuff,
									NULL);
	}

	//頂点バッファの設定
	if (*ppVtxBuff != NULL)
	{
		VERTEX_3D *pVtx;	//頂点バッファのポインタ

							//頂点バッファをロックし、頂点データへのポインタを取得
		(*ppVtxBuff)->Lock(0, 0, (void**)&pVtx, 0);

		int nVtxNum = 0;
		for (int nCntY = 0; nCntY < m_nYPoly + 1; nCntY++)
		{
			for (int nCntX = 0; nCntX < m_nXPoly + 1; nCntX++, nVtxNum++)
			{
				pVtx[nVtxNum].pos = D3DXVECTOR3(cosf(D3DX_PI * 2 / m_nXPoly * nCntX) * sinf(D3DX_PI * 2 / m_nXPoly * nCntY + (D3DX_PI / 2)) * m_nRadius,
												sinf(D3DX_PI * 2 / m_nXPoly * nCntY) * m_nRadius,
												sinf(D3DX_PI * 2 / m_nXPoly * nCntX) * sinf(D3DX_PI * 2 / m_nXPoly * nCntY + (D3DX_PI / 2)) * m_nRadius);
				pVtx[nVtxNum].nor = D3DXVECTOR3(0.0f, -1.0f, 0.0f);
				pVtx[nVtxNum].col = D3DCOLOR_RGBA(255, 255, 255, 255);
				pVtx[nVtxNum].tex = D3DXVECTOR2((1.0f / m_nXPoly) * nCntX, (1.0f / m_nYPoly) * nCntY);
			}
		}
		nVtxNum = 0;
		//頂点バッファをアンロックする
		(*ppVtxBuff)->Unlock();
	}

	//インデックスバッファのの取得
	LPDIRECT3DINDEXBUFFER9* ppIdxBuff = GetIdxBuff();

	//インデックスバッファの生成
	if (*ppIdxBuff == NULL)
	{
		pDevice->CreateIndexBuffer( sizeof(WORD) * nNumIdx,
									D3DUSAGE_WRITEONLY,
									D3DFMT_INDEX16,
									D3DPOOL_MANAGED,
									ppIdxBuff,
									NULL);
	}
	//インデックスバッファの設定
	if (*ppIdxBuff != NULL)
	{
		WORD *pIdx;	//インデックス情報へのポインタ

					//インデックスバッファをロックし、番号データへのポインタを取得
		(*ppIdxBuff)->Lock(0, 0, (void**)&pIdx, 0);

		//角被さり以外の頂点
		for (int nCntZ = 0; nCntZ < m_nYPoly; nCntZ++)
		{
			for (int nCntX = 0; nCntX < m_nXPoly + 1; nCntX++)
			{
				pIdx[(nCntX * 2) + 0 + ((m_nXPoly + 2) * 2) * nCntZ] = ((m_nXPoly + 1) + nCntX) + ((m_nXPoly + 1) * nCntZ);
				pIdx[(nCntX * 2) + 1 + ((m_nXPoly + 2) * 2) * nCntZ] = (0 + nCntX) + ((m_nXPoly + 1) * nCntZ);
			}
		}
		//角被さりの頂点
		for (int nCntZ = 0; nCntZ < m_nYPoly - 1; nCntZ++)
		{
			pIdx[(((m_nXPoly + 1) * 2 + 0) * (nCntZ + 1)) + (2 * nCntZ)] = m_nXPoly + ((m_nXPoly + 1) * nCntZ);
			pIdx[(((m_nXPoly + 1) * 2 + 1) * (nCntZ + 1)) + (1 * nCntZ)] = (m_nXPoly * 2 + 2) + ((m_nXPoly + 1) * nCntZ);
		}

		//インデックスバッファをアンロックする
		(*ppIdxBuff)->Unlock();
	}

	CScene3D::Init();

	return S_OK;
}

//=============================================================================
// 終了処理
//=============================================================================
void CMeshsphere::Uninit(void)
{
	CScene3D::Uninit();
}

//=============================================================================
// 更新処理
//=============================================================================
void CMeshsphere::Update(void)
{
	CScene3D::Update();
}

//=============================================================================
// 描画処理
//=============================================================================
void CMeshsphere::Draw(void)
{
	CScene3D::Draw();
}

//=============================================================================
// 生成処理
//=============================================================================
CMeshsphere* CMeshsphere::Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot, int nPolyX, int nPolyY, int nRadius, string type)
{
	CMeshsphere* pSphere;
	pSphere = new CMeshsphere;
	if (pSphere != NULL)
	{
		pSphere->m_Type = type;
		pSphere->m_nXPoly = nPolyX;
		pSphere->m_nYPoly = nPolyY;
		pSphere->m_nRadius = nRadius;
		pSphere->SetPos(pos);
		pSphere->SetRot(rot);
		pSphere->SetNumVtx((nPolyX + 1) * (nPolyY + 1));
		pSphere->SetNumIdx((nPolyX + 1) * (nPolyY + 1) + (nPolyY - 1) * (nPolyX + 3));
		pSphere->Init();
	}

	return pSphere;
}