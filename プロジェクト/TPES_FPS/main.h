//=============================================
//
//3DTemplate[main.h]
//Auther Matsuda Towa
//
//=============================================
#ifndef _MAIN_H_ //���ꂪ��`����ĂȂ��Ƃ�

#define _MAIN_H_
#include "renderer.h"

//���C�u�����̃����N
#pragma comment(lib,"d3d9.lib") //�`�揈���ɕK�v
#pragma comment(lib,"d3dx9.lib") //���̊g�����C�u����
#pragma comment(lib,"dxguid.lib")
#pragma	comment(lib,"winmm.lib")
#pragma comment(lib,"dinput8.lib")
#pragma comment(lib,"xinput.lib")

//���_���(2D)�̍\���̂��`
typedef struct
{
	D3DXVECTOR3 pos; //���_���W
	float rhw; //���W�ϊ��p�W���i1.0f�j
	D3DCOLOR col; //���_�J���[
	D3DXVECTOR2 tex; //�e�N�X�`��
}VERTEX_2D;

//���_���(3D)�̍\���̂��`
typedef struct
{
	D3DXVECTOR3 pos; //���_���W
	D3DXVECTOR3 nor; //�@���x�N�g��
	D3DCOLOR col; //���_�J���[
	D3DXVECTOR2 tex; //�e�N�X�`��
}VERTEX_3D;

int GetFps();//fps�擾
#endif // !_MAIN_H_ //���ꂪ��`����ĂȂ��Ƃ�