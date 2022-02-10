//=============================================================================
//
// マズルフラッシュ処理 [gunfire.cpp]
// Author : 羽鳥太一
//
//=============================================================================
//=============================================================================
// インクルード
//=============================================================================
#include "gunfire.h"
#include "renderer.h"
#include "manager.h"

//=============================================================================
// デフォルトコンストラクタ
//=============================================================================
CGunFire::CGunFire()
{

}

//=============================================================================
// デフォルトデストラクタ
//=============================================================================
CGunFire::~CGunFire()
{

}

//=============================================================================
// ポリゴンの初期化処理
//=============================================================================
HRESULT CGunFire::Init(void)
{
	LPDIRECT3DDEVICE9 pDevice; //デバイスのポインタ
	pDevice = CManager::GetRenderer()->GetDevice();	//デバイスを取得する

	//テクスチャの設定
	CBilboard::SetTexture(m_Type);

	//頂点バッファの取得
	LPDIRECT3DVERTEXBUFFER9 *ppVtxBuff = CBilboard::GetVtxBuff();

	int nNumVtx = CBilboard::GetNumVtx();	//頂点数の取得
	int nNumIdx = CBilboard::GetNumIdx();	//インデックス数の取得

	// 頂点バッファの生成
	if (*ppVtxBuff == NULL)
	{
		pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * nNumVtx,
									D3DUSAGE_WRITEONLY,
									FVF_VERTEX_3D,
									D3DPOOL_MANAGED,
									ppVtxBuff,
									NULL);
	}

	// 頂点バッファの設定
	if (*ppVtxBuff != NULL)
	{
		VERTEX_3D *pVtx;	// 頂点バッファのポインタ

		// 頂点バッファをロック
		(*ppVtxBuff)->Lock(0, 0, (void**)&pVtx, 0);

		// 頂点座標の設定
		pVtx[0].pos = D3DXVECTOR3(-m_Size.x, -m_Size.y, m_Size.z);
		pVtx[1].pos = D3DXVECTOR3(m_Size.x, -m_Size.y, m_Size.z);
		pVtx[2].pos = D3DXVECTOR3(-m_Size.x, m_Size.y, -m_Size.z);
		pVtx[3].pos = D3DXVECTOR3(m_Size.x, m_Size.y, -m_Size.z);

		pVtx[0].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
		pVtx[1].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
		pVtx[2].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
		pVtx[3].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);

		pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

		pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
		pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
		pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

		// 頂点バッファをアンロックする
		(*ppVtxBuff)->Unlock();
	}

	// インデックスバッファのの取得
	LPDIRECT3DINDEXBUFFER9 *ppIdxBuff = CBilboard::GetIdxBuff();

	// インデックスバッファの生成
	if (*ppIdxBuff == NULL)
	{
		pDevice->CreateIndexBuffer(	sizeof(WORD) * nNumIdx,
									D3DUSAGE_WRITEONLY,
									D3DFMT_INDEX16,
									D3DPOOL_MANAGED,
									ppIdxBuff,
									NULL);
	}

	// インデックスバッファの設定
	if (*ppIdxBuff != NULL)
	{
		WORD *pIdx;	// インデックス情報へのポインタ

		// インデックスバッファをロックし、番号データへのポインタを取得
		(*ppIdxBuff)->Lock(0, 0, (void**)&pIdx, 0);

		// 番号データ設定
		pIdx[0] = 0;
		pIdx[1] = 1;
		pIdx[2] = 2;
		pIdx[3] = 3;

		// インデックスバッファをアンロックする
		(*ppIdxBuff)->Unlock();
	}

	CBilboard::Init();

	return S_OK;
}

//=============================================================================
// ポリゴンの終了処理
//=============================================================================
void CGunFire::Uninit(void)
{
	CBilboard::Uninit();
}

//=============================================================================
// ポリゴンの更新処理
//=============================================================================
void CGunFire::Update(void)
{
	m_nClearCnt++;
	if (m_nClearCnt >= (FPS / 10))
	{
		Uninit();
	}
}

//=============================================================================
// ポリゴンの描画処理
//=============================================================================
void CGunFire::Draw(void)
{
	CBilboard::Draw();
}

//=============================================================================
// 生成
//=============================================================================
CGunFire *CGunFire::Create(D3DXVECTOR3 pos, D3DXVECTOR3 size, D3DXVECTOR3 scale, string type)
{
	CGunFire *pFire;
	pFire = new CGunFire;
	if (pFire != NULL)
	{
		pFire->m_Type = type;
		pFire->m_Size = size;
		pFire->SetPos(pos);
		pFire->SetScale(scale);
		pFire->SetNumVtx(4);
		pFire->SetNumIdx(4);
		pFire->Init();
	}

	return pFire;
}