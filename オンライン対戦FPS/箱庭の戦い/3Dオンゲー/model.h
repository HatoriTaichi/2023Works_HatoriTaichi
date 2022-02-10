//=============================================================================
//
// Xファイルモデル処理 [sceneX.h]
// Author : 羽鳥太一&鶴間俊樹
//
//=============================================================================
#ifndef _SCENEX_H_
#define _SCENEX_H_

//*****************************************************************************
// ヘッダファイルのインクルード
//*****************************************************************************
#include "main.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define BOXVTX_MAX (8)	// 箱の頂点数
#define BOX_SURFACE (6)	// 箱の面の数
#define PLAYER_WIDTH (20.0f)	// プレイヤーの幅

//*****************************************************************************
// クラス定義
//*****************************************************************************
class CModel
{
public:
	//---------------------------
	// 列挙型
	//---------------------------
	enum class MOSTION
	{
		NEUTRAL = 0,	// ニュートラルモーション
		WORK,			// 歩く
		BUCK_WORK,		// 後ろ歩き
		ATTACK,			// 攻撃
		MAX				// リストの数
	};

	//---------------------------
	// 構造体
	//---------------------------
	typedef struct
	{
		float fPosX;	// 位置X
		float fPosY;	// 位置Y
		float fPosZ;	// 位置Z
		float fRotX;	// 向きX
		float fRotY;	// 向きY
		float fRotZ;	// 向きZ
	} KEY;

	typedef struct
	{
		float fFrame;	// 再生フレーム
		KEY aKey;		// モデル毎のキー要素
	} KEYINFO;

	typedef struct
	{
		bool bLoop;			// ループするか
		int nNumKey;		// キーの総数
		int nKeyCnt;		// キーカウント
		float fFrameCnt;	// モーションカウント
		vector<KEYINFO*> aKeyinfo;	// キーの情報(キーの総数分)
	} MOTIONINFO;

	typedef struct
	{
		LPD3DXMESH pMesh;		// メッシュ（頂点情報）へのポインタ
		LPD3DXBUFFER pBuffMat;	// マテリアルへのポインタ
		DWORD nNumMat;			// マテリアルの数
		D3DXVECTOR3 vtxMin = D3DXVECTOR3(10000.0f, 10000.0f, 10000.0f);	// 頂点の端情報
		D3DXVECTOR3	vtxMax = D3DXVECTOR3(-10000.0f, -10000.0f, -10000.0f);	// 頂点の端情報
	}MODEL_DATA;

	//---------------------------
	// 列挙型
	//---------------------------
	enum class TYPE
	{
		PLAYER_BODY = 0,	// 体
		PLAYER_HEAD,		// 頭
		PLAYER_RIGHTARM,	// 右腕
		PLAYER_RIGHTHAND,	// 右手
		PLAYER_LEFTARM,		// 左腕
		PLAYER_LEFTHAND,	// 左手
		PLAYER_RIGHTFOOT,	// 右太もも
		PLAYER_RIGHTLEG,	// 右足
		PLAYER_LEFTFOOT,	// 左太もも
		PLAYER_LEFTLEG,		// 左足
		PLAYER_GUN,			// 銃
		TRANSPARENT_BOX,	// 透明な箱
		CONTAINER,			// コンテナ
		PORT_FLOOR,			// 海ステージ床
		MAX,
	};

	CModel();	// デフォルトコンストラクタ
	~CModel();	// デフォルトデストラクタ
	HRESULT Init(void);	// ポリゴンの初期化
	HRESULT Init(int *nPreants, FILE *pFile);	// ポリゴンの初期化
	void Uninit(void);	// ポリゴンの終了
	void Update(void);	// ポリゴンの更新
	void Draw(void);	// ポリゴンの描画
	bool BoxCollision(D3DXVECTOR3 *pos, D3DXVECTOR3 posold);	// 当たり判定
	void SetPos(D3DXVECTOR3 pos) { m_Pos = pos; }	// セッター
	void SetRot(D3DXVECTOR3 rot) { m_Rot = rot; }	// セッター
	void SetScale(D3DXVECTOR3 scale) { m_Scale = scale; }	// セッター
	void SetMatrix(D3DXMATRIX mtx) { m_MtxWold = mtx; }	// セッター
	void SetPrent(CModel *pModel) { m_pPrent = pModel; }	// セッター
	D3DXVECTOR3 GetPos(void) { return m_Pos; }		// ゲッター
	D3DXVECTOR3 GetRot(void) { return m_Rot; }		// ゲッター
	D3DXVECTOR3 GetScale(void) { return m_Scale; }		// ゲッター
	D3DXMATRIX GetMatrix(void) { return m_MtxWold; }	// ゲッター
	MODEL_DATA *GetModelData(void) { return m_aModelData; }
	D3DXVECTOR3 GetVMin(TYPE type) { return m_aModelData[(int)type].vtxMin; }	// ゲッター
	D3DXVECTOR3 GetVMax(TYPE type) { return m_aModelData[(int)type].vtxMax; }	// ゲッター
	MOTIONINFO *GetMotion(int nMotion) { return &m_Motion[nMotion]; }	// ゲッター
	static HRESULT Load(void);	// モデルデータの読み込み
	static void UnLoad(void);	// モデルデータの破棄
	static CModel *Create(TYPE type);	// 生成
	static CModel *Create(TYPE type, D3DXVECTOR3 scale, int *nPreants, FILE *pFile);	// 生成
private:
	void UpdateColliSion(void);	// 当たり判定の更新
	static MODEL_DATA *m_aModelData;	// 全モデルの情報
	vector<LPDIRECT3DTEXTURE9> m_pTexture;	// テクスチャ
	TYPE m_Type;	// モデルの種類
	MOTIONINFO m_Motion[(int)MOSTION::MAX];	// モーション
	CModel *m_pPrent;	// 親のモデル
	D3DXMATRIX m_MtxWold;	// ワールドマトリックス
	D3DXVECTOR3 m_Pos;		// 位置
	D3DXVECTOR3 m_Scale;	// スケール
	D3DXVECTOR3 m_Rot;		// 向き
	D3DXVECTOR3 m_vtxMin = D3DXVECTOR3(10000.0f, 10000.0f, 10000.0f);	// 頂点の端情報
	D3DXVECTOR3	m_vtxMax = D3DXVECTOR3(-10000.0f, -10000.0f, -10000.0f);	// 頂点の端情報
	D3DXVECTOR3 m_BoxVtx[BOXVTX_MAX];	// 箱の頂点
	D3DXVECTOR3 m_Nor[BOX_SURFACE];	// 箱の面の法線
	D3DXVECTOR3 m_CenterVtx[BOX_SURFACE];	// 箱の面の中心点
};

#endif
