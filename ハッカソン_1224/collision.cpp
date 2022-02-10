//=============================================================================
//
// 2Dポリゴン処理 [textureobj.cpp]
// Author : 羽鳥太一
//
//=============================================================================
//=============================================================================
// インクルード
//=============================================================================
#include "collision.h"
#include "manager.h"
#include "fade.h"
#include "mouseinput.h"
#include "fade.h"
#include "Notes.h"
#include "keyinput.h"
#include "enemy.h"
#include "counter.h"
#include "game.h"
#include "sound.h"

//=============================================================================
// デフォルトコンストラクタ
//=============================================================================
CCollision::CCollision()
{

}

//=============================================================================
// デフォルトデストラクタ
//=============================================================================
CCollision::~CCollision()
{

}

//=============================================================================
// ポリゴンの初期化
//=============================================================================
HRESULT CCollision::Init(void)
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
void CCollision::Uninit(void)
{
	CScene2D::Uninit();
}

//=============================================================================
// ポリゴンの更新
//=============================================================================
void CCollision::Update(void)
{
	CKeyboard *pKey = CManager::GetKeyboard();
	CSound *pSound = CManager::GetSound();
	CCounter *pCombo = CManager::GetGame()->GetCombo();
	CCounter *pScore = CManager::GetGame()->GetScore();
	D3DXVECTOR3 Pos = CScene2D::GetPos();
	D3DXVECTOR2 Size = CScene2D::GetSize();

	Pos.y += 1.0f;

	if (m_TexType == "LEFT_ARROWFRAME" ||
		m_TexType == "RIGHT_ARROWFRAME")
	{
		Size.x -= 1.0f;
		Size.y -= 0.5f;
		if ((m_pNoets->GetSize().x * MAX_EXTENSION) >= Size.x &&
			(m_pNoets->GetSize().y * MAX_EXTENSION) >= Size.y)
		{
			if (pKey->GetTrigger(pKey->LEFT) == true || pKey->GetTrigger(pKey->RIGHT) == true)
			{
				m_pNoets->GetEnemy()->SetUse(true);
				pSound->Play(CSound::SOUND_LABEL_SE_TAP);
				pCombo->AddCounter(1);
				pScore->AddCounter(1000);
			}
		}
		else if ((m_pNoets->GetSize().x * MIN_EXTENSION) >= Size.x &&
				 (m_pNoets->GetSize().y * MIN_EXTENSION) >= Size.y)
		{
			if (pKey->GetTrigger(pKey->LEFT) == true || pKey->GetTrigger(pKey->RIGHT) == true)
			{
				m_pNoets->GetEnemy()->SetUse(true);
				pSound->Play(CSound::SOUND_LABEL_SE_TAP);
				pCombo->AddCounter(1);
				pScore->AddCounter(500);
			}
		}
		else if ((m_pNoets->GetSize().x * MAX_EXTENSION) <= Size.x &&
				 (m_pNoets->GetSize().y * MAX_EXTENSION) <= Size.y)
		{
			if (pKey->GetTrigger(pKey->LEFT) == true || pKey->GetTrigger(pKey->RIGHT) == true)
			{
				m_pNoets->GetEnemy()->SetbMove(true);
				pCombo->SetCounterNum(0);
			}
		}
	}
	else if (m_TexType == "UP_ARROWFRAME" ||
			 m_TexType == "DOWN_ARROWFRAME")
	{
		Size.x -= 0.5f;
		Size.y -= 1.0f;
		if ((m_pNoets->GetSize().x * MAX_EXTENSION) >= Size.x &&
			(m_pNoets->GetSize().y * MAX_EXTENSION) >= Size.y)
		{
			if (pKey->GetTrigger(pKey->UP) == true || pKey->GetTrigger(pKey->DOWN) == true)
			{
				m_pNoets->GetEnemy()->SetUse(true);
				pSound->Play(CSound::SOUND_LABEL_SE_TAP);
				pCombo->AddCounter(1);
				pScore->AddCounter(1000);
			}
		}
		else if ((m_pNoets->GetSize().x * MIN_EXTENSION) >= Size.x &&
				 (m_pNoets->GetSize().y * MIN_EXTENSION) >= Size.y)
		{
			if (pKey->GetTrigger(pKey->LEFT) == true || pKey->GetTrigger(pKey->RIGHT) == true)
			{
				m_pNoets->GetEnemy()->SetUse(true);
				pSound->Play(CSound::SOUND_LABEL_SE_TAP);
				pCombo->AddCounter(1);
				pScore->AddCounter(500);
			}
		}
		else if ((m_pNoets->GetSize().x * MAX_EXTENSION) <= Size.x &&
				 (m_pNoets->GetSize().y * MAX_EXTENSION) <= Size.y)
		{
			if (pKey->GetTrigger(pKey->UP) == true || pKey->GetTrigger(pKey->DOWN) == true)
			{
				m_pNoets->GetEnemy()->SetbMove(true);
				pCombo->SetCounterNum(0);
			}
		}
	}

	CScene2D::SetPos(Pos);
	CScene2D::SetSize(D3DXVECTOR3(Size.x, Size.y, 0.0f));

	CScene2D::Update();

	if ((m_pNoets->GetSize().x * MIN_EXTENSION) >= Size.x &&
		(m_pNoets->GetSize().y * MIN_EXTENSION) >= Size.y)
	{
		m_pNoets->GetEnemy()->SetbMove(true);
		m_pNoets->Uninit();
		m_pNoets = NULL;
		Uninit();
	}
}

//=============================================================================
// ポリゴンの描画
//=============================================================================
void CCollision::Draw(void)
{
	CScene2D::Draw();
}

//=============================================================================
// インクルード
//=============================================================================
CCollision *CCollision::Create(D3DXVECTOR3 pos, D3DXVECTOR2 size, string Type, CNotes *pNotes)
{
	CCollision *pCollision = NULL;
	if (pCollision == NULL)
	{
		pCollision = new CCollision;
	}

	pCollision->m_Pos = pos;
	pCollision->m_Size = size;
	pCollision->m_TexType = Type;
	pCollision->m_pNoets = pNotes;

	if (pCollision != NULL)
	{
		pCollision->Init();
	}
	return pCollision;
}