//=============================================================================
//
// 3Dポリゴン処理 [floo.cpp]
// Author : 羽鳥太一
//
//=============================================================================
#include "meshfloo.h"
#include "manager.h"
#include "renderer.h"

//=============================================================================
// 静的メンバ変数宣言
//=============================================================================

//=============================================================================
// デフォルトコンストラクタ
//=============================================================================
CMeshFloo::CMeshFloo()
{
	int m_nXPoly = 0;
	int m_nZPoly = 0;
	int m_nXRadius = 0;
	int m_nZRadius = 0;
	D3DXMatrixIdentity(&m_mtxWorld);
}

//=============================================================================
// デストラクタ
//=============================================================================
CMeshFloo::~CMeshFloo()
{

}

//=============================================================================
// 初期化処理
//=============================================================================
HRESULT CMeshFloo::Init(void)
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
		pDevice->CreateVertexBuffer(	sizeof(VERTEX_3D) * nNumVtx,
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
		for (int nCntZ = 0; nCntZ < m_nZPoly + 1; nCntZ++)
		{
			for (int nCntX = 0; nCntX < m_nXPoly + 1; nCntX++, nVtxNum++)
			{
				pVtx[nVtxNum].pos = D3DXVECTOR3(-m_nXRadius + (((m_nXRadius * 2) / m_nXPoly) * nCntX), 0.0f, m_nZRadius - (((m_nZRadius * 2) / m_nZPoly) * nCntZ));
				pVtx[nVtxNum].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
				pVtx[nVtxNum].col = D3DCOLOR_RGBA(255, 255, 255, 255);
				pVtx[nVtxNum].tex = D3DXVECTOR2(0.0f + (1.0f * nCntX), 0.0f + (1.0f * nCntZ));
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
		pDevice->CreateIndexBuffer(	sizeof(WORD) * nNumIdx,
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
		for (int nCntZ = 0; nCntZ < m_nZPoly; nCntZ++)
		{
			for (int nCntX = 0; nCntX < m_nXPoly + 1; nCntX++)
			{
				pIdx[(nCntX * 2) + 0 + ((m_nXPoly + 2) * 2) * nCntZ] = ((m_nXPoly + 1) + nCntX) + ((m_nXPoly + 1) * nCntZ);
				pIdx[(nCntX * 2) + 1 + ((m_nXPoly + 2) * 2) * nCntZ] = (0 + nCntX) + ((m_nXPoly + 1) * nCntZ);
			}
		}
		//角被さりの頂点
		for (int nCntZ = 0; nCntZ < m_nZPoly - 1; nCntZ++)
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
void CMeshFloo::Uninit(void)
{
	CScene3D::Uninit();
}

//=============================================================================
// 更新処理
//=============================================================================
void CMeshFloo::Update(void)
{
	if (m_Type == "SEE")
	{
		D3DXVECTOR3 Pos = GetPos();
		m_nMoveReversCnt++;

		if (m_nMoveReversCnt >= (FPS * 5))
		{
			if (m_bRevers == false)
			{
				m_bRevers = true;
			}
			else
			{
				m_bRevers = false;
			}
			m_nMoveReversCnt = 0;
		}

		if (m_bRevers == true)
		{
			Pos.x += 0.1f;
			Pos.z += 0.5f;
		}
		else if (m_bRevers == false)
		{
			Pos.x -= 0.1f;
			Pos.z -= 0.5f;
		}
		SetPos(Pos);
	}
	CScene3D::Update();
}

//=============================================================================
// 描画処理
//=============================================================================
void CMeshFloo::Draw(void)
{
	CScene3D::Draw();
}

//=============================================================================
// 生成処理
//=============================================================================
CMeshFloo* CMeshFloo::Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot, int nPolyX, int nPolyZ, int nRadiusX, int nRadiusZ, string type)
{
	CMeshFloo* pFloo;
	pFloo = new CMeshFloo;
	if (pFloo != NULL)
	{
		pFloo->m_Type = type;
		pFloo->m_nXPoly = nPolyX;
		pFloo->m_nZPoly = nPolyZ;
		pFloo->m_nXRadius = nRadiusX;
		pFloo->m_nZRadius = nRadiusZ;
		pFloo->SetPos(pos);
		pFloo->SetRot(rot);
		pFloo->SetNumVtx((nPolyX + 1) * (nPolyZ + 1));
		pFloo->SetNumIdx((nPolyX + 1) * (nPolyZ + 1) + (nPolyZ - 1) * (nPolyX + 3));
		pFloo->Init();
	}

	return pFloo;
}