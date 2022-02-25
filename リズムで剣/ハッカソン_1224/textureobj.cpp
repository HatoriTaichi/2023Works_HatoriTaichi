//=============================================================================
//
// 2D�|���S������ [textureobj.cpp]
// Author : �H������
//
//=============================================================================
//=============================================================================
// �C���N���[�h
//=============================================================================
#include "textureobj.h"
#include "manager.h"
#include "fade.h"
#include "mouseinput.h"
#include "fade.h"
#include "mouseinput.h"
#include "sound.h"

//=============================================================================
// �f�t�H���g�R���X�g���N�^
//=============================================================================
CUiObj::CUiObj()
{
	m_Color.a = 0.0f;
	m_Color.r = 0.0f;
	m_Color.b = 0.0f;
	m_Color.g = 0.0f;
	m_nChangeCnt = 0;
}

//=============================================================================
// �f�t�H���g�f�X�g���N�^
//=============================================================================
CUiObj::~CUiObj()
{

}

//=============================================================================
// �|���S���̏�����
//=============================================================================
HRESULT CUiObj::Init(void)
{
	CScene2D::SetTexType(m_TexType);
	CScene2D::Init();
	CScene2D::SetPos(m_Pos);
	CScene2D::SetSize(m_Size);
	m_Color.a = 1.0f;
	m_Color.r = 1.0f;
	m_Color.b = 1.0f;
	m_Color.g = 1.0f;

	return S_OK;
}

//=============================================================================
// �|���S���̏I��
//=============================================================================
void CUiObj::Uninit(void)
{
	CScene2D::Uninit();
}

//=============================================================================
// �|���S���̍X�V
//=============================================================================
void CUiObj::Update(void)
{
	CSound *pSound = CManager::GetSound();
	CMouse *pMouse = CManager::GetMouse();
	CFade *pFade = CManager::GetFade();
	POINT MousePos;
	D3DXVECTOR3 Pos = CScene2D::GetPos();
	D3DXVECTOR2 Size = CScene2D::GetSize();
	GetCursorPos(&MousePos);
	ScreenToClient(CManager::GetHandle(), &MousePos);

	if (m_TexType == "START")
	{
		if (Pos.x + Size.x >= MousePos.x &&
			Pos.x - Size.x <= MousePos.x &&
			Pos.y + Size.y >= MousePos.y &&
			Pos.y - Size.y <= MousePos.y)
		{
			m_Color.a = 0.5f;
			CScene2D::SetCol(m_Color);
			if (pMouse->GetTrigger(pMouse->LEFT_BOTTON) == true && pFade->GetFade() == pFade->FADE_NONE)
			{
				pSound->Play(CSound::SOUND_LABEL_SE_START);
				pFade->SetFade(CManager::MODE::GAME);
			}
		}
		else
		{
			m_Color.a = 1.0f;
			CScene2D::SetCol(m_Color);
		}
	}
	if (m_TexType == "RULE")
	{
		if (Pos.x + Size.x >= MousePos.x &&
			Pos.x - Size.x <= MousePos.x &&
			Pos.y + Size.y >= MousePos.y &&
			Pos.y - Size.y <= MousePos.y)
		{
			m_Color.a = 0.5f;
			CScene2D::SetCol(m_Color);
			if (pMouse->GetTrigger(pMouse->LEFT_BOTTON) == true && pFade->GetFade() == pFade->FADE_NONE)
			{
				pSound->Play(CSound::SOUND_LABEL_SE_START);
				pFade->SetFade(CManager::MODE::MANUAL);
			}
		}
		else
		{
			m_Color.a = 1.0f;
			CScene2D::SetCol(m_Color);
		}
	}
	if (m_TexType == "BUCK")
	{
		if (Pos.x + Size.x >= MousePos.x &&
			Pos.x - Size.x <= MousePos.x &&
			Pos.y + Size.y >= MousePos.y &&
			Pos.y - Size.y <= MousePos.y)
		{
			m_Color.a = 0.5f;
			CScene2D::SetCol(m_Color);
			if (pMouse->GetTrigger(pMouse->LEFT_BOTTON) == true && pFade->GetFade() == pFade->FADE_NONE)
			{
				pSound->Play(CSound::SOUND_LABEL_SE_START);
				pFade->SetFade(CManager::MODE::TITLE);
			}
		}
		else
		{
			m_Color.a = 1.0f;
			CScene2D::SetCol(m_Color);
		}
	}

	CScene2D::Update();
}

//=============================================================================
// �|���S���̕`��
//=============================================================================
void CUiObj::Draw(void)
{
	CScene2D::Draw();
}

//=============================================================================
// �C���N���[�h
//=============================================================================
CUiObj *CUiObj::Create(D3DXVECTOR3 pos, D3DXVECTOR3 size, string Type)
{
	CUiObj *pUi = NULL;
	if (pUi == NULL)
	{
		pUi = new CUiObj;
	}

	pUi->m_Pos = pos;
	pUi->m_Size = size;
	pUi->m_TexType = Type;

	if (pUi != NULL)
	{
		pUi->Init();
	}
	return pUi;
}