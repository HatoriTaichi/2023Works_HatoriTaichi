//=============================================================================
//
// 入力処理 [input.cpp]
// Author : 羽鳥太一
//
//=============================================================================
//=============================================================================
// インクルード
//=============================================================================
#include "player.h"
#include "manager.h"
#include "keyinput.h"

//=============================================================================
// デフォルトコンストラクタ
//=============================================================================
CPlayer::CPlayer()
{

}

//=============================================================================
// デフォルトデストラクタ
//=============================================================================
CPlayer::~CPlayer()
{

}

//=============================================================================
// 初期化
//=============================================================================
HRESULT CPlayer::Init(void)
{
	CScene2D::SetTexType(m_Type);
	CScene2D::Init();
	CScene2D::SetPos(m_Pos);
	CScene2D::SetSize(m_Size);

	return S_OK;
}

//=============================================================================
// 終了
//=============================================================================
void CPlayer::Uninit(void)
{
	CScene2D::Uninit();
}

//=============================================================================
// 更新処理
//=============================================================================
void CPlayer::Update(void)
{
	// 攻撃中でないなら
	if (!m_bNowAttack)
	{
		Attack();
	}

	// 攻撃中なら
	else
	{
		if (m_nAttackTime == 0)
		{
			switch (m_nMoveDirection)
			{
			case CKeyboard::UP:
				m_Pos.y -= m_fMove;
				break;
			case CKeyboard::LEFT:
				m_Pos.x -= m_fMove;
				break;
			case CKeyboard::DOWN:
				m_Pos.y += m_fMove;
				break;
			case CKeyboard::RIGHT:
				m_Pos.x += m_fMove;
				break;
			}
			m_fMove -= 0.1f;
		}

		if (m_fMove <= 0.0f)
		{
			m_nAttackTime++;

			if (m_nAttackTime > m_nMaxAttackTime ||
				Attack())
			{
				m_fMove = 2.5f;
				m_bNowAttack = false;
				m_nMoveDirection = 0;
				m_nAttackTime = 0;
				m_Pos = m_PosFix;
			}
		}
	}

	// 攻撃中でないなら
	if (!m_bNowAttack)
	{
		Attack();
	}

	CScene2D::SetPos(m_Pos);

	CScene2D::Update();
}

//=============================================================================
// 描画処理
//=============================================================================
void CPlayer::Draw(void)
{
	CScene2D::Draw();
}

//=============================================================================
// 生成処理
//=============================================================================
CPlayer *CPlayer::Create(D3DXVECTOR3 pos, D3DXVECTOR3 size, string type)
{
	CPlayer *pPlayer = NULL;

	if (pPlayer == NULL)
	{
		pPlayer = new CPlayer;
	}

	pPlayer->m_Pos = pos;
	pPlayer->m_Size = size;
	pPlayer->m_Type = type;
	pPlayer->m_nMoveDirection = 0;
	pPlayer->m_bNowAttack = false;
	pPlayer->m_nAttackTime = 0;
	pPlayer->m_fMove = 2.5f;

	if (pPlayer != NULL)
	{
		pPlayer->Init();
	}

	return pPlayer;
}

bool CPlayer::Attack(void)
{
	CKeyboard *pKey = CManager::GetKeyboard();

	// 上
	if (pKey->GetTrigger(pKey->UP))
	{
		m_bNowAttack = true;
		m_nMoveDirection = pKey->UP;
		m_Pos.y -= m_fPosMoveStart;
		CScene2D::SetTex(3, 5, 1);
		return true;
	}

	// 左
	if (pKey->GetTrigger(pKey->LEFT))
	{
		m_bNowAttack = true;
		m_nMoveDirection = pKey->LEFT;
		m_Pos.x -= m_fPosMoveStart;
		CScene2D::SetTex(1, 5, 1);
		return true;
	}

	// 下
	if (pKey->GetTrigger(pKey->DOWN))
	{
		m_bNowAttack = true;
		m_nMoveDirection = pKey->DOWN;
		m_Pos.y += m_fPosMoveStart;
		CScene2D::SetTex(4, 5, 1);
		return true;
	}

	// 右
	if (pKey->GetTrigger(pKey->RIGHT))
	{
		m_bNowAttack = true;
		m_nMoveDirection = pKey->RIGHT;
		m_Pos.x += m_fPosMoveStart;
		CScene2D::SetTex(2, 5, 1);
		return true;
	}
	if (m_Pos == D3DXVECTOR3(SCREEN_CENTER_X, SCREEN_CENTER_Y, 0.0f))
	{
		CScene2D::SetTex(0, 5, 1);
	}

	return false;
}