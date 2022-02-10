//=============================================================================
//
// 2Dポリゴン処理 [textureobj.cpp]
// Author : 羽鳥太一
//
//=============================================================================
//=============================================================================
// インクルード
//=============================================================================
#include "textureobj.h"
#include "manager.h"
#include "fade.h"
#include "mouseinput.h"
#include "fade.h"
#include "sound.h"

//=============================================================================
// デフォルトコンストラクタ
//=============================================================================
CUiObj::CUiObj(LAYER_TYPE Layer) : CScene2D(Layer)
{
	m_Color.a = 0.0f;
	m_Color.r = 0.0f;
	m_Color.b = 0.0f;
	m_Color.g = 0.0f;
	m_nChangeCnt = 0;
}

//=============================================================================
// デフォルトデストラクタ
//=============================================================================
CUiObj::~CUiObj()
{

}

//=============================================================================
// ポリゴンの初期化
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
// ポリゴンの終了
//=============================================================================
void CUiObj::Uninit(void)
{
	CScene2D::Uninit();
}

//=============================================================================
// ポリゴンの更新
//=============================================================================
void CUiObj::Update(void)
{
	CSound *pSound = CManager::GetSound();
	D3DXVECTOR3 Pos = CScene2D::GetPos();
	D3DXVECTOR2 Size = CScene2D::GetSize();
	CMouse *pMouse = CManager::GetMouse();
	CFade *pFade = CManager::GetFade();
	POINT MousePos;
	GetCursorPos(&MousePos);
	ScreenToClient(CManager::GetHandle(), &MousePos);

	if (m_TexType == "MATCHING")
	{
		if (m_bAlpha == false)
		{
			m_Color.a -= 0.01f;
			CScene2D::SetCol(m_Color);
			if (m_Color.a <= 0.0f)
			{
				m_bAlpha = true;
			}
		}
		else if (m_bAlpha == true)
		{
			m_Color.a += 0.01f;
			CScene2D::SetCol(m_Color);
			if (m_Color.a >= 1.0f)
			{
				m_bAlpha = false;
			}
		}
	}
	else if (m_TexType == "YES")
	{
		if (m_Pos.x + m_Size.x >= MousePos.x &&
			m_Pos.x - m_Size.x <= MousePos.x &&
			m_Pos.y + m_Size.y >= MousePos.y &&
			m_Pos.y - m_Size.y <= MousePos.y)
		{
			m_Color.a = 0.5f;
			CScene2D::SetCol(m_Color);
			if (pMouse->GetTrigger(pMouse->LEFT_BOTTON) == true && pFade->GetFade() == CFade::FADE::FADE_NONE)
			{
				pSound->PlaySound(CSound::X2SOUND_LABEL::GONEXT);
				pFade->SetFade(CManager::MODE::MATCHING);
			}
		}
		else
		{
			m_Color.a = 1.0f;
			CScene2D::SetCol(m_Color);
		}
	}
	else if (m_TexType == "NO")
	{
		if (m_Pos.x + m_Size.x >= MousePos.x &&
			m_Pos.x - m_Size.x <= MousePos.x &&
			m_Pos.y + m_Size.y >= MousePos.y &&
			m_Pos.y - m_Size.y <= MousePos.y)
		{
			m_Color.a = 0.5f;
			CScene2D::SetCol(m_Color);
			if (pMouse->GetTrigger(pMouse->LEFT_BOTTON) == true && pFade->GetFade() == CFade::FADE::FADE_NONE)
			{
				pSound->PlaySound(CSound::X2SOUND_LABEL::GONEXT);
				pFade->SetFade(CManager::MODE::TITLE);
			}
		}
		else
		{
			m_Color.a = 1.0f;
			CScene2D::SetCol(m_Color);
		}
	}
	else if (m_TexType == "GAMESTART")
	{
		if (m_Pos.x + m_Size.x >= MousePos.x &&
			m_Pos.x - m_Size.x <= MousePos.x &&
			m_Pos.y + m_Size.y >= MousePos.y &&
			m_Pos.y - m_Size.y <= MousePos.y)
		{
			m_Color.a = 0.5f;
			CScene2D::SetCol(m_Color);
			if (pMouse->GetTrigger(pMouse->LEFT_BOTTON) == true && pFade->GetFade() == CFade::FADE::FADE_NONE)
			{
				pSound->PlaySound(CSound::X2SOUND_LABEL::GONEXT);
				pFade->SetFade(CManager::MODE::MATCHING);
			}
		}
		else
		{
			m_Color.a = 1.0f;
			CScene2D::SetCol(m_Color);
		}
	}
	else if (m_TexType == "RELE")
	{
		if (m_Pos.x + m_Size.x >= MousePos.x &&
			m_Pos.x - m_Size.x <= MousePos.x &&
			m_Pos.y + m_Size.y >= MousePos.y &&
			m_Pos.y - m_Size.y <= MousePos.y)
		{
			m_Color.a = 0.5f;
			CScene2D::SetCol(m_Color);
			if (pMouse->GetTrigger(pMouse->LEFT_BOTTON) == true && pFade->GetFade() == CFade::FADE::FADE_NONE)
			{
				pSound->PlaySound(CSound::X2SOUND_LABEL::GONEXT);
				pFade->SetFade(CManager::MODE::RULE);
			}
		}
		else
		{
			m_Color.a = 1.0f;
			CScene2D::SetCol(m_Color);
		}
	}
	else if (m_TexType == "MANUAL")
	{
		if (m_Pos.x + m_Size.x >= MousePos.x &&
			m_Pos.x - m_Size.x <= MousePos.x &&
			m_Pos.y + m_Size.y >= MousePos.y &&
			m_Pos.y - m_Size.y <= MousePos.y)
		{
			m_Color.a = 0.5f;
			m_bSelect = true;
			CScene2D::SetCol(m_Color);
		}
		else
		{
			m_bSelect = false;
			m_Color.a = 1.0f;
			CScene2D::SetCol(m_Color);
		}
	}
	else if (m_TexType == "WEAPON_LETTER")
	{
		if (m_Pos.x + m_Size.x >= MousePos.x &&
			m_Pos.x - m_Size.x <= MousePos.x &&
			m_Pos.y + m_Size.y >= MousePos.y &&
			m_Pos.y - m_Size.y <= MousePos.y)
		{
			m_Color.a = 0.5f;
			m_bSelect = true;
			CScene2D::SetCol(m_Color);
		}
		else
		{
			m_bSelect = false;
			m_Color.a = 1.0f;
			CScene2D::SetCol(m_Color);
		}
	}
	else if (m_TexType == "WINCONDITION")
	{
		if (m_Pos.x + m_Size.x >= MousePos.x &&
			m_Pos.x - m_Size.x <= MousePos.x &&
			m_Pos.y + m_Size.y >= MousePos.y &&
			m_Pos.y - m_Size.y <= MousePos.y)
		{
			m_Color.a = 0.5f;
			m_bSelect = true;
			CScene2D::SetCol(m_Color);
		}
		else
		{
			m_bSelect = false;
			m_Color.a = 1.0f;
			CScene2D::SetCol(m_Color);
		}
	}
	else if (m_TexType == "BUCK")
	{
		if (m_Pos.x + m_Size.x >= MousePos.x &&
			m_Pos.x - m_Size.x <= MousePos.x &&
			m_Pos.y + m_Size.y >= MousePos.y &&
			m_Pos.y - m_Size.y <= MousePos.y)
		{
			m_Color.a = 0.5f;
			CScene2D::SetCol(m_Color);
			if (pMouse->GetTrigger(pMouse->LEFT_BOTTON) == true && pFade->GetFade() == CFade::FADE::FADE_NONE)
			{
				pSound->PlaySound(CSound::X2SOUND_LABEL::GONEXT);
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
// ポリゴンの描画
//=============================================================================
void CUiObj::Draw(void)
{
	CScene2D::Draw();
}

//=============================================================================
// インクルード
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