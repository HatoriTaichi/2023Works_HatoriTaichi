//=============================================================================
//
// 2Dポリゴン処理 [scene2D.h]
// Author : 羽鳥太一
//
//=============================================================================
#ifndef _SCENE2D_H_
#define _SCENE2D_H_

//*****************************************************************************
// ヘッダファイルのインクルード
//*****************************************************************************
#include "main.h"
#include "scene.h"
#include "texture.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define FVF_VERTEX_2D (D3DFVF_XYZRHW|D3DFVF_DIFFUSE|D3DFVF_TEX1) //2Dの柔軟な頂点フォーマット
#define VERTEX_NUM (4)	// 頂点の数

//*****************************************************************************
// 構造体定義
//*****************************************************************************
typedef struct
{
	D3DXVECTOR3 pos;//頂点座標
	float rhw;		//1.0fで固定
	D3DCOLOR col;	//頂点カラー
	D3DXVECTOR2 tex;//テクスチャ座標
} VERTEX_2D;

//*****************************************************************************
// クラス定義
//*****************************************************************************
class CScene2D : public CScene
{
public:
	CScene2D(LAYER_TYPE Layer = LAYER_TYPE::LAYER_00);	// デフォルトコンストラクタ
	~CScene2D();	// デフォルトデストラクタ
	virtual HRESULT Init(void);	// ポリゴンの初期化
	virtual void Uninit(void);	// ポリゴンの終了
	virtual void Update(void);	// ポリゴンの更新
	virtual void Draw(void);	// ポリゴンの描画
	static CScene2D *Create(D3DXVECTOR3 pos, D3DXVECTOR3 size, string Type);	// オブジェクトの生成(位置, 種類)
	D3DXVECTOR3 GetPos(void) { return m_Pos; }		// ゲッダー
	D3DXVECTOR3 GetSize(void) { return m_Size; }	// ゲッダー
	void SetPos(D3DXVECTOR3 pos);	// セッター
	void SetSize(D3DXVECTOR3 size);	// セッター
	void SetTexType(string type) { m_TexType = type; m_pTexture = CTexture::GetTexture(m_TexType); }	// セッター
	void SetCol(D3DXCOLOR col);	// セッター
	void SetTex(int nScore);	// セッター
	void SetTex(int nPattern, int nAnimMaxX, int nAnimMaxY);//テクスセッターチャ 
private:
	LPDIRECT3DTEXTURE9		m_pTexture = NULL;		//テクスチャへのポインタ
	LPDIRECT3DVERTEXBUFFER9 m_pVtxBuff = NULL;		//頂点バッファへのポインタ
	D3DXVECTOR3				m_Pos;	// ポリゴンの原点
	D3DXVECTOR3				m_Size;	// サイズ
	string					m_TexType;	// テクスチャタイプ
};

#endif