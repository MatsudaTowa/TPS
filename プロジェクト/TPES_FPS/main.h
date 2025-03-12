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
struct VERTEX_2D
{
	D3DXVECTOR3 pos; //���_���W
	float rhw; //���W�ϊ��p�W���i1.0f�j
	D3DCOLOR col; //���_�J���[
	D3DXVECTOR2 tex; //�e�N�X�`��
};

//���_���(3D)�̍\���̂��`
struct VERTEX_3D
{
	D3DXVECTOR3 pos; //���_���W
	D3DXVECTOR3 nor; //�@���x�N�g��
	D3DCOLOR col; //���_�J���[
	D3DXVECTOR2 tex; //�e�N�X�`��
};

int GetFps();//fps�擾
#endif // !_MAIN_H_ //���ꂪ��`����ĂȂ��Ƃ�