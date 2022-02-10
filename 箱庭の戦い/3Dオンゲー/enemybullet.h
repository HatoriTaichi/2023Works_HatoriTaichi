//=============================================================================
//
// 敵の弾処理 [playerbullet.h]
// Author : 羽鳥太一
//
//=============================================================================
#ifndef _ENEMY_BULLET_H_
#define _ENEMY_BULLET_H_

//*****************************************************************************
// ヘッダファイルのインクルード
//*****************************************************************************
#include "main.h"
#include "bullet.h"
#include "texture.h"

//*****************************************************************************
// クラス定義
//*****************************************************************************
class CEnemyBullet : public CBullet
{
public:
	CEnemyBullet();	// デフォルトコンストラクタ
	~CEnemyBullet();	// デフォルトデストラクタ
	HRESULT Init(void);	// ポリゴンの初期化
	void Uninit(void);	// ポリゴンの終了
	void Update(void);	// ポリゴンの更新
	void Draw(void);	// ポリゴンの描画
	static CEnemyBullet *Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot, D3DXVECTOR3 size, D3DXVECTOR3 scale, string type, float fMoveSpeed);	// 生成
private:
	D3DXVECTOR3 m_Size;	// サイズ
	D3DXVECTOR3 m_Scale;	// スケール
	D3DXMATRIX m_mtxWorld;// ワールドマトリックス
	string m_Type;	// テクスチャ
};

#endif 