//=============================================================================
//
// テクスチャ処理 [texture.cpp]
// Author : 羽鳥太一
//
//=============================================================================
//=============================================================================
// インクルード
//=============================================================================
#include "texture.h"
#include "renderer.h"
#include "manager.h"

//=============================================================================
// 静的メンバ変数宣言
//=============================================================================
vector<LPDIRECT3DTEXTURE9>	CTexture::m_pTexture;	//テクスチャ
int CTexture::m_nTextureMax;	// 読み込むテクスチャの最大数
vector<string> CTexture::m_FilePas;	// ファイルのパス
vector<string> CTexture::m_Enum;	// 文字列の保存
map<string, int> CTexture::m_TexType;	// 文字列とintのmap

//=============================================================================
// デフォルトコンストラクタ
//=============================================================================
CTexture::CTexture()
{
	m_nTextureMax = NULL;
	m_TexType.clear();
}

//=============================================================================
// デフォルトデストラクタ
//=============================================================================
CTexture::~CTexture()
{

}

//=============================================================================
// テクスチャの生成
//=============================================================================
void CTexture::Init(void)
{
	LPDIRECT3DDEVICE9 pDevice; //デバイスのポインタ
	pDevice = CManager::GetRenderer()->GetDevice();	//デバイスを取得する
	FILE *pFile;
	char aFile[64];

	pFile = fopen("data/Txtdata/texturedata.txt", "r");

	if (pFile != NULL)
	{
		while (true)
		{
			fscanf(pFile, "%s", &aFile[0]);
			if (strcmp(&aFile[0], "TEX_NUM") == 0) // TEX_NUMの文字列を見つけたら
			{
				fscanf(pFile, "%s", &aFile[0]);
				fscanf(pFile, "%d", &m_nTextureMax);
			}
			else if (strcmp(&aFile[0], "ENUM_NAME") == 0) // ENUM_NAMEの文字列を見つけたら
			{
				for (int nCnt = 0; nCnt < m_nTextureMax; nCnt++)
				{
					int nNumber;
					char aEnumBuf[1][64];
					string Enum;

					fscanf(pFile, "%s%s%d", aEnumBuf[0], &aFile[0], &nNumber);
					Enum = aEnumBuf[0];
					m_Enum.push_back(Enum);
					m_TexType[Enum] = nNumber;
				}
			}
			else if (strcmp(&aFile[0], "TEXTURE_PAS") == 0) // TEXTURE_PASの文字列を見つけたら
			{
				for (int nCnt = 0; nCnt < m_nTextureMax; nCnt++)
				{
					char aPasBuf[1][64];
					string Pas;

					fscanf(pFile, "%s", aPasBuf[0]);

					Pas = aPasBuf[0];
					m_FilePas.push_back(Pas);
				}
			}
			else if (strcmp(&aFile[0], "END") == 0) //ENDの文字列を見つけたら
			{
				break;
			}
		}
	}
	else
	{
		printf("テクスチャデータが読み取れませんでした。");
	}

	fclose(pFile);

	for (int nCnt = 0; nCnt < m_nTextureMax; nCnt++)
	{
		LPDIRECT3DTEXTURE9 pTex = NULL;
		D3DXCreateTextureFromFile(	pDevice,
									m_FilePas[nCnt].c_str(),	// テクスチャパス
									&pTex);
		m_pTexture.push_back(pTex);
	}
}

//=============================================================================
// 終了
//=============================================================================
void CTexture::Uniinit(void)
{
	for (int nCntTexture = 0; nCntTexture < m_nTextureMax; nCntTexture++)
	{
		//テクスチャの破棄
		if (m_pTexture[nCntTexture] != NULL)
		{
			m_pTexture[nCntTexture]->Release();
			m_pTexture[nCntTexture] = NULL;
		}
	}
}