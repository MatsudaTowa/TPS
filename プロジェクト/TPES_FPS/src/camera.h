//=============================================
//
//�J����[camera.h]
//Author Matsuda Towa
//
//=============================================
#ifndef _CAMERA_H_ //���ꂪ��`����ĂȂ��Ƃ�

#define _CAMERA_H_
#include "main.h"
#include "input.h"
#include "camera_state.h"

//=============================================
// �O���錾
//=============================================
class CCameraState;

//=============================================
// �J�����N���X
//=============================================
class CCamera
{
public:
	//�J�����^�C�v�錾
	enum CANERA_TYPE
	{
		TYPE_THIRDVIEW, //��O�Ҏ��_
		TYPE_ULTVIEW, //�E���g���_
		TYPE_DEBUG,
		TYPE_MAX,
	};
	/**
	 * @brief �R���X�g���N�^
	 */
	CCamera();
	/**
	 * @brief �f�X�g���N�^
	 */
	~CCamera();
	/**
	 * @brief ������
	 * @return ����������
	 */
	HRESULT Init();
	/**
	 * @brief �I��
	 */
	void Uninit();
	/**
	 * @brief �X�V
	 */
	void Update();
	/*
	 * @brief �J�����ݒ� 
	 */
	void SetCamera();
	/**
	 * @brief �J�������Z�b�g
	 */
	void ResetCamera();

	/**
	 * @brief ���͏���
	 */
	void InputMove();

	/**
	 * @brief �X�e�[�g�ύX
	 * @param [in]���̃X�e�[�g
	 */
	void ChangeCameraState(CCameraState* state);

	/**
	 * @brief �����ݒ�
	 * @param [in]����
	 */
	inline void SetRot(D3DXVECTOR3 rot)
	{
		m_rot = rot;
	}
	/**
	 * @brief ���_�ݒ�
	 * @param [in]���_�ʒu
	 */
	inline void SetPosV(D3DXVECTOR3 posV)
	{
		m_posV = posV;
	}
	/**
	 * @brief �����_�ݒ�
	 * @param [in]�����_�ʒu
	 */
	inline void SetPosR(D3DXVECTOR3 posR)
	{
		m_posR = posR;
	}

	/**
	 * @brief ���������ݒ�
	 * @param [in]isActive
	 */
	inline void SetActive(bool isActive)
	{
		m_isActive = isActive;
	}

	/**
	 * @brief �����ݒ�
	 * @param [in]����
	 */
	inline void SetLength(float length)
	{
		m_fLength = length;
	}

	/**
	 * @brief �����擾
	 * @return ����
	 */
	inline D3DXVECTOR3 GetRot()
	{
		return m_rot;
	}

	/**
	 * @brief ���_�擾
	 * @return ���_�ʒu
	 */
	inline D3DXVECTOR3 GetPosV()
	{
		return m_posV;
	}

	/**
	 * @brief �����_�擾
	 * @return �����_�ʒu
	 */
	inline D3DXVECTOR3 GetPosR()
	{
		return m_posR;
	}

	/**
	 * @brief ��������Ԃ��擾
	 * @return ���
	 */
	inline bool GetActive()
	{
		return m_isActive;
	}

	/**
	 * @brief �����擾
	 * @return ����
	 */
	inline float& GetLength()
	{
		return m_fLength;
	}

	/**
	 * @brief �ݒ肳�ꂽ�l�����x�ɕϊ�
	 * @param [in]0.0�`1.0�̒l
	 */
	void ConvertSens(float value)
	{
		m_sens = MIN_MOUSE_SENS + value * (MAX_MOUSE_SENS - MIN_MOUSE_SENS);
	}

	/**
	 * @brief ���x��ݒ肷��l�ɕϊ�
	 * @return 0.0�`1.0�̒l
	 */
	float ConvertSensToSettingValue()
	{
		return (m_sens - MIN_MOUSE_SENS) / (MAX_MOUSE_SENS - MIN_MOUSE_SENS);
	}

	/**
	 * @brief �J�����̃f�o�b�O�\��
	 */
	void DebugCameraDraw();

	/**
	 * @brief �J�����̃f�o�b�O�\��
	 */
	void ThirdViewCamera(); //�T�[�h�p�[�\���r���[����
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

	static constexpr float DEFAULT_MOUSE_SENS = 0.001f; //�f�t�H���g�̃}�E�X���x
	static constexpr float MAX_MOUSE_SENS = 0.01f;		//�ő�̃}�E�X���x
	static constexpr float MIN_MOUSE_SENS = 0.0001f;	//�ŏ��̃}�E�X���x

	static constexpr float TURN_SPEED = 0.02f; //�J�����̉�]�X�s�[�h

	static constexpr float MAX_TURN_X = 0.5f; //�T�[�h�p�[�\���r���[����X�̍ő����
	static constexpr float MIN_TURN_X = -0.15f; //�T�[�h�p�[�\���r���[����X�̍ŏ�����

	/**
	 * @brief �J������]����
	 */
	void CameraTurn();

	D3DXVECTOR3 m_posV; //���_
	D3DXVECTOR3 m_posR; //�����_

	D3DXVECTOR3 m_moveV; //���_�ړ���
	D3DXVECTOR3 m_moveR; //�����_�ړ���

	D3DXVECTOR3 m_vecU; //������x�N�g��

	D3DXVECTOR3 m_rot; //����
	D3DXVECTOR3 m_rotmove; //��]��

	bool m_isActive;	//���������Ԃ��ǂ���
	float m_sens;		//�}�E�X���x
	float m_fLength;	//�ΏۂƂ̋���
	float m_fAngle;		//�ΏۂƂ̑Ίp���̊p�x

	D3DXMATRIX m_mtxProjection; //�v���W�F�N�V����
	D3DXMATRIX m_mtxView; //�r���[�s��
	CCameraState* m_pCameraState;

};
#endif
