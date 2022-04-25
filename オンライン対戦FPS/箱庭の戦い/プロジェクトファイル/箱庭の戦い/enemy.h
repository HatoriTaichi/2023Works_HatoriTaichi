//=============================================================================
//
// 敵処理 [enemy.h]
// Author : 羽鳥太一
//
//=============================================================================
#ifndef _ENEMY_H_
#define _ENEMY_H_

//*****************************************************************************
// ヘッダファイルのインクルード
//*****************************************************************************
#include "main.h"
#include "scene.h"
#include "communicationdata.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define ENEMY_HEIGHT (80.0f)	// 自分の高さ
#define ENEMY_RADIUS (25.0f)	// 自分の半径
#define MAX_LIFE (100.0f)	// 体力
#define MAX_STOCK (10)	// 残気量

//*****************************************************************************
// 前方宣言
//*****************************************************************************
class CModel;

//*****************************************************************************
// クラス定義
//*****************************************************************************
class CEnemy : public CScene
{
public:
	CEnemy(LAYER_TYPE Layer = LAYER_TYPE::LAYER_00);	// デフォルトコンストラクタ
	~CEnemy();	// デフォルトデストラクタ
	HRESULT Init(void);	// ポリゴンの初期化
	void Uninit(void);	// ポリゴンの終了
	void Update(void);	// ポリゴンの更新
	void Draw(void);	// ポリゴンの描画
	int GetStock(void) { return m_nStock; }	// ゲッダー
	CCommunicationData::COMMUNICATION_DATA *GetCommuData(void) { return m_CommuData.GetCmmuData(); }	// ゲッダー
	bool ToBulletCollision(D3DXVECTOR3 pos, float fwigth, float fheight);	// 弾との当たり判定
	static CEnemy *Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot);	// 生成
	static void Recv(void);	// レシーブスレッド
private:
	void Attack(void);	// 攻撃
	void Move(void);	// 移動
	void Motion(void);	// モーション
	void StockCnt(void);	// ストックカウンタ
	static CCommunicationData m_CommuData;	// 通信データ
	vector<CModel*> m_pModel;	// モデル
	D3DXVECTOR3 m_Pos;		// 位置
	D3DXVECTOR3 m_PosOld;	// 前回の位置
	D3DXVECTOR3 m_Rot;		// 向き
	D3DXMATRIX m_MtxWold;	// ワールドマトリックス
	int m_nParts;	// パーツ数
	int m_nStock = MAX_STOCK;	// 残気
};

#endif