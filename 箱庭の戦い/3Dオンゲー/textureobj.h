//=============================================================================
//
// 文字ポリゴンの処理 [textureobj.h]
// Author : 羽鳥太一
//
//=============================================================================
#ifndef _UIOBJ_H_
#define _UIOBJ_H_

//*****************************************************************************
// ヘッダファイルのインクルード
//*****************************************************************************
#include "scene2D.h"

//*****************************************************************************
// クラス定義
//*****************************************************************************
class CUiObj : public CScene2D
{
public:
	CUiObj(LAYER_TYPE Layer = LAYER_TYPE::LAYER_05);	// デフォルトコンストラクタ
	~CUiObj();	// デフォルトデストラクタ
	HRESULT Init(void);	// ポリゴンの初期化
	void Uninit(void);	// ポリゴンの終了
	void Update(void);	// ポリゴンの更新
	void Draw(void);	// ポリゴンの描画
	void SetAlpha(float a) { m_Color.a = a; CScene2D::SetCol(m_Color); }	// セッター
	void SetSelect(bool select) { m_bSelect = select; }	// セッター
	string GetType(void) { return m_TexType; }	// ゲッダー
	bool GetSelect(void) { return m_bSelect; }	// ゲッダー
	static CUiObj *Create(D3DXVECTOR3 pos, D3DXVECTOR3 size, string Type);	// 生成(位置、サイズ、テクスチャ)
private:
	D3DXVECTOR3 m_Pos;	// 位置
	D3DXVECTOR3 m_Size;	// サイズ
	string m_TexType;	// テクスチャ
	D3DXCOLOR m_Color;	// カラー
	int m_nChangeCnt;	// 点滅カウント
	bool m_bAlpha = false;	// アルファのチェンジ
	bool m_bSelect = false;	// 選択
};

#endif