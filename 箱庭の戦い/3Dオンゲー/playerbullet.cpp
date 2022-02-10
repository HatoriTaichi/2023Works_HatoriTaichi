//=============================================================================
//
// 敵の弾処理 [enemybullet.cpp]
// Author : 羽鳥太一
//
//=============================================================================
//=============================================================================
// インクルード
//=============================================================================
#include "player.h"
#include "playerbullet.h"
#include "renderer.h"
#include "manager.h"
#include "texture.h"
#include "game.h"
#include "enemy.h"
#include "communicationdata.h"

//=============================================================================
// デフォルトコンストラクタ
//=============================================================================
CPlayerBullet::CPlayerBullet()
{
	m_Size = D3DXVECTOR3(0.0f, 0.0f, 0.0f);	// サイズ
	D3DXMatrixIdentity(&m_mtxWorld);
}

//=============================================================================
// デフォルトデストラクタ
//=============================================================================
CPlayerBullet::~CPlayerBullet()
{

}

//=============================================================================
// ポリゴンの初期化処理
//=============================================================================
HRESULT CPlayerBullet::Init(void)
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

		//頂点バッファをロック
		(*ppVtxBuff)->Lock(0, 0, (void**)&pVtx, 0);

		//頂点座標の設定
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

		//頂点バッファをアンロックする
		(*ppVtxBuff)->Unlock();
	}

	//インデックスバッファのの取得
	LPDIRECT3DINDEXBUFFER9 *ppIdxBuff = CBilboard::GetIdxBuff();

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

		//番号データ設定
		pIdx[0] = 0;
		pIdx[1] = 1;
		pIdx[2] = 2;
		pIdx[3] = 3;

		//インデックスバッファをアンロックする
		(*ppIdxBuff)->Unlock();
	}

	CBullet::Init();

	return S_OK;
}

//=============================================================================
// ポリゴンの終了処理
//=============================================================================
void CPlayerBullet::Uninit(void)
{
	CBullet::Uninit();
}

//=============================================================================
// ポリゴンの更新処理
//=============================================================================
void CPlayerBullet::Update(void)
{
	D3DXVECTOR3 Pos = CBullet::GetPos();
	CPlayer *pPlayer = CManager::GetGame()->GetPlayer();
	CEnemy *pEnemy = CManager::GetGame()->GetEnemy();
	CCommunicationData::COMMUNICATION_DATA *pData = pPlayer->GetCommuData();
	
	CBullet::Update();

	if (pEnemy->ToBulletCollision(Pos, m_Size.x, m_Size.y) == true)
	{
		Uninit();
		for (int nCnt = 0; nCnt < MAX_BULLET; nCnt++)
		{
			if (pData->Bullet[nCnt].bUse == true)
			{
				pData->Bullet[nCnt].bUse = false;
				break;
			}
		}
	}
}

//=============================================================================
// ポリゴンの描画処理
//=============================================================================
void CPlayerBullet::Draw(void)
{
	CBullet::Draw();
}

//=============================================================================
// 生成
//=============================================================================
CPlayerBullet *CPlayerBullet::Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot, D3DXVECTOR3 size, D3DXVECTOR3 scale, string type, float fMoveSpeed)
{
	CPlayerBullet *pPlayerBullet;
	pPlayerBullet = new CPlayerBullet;
	if (pPlayerBullet != NULL)
	{
		pPlayerBullet->m_Type = type;
		pPlayerBullet->m_Size = size;
		pPlayerBullet->m_fMoveSpeed = fMoveSpeed;
		pPlayerBullet->SetPos(pos);
		pPlayerBullet->SetRot(rot);
		pPlayerBullet->SetScale(scale);
		pPlayerBullet->SetNumVtx(4);
		pPlayerBullet->SetNumIdx(4);
		pPlayerBullet->Init();
	}
	return pPlayerBullet;
}