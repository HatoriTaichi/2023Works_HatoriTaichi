//=============================================================================
//
// 入力処理 [input.cpp]
// Author : 羽鳥太一
//
//=============================================================================
//=============================================================================
// インクルード
//=============================================================================
#include "enemy.h"

//=============================================================================
// デフォルトコンストラクタ
//=============================================================================
CEnemy::CEnemy()
{

}

//=============================================================================
// デフォルトデストラクタ
//=============================================================================
CEnemy::~CEnemy()
{

}

//=============================================================================
// 初期化
//=============================================================================
HRESULT CEnemy::Init(void)
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
void CEnemy::Uninit(void)
{
	CScene2D::Uninit();
}

//=============================================================================
// 更新処理
//=============================================================================
void CEnemy::Update(void)
{
	D3DXVECTOR3 Pos = CScene2D::GetPos();

	m_nAnimFrame++;
	if (m_bMove == true)
	{
		if (m_Type == "ENEMY_LEFT")
		{
			Pos.x -= 10.0f;
			CScene2D::SetPos(Pos);
		}
		else if (m_Type == "ENEMY_RIGHT")
		{
			Pos.x += 10.0f;
			CScene2D::SetPos(Pos);
		}
		else if (m_Type == "ENEMY_UP")
		{
			Pos.y -= 10.0f;
			CScene2D::SetPos(Pos);
		}
		else if (m_Type == "ENEMY_DOWN")
		{
			Pos.y += 10.0f;
			CScene2D::SetPos(Pos);
		}
		
		if (m_nAnimFrame >= (FPS / 8))
		{
			if (m_Type == "ENEMY_RIGHT" ||
				m_Type == "ENEMY_LEFT")
			{
				CScene2D::SetTex(m_nAnim, 8, 1);
				m_nAnimFrame = 0;
				m_nAnim++;
			}
			else if (m_Type == "ENEMY_UP" ||
					 m_Type == "ENEMY_DOWN")
			{
				CScene2D::SetTex(m_nAnim, 4, 1);
				m_nAnimFrame = 0;
				m_nAnim++;
			}
		}

		if (m_bUse == false)
		{
			if (Pos.x < 0.0f ||
				Pos.x > SCREEN_WIDTH ||
				Pos.y < 0.0f || 
				Pos.y > SCREEN_HEIGHT)
			{
				Uninit();
			}
		}
	}
	else
	{
		if (m_Type != "ENEMY_DAMAGE")
		{
			if (m_nAnimFrame >= (FPS / 8))
			{
				if (m_Type == "ENEMY_RIGHT" ||
					m_Type == "ENEMY_LEFT")
				{
					CScene2D::SetTex(m_nAnim, 8, 1);
					m_nAnimFrame = 0;
					m_nAnim++;
				}
				else if (m_Type == "ENEMY_UP" ||
						 m_Type == "ENEMY_DOWN")
				{
					CScene2D::SetTex(m_nAnim, 4, 1);
					m_nAnimFrame = 0;
					m_nAnim++;
				}
			}
		}
	}

	CScene2D::Update();

	if (m_bUse == true)
	{
		Pos = D3DXVECTOR3(SCREEN_CENTER_X, SCREEN_CENTER_Y, 0.0f);
		CScene2D::SetPos(Pos);
		m_Type = "ENEMY_DAMAGE";
		CScene2D::SetTexType(m_Type);
		CScene2D::SetTex(0, 1, 1);
		m_nDeth++;
		if (m_nDeth >= (FPS * 2))
		{
			Uninit();
		}
	}
}

//=============================================================================
// 描画処理
//=============================================================================
void CEnemy::Draw(void)
{
	CScene2D::Draw();
}

//=============================================================================
// 生成処理
//=============================================================================
CEnemy *CEnemy::Create(D3DXVECTOR3 pos, D3DXVECTOR3 size, string type)
{
	CEnemy *pEnemy = NULL;

	if (pEnemy == NULL)
	{
		pEnemy = new CEnemy;
	}

	pEnemy->m_Pos = pos;
	pEnemy->m_Size = size;
	pEnemy->m_Type = type;

	if (pEnemy != NULL)
	{
		pEnemy->Init();
	}

	return pEnemy;
}
