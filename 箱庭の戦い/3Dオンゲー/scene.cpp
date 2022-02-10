//=============================================================================
//
// �I�u�W�F�N�g���� [scene.cpp]
// Author : �H������
//
//=============================================================================
//=============================================================================
// �C���N���[�h
//=============================================================================
#include "scene.h"

//=============================================================================
// �ÓI�����o�ϐ��錾
//=============================================================================
vector<CScene*> CScene::m_pObjet[(int)LAYER_TYPE::MAX_LAYER];

//=============================================================================
// �f�t�H���g�R���X�g���N�^
//=============================================================================
CScene::CScene(LAYER_TYPE Layer)
{
	m_bDeth = false;
	m_nPriority = (int)Layer;

	m_pObjet[m_nPriority].push_back(this);
}

//=============================================================================
// �f�t�H���g�f�X�g���N�^
//=============================================================================
CScene::~CScene()
{
	
}

//=============================================================================
// �S���폜
//=============================================================================
void CScene::ReleaseAll(void)
{
	for (int nCnt = 0; nCnt < (int)LAYER_TYPE::MAX_LAYER; nCnt++)
	{
		for (int nCntPop = 0; nCntPop < m_pObjet[nCnt].size(); nCntPop++)
		{
			delete m_pObjet[nCnt][nCntPop];
		}

		int nPrioltySize = m_pObjet[nCnt].size();
		for (int nCntPop = 0; nCntPop < nPrioltySize; nCntPop++)
		{
			m_pObjet[nCnt].pop_back();
		}
	}
}

//=============================================================================
// �S���X�V
//=============================================================================
void CScene::UpdateAll(void)
{
	for (int nCnt = 0; nCnt < (int)LAYER_TYPE::MAX_LAYER; nCnt++)
	{
		for (int nCntUpdate = 0; nCntUpdate < m_pObjet[nCnt].size(); nCntUpdate++)
		{
			m_pObjet[nCnt][nCntUpdate]->Update();
			if (m_pObjet[nCnt][nCntUpdate]->m_bDeth == true)
			{
				delete m_pObjet[nCnt][nCntUpdate];
				m_pObjet[nCnt][nCntUpdate] = NULL;
				m_pObjet[nCnt].erase(m_pObjet[nCnt].begin() + nCntUpdate);
			}
		}
	}
}

//=============================================================================
// �S���`��
//=============================================================================
void CScene::DrawAll(void)
{
	for (int nCnt = 0; nCnt < (int)LAYER_TYPE::MAX_LAYER; nCnt++)
	{
		for (int nCntUpdate = 0; nCntUpdate < m_pObjet[nCnt].size(); nCntUpdate++)
		{
			m_pObjet[nCnt][nCntUpdate]->Draw();
		}
	}
}