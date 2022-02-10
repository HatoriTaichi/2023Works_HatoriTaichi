//=============================================================================
//
// マズルフラッシュ処理 [gunfire.h]
// Author : 羽鳥太一
//
//=============================================================================
#ifndef _GUNFIRE_H_
#define _GUNFIRE_H_

//*****************************************************************************
// ヘッダファイルのインクルード
//*****************************************************************************
#include "main.h"
#include "bilboard.h"
#include "texture.h"

//*****************************************************************************
// クラス定義
//*****************************************************************************
class CGunFire : public CBilboard
{
public:
	CGunFire();	// デフォルトコンストラクタ
	~CGunFire();	// デフォルトデストラクタ
	HRESULT Init(void);	// ポリゴンの初期化
	void Uninit(void);	// ポリゴンの終了
	void Update(void);	// ポリゴンの更新
	void Draw(void);	// ポリゴンの描画
	static CGunFire *Create(D3DXVECTOR3 pos, D3DXVECTOR3 size, D3DXVECTOR3 scale, string type);	// 生成処理
private:
	D3DXVECTOR3 m_Size;	// サイズ
	string m_Type;	// テクスチャ
	int m_nClearCnt;	// 消えるまでのカウント
};

#endif