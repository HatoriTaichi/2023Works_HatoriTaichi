//=============================================================================
//
// プレイヤー処理 [player.h]
// Author : 羽鳥太一
//
//=============================================================================
#ifndef _PLAYER_H_
#define _PLAYER_H_

//*****************************************************************************
// ヘッダファイルのインクルード
//*****************************************************************************
#include "main.h"
#include "scene.h"
#include "communicationdata.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define DUSH_SPEED (5.0f)
#define NORMAL_SPEED (1.0f)
#define PLAYER_HEIGHT (60.0f)	// 自分の高さ
#define PLAYER_RADIUS (25.0f)	// 自分の半径
#define MAX_LIFE (100.0f)	// 体力
#define RECOVERY_TIME (FPS * 3)	// 回復するまでの時間
#define MAX_STOCK (10)	// 残気量

//*****************************************************************************
// 前方宣言
//*****************************************************************************
class CModel;
class CUiObj;

//*****************************************************************************
// クラス定義
//*****************************************************************************
class CPlayer : public CScene
{
public:
	CPlayer(LAYER_TYPE Layer = LAYER_TYPE::LAYER_01);	// デフォルトコンストラクタ
	~CPlayer();	// デフォルトデストラクタ
	HRESULT Init(void);	// ポリゴンの初期化
	void Uninit(void);	// ポリゴンの終了
	void Update(void);	// ポリゴンの更新
	void Draw(void);	// ポリゴンの描画
	bool ToBulletCollision(D3DXVECTOR3 pos, float fwigth, float fheight);	// 弾との当たり判定
	static CPlayer *Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot);	// 生成
	void SetIndex(int nIndex) { CCommunicationData::COMMUNICATION_DATA *pData = m_CommuData.GetCmmuData(); pData->Player.nNumber = nIndex; }	// セッター
	void SetEndBattle(bool bEnd) { m_bEndBattle = bEnd; }	// セッター
	D3DXVECTOR3 GetPos(void) { return m_Pos; }	// ゲッダー
	D3DXVECTOR3 GetRot(void) { return m_Rot; }	// ゲッダー
	bool GetEndBattle(void) { return m_bEndBattle; }	// ゲッダー
	int GetStock(void) { return m_nStock; }	// ゲッダー
	CCommunicationData::COMMUNICATION_DATA *GetCommuData(void) { return m_CommuData.GetCmmuData(); }	// ゲッダー
private:
	void Move(void);	// 移動
	void Attack(void);	// 攻撃
	void Motion(void);	// モーション
	void Damage(void);	// ダメージ
	void CntStock(void);	// ストックカウンタ
	CCommunicationData m_CommuData;	// 通信データクラス
	CModel::MOSTION m_Motion;	// モーションの種類
	vector<CModel*> m_pModel;	// モデル
	vector<CUiObj*> m_Boold;	// 血
	D3DXVECTOR3 m_Pos;		// 位置
	D3DXVECTOR3 m_PosOld;	// 前回位置
	D3DXVECTOR3 m_Rot;		// 向き
	D3DXMATRIX m_MtxWold;	// ワールドマトリックス
	int m_nParts;		// パーツ数
	int m_nDamageTime;	// ダメージの一定時間カウント
	int m_nStock = MAX_STOCK;	// 残気
	int m_nRateTime;	// レート
	int m_nReloadCnt;	// リロード時間
	int m_nIvbTime;		// 無敵時間
	float m_fMoveSpeed;	// 移動スピード
	float m_fLife = MAX_LIFE;	// 体力
	bool m_bRespawn;	// リス最中
	bool m_bDamageTime;	// ダメージ一定時間ダメージ
	bool m_bHitDamage;	// ダメージ
	bool m_bAttack;		// 攻撃してるか
	bool m_bEndBattle;	// 勝敗
	bool m_bShoot;		// 打てるか
	bool m_bReload;		// リロード中か
	bool m_bInvincible;	// 無敵か
};

#endif