//=============================================
//
//3DTemplate[camera.h]
//Auther Matsuda Towa
//
//=============================================
#ifndef _CAMERA_H_ //���ꂪ��`����ĂȂ��Ƃ�

#define _CAMERA_H_
#include "main.h"
#include "input.h"
class CCamera
{
public:
	//�J�����^�C�v�錾
	typedef enum
	{
		TYPE_BIRDVIEW = 0,
		TYPE_SIDEVIEW,
		TYPE_PARALLEL_SIDEVIEW, //���s���e
		TYPE_THIRDVIEW, //��O�Ҏ��_
		TYPE_DEBUG,
		TYPE_MAX,
	}CANERA_TYPE;

	static CANERA_TYPE m_type; //�J�����^�C�v

	CCamera();
	~CCamera();
	HRESULT Init();
	void Uninit();
	void Update();
	void SetCamera();
	void ResetCamera();

	//�����擾
	void SetRot(D3DXVECTOR3 rot)
	{
		m_rot = rot;
	}
	//���_�擾
	void SetPosV(D3DXVECTOR3 posV)
	{
		m_posV = posV;
	}
	//�����_�擾
	void SetPosR(D3DXVECTOR3 posR)
	{
		m_posR = posR;
	}

	//�����擾
	D3DXVECTOR3 GetRot();
	//���_�擾
	D3DXVECTOR3 GetPosV();
	//�����_�擾
	D3DXVECTOR3 GetPosR();

	//�J�����̃f�o�b�N�\��
	void DebugCameraDraw(); 

	//���݂̃J�����̃^�C�v�擾
	static CANERA_TYPE GetType();
private:
	static const float DEFAULT_MOVE; //�ʏ펞�̈ړ�
	static const float DAMPING_COEFFICIENT; //�ړ���R

	static const float DEFAULT_LENGTH_Y; //�ʏ��Ԃ�Y�̋���
	static const float DEFAULT_LENGTH_Z; //�ʏ��Ԃ�Z�̋���

	static const float BIRDVIEW_LENGTH_Y; //�o�[�h�r���[����Y�̋���

	static const float SIDEVIEW_LENGTH_X; //�T�C�h�r���[����X�̋���
	static const float SIDEVIEW_LENGTH_Y; //�T�C�h�r���[����Y�̋���
	static const float SIDEVIEW_LENGTH_Z; //�T�C�h�r���[����Z�̋���

	static const float THIRDVIEW_CORRECT_X; //�T�[�h�p�[�\���r���[���̕␳�lX
	static const float THIRDVIEW_CORRECT_Y; //�T�[�h�p�[�\���r���[���̕␳�lY
	static const float THIRDVIEW_CORRECT_Z; //�T�[�h�p�[�\���r���[���̕␳�lZ

	static const float THIRDVIEW_LENGTH; //�T�[�h�p�[�\���r���[���̋���

	static const float MAX_TURN_X; //�T�[�h�p�[�\���r���[����X�̍ő����
	static const float MIN_TURN_X; //�T�[�h�p�[�\���r���[����X�̍ŏ�����

	void CameraMove(); //�J�����ړ�����

	void CameraTurn(); //�J������]����

	void BirdViewCamera(); //�o�[�h�r���[����

	void SideViewCamera(); //�T�C�h�r���[����

	void ThirdViewCamera(); //�T�[�h�p�[�\���r���[����

	D3DXVECTOR3 m_posV; //���_
	D3DXVECTOR3 m_posR; //�����_

	D3DXVECTOR3 m_moveV; //���_�ړ���
	D3DXVECTOR3 m_moveR; //�����_�ړ���

	D3DXVECTOR3 m_vecU; //������x�N�g��

	D3DXVECTOR3 m_rot; //����
	D3DXVECTOR3 m_rotmove; //��]��

	float m_fLength; //�ΏۂƂ̋���
	float m_fAngle; //�ΏۂƂ̑Ίp���̊p�x

	D3DXMATRIX m_mtxProjection; //�v���W�F�N�V����
	D3DXMATRIX m_mtxView; //�r���[�s��
};
#endif
