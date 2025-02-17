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

//�J���[������
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
#define HALF_PI	(D3DX_PI * 0.5f)
//1/4�~
#define QRTR_PI	(D3DX_PI * 0.25f)

//���ˏ�Ƀ����_��
#define CICRLE_RAND  ((float)(rand() % 629 - 314) / 100.0f)

#endif