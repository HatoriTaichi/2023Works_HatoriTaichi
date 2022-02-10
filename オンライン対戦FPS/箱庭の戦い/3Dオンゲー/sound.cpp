//=============================================================================
//
// サウンド処理 [sound.cpp]
// Author : 羽鳥太一
//
//=============================================================================
//=============================================================================
// インクルード
//=============================================================================
#include "sound.h"
#include "manager.h"
#include "renderer.h"
#include "camera.h"
#include "manager.h"

//=============================================================================
// 静的メンバ変数宣言
//=============================================================================
CSound::PARAM CSound::m_aParam[(int)X2SOUND_LABEL::LABEL_MAX] =
{
	{ "data/Sound/Bgm/Title.wav", -1 },		// タイトル
	{ "data/Sound/Se/GoNext.wav", 0 },		// 次へ
	{ "data/Sound/Se/WinVoice.wav", 0 },	// 勝ち
	{ "data/Sound/Se/LoseVoice.wav", 0 },	// 負け
	{ "data/Sound/Se/Reload.wav", 0 },		// リロード
	{ "data/Sound/Se/Shoot.wav", 0 },		// 銃声
};
map<CSound::DXLIBSOUND_LABEL, string> CSound::m_DxlibSound =
{
	{ DXLIBSOUND_LABEL::SHOOT, "data/Sound/Se/Shoot.wav" },	// 銃声
	{ DXLIBSOUND_LABEL::FOOT_STEP, "data/Sound/Se/FootStep.wav" },	// 足音
};
int CSound::m_nSoundHandle = 0;

//=============================================================================
// デフォルトコンストラクタ
//=============================================================================
CSound::CSound()
{

}

//=============================================================================
// デフォルトデストラクタ
//=============================================================================
CSound::~CSound()
{

}

//=============================================================================
// 初期化
//=============================================================================
HRESULT CSound::InitSound(HWND hWnd)
{
	HRESULT hr;

	// COMライブラリの初期化
	CoInitializeEx(NULL, COINIT_MULTITHREADED);

	// XAudio2オブジェクトの作成
	hr = XAudio2Create(&m_pXAudio2, 0);
	if (FAILED(hr))
	{
		// COMライブラリの終了処理
		CoUninitialize();
		return E_FAIL;
	}

	// マスターボイスの生成
	hr = m_pXAudio2->CreateMasteringVoice(&m_pMasteringVoice);
	if (FAILED(hr))
	{
		if (m_pXAudio2)
		{
			// XAudio2オブジェクトの開放
			m_pXAudio2->Release();
		}

		// COMライブラリの終了処理
		CoUninitialize();
		return E_FAIL;
	}

	// サウンドデータの初期化
	for (int nCntSound = 0; nCntSound < (int)X2SOUND_LABEL::LABEL_MAX; nCntSound++)
	{
		HANDLE hFile;
		DWORD dwChunkSize = 0;
		DWORD dwChunkPosition = 0;
		DWORD filetype;
		WAVEFORMATEXTENSIBLE wfx;
		XAUDIO2_BUFFER buffer;

		// バッファのクリア
		memset(&wfx, 0, sizeof(WAVEFORMATEXTENSIBLE));
		memset(&buffer, 0, sizeof(XAUDIO2_BUFFER));

		// サウンドデータファイルの生成
		hFile = CreateFile(m_aParam[nCntSound].filename, GENERIC_READ,
			FILE_SHARE_READ, NULL, OPEN_EXISTING, 0, NULL);
		if (hFile == INVALID_HANDLE_VALUE)
		{
			return HRESULT_FROM_WIN32(GetLastError());
		}
		if (SetFilePointer(hFile, 0, NULL, FILE_BEGIN) == INVALID_SET_FILE_POINTER)
		{
			return HRESULT_FROM_WIN32(GetLastError());
		}

		// WAVEファイルのチェック
		hr = CheckChunk(hFile, 'FFIR', &dwChunkSize, &dwChunkPosition);
		if (FAILED(hr))
		{
			return S_FALSE;
		}
		hr = ReadChunkData(hFile, &filetype, sizeof(DWORD), dwChunkPosition);
		if (FAILED(hr))
		{
			return S_FALSE;
		}
		if (filetype != 'EVAW')
		{
			return S_FALSE;
		}

		// フォーマットチェック
		hr = CheckChunk(hFile, ' tmf', &dwChunkSize, &dwChunkPosition);
		if (FAILED(hr))
		{
			return S_FALSE;
		}
		hr = ReadChunkData(hFile, &wfx, dwChunkSize, dwChunkPosition);
		if (FAILED(hr))
		{
			return S_FALSE;
		}

		// オーディオデータ読み込み
		hr = CheckChunk(hFile, 'atad', &m_aSizeAudio[nCntSound], &dwChunkPosition);
		if (FAILED(hr))
		{
			return S_FALSE;
		}
		m_apDataAudio[nCntSound] = (BYTE*)malloc(m_aSizeAudio[nCntSound]);
		hr = ReadChunkData(hFile, m_apDataAudio[nCntSound], m_aSizeAudio[nCntSound], dwChunkPosition);
		if (FAILED(hr))
		{
			return S_FALSE;
		}

		m_pXAudio2->CreateSourceVoice(&m_apSourceVoice[nCntSound], &(wfx.Format));

		// バッファの設定
		memset(&buffer, 0, sizeof(XAUDIO2_BUFFER));
		buffer.AudioBytes = m_aSizeAudio[nCntSound];
		buffer.pAudioData = m_apDataAudio[nCntSound];
		buffer.Flags = XAUDIO2_END_OF_STREAM;
		buffer.LoopCount = m_aParam[nCntSound].nCntLoop;

		m_apSourceVoice[nCntSound]->SubmitSourceBuffer(&buffer);

		// ファイルをクローズ
		CloseHandle(hFile);
	}

	SetUserWindow(hWnd);

	return S_OK;
}

//=============================================================================
// リスナーの更新
//=============================================================================
void CSound::UpdateListener(VECTOR pos, VECTOR dir)
{
	// リスナーの位置を初期化
	m_ListenerPos = pos;

	// リスナーの向きを初期化
	m_ListenerDir = dir;

	// リスナーの位置と向きを設定
	Set3DSoundListenerPosAndFrontPos_UpVecY(m_ListenerPos, VAdd(m_ListenerPos, m_ListenerDir));
}

//=============================================================================
// dxlibの初期化
//=============================================================================
void CSound::InitDxlibSound(void)
{
	// １メートルに相当する値を設定する
	Set3DSoundOneMetre(DX3D_SOUND_DISTANCE);

	ChangeWindowMode(TRUE);

	SetEnableXAudioFlag(TRUE);

	SetNotWinFlag(TRUE);

	// ＤＸライブラリの初期化
	DxLib_Init();

	// 描画先を裏画面にする
	SetDrawScreen(DX_SCREEN_BACK);

	// リスナーの位置を初期化
	m_ListenerPos = VGet(0.0f, 0.0f, 0.0f);

	// リスナーの向きを初期化
	m_ListenerDir.x = 0.0f;
	m_ListenerDir.y = 0.0f;
	m_ListenerDir.z = 1.0f;

	// リスナーの位置と向きを設定
	Set3DSoundListenerPosAndFrontPos_UpVecY(m_ListenerPos, VAdd(m_ListenerPos, m_ListenerDir));
}

//=============================================================================
// dxlibの終了
//=============================================================================
void CSound::UninitDxlibSound(void)
{
	// サウンドハンドルの削除
	DeleteSoundMem(m_nSoundHandle);

	// ＤＸライブラリの後始末
	DxLib_End();
}

//=============================================================================
// 鳴らす設定
//=============================================================================
void CSound::PlayDxlibSound(DXLIBSOUND_LABEL label, float fdistance, VECTOR pos)
{
	// 音を３Ｄサウンドとして読み込む
	SetCreate3DSoundFlag(TRUE);
	m_nSoundHandle = LoadSoundMem(m_DxlibSound[label].c_str());
	SetCreate3DSoundFlag(FALSE);

	// 音が聞こえる距離を設定する
	Set3DRadiusSoundMem(fdistance, m_nSoundHandle);

	// 音を鳴らす位置を設定する
	Set3DPositionSoundMem(pos, m_nSoundHandle);

	// リバーブエフェクトパラメータをプリセット「講堂」を使用して設定
	Set3DPresetReverbParamSoundMem(DX_REVERB_PRESET_PLAIN, m_nSoundHandle);

	PlaySoundMem(m_nSoundHandle, DX_PLAYTYPE_BACK);

	//thread th(ThSound);

	//th.detach();
}

//=============================================================================
// 終了処理
//=============================================================================
void CSound::UninitSound(void)
{
	// 一時停止
	for (int nCntSound = 0; nCntSound < (int)X2SOUND_LABEL::LABEL_MAX; nCntSound++)
	{
		if (m_apSourceVoice[nCntSound] != NULL)
		{
			// 一時停止
			m_apSourceVoice[nCntSound]->Stop(0);

			// ソースボイスの破棄
			m_apSourceVoice[nCntSound]->DestroyVoice();

			// オーディオデータの開放
			free(m_apDataAudio[nCntSound]);
		}
	}

	// マスターボイスの破棄
	m_pMasteringVoice->DestroyVoice();

	if (m_pXAudio2)
	{
		// XAudio2オブジェクトの開放
		m_pXAudio2->Release();
	}

	// COMライブラリの終了処理
	CoUninitialize();
}

//=============================================================================
// セグメント再生(停止)
//=============================================================================
HRESULT CSound::PlaySound(X2SOUND_LABEL label)
{
	XAUDIO2_VOICE_STATE xa2state;
	XAUDIO2_BUFFER       buffer;

	// バッファの設定
	memset(&buffer, 0, sizeof(XAUDIO2_BUFFER));
	buffer.AudioBytes = m_aSizeAudio[(int)label];
	buffer.pAudioData = m_apDataAudio[(int)label];
	buffer.Flags = XAUDIO2_END_OF_STREAM;
	buffer.LoopCount = m_aParam[(int)label].nCntLoop;
	buffer.PlayBegin = 4000;

	// 状態取得
	m_apSourceVoice[(int)label]->GetState(&xa2state);
	if (xa2state.BuffersQueued != 0)
	{// 再生中
	 // 一時停止
		m_apSourceVoice[(int)label]->Stop(0);

		// クリア
		m_apSourceVoice[(int)label]->FlushSourceBuffers();
	}

	// 登録
	m_apSourceVoice[(int)label]->SubmitSourceBuffer(&buffer);

	// 再生
	m_apSourceVoice[(int)label]->Start(0);

	return S_OK;
}

//=============================================================================
// セグメント停止
//=============================================================================
void CSound::StopSound(X2SOUND_LABEL label)
{
	XAUDIO2_VOICE_STATE xa2state;

	// 状態取得
	m_apSourceVoice[(int)label]->GetState(&xa2state);
	if (xa2state.BuffersQueued != 0)
	{	// 再生中
		// 一時停止
		m_apSourceVoice[(int)label]->Stop(0);

		// クリア
		m_apSourceVoice[(int)label]->FlushSourceBuffers();
	}
}

//=============================================================================
// セグメント停止
//=============================================================================
void CSound::StopSound(void)
{
	for (int nCntSound = 0; nCntSound < (int)X2SOUND_LABEL::LABEL_MAX; nCntSound++)
	{
		if (m_apSourceVoice[nCntSound] != NULL)
		{
			// 一時停止
			m_apSourceVoice[nCntSound]->Stop(0);

			// クリア
			m_apSourceVoice[nCntSound]->FlushSourceBuffers();
		}
	}
}

//=============================================================================
// チャンクのチェック
//=============================================================================
HRESULT CSound::CheckChunk(HANDLE hFile, DWORD format, DWORD *pChunkSize, DWORD *pChunkDataPosition)
{
	HRESULT hr = S_OK;
	DWORD dwRead;
	DWORD dwChunkType;
	DWORD dwChunkDataSize;
	DWORD dwRIFFDataSize = 0;
	DWORD dwFileType;
	DWORD dwBytesRead = 0;
	DWORD dwOffset = 0;

	if (SetFilePointer(hFile, 0, NULL, FILE_BEGIN) == INVALID_SET_FILE_POINTER)
	{// ファイルポインタを先頭に移動
		return HRESULT_FROM_WIN32(GetLastError());
	}

	while (hr == S_OK)
	{
		if (ReadFile(hFile, &dwChunkType, sizeof(DWORD), &dwRead, NULL) == 0)
		{// チャンクの読み込み
			hr = HRESULT_FROM_WIN32(GetLastError());
		}

		if (ReadFile(hFile, &dwChunkDataSize, sizeof(DWORD), &dwRead, NULL) == 0)
		{// チャンクデータの読み込み
			hr = HRESULT_FROM_WIN32(GetLastError());
		}

		switch (dwChunkType)
		{
		case 'FFIR':
			dwRIFFDataSize = dwChunkDataSize;
			dwChunkDataSize = 4;
			if (ReadFile(hFile, &dwFileType, sizeof(DWORD), &dwRead, NULL) == 0)
			{// ファイルタイプの読み込み
				hr = HRESULT_FROM_WIN32(GetLastError());
			}
			break;

		default:
			if (SetFilePointer(hFile, dwChunkDataSize, NULL, FILE_CURRENT) == INVALID_SET_FILE_POINTER)
			{// ファイルポインタをチャンクデータ分移動
				return HRESULT_FROM_WIN32(GetLastError());
			}
		}

		dwOffset += sizeof(DWORD) * 2;
		if (dwChunkType == format)
		{
			*pChunkSize = dwChunkDataSize;
			*pChunkDataPosition = dwOffset;

			return S_OK;
		}

		dwOffset += dwChunkDataSize;
		if (dwBytesRead >= dwRIFFDataSize)
		{
			return S_FALSE;
		}
	}

	return S_OK;
}

//=============================================================================
// チャンクデータの読み込み
//=============================================================================
HRESULT CSound::ReadChunkData(HANDLE hFile, void *pBuffer, DWORD dwBuffersize, DWORD dwBufferoffset)
{
	DWORD dwRead;

	if (SetFilePointer(hFile, dwBufferoffset, NULL, FILE_BEGIN) == INVALID_SET_FILE_POINTER)
	{// ファイルポインタを指定位置まで移動
		return HRESULT_FROM_WIN32(GetLastError());
	}

	if (ReadFile(hFile, pBuffer, dwBuffersize, &dwRead, NULL) == 0)
	{// データの読み込み
		return HRESULT_FROM_WIN32(GetLastError());
	}

	return S_OK;
}