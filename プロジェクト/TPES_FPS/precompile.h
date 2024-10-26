#ifndef PRECOMPILE_H_
#define PRECOMPILE_H_
#include <windows.h>
#include <string.h>
#include<Mmsystem.h>
#include <assert.h>
#include<stdio.h>
#include <string>
#include <vector>

#define DIRECTINPUT_VERSION (0x0800) //�x���Ώ��p
#include "dinput.h" //���͏����ɕK�v
#include "d3dx9.h" //�`�揈���ɕK�v
#include "xaudio2.h"
#include "Xinput.h"

//�}�N����`
#define SCREEN_WIDTH	(1280) //�E�B���h�E�̕�
#define SCREEN_HEIGHT	(720) //�E�B���h�E�̍���
#define WORLD_WIDTH	(111280) //�E�B���h�E�̕�
#define WORLD_HEIGHT	(1440) //�E�B���h�E�̍���
#define FVF_VERTEX_2D	(D3DFVF_XYZRHW | D3DFVF_DIFFUSE |D3DFVF_TEX1) //���W�ƃJ���[�ƃe�N�X�`��
#define FVF_VERTEX_3D	(D3DFVF_XYZ |D3DFVF_NORMAL| D3DFVF_DIFFUSE |D3DFVF_TEX1) //���W�ƃJ���[�ƃe�N�X�`��


#endif // PRECOMPILE_H_

