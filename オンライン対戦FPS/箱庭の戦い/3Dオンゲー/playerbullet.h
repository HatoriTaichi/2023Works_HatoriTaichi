//=============================================================================
//
// プレイヤーの弾処理 [playerbullet.h]
// Author : 羽鳥太一
//
//=============================================================================
#ifndef _PLAYER_BULLET_H_
#define _PLAYER_BULLET_H_

//*****************************************************************************
// ヘッダファイルのインクルード
//*****************************************************************************
#include "main.h"
#include "bullet.h"
#include "texture.h"

//*****************************************************************************
// クラス定義
//*****************************************************************************
class CPlayerBullet : public CBullet
{
public:
	CPlayerBullet();	// デフォルトコンストラクタ
	~CPlayerBullet();	// デフォルトデストラクタ
	HRESULT Init(void);	// ポリゴンの初期化
	void Uninit(void);	// ポリゴンの終了
	void Update(void);	// ポリゴンの更新
	void Draw(void);	// ポリゴンの描画
	static CPlayerBullet *Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot, D3DXVECTOR3 size, D3DXVECTOR3 scale, string type, float fMoveSpeed);	// 生成
private:
	D3DXVECTOR3 m_Size;	// サイズ
	D3DXMATRIX m_mtxWorld;// ワールドマトリックス
	string m_Type;	// テクスチャ
};

#endif