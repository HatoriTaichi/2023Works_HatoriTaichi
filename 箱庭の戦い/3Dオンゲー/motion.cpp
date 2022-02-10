//=============================================================================
//
// モーション処理 [motion.cpp]
// Author : 羽鳥太一
//
//=============================================================================
//=============================================================================
// インクルード
//=============================================================================
#include "motion.h"

//=============================================================================
// デフォルトコンストラクタ
//=============================================================================
CMotion::CMotion()
{

}

//=============================================================================
// デフォルトデストラクタ
//=============================================================================
CMotion::~CMotion()
{

}

//=============================================================================
// モーションの再生
//=============================================================================
bool CMotion::PlayMotin(CModel::MOTIONINFO *motion, D3DXVECTOR3 *pos, D3DXVECTOR3 *rot)
{
	D3DXVECTOR3 PosAsk;		//求める値位置X
	D3DXVECTOR3 RotAsk;		//求める値向きX
	D3DXVECTOR3 PosDifference;	//位置の差分X
	D3DXVECTOR3 RotDifference;	//向きの差分X
	bool bEnd = false;

	if (motion->nKeyCnt < (motion->nNumKey - 1))
	{
		PosDifference.x = motion->aKeyinfo[motion->nKeyCnt + 1]->aKey.fPosX - motion->aKeyinfo[motion->nKeyCnt]->aKey.fPosX;
		PosDifference.y = motion->aKeyinfo[motion->nKeyCnt + 1]->aKey.fPosY - motion->aKeyinfo[motion->nKeyCnt]->aKey.fPosY;
		PosDifference.z = motion->aKeyinfo[motion->nKeyCnt + 1]->aKey.fPosZ - motion->aKeyinfo[motion->nKeyCnt]->aKey.fPosZ;

		RotDifference.x = motion->aKeyinfo[motion->nKeyCnt + 1]->aKey.fRotX - motion->aKeyinfo[motion->nKeyCnt]->aKey.fRotX;
		RotDifference.y = motion->aKeyinfo[motion->nKeyCnt + 1]->aKey.fRotY - motion->aKeyinfo[motion->nKeyCnt]->aKey.fRotY;
		RotDifference.z = motion->aKeyinfo[motion->nKeyCnt + 1]->aKey.fRotZ - motion->aKeyinfo[motion->nKeyCnt]->aKey.fRotZ;

		PosAsk.x = motion->aKeyinfo[motion->nKeyCnt]->aKey.fPosX + PosDifference.x * (motion->fFrameCnt / motion->aKeyinfo[motion->nKeyCnt]->fFrame);
		PosAsk.y = motion->aKeyinfo[motion->nKeyCnt]->aKey.fPosY + PosDifference.y * (motion->fFrameCnt / motion->aKeyinfo[motion->nKeyCnt]->fFrame);
		PosAsk.z = motion->aKeyinfo[motion->nKeyCnt]->aKey.fPosZ + PosDifference.z * (motion->fFrameCnt / motion->aKeyinfo[motion->nKeyCnt]->fFrame);

		RotAsk.x = motion->aKeyinfo[motion->nKeyCnt]->aKey.fRotX + RotDifference.x * (motion->fFrameCnt / motion->aKeyinfo[motion->nKeyCnt]->fFrame);
		RotAsk.y = motion->aKeyinfo[motion->nKeyCnt]->aKey.fRotY + RotDifference.y * (motion->fFrameCnt / motion->aKeyinfo[motion->nKeyCnt]->fFrame);
		RotAsk.z = motion->aKeyinfo[motion->nKeyCnt]->aKey.fRotZ + RotDifference.z * (motion->fFrameCnt / motion->aKeyinfo[motion->nKeyCnt]->fFrame);

		pos->x = PosAsk.x;
		pos->y = PosAsk.y;
		pos->z = PosAsk.z;

		rot->x = RotAsk.x;
		rot->y = RotAsk.y;
		rot->z = RotAsk.z;

		motion->fFrameCnt += 1.0f;
		//モーションカウンタがフレーム数を超えたら
		if (motion->fFrameCnt >= motion->aKeyinfo[motion->nKeyCnt]->fFrame)
		{
			//次のキー
			motion->nKeyCnt++;
			//モーションカウンタ初期化
			motion->fFrameCnt = 0.0f;
			bEnd = false;
		}
	}
	else if (motion->nKeyCnt == (motion->nNumKey - 1))
	{
		PosDifference.x = motion->aKeyinfo[motion->nKeyCnt - 1]->aKey.fPosX - motion->aKeyinfo[motion->nKeyCnt]->aKey.fPosX;
		PosDifference.y = motion->aKeyinfo[motion->nKeyCnt - 1]->aKey.fPosY - motion->aKeyinfo[motion->nKeyCnt]->aKey.fPosY;
		PosDifference.z = motion->aKeyinfo[motion->nKeyCnt - 1]->aKey.fPosZ - motion->aKeyinfo[motion->nKeyCnt]->aKey.fPosZ;

		RotDifference.x = motion->aKeyinfo[motion->nKeyCnt - 1]->aKey.fRotX - motion->aKeyinfo[motion->nKeyCnt]->aKey.fRotX;
		RotDifference.y = motion->aKeyinfo[motion->nKeyCnt - 1]->aKey.fRotY - motion->aKeyinfo[motion->nKeyCnt]->aKey.fRotY;
		RotDifference.z = motion->aKeyinfo[motion->nKeyCnt - 1]->aKey.fRotZ - motion->aKeyinfo[motion->nKeyCnt]->aKey.fRotZ;

		PosAsk.x = motion->aKeyinfo[motion->nKeyCnt]->aKey.fPosX + PosDifference.x * (motion->fFrameCnt / motion->aKeyinfo[motion->nKeyCnt]->fFrame);
		PosAsk.y = motion->aKeyinfo[motion->nKeyCnt]->aKey.fPosY + PosDifference.y * (motion->fFrameCnt / motion->aKeyinfo[motion->nKeyCnt]->fFrame);
		PosAsk.z = motion->aKeyinfo[motion->nKeyCnt]->aKey.fPosZ + PosDifference.z * (motion->fFrameCnt / motion->aKeyinfo[motion->nKeyCnt]->fFrame);

		RotAsk.x = motion->aKeyinfo[motion->nKeyCnt]->aKey.fRotX + RotDifference.x * (motion->fFrameCnt / motion->aKeyinfo[motion->nKeyCnt]->fFrame);
		RotAsk.y = motion->aKeyinfo[motion->nKeyCnt]->aKey.fRotY + RotDifference.y * (motion->fFrameCnt / motion->aKeyinfo[motion->nKeyCnt]->fFrame);
		RotAsk.z = motion->aKeyinfo[motion->nKeyCnt]->aKey.fRotZ + RotDifference.z * (motion->fFrameCnt / motion->aKeyinfo[motion->nKeyCnt]->fFrame);

		pos->x = PosAsk.x;
		pos->y = PosAsk.y;
		pos->z = PosAsk.z;

		rot->x = RotAsk.x;
		rot->y = RotAsk.y;
		rot->z = RotAsk.z;

		motion->fFrameCnt += 1.0f;
		//モーションカウンタがフレーム数を超えたら
		if (motion->fFrameCnt >= motion->aKeyinfo[motion->nKeyCnt]->fFrame)
		{
			if (motion->bLoop == true)
			{
				//次のキー
				motion->nKeyCnt = 0;
			}
			else
			{
				motion->nKeyCnt = 0;
				bEnd = true;
			}
			//モーションカウンタ初期化
			motion->fFrameCnt = 0.0f;
		}
	}

	return bEnd;
}