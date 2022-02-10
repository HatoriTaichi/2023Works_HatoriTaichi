#pragma once
//{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{
// ƒTƒEƒ“ƒhˆ— [sound.h]
// Author : SAKAI KAZUTO
//{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{
#ifndef _SOUND_H_
#define _SOUND_H_

#include "main.h"

//=================================
// ƒTƒEƒ“ƒhƒtƒ@ƒCƒ‹
//=================================
typedef enum
{
	SOUND_TITLE_BGM = 0,	//ƒ^ƒCƒgƒ‹BGM
	SOUND_OPERAT_BGM,		//‘€ìà–¾BGN
	SOUND_GAME_BGM,			//ƒQ[ƒ€BGM
	SOUND_RESULT_BGN,		//ƒŠƒUƒ‹ƒgBGN
	SOUND_PUSH_SE,			//ƒ{ƒ^ƒ“SE
	SOUND_SHOT_00,			//”­ŽËSE
	SOUND_RELOAD_00,		//ƒŠƒ[ƒhSE
	SOUND_EXPOSION,			//”š”­SE
	SOUND_LABEL_MAX,		//BGM.SE‚ÌÅ‘å”
} SOUND_LABEL;

//=============================================================================
// ƒvƒƒgƒ^ƒCƒvéŒ¾
//=============================================================================
HRESULT InitSound(HWND hWnd);
void UninitSound(void);
HRESULT PlaySound(SOUND_LABEL label);
void StopSound(SOUND_LABEL label);
void StopSound(void);

#endif