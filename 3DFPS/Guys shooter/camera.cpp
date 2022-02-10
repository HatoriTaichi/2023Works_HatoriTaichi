//---------------------------
//�C���N���[�h�t�@�C��
//---------------------------
#include <stdio.h>
#include "camara.h"
#include "keyinput.h"
#include "mouseinput.h"
#include "player.h"

//---------------------------
//�O���[�o���ϐ�
//---------------------------
Camera	g_Camera[MAX_CAMERA];	//�J����
int		g_move;

//--------------------------- 
//����������
//---------------------------
HRESULT InitCamera(void)
{
	g_Camera[0].PosV = (D3DXVECTOR3(0.0f, 25.0f, 5.0f));
	g_Camera[0].PosR = (D3DXVECTOR3(0.0f, 25.0f, CAMERA_DESTAANCE));
	g_Camera[0].Rot = (D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	g_Camera[0].VecU = (D3DXVECTOR3(0.0f, 1.0f, 0.0f));
	g_Camera[0].viewport.X = 0;
	g_Camera[0].viewport.Y = 0;
	g_Camera[0].viewport.Width = SCREEN_WIDTH;
	g_Camera[0].viewport.Height = SCREEN_HEIGHT;
	g_Camera[0].viewport.MinZ = 0.0f;
	g_Camera[0].viewport.MaxZ = 1.0f;
	g_Camera[0].bUse = true;

	g_Camera[1].PosV = (D3DXVECTOR3(0.0f, 550.0f, 350.0f));
	g_Camera[1].PosR = (D3DXVECTOR3(0.0f, 0.0f, 349.0f));
	g_Camera[1].Rot = (D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	g_Camera[1].VecU = (D3DXVECTOR3(0.0f, 1.0f, 0.0f));
	g_Camera[1].viewport.X = 0;
	g_Camera[1].viewport.Y = 0;
	g_Camera[1].viewport.Width = SCREEN_WIDTH / 5;
	g_Camera[1].viewport.Height = SCREEN_HEIGHT / 5;
	g_Camera[1].viewport.MinZ = 0.0f;
	g_Camera[1].viewport.MaxZ = 1.0f;
	g_Camera[1].bUse = false;

	return S_OK;
}

//---------------------------
//�I������
//---------------------------
void UninitCamera(void)
{
	
}

//---------------------------
//�X�V����
//---------------------------
void UpdateCamera(void)
{
	Player *pPlayer;
	D3DXVECTOR3 PosR = g_Camera[0].PosR;

	pPlayer = GetPlayer();

	//---------------------------
	//FPS���_
	//---------------------------
	pPlayer->pos.x = g_Camera[0].PosV.x;
	g_Camera[0].PosV.y = pPlayer->pos.y + 25.0f;
	pPlayer->pos.z = g_Camera[0].PosV.z;

	//---------------------------
	//�g���Ă�J�����̃}�E�X���
	//---------------------------
	for (int nCntCm = 0; nCntCm < MAX_CAMERA; nCntCm++)
	{
		if (g_Camera[nCntCm].bUse == true)
		{
			//�}�E�X���W�̎擾
			GetCursorPos(&g_Camera[nCntCm].Pointer);
		}
	}

	//---------------------------
	//�}�E�X�̍��W�̈ʒu���ǂ���
	//---------------------------
	for (int nCntCm = 0; nCntCm < MAX_CAMERA; nCntCm++)
	{
		if (g_Camera[nCntCm].bUse == true)
		{
			if (g_Camera[nCntCm].Pointer.x < SCREEN_WIDTH / 2)
			{
				g_Camera[nCntCm].Poimove.x = SCREEN_WIDTH / 2 - g_Camera[nCntCm].Pointer.x;
			}
			else if (g_Camera[nCntCm].Pointer.x > SCREEN_WIDTH / 2)
			{
				g_Camera[nCntCm].Poimove.x = SCREEN_WIDTH / 2 - g_Camera[nCntCm].Pointer.x;
			}
			if (g_Camera[nCntCm].Pointer.y < SCREEN_HEIGHT / 2)
			{
				g_Camera[nCntCm].Poimove.y = SCREEN_HEIGHT / 2 - g_Camera[nCntCm].Pointer.y;
			}
			else if (g_Camera[nCntCm].Pointer.y > SCREEN_HEIGHT / 2)
			{
				g_Camera[nCntCm].Poimove.y = SCREEN_HEIGHT / 2 - g_Camera[nCntCm].Pointer.y;
			}
			if (g_Camera[nCntCm].Pointer.y == SCREEN_HEIGHT / 2 &&
				g_Camera[nCntCm].Pointer.x == SCREEN_WIDTH / 2)
			{
				g_Camera[nCntCm].Poimove.y = 0.0f;
				g_Camera[nCntCm].Poimove.x = 0.0f;
			}
		}
	}

	for (int nCntCm = 0; nCntCm < MAX_CAMERA; nCntCm++)
	{
		//�J�����ƒ����_�̋���
		g_Camera[nCntCm].Long = CAMERA_DESTAANCE;
	}
	//�_�b�V��
	if (GetKeyboardPress(DIK_LSHIFT) == true)
	{
		g_move = 2.5f;
	}
	else if (GetKeyboardPress(DIK_LSHIFT) == false)
	{
		g_move = 1.0f;
	}
	//---------------------------
	//���_�����_�ړ�
	//---------------------------
	for (int nCntCm = 0; nCntCm < MAX_CAMERA; nCntCm++)
	{
		if (g_Camera[nCntCm].bUse == true)
		{
			if (GetKeyboardPress(DIK_W) == true)
			{
				g_Camera[nCntCm].PosV.x = g_Camera[nCntCm].PosV.x + sinf(g_Camera[nCntCm].Rot.y) * CAMERA_MOVE_SPEED * g_move;
				g_Camera[nCntCm].PosV.z = g_Camera[nCntCm].PosV.z + cosf(g_Camera[nCntCm].Rot.y) * CAMERA_MOVE_SPEED * g_move;

				g_Camera[nCntCm].PosR.x = g_Camera[nCntCm].PosR.x + sinf(g_Camera[nCntCm].Rot.y) * CAMERA_MOVE_SPEED * g_move;
				g_Camera[nCntCm].PosR.z = g_Camera[nCntCm].PosR.z + cosf(g_Camera[nCntCm].Rot.y) * CAMERA_MOVE_SPEED * g_move;
			}
			if (GetKeyboardPress(DIK_S) == true)
			{
				g_Camera[nCntCm].PosV.x = g_Camera[nCntCm].PosV.x - sinf(g_Camera[nCntCm].Rot.y) * CAMERA_MOVE_SPEED * g_move;
				g_Camera[nCntCm].PosV.z = g_Camera[nCntCm].PosV.z - cosf(g_Camera[nCntCm].Rot.y) * CAMERA_MOVE_SPEED * g_move;

				g_Camera[nCntCm].PosR.x = g_Camera[nCntCm].PosR.x - sinf(g_Camera[nCntCm].Rot.y) * CAMERA_MOVE_SPEED * g_move;
				g_Camera[nCntCm].PosR.z = g_Camera[nCntCm].PosR.z - cosf(g_Camera[nCntCm].Rot.y) * CAMERA_MOVE_SPEED * g_move;
			}
			if (GetKeyboardPress(DIK_A) == true)
			{
				g_Camera[nCntCm].PosV.x = g_Camera[nCntCm].PosV.x - cosf(g_Camera[nCntCm].Rot.y) * CAMERA_MOVE_SPEED * g_move;
				g_Camera[nCntCm].PosV.z = g_Camera[nCntCm].PosV.z + sinf(g_Camera[nCntCm].Rot.y) * CAMERA_MOVE_SPEED * g_move;

				g_Camera[nCntCm].PosR.x = g_Camera[nCntCm].PosR.x - cosf(g_Camera[nCntCm].Rot.y) * CAMERA_MOVE_SPEED * g_move;
				g_Camera[nCntCm].PosR.z = g_Camera[nCntCm].PosR.z + sinf(g_Camera[nCntCm].Rot.y) * CAMERA_MOVE_SPEED * g_move;
			}
			if (GetKeyboardPress(DIK_D) == true)
			{
				g_Camera[nCntCm].PosV.x = g_Camera[nCntCm].PosV.x + cosf(g_Camera[nCntCm].Rot.y) * CAMERA_MOVE_SPEED * g_move;
				g_Camera[nCntCm].PosV.z = g_Camera[nCntCm].PosV.z - sinf(g_Camera[nCntCm].Rot.y) * CAMERA_MOVE_SPEED * g_move;

				g_Camera[nCntCm].PosR.x = g_Camera[nCntCm].PosR.x + cosf(g_Camera[nCntCm].Rot.y) * CAMERA_MOVE_SPEED * g_move;
				g_Camera[nCntCm].PosR.z = g_Camera[nCntCm].PosR.z - sinf(g_Camera[nCntCm].Rot.y) * CAMERA_MOVE_SPEED * g_move;
			}
			//---------------------------
			//�����_���ړ�
			//---------------------------
			if (g_Camera[nCntCm].Poimove.x > 0)
			{
				g_Camera[nCntCm].Rot.y -= g_Camera[nCntCm].Poimove.x * 0.01;
				g_Camera[nCntCm].PosR.x = g_Camera[nCntCm].PosV.x + sinf(g_Camera[nCntCm].Rot.y) * g_Camera[nCntCm].Long;
				g_Camera[nCntCm].PosR.z = g_Camera[nCntCm].PosV.z + cosf(g_Camera[nCntCm].Rot.y) * g_Camera[nCntCm].Long;
			}
			else if (g_Camera[nCntCm].Poimove.x < 0)
			{
				g_Camera[nCntCm].Rot.y += g_Camera[nCntCm].Poimove.x * -0.01;
				g_Camera[nCntCm].PosR.x = g_Camera[nCntCm].PosV.x + sinf(g_Camera[nCntCm].Rot.y) * g_Camera[nCntCm].Long;
				g_Camera[nCntCm].PosR.z = g_Camera[nCntCm].PosV.z + cosf(g_Camera[nCntCm].Rot.y) * g_Camera[nCntCm].Long;
			}
			//---------------------------
			//�����_�c�ړ�
			//---------------------------
			if (g_Camera[nCntCm].Poimove.y > 0)
			{
				g_Camera[nCntCm].Rot.x -= g_Camera[nCntCm].Poimove.y * -0.01;
				g_Camera[nCntCm].PosR.y = g_Camera[nCntCm].PosV.y + sinf(g_Camera[nCntCm].Rot.x) * g_Camera[nCntCm].Long;
			}
			else if (g_Camera[nCntCm].Poimove.y < 0)
			{
				g_Camera[nCntCm].Rot.x += g_Camera[nCntCm].Poimove.y * 0.01;
				g_Camera[nCntCm].PosR.y = g_Camera[nCntCm].PosV.y + sinf(g_Camera[nCntCm].Rot.x) * g_Camera[nCntCm].Long;
			}
		}
	}
#ifdef _DEBUG
	//---------------------------
	//�J�����̐؂�ւ�
	//---------------------------
	if (GetKeyboardTrigger(DIK_1) == true)
	{
		if (g_Camera[0].bUse == true)
		{
			g_Camera[1].bUse = true;
			g_Camera[0].bUse = false;
		}
		else if (g_Camera[1].bUse == true)
		{
			g_Camera[0].bUse = true;
			g_Camera[1].bUse = false;
		}
	}
	else if (GetKeyboardTrigger(DIK_2) == true)
	{
		if (g_Camera[0].bUse == true)
		{
			g_Camera[1].bUse = true;
			g_Camera[0].bUse = false;
		}
		else if (g_Camera[1].bUse == true)
		{
			g_Camera[0].bUse = true;
			g_Camera[1].bUse = false;
		}
	}
#endif // _DEBUG
	if (GetKeyboardPress(DIK_LSHIFT) == true && GetKeyboardPress(DIK_L) == true)
	{
		g_Camera[0].PosV = (D3DXVECTOR3(0.0f, 25.0f, 5.0f));
		g_Camera[0].PosR = (D3DXVECTOR3(0.0f, 25.0f, CAMERA_DESTAANCE));
		g_Camera[0].Rot = (D3DXVECTOR3(0.0f, 0.0f, 0.0f));

		g_Camera[1].PosV = (D3DXVECTOR3(0.0f, 100.0f, -50.0f));
		g_Camera[1].PosR = (D3DXVECTOR3(0.0f, 0.0f, 0.0f));
		g_Camera[1].Rot = (D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	}
}

//---------------------------
//�`�揈��
//---------------------------
void SetCamera(int nIdx)
{
	LPDIRECT3DDEVICE9	pDevice;			//�f�o�C�X�̃|�C���^

	pDevice = GetDevice();					//�f�o�C�X���擾����

	//---------------------------
	//�r���[�|�[�g�̐ݒ�
	//---------------------------
	pDevice->SetViewport(&g_Camera[nIdx].viewport);

	//---------------------------
	//�}�g���b�N�X�̐ݒ�
	//---------------------------
	D3DXMatrixIdentity(&g_Camera[nIdx].mtxProjection);	//�}�g���b�N�X������

	//�}�g���b�N�X�̍쐬
	D3DXMatrixPerspectiveFovLH(	&g_Camera[nIdx].mtxProjection,
								D3DXToRadian(110.0f),	//����p
								(float)SCREEN_WIDTH / (float)SCREEN_HEIGHT,	//�A�X��
								10.0f,		//�J�����̍ŏ��`�拗��
								300000.0f);	//�J�����̍ő�`�拗��

					//�v���W�F�N�V�����}�g���b�N�X�ݒ�
	pDevice->SetTransform(	D3DTS_PROJECTION,
							&g_Camera[nIdx].mtxProjection);

	//�r���[�}�g���b�N�X�̏�����
	D3DXMatrixIdentity(&g_Camera[nIdx].mtxView);

	//�r���[�}�g���b�N�X�̍쐬
	D3DXMatrixLookAtLH(	&g_Camera[nIdx].mtxView,
						&g_Camera[nIdx].PosV,
						&g_Camera[nIdx].PosR,
						&g_Camera[nIdx].VecU);

	//�r���[�}�g���b�N�X�̐ݒ�
	pDevice->SetTransform(	D3DTS_VIEW,
							&g_Camera[nIdx].mtxView);
}

//---------------------------
//�J�������
//---------------------------
Camera *GetCamera(void)
{
	return &g_Camera[0];
}