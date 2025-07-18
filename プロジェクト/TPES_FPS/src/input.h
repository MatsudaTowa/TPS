//=============================================
//
//3DTemplate[input.h]
//Author Matsuda Towa
//
//=============================================
#ifndef _INPUT_H_ //��`����ĂȂ�������
#define _INPUT_H_ //�Q��C���N���[�h�h�~
#include "main.h"

//�C���v�b�g�N���X
class CInput
{
public:
	/**
	 * @brief �R���X�g���N�^
	 */
	CInput();
	/**
	 * @brief �f�X�g���N�^
	 */
	~CInput();
	/**
	 * @brief ������
	 * @param [in]�C���X�^���X
	 * @param [in]�n���h�������h
	 * @return ����������
	 */
	virtual HRESULT Init(HINSTANCE hInstance, HWND hWnd);
	/**
	 * @brief �I��
	 */
	virtual void Uninit();
	/**
	 * @brief �X�V
	 */
	virtual void Update() = 0;
protected:
	static LPDIRECTINPUT8 m_pInput;
	LPDIRECTINPUTDEVICE8 m_pDevice;
};

//�L�[�{�[�h�N���X
class CInputKeyboard:public CInput
{
public:
	static const int NUM_KEY_MAX = 256; //�L�[�{�[�h�̃L�[��
	/**
	 * @brief �R���X�g���N�^
	 */
	CInputKeyboard();
	/**
	 * @brief �f�X�g���N�^
	 */
	~CInputKeyboard();
	/**
	 * @brief ������
	 * @param [in]�C���X�^���X
	 * @param [in]�n���h�������h
	 * @return ����������
	 */
	HRESULT Init(HINSTANCE hInstance, HWND hWnd) override;
	/**
	 * @brief �I��
	 */
	void Uninit() override;
	/**
	 * @brief �X�V
	 */
	void Update() override;

	/**
	 * @brief �v���X���擾
	 * @param [in]�L�[�ԍ�
	 * @return ������Ă��邩
	 */
	inline bool GetPress(int nKey)
	{
		return(m_aKeyState[nKey] & 0x80) != 0;
	}

	/**
	 * @brief �g���K�[���擾
	 * @param [in]�L�[�ԍ�
	 * @return ������Ă��邩
	 */
	inline bool GetTrigger(int nKey)
	{
		return(m_aKeyStateTrigger[nKey] & 0x80) != 0;
	}

	/**
	 * @brief �����[�X���擾
	 * @param [in]�L�[�ԍ�
	 * @return ������Ă��邩
	 */	
	inline bool GetRelease(int nKey)
	{
		return(m_aKeyStateRelease[nKey] & 0x80) != 0;
	}
private:
	BYTE m_aKeyStateTrigger[NUM_KEY_MAX]; //�L�[�{�[�h�̃g���K�[���
	BYTE m_aKeyStateRelease[NUM_KEY_MAX]; //�L�[�{�[�h�̃����[�X���
	BYTE m_aKeyState[NUM_KEY_MAX]; //�L�[�{�[�h�̃v���X���
};

//�}�E�X�N���X
class CInputMouse :public CInput
{
public:
	static const int NUM_MOUSE_MAX = 3; //�}�E�X�̃L�[��
	/**
	 * @brief �R���X�g���N�^
	 */
	CInputMouse();
	/**
	 * @brief �f�X�g���N�^
	 */
	~CInputMouse();
	/**
	 * @brief ������
	 * @param [in]�C���X�^���X
	 * @param [in]�n���h�������h
	 * @return ����������
	 */
	HRESULT Init(HINSTANCE hInstance, HWND hWnd) override;
	/**
	 * @brief �I��
	 */
	void Uninit() override;
	/**
	 * @brief �X�V
	 */
	void Update() override;

	/**
	 * @brief �v���X���擾
	 * @param [in]�L�[�ԍ�
	 * @return ������Ă��邩
	 */	
	inline bool GetPress(int nKey)
	{
		return(m_KeyState.rgbButtons[nKey] & 0x80) != 0;
	}

	/**
	* @brief �g���K�[���擾
	* @param [in]�L�[�ԍ�
	* @return ������Ă��邩
	*/	
	inline bool GetTrigger(int nKey)
	{
		return(m_KeyStateTrigger.rgbButtons[nKey] & 0x80) != 0;
	}

	/**
	* @brief �����[�X���擾
	* @param [in]�L�[�ԍ�
	* @return ������Ă��邩
	*/	
	inline bool GetRelease(int nKey)
	{
		return(m_KeyStateRelease.rgbButtons[nKey] & 0x80) != 0;
	}

	/**
	 * @brief �ړ��ʎ擾
	 * @return �ړ���
	 */
	inline D3DXVECTOR3 GetMouseMove(void)
	{
		return m_MouseMove;
	}

	/**
	 * @brief �f�o�b�O���
	 */
	void Debug();
private:
	DIMOUSESTATE m_KeyStateTrigger; //�}�E�X�̃g���K�[���
	DIMOUSESTATE m_KeyStateRelease; //�}�E�X�̃����[�X���
	DIMOUSESTATE m_KeyState; //�}�E�X�̃v���X���
	DIMOUSESTATE m_zdiMouseMove; //�}�E�X���[�u
	D3DXVECTOR3 m_MousePos;
	D3DXVECTOR3 m_MouseMove;
};

#endif // _INPUT_H_ //��`����ĂȂ�������