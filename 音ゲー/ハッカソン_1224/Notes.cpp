//=============================================================================
//
// 2Dポリゴン処理 [textureobj.cpp]
// Author : 羽鳥太一
//
//=============================================================================
//=============================================================================
// インクルード
//=============================================================================
#include "notes.h"
#include "manager.h"
#include "fade.h"
#include "mouseinput.h"
#include "fade.h"
#include "collision.h"
#include "enemy.h"

//=============================================================================
// デフォルトコンストラクタ
//=============================================================================
CNotes::CNotes()
{

}

//=============================================================================
// デフォルトデストラクタ
//=============================================================================
CNotes::~CNotes()
{

}

//=============================================================================
// ポリゴンの初期化
//=============================================================================
HRESULT CNotes::Init(void)
{
	CScene2D::SetTexType(m_TexType);
	CScene2D::Init();
	CScene2D::SetPos(m_Pos);
	CScene2D::SetSize(D3DXVECTOR3(m_Size.x, m_Size.y, 0.0f));

	return S_OK;
}

//=============================================================================
// ポリゴンの終了
//=============================================================================
void CNotes::Uninit(void)
{
	CScene2D::Uninit();
}

//=============================================================================
// ポリゴンの更新
//=============================================================================
void CNotes::Update(void)
{
	D3DXVECTOR3 Pos = CScene2D::GetPos();
	D3DXVECTOR2 Size = CScene2D::GetSize();

	Pos.y += 1.0f;

	CScene2D::SetPos(Pos);

	CScene2D::Update();
}

//=============================================================================
// ポリゴンの描画
//=============================================================================
void CNotes::Draw(void)
{
	CScene2D::Draw();
}

//=============================================================================
// インクルード
//=============================================================================
CNotes *CNotes::Create(D3DXVECTOR3 pos, D3DXVECTOR2 size, string Type)
{
	CNotes *pNotes = NULL;
	if (pNotes == NULL)
	{
		pNotes = new CNotes;
	}

	pNotes->m_Pos = pos;
	pNotes->m_Size = size;
	pNotes->m_TexType = Type;
	if (Type == "RIGHT_ARROW")
	{
		pNotes->m_pCollision = CCollision::Create(pos, D3DXVECTOR2(size.x * 2, size.y * 2), "RIGHT_ARROWFRAME", pNotes);
		pNotes->m_pEnemy = CEnemy::Create(D3DXVECTOR3(SCREEN_WIDTH, SCREEN_CENTER_Y, 0.0f), D3DXVECTOR3(50.0f, 50.0f, 0.0f), "ENEMY_LEFT");
	}
	else if (Type == "LEFT_ARROW")
	{
		pNotes->m_pCollision = CCollision::Create(pos, D3DXVECTOR2(size.x * 2, size.y * 2), "LEFT_ARROWFRAME", pNotes);
		pNotes->m_pEnemy = CEnemy::Create(D3DXVECTOR3(0.0f, SCREEN_CENTER_Y, 0.0f), D3DXVECTOR3(50.0f, 50.0f, 0.0f), "ENEMY_RIGHT");
	}
	else if (Type == "UP_ARROW")
	{
		pNotes->m_pCollision = CCollision::Create(pos, D3DXVECTOR2(size.x * 2, size.y * 2), "UP_ARROWFRAME", pNotes);
		pNotes->m_pEnemy = CEnemy::Create(D3DXVECTOR3(SCREEN_CENTER_X, 0.0f, 0.0f), D3DXVECTOR3(50.0f, 50.0f, 0.0f), "ENEMY_DOWN");
	}
	else if (Type == "DOWN_ARROW")
	{
		pNotes->m_pCollision = CCollision::Create(pos, D3DXVECTOR2(size.x * 2, size.y * 2), "DOWN_ARROWFRAME", pNotes);
		pNotes->m_pEnemy = CEnemy::Create(D3DXVECTOR3(SCREEN_CENTER_X, SCREEN_HEIGHT, 0.0f), D3DXVECTOR3(50.0f, 50.0f, 0.0f), "ENEMY_UP");
	}

	if (pNotes != NULL)
	{
		pNotes->Init();
	}
	return pNotes;
}