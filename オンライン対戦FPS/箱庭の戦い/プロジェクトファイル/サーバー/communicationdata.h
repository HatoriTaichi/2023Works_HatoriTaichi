//====================================================
//
// コミュニケーションデータのヘッダーファイル(communicationdata.h)
// Author : 羽鳥 太一
//
//====================================================
#ifndef _COMUNICASION_DATA_H_
#define _COMUNICASION_DATA_H_

//-------------------------------
// インクルード
//-------------------------------
#include "main.h"
#include "d3dx9.h"

//-------------------------------
// マクロ定義
//-------------------------------
#define MAX_BULLET (30)

//-------------------------------
// Classの定義
//-------------------------------
class CCommunicationData
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
		int nNumber;	// プレイヤーのインデックス
		int nStock;	// プレイヤーの残気
		bool bPushKey;	// プレイヤーがキーを押したか
		D3DXVECTOR3 Pos;	// プレイヤーの位置
		D3DXVECTOR3 Rot;	// 角度
		MOSTION Motion;	// モーションの種類
	} PLAYUER_DATA;

	typedef struct
	{
		D3DXVECTOR3 Rot;	// 弾の角度
		bool bUse;	// うったか
	} BULLET_DATA;

	typedef struct
	{
		PLAYUER_DATA Player;	// プレイヤーデータ
		BULLET_DATA Bullet[MAX_BULLET];	// 弾データ
		bool bConnect = false;	// 接続確認
	} COMMUNICATION_DATA;
	CCommunicationData();	// デフォルトコンストラクタ
	~CCommunicationData();	// デフォルトデストラクタ
	COMMUNICATION_DATA *GetCmmuData(void) { return &m_CommuData; }	// データのセッター
	void SetCmmuData(COMMUNICATION_DATA Data) { m_CommuData = Data; }	// データのゲッダー
private:
	SOCKET m_socket;	// ソケット
	COMMUNICATION_DATA m_CommuData;	// データ
};

#endif // _TCP_CLIENT_H_