//=============================================================================
//
// 弾処理 [bullet.h]
// Author : 羽鳥太一
//
//=============================================================================
#ifndef _BULLET_H_
#define _BULLET_H_

//*****************************************************************************
// ヘッダファイルのインクルード
//*****************************************************************************
#include "main.h"
#include "bilboard.h"
#include "texture.h"

//*****************************************************************************
// クラス定義
//*****************************************************************************
class CBullet : public CBilboard
{
public:
	CBullet();	// デフォルトコンストラクタ
	~CBullet();	// デフォルトデストラクタ
	HRESULT Init(void);	// ポリゴンの初期化
	void Uninit(void);	// ポリゴンの終了
	void Update(void);	// ポリゴンの更新
	void Draw(void);	// ポリゴンの描画
private:
	float m_fMove;	// 移動量を足す為
protected:
	float m_fMoveSpeed;	// 移動量
};

#endif
