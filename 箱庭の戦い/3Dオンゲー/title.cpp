//=============================================================================
//
// 入力処理 [input.cpp]
// Author : 羽鳥太一
//
//=============================================================================
//=============================================================================
// インクルード
//=============================================================================
#include "title.h"
#include "manager.h"
#include "textureobj.h"
#include "sound.h"

//=============================================================================
// デフォルトコンストラクタ
//=============================================================================
CTitle::CTitle()
{

}

//=============================================================================
// デフォルトデストラクタ
//=============================================================================
CTitle::~CTitle()
{

}

//=============================================================================
// 初期化
//=============================================================================
HRESULT CTitle::Init(void)
{
	CSound *pSound = CManager::GetSound();
	FILE *pFile;
	string FileString;
	D3DXVECTOR3 Pos;
	D3DXVECTOR3 Size;
	char aFile[1][128];

	pFile = fopen("data/Txtdata/titledata.txt", "r");

	if (pFile != NULL)
	{
		int nCnt = 0;
		while (true)
		{
			fscanf(pFile, "%s", aFile[0]);
			if (strcmp(aFile[0], "UI_NUM") == 0) // UI_NUMの文字列を見つけたら
			{
				fscanf(pFile, "%*s%d", &m_nUiNum);
			}
			if (strcmp(aFile[0], "SET_UI") == 0) // SET_UIの文字列を見つけたら
			{
				while (true)
				{
					fscanf(pFile, "%s", aFile[0]);

					// TEX_TYPEの文字列を見つけたら
					if (strcmp(aFile[0], "TEX_TYPE") == 0) // TEX_TYPEの文字列を見つけたら
					{
						char aTypeBuf[1][64];
						string Type;
						fscanf(pFile, "%*s%s", aTypeBuf[0]);
						Type = aTypeBuf[0];
						m_Type.push_back(Type);
					}
					// POSの文字列を見つけたら
					else if (strcmp(aFile[0], "POS") == 0)
					{
						fscanf(pFile, "%*s%f%f%f", &Pos.x, &Pos.y, &Pos.z);
					}
					// SIZEの文字列を見つけたら
					else if (strcmp(aFile[0], "SIZE") == 0)
					{
						fscanf(pFile, "%*s%f%f%f", &Size.x, &Size.y, &Size.z);
					}
					// END_UISETの文字列を見つけたら
					else if (strcmp(aFile[0], "END_UISET") == 0)
					{
						CUiObj::Create(Pos, Size, m_Type[nCnt]);
						nCnt++;
						break;
					}
				}
			}
			else if (strcmp(aFile[0], "END") == 0)
			{
				break;
			}
		}
	}
	else
	{
		cout << "テキストファイルがひらけませんでした。";
	}

	fclose(pFile);

	pSound->PlaySound(CSound::X2SOUND_LABEL::TITLE);

	return S_OK;
}

//=============================================================================
// 終了
//=============================================================================
void CTitle::Uninit(void)
{
	CScene::ReleaseAll();
}

//=============================================================================
// 更新処理
//=============================================================================
void CTitle::Update(void)
{

}

//=============================================================================
// 描画処理
//=============================================================================
void CTitle::Draw(void)
{

}