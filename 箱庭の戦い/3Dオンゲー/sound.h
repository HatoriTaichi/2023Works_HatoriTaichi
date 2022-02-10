//=============================================================================
//
// サウンド処理 [sound.h]
// Author : 羽鳥太一
//
//=============================================================================
#ifndef _SOUND_H_
#define _SOUND_H_

//*****************************************************************************
// ヘッダファイルのインクルード
//*****************************************************************************
#include "main.h"
#include "DxLib.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define DX3D_SOUND_DISTANCE (10.0f)	// 1Mの定義

//*****************************************************************************
// クラス定義
//*****************************************************************************
class CSound
{
public:
	CSound();
	~CSound();
	enum class X2SOUND_LABEL
	{
		TITLE = 0,	// タイトル
		GONEXT,		// 次へ
		WIN,		// 勝ちボイス
		LOSE,		// 負けボイス
		RELOAD,		// リロード
		SHOOT,		// 銃声
		LABEL_MAX,	// サウンド合計
	};
	enum class DXLIBSOUND_LABEL
	{
		SHOOT = 0,	// 銃声
		FOOT_STEP,	// 足音
		LABEL_MAX,	// サウンド合計
	};
	HRESULT InitSound(HWND hWnd);	// 初期化
	void UninitSound(void);	// 終了
	void UpdateListener(VECTOR pos, VECTOR dir);	// リスナーの更新
	HRESULT PlaySound(X2SOUND_LABEL label);	// 再生
	void StopSound(X2SOUND_LABEL label);		// 決めたのストップ
	void StopSound(void);	// 全部ストップ
	void ControllVolume(X2SOUND_LABEL label, float fVolume) { m_apSourceVoice[(int)label]->SetVolume(fVolume); }	// 音量調節
	void InitDxlibSound(void);	// dxlibの初期化
	void UninitDxlibSound(void);	// dxlibの終了
	void PlayDxlibSound(DXLIBSOUND_LABEL label, float fdistance, VECTOR pos);	// 鳴らす設定
	static void ThSound(void) { PlaySoundMem(m_nSoundHandle, DX_PLAYTYPE_NORMAL); }	// dxlibのスレット分け
private:
	typedef struct
	{
		char *filename;		// ファイル名
		int nCntLoop;		// ループカウント
	} PARAM;
	static map<DXLIBSOUND_LABEL, string> m_DxlibSound;	// Dxlibのサウンド
	static PARAM m_aParam[(int)X2SOUND_LABEL::LABEL_MAX];		// 各音素材のパラメータ
	static int m_nSoundHandle;
	HRESULT CheckChunk(HANDLE hFile, DWORD format, DWORD *pChunkSize, DWORD *pChunkDataPosition);
	HRESULT ReadChunkData(HANDLE hFile, void *pBuffer, DWORD dwBuffersize, DWORD dwBufferoffset);
	IXAudio2 *m_pXAudio2 = NULL;								// XAudio2オブジェクトへのインターフェイス
	IXAudio2MasteringVoice *m_pMasteringVoice = NULL;			// マスターボイス
	IXAudio2SourceVoice *m_apSourceVoice[(int)X2SOUND_LABEL::LABEL_MAX] = {};	// ソースボイス
	BYTE *m_apDataAudio[(int)X2SOUND_LABEL::LABEL_MAX] = {};					// オーディオデータ
	DWORD m_aSizeAudio[(int)X2SOUND_LABEL::LABEL_MAX] = {};					// オーディオデータサイズ
	VECTOR m_ListenerPos;	// リスナーの位置
	VECTOR m_ListenerDir;	// リスナーの
};

#endif