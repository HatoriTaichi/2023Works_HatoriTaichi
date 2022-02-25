//*****************************************************************************
//
// サウンド処理 [sound.h]
// Author : 三橋錬
//
//*****************************************************************************
#ifndef _SOUND_H_
#define _SOUND_H_

//*****************************************************************************
// ヘッダファイルのインクルード
//*****************************************************************************
#include "main.h"

//*****************************************************************************
// クラス定義
//*****************************************************************************
class CSound
{
public:
	CSound();
	~CSound();

	// サウンドファイル
	typedef enum
	{
		SOUND_LABEL_BGM_TITLE,		// BGMタイトル
		SOUND_LABEL_BGM_GAME,		// BGMゲーム

		SOUND_LABEL_SE_TAP,
		SOUND_LABEL_SE_START,

		SOUND_LABEL_MAX
	} SOUND_LABEL;

	HRESULT Init(HWND hWnd);
	void Uninit(void);
	HRESULT Play(SOUND_LABEL label);
	void Stop(SOUND_LABEL label);
	void Stop(void);

	void ControllVoice(SOUND_LABEL label, float fVolume) { m_apSourceVoice[label]->SetVolume(fVolume); }	//音量調整

private:
	// パラメータ構造体
	typedef struct
	{
		char *m_filename;			// ファイル名
		int m_nCntLoop;				// ループカウント
	} PARAM;

	HRESULT CheckChunk(HANDLE hFile, DWORD format, DWORD *pChunkSize, DWORD *pChunkDataPosition);
	HRESULT ReadChunkData(HANDLE hFile, void *pBuffer, DWORD dwBuffersize, DWORD dwBufferoffset);

	IXAudio2 *m_pXAudio2 = NULL;								// XAudio2オブジェクトへのインターフェイス
	IXAudio2MasteringVoice *m_pMasteringVoice = NULL;			// マスターボイス
	IXAudio2SourceVoice *m_apSourceVoice[SOUND_LABEL_MAX] = {};	// ソースボイス
	BYTE *m_apDataAudio[SOUND_LABEL_MAX] = {};					// オーディオデータ
	DWORD m_aSizeAudio[SOUND_LABEL_MAX] = {};					// オーディオデータサイズ
																
	static PARAM m_aParam[SOUND_LABEL_MAX];						// 各音声素材のパラメータ
};

#endif