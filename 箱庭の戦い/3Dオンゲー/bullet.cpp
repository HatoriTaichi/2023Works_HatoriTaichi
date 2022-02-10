//=============================================================================
//
// 弾処理 [bullet.cpp]
// Author : 羽鳥太一
//
//=============================================================================
//=============================================================================
// インクルード
//=============================================================================
#include "bullet.h"
#include "mouseinput.h"
#include "manager.h"
#include "player.h"
#include "game.h"
#include "model.h"
#include "singlemodel.h"

//=============================================================================
// デフォルトコンストラクタ
//=============================================================================
CBullet::CBullet()
{

}

//=============================================================================
// デフォルトデストラクタ
//=============================================================================
CBullet::~CBullet()
{

}

//=============================================================================
// ポリゴンの初期化処理
//=============================================================================
HRESULT CBullet::Init(void)
{
	CBilboard::Init();

	return S_OK;
}

//=============================================================================
// ポリゴンの終了処理
//=============================================================================
void CBullet::Uninit(void)
{
	CBilboard::Uninit();
}

//=============================================================================
// ポリゴンの更新処理
//=============================================================================
void CBullet::Update(void)
{
	CMouse *pMouse = CManager::GetMouse();
	CPlayer *pPlayer = CManager::GetGame()->GetPlayer();
	D3DXVECTOR3 Pos = CBilboard::GetPos();
	D3DXVECTOR3 Rot = CBilboard::GetRot();
	D3DXVECTOR3 PlayerPos = pPlayer->GetPos();
	D3DXVECTOR3 PosOld;
	int nMaxModel = CManager::GetGame()->GetMaxModel();

	PosOld = Pos;

	m_fMove += m_fMoveSpeed;

	Pos.x += (sinf(Rot.y) * sinf(Rot.x)) * m_fMove;
	Pos.y +=  cosf(Rot.y)				 * m_fMove;
	Pos.z += (sinf(Rot.y) * cosf(Rot.x)) * m_fMove;

	CBilboard::SetPos(Pos);
	CBilboard::SetRot(Rot);

	CBilboard::Update();

	if (Pos.x >= 1000.0f)
	{
		Uninit();
	}
	else if (Pos.x <= -1000.0f)
	{
		Uninit();
	}

	if (Pos.y >= 1000.0f)
	{
		Uninit();
	}
	else if (Pos.y <= -1000.0f)
	{
		Uninit();
	}

	if (Pos.z >= 1000.0f)
	{
		Uninit();
	}
	else if (Pos.z <= -1000.0f)
	{
		Uninit();
	}

	for (int nCnt = 0; nCnt < nMaxModel; nCnt++)
	{
		CModel *pModel = CManager::GetGame()->GetModel(nCnt)->GetModel();
		if (pModel->BoxCollision(&Pos, PosOld) == true)
		{
			Uninit();
		}
	}
}

//=============================================================================
// ポリゴンの描画処理
//=============================================================================
void CBullet::Draw(void)
{
	CBilboard::Draw();
}