//=============================================================================
//
// フェード処理 [fade.h]
// Author : 羽鳥太一
//
//=============================================================================
#ifndef _FADE_H_
#define _FADE_H_

//*****************************************************************************
// インクルード
//*****************************************************************************
#include "main.h"
#include "manager.h"
#include "scene2D.h"

//*****************************************************************************
// クラス定義
//*****************************************************************************
class CFade
{
public:
	//---------------------------
	//列挙型
	//---------------------------
	typedef enum
	{
		FADE_NONE = 0,
		FADE_IN,
		FADE_OUT,
		FADE_MAX
	} FADE;
	CFade();	// デフォルトコンストラクタ
	~CFade();	// デストラクタ
	HRESULT Init(void);	// 初期化処理
	void Uninit(void);	// 終了処理
	void Update(void);	// 更新処理
	void Draw(void);	// 描画処理
	void SetFade(CManager::MODE mode);	// フェードの設定
	FADE GetFade(void) { return m_Fade; }	// フェード中かどうかを取得
private:
	LPDIRECT3DVERTEXBUFFER9 m_pVtxBuff;	// 頂点バッファへのポインタ
	CManager::MODE m_nextMode;	// 次のモード
	FADE m_Fade;	// フェード
	float m_colA;	// カラーのアルファ値
};

#endif // !_FADE_H_