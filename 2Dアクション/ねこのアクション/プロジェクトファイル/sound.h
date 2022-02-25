#pragma once
//Å{Å{Å{Å{Å{Å{Å{Å{Å{Å{Å{Å{Å{Å{Å{Å{Å{Å{Å{Å{Å{Å{Å{Å{Å{Å{Å{Å{Å{Å{Å{Å{Å{Å{Å{Å{Å{Å{
// ÉTÉEÉìÉhèàóù [sound.h]
// Author : SAKAI KAZUTO
//Å{Å{Å{Å{Å{Å{Å{Å{Å{Å{Å{Å{Å{Å{Å{Å{Å{Å{Å{Å{Å{Å{Å{Å{Å{Å{Å{Å{Å{Å{Å{Å{Å{Å{Å{Å{Å{Å{
#ifndef _SOUND_H_
#define _SOUND_H_

#include "main.h"

//=================================
// ÉTÉEÉìÉhÉtÉ@ÉCÉã
//=================================
typedef enum
{
	SOUND_LABEL_BGM000 = 0,		// É^ÉCÉgÉã
	SOUND_LABEL_BGM001,			// ÉQÅ[ÉÄ
	SOUND_LABEL_BGM002,			// ÉäÉUÉãÉg
	SOUND_LABEL_BGM003,			// ÉQÅ[ÉÄÉIÅ[Éo
	SOUND_LABEL_BGM004,			// É{ÉX
	SOUND_LABEL_SE000,			// ok
	SOUND_LABEL_SE001,			// ÉVÉáÉbÉg
	SOUND_LABEL_SE002,			// ìñÇΩÇ¡ÇΩ
	SOUND_LABEL_MAX,
} SOUND_LABEL;

//=============================================================================
// ÉvÉçÉgÉ^ÉCÉvêÈåæ
//=============================================================================
HRESULT InitSound(HWND hWnd);
void UninitSound(void);
HRESULT PlaySound(SOUND_LABEL label);
void StopSound(SOUND_LABEL label);
void StopSound(void);

#endif