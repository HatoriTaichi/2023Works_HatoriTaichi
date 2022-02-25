//=============================================================================
//
// テクスチャ処理 [texture.h]
// Author : 羽鳥太一
//
//=============================================================================
#ifndef _TEXTURE_H_
#define _TEXTURE_H_

//*****************************************************************************
// ヘッダファイルのインクルード
//*****************************************************************************
#include "main.h"

//*****************************************************************************
// クラス定義
//*****************************************************************************
class CTexture
{
public:
	CTexture();	// デフォルトコンストラクタ
	~CTexture();// デフォルトデストラクタ
	static void Init(void);	// テクスチャの生成
	static LPDIRECT3DTEXTURE9 GetTexture(string type) { return m_pTexture[m_TexType[type]]; }	// テクスチャの割り当て(テクスチャの種類) { return 選んだテクスチャを返す }
	static int GetTexNum(void) { return m_nTextureMax; }	// ゲッダー
	static string *GetPasName(void) { return &m_FilePas[0]; }	// ゲッダー
	static string GetEnumName(int nCntPas) { return m_Enum[nCntPas]; }	// ゲッダー
	static void Uniinit(void);	// 終了
private:
	static vector<LPDIRECT3DTEXTURE9>	m_pTexture;	//テクスチャ
	static vector<string> m_FilePas;	// ファイルのパス
	static vector<string> m_Enum;	// 文字列の保存
	static map<string, int> m_TexType;	// 文字列とintのmap
	static int m_nTextureMax;	// 読み込むテクスチャの最大数
};

#endif