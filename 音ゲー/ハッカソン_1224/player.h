//=============================================================================
//
// 入力処理 [input.h]
// Author : 羽鳥太一
//
//=============================================================================
#ifndef _PLAYER_H_
#define _PLAYER_H_

//*****************************************************************************
// ヘッダファイルのインクルード
//*****************************************************************************
#include "main.h"
#include "scene2D.h"

//*****************************************************************************
// クラス定義
//*****************************************************************************
class CPlayer : public CScene2D
{
public:
	CPlayer();	// デフォルトコンストラクタ
	~CPlayer();	// デフォルトデストラクタ
	HRESULT Init(void);	// 初期化
	void Uninit(void);	// 終了
	void Update(void);	// 更新
	void Draw(void);	// 描画
	static CPlayer *Create(D3DXVECTOR3 pos, D3DXVECTOR3 size, string type);

	bool Attack();		// 攻撃
private:
	D3DXVECTOR3 m_Pos;	// 位置
	D3DXVECTOR3 m_Size;	// サイズ
	string m_Type;		// タイプ

	bool m_bNowAttack;	// 今攻撃中か

	float m_fMove = 2.5f;				// 移動量
	int m_nAttackTime;					// 攻撃のタイマー
	const int m_nMaxAttackTime = 24;	// 攻撃の持続時間

	int m_nMoveDirection;		// 切る方向

	const float m_fPosMoveStart = 300.0f;	// 移動の始点
	const D3DXVECTOR3 m_PosFix = D3DXVECTOR3(SCREEN_CENTER_X, SCREEN_CENTER_Y, 0.0f);	// 初期位置
};

#endif