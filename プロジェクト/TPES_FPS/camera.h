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
#include "camera_state.h"

class CCameraState;
class CCamera
{
public:
	//�J�����^�C�v�錾 TODO:�X�e�[�g�p�^�[����
	enum CANERA_TYPE
	{
		TYPE_THIRDVIEW, //��O�Ҏ��_
		TYPE_ULTVIEW, //�E���g���_
		TYPE_DEBUG,
		TYPE_MAX,
	};

	CCamera();
	~CCamera();
	HRESULT Init();
	void Uninit();
	void Update();
	void SetCamera();
	void ResetCamera();

	void InputMove();


	void ChangeCameraState(CCameraState* state);

	//�����擾
	inline void SetRot(D3DXVECTOR3 rot)
	{
		m_rot = rot;
	}
	//���_�擾
	inline void SetPosV(D3DXVECTOR3 posV)
	{
		m_posV = posV;
	}
	//�����_�擾
	inline void SetPosR(D3DXVECTOR3 posR)
	{
		m_posR = posR;
	}

	inline void SetLength(float length)
	{
		m_fLength = length;
	}

	//�����擾
	inline D3DXVECTOR3 GetRot()
	{
		return m_rot;
	}

	//���_�擾
	inline D3DXVECTOR3 GetPosV()
	{
		return m_posV;
	}
	//�����_�擾
	inline D3DXVECTOR3 GetPosR()
	{
		return m_posR;
	}

	inline float& GetLength()
	{
		return m_fLength;
	}

	//�J�����̃f�o�b�N�\��
	void DebugCameraDraw();

	void ThirdViewCamera(); //�T�[�h�p�[�\���r���[����


	CCameraState* m_pCameraState;
private:
	static constexpr float DEFAULT_MOVE = 1.0f; //�ʏ펞�̈ړ�
	static constexpr float DAMPING_COEFFICIENT = 0.2f; //�ړ���R

	static constexpr float DEFAULT_LENGTH_Y = 200.0f; //�ʏ��Ԃ�Y�̋���
	static constexpr float DEFAULT_LENGTH_Z = 500.0f; //�ʏ��Ԃ�Z�̋���

	static constexpr float BIRDVIEW_LENGTH_Y = 300.0f; //�o�[�h�r���[����Y�̋���

	static constexpr float SIDEVIEW_LENGTH_X = 20.0f; //�T�C�h�r���[����X�̋���
	static constexpr float SIDEVIEW_LENGTH_Y = 50.0f; //�T�C�h�r���[����Y�̋���
	static constexpr float SIDEVIEW_LENGTH_Z = 200.0f; //�T�C�h�r���[����Z�̋���

	static constexpr float THIRDVIEW_CORRECT_X = 20.0f; //�T�[�h�p�[�\���r���[���̕␳�lX
	static constexpr float THIRDVIEW_CORRECT_Y = 105.0f; //�T�[�h�p�[�\���r���[���̕␳�lY
	static constexpr float THIRDVIEW_CORRECT_Z = 20.0f; //�T�[�h�p�[�\���r���[���̕␳�lZ

	static constexpr float MOUSE_SENS = 0.001f; //�f�t�H���g�̃}�E�X���x

	static constexpr float MAX_TURN_X = 0.5f; //�T�[�h�p�[�\���r���[����X�̍ő����
	static constexpr float MIN_TURN_X = -0.15f; //�T�[�h�p�[�\���r���[����X�̍ŏ�����

	void CameraTurn(); //�J������]����

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
