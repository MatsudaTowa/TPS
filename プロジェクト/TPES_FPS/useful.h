//=============================================
//
//���p�I�ȏ������܂Ƃ߂�����[useful.h]
//Auther Matsuda Towa
//
//============================================= 

//�Q�d�C���N���[�h�h�~
#ifndef _USEFUL_H_ //���ꂪ��`����ĂȂ��Ƃ�
#define _USEFUL_H_

#include "main.h"

//0�������p
#define INT_ZERO (0)
#define FLOAT_ZERO (0.0f)
#define INT_ONE (1)
#define FLOAT_ONE (1.0f)

//����
#define HALF	(0.5f)

//�J���[������
#define COLOR_NONE (D3DXCOLOR(0.0f,0.0f,0.0f,0.0f))
#define COLOR_BLACK (D3DXCOLOR(0.0f,0.0f,0.0f,1.0f))
#define COLOR_WHITE (D3DXCOLOR(1.0f,1.0f,1.0f,1.0f))
#define COLOR_RED (D3DXCOLOR(1.0f,0.0f,0.0f,1.0f))
#define COLOR_GREEN (D3DXCOLOR(0.0f,1.0f,0.0f,1.0f))
#define COLOR_BLUE (D3DXCOLOR(0.0f,0.0f,1.0f,1.0f))

//���_3D������
#define VEC3_RESET_ZERO (D3DXVECTOR3(0.0f,0.0f,0.0f))
#define VEC3_RESET_ONE (D3DXVECTOR3(1.0f,1.0f,1.0f))

//���_2D������
#define VEC2_RESET_ZERO (D3DXVECTOR2(0.0f,0.0f))
#define VEC2_RESET_ONE (D3DXVECTOR2(1.0f,1.0f))

//���~
#define HALF_PI	(D3DX_PI * HALF)
//1/4�~
#define QRTR_PI	(D3DX_PI * (HALF * HALF))

//�������ő吔
#define MAX_TXT (256)

//���ˏ�Ƀ����_��
#define CICRLE_RAND  ((float)(rand() % 629 - 314) / 100.0f)

#endif