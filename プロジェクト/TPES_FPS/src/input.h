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

//pad�N���X
class CInputPad :public CInput
{
public:
	//�L�[�̎��
	enum JOYKEY
	{
		JOYKEY_UP = 0,
		JOYKEY_DOWN,
		JOYKEY_LEFT,
		JOYKEY_RIGHT,
		JOYKEY_START,
		JOYKEY_BACK,
		JOYKEY_L3,
		JOYKEY_R3,
		JOYKEY_LB,
		JOYKEY_RB,
		JOYKEY_LT,
		JOYKEY_RT,
		JOYKEY_A,
		JOYKEY_B,
		JOYKEY_X,
		JOYKEY_Y,
		JOYKEY_MAX
	};

	//�X�e�B�b�N�̔ԍ�
	enum STICKTYPE
	{
		STICKTYPE_LEFT = 0, // ���X�e�B�b�N
		STICKTYPE_RIGHT, // �E�X�e�B�b�N
		STICKTYPE_MAX
	};

	//�X�e�B�b�N�̕���
	enum STICKANGLE
	{
		STICKANGLE_UP = 0, // ��
		STICKANGLE_DOWN,   // ��
		STICKANGLE_LEFT,   // ��
		STICKANGLE_RIGHT,  // �E
		STICKANGLE_MAX,
	};

	//�X�e�B�b�N�̓��͏��
	struct STICKINPUT
	{
		float afTplDiameter[STICKTYPE_MAX];                      // �X�e�B�b�N�̓|���
		float afAngle[STICKTYPE_MAX];                            // �X�e�B�b�N�̊p�x
		bool abAnglePress[STICKTYPE_MAX][STICKANGLE_MAX];        // �X�e�B�b�N�̕����v���X���
		bool abAngleTrigger[STICKTYPE_MAX][STICKANGLE_MAX];      // �X�e�B�b�N�̕����g���K�[���
		bool abAngleRepeat[STICKTYPE_MAX][STICKANGLE_MAX];       // �X�e�B�b�N�̕������s�[�g���
		bool abAngleRelease[STICKTYPE_MAX][STICKANGLE_MAX];      // �X�e�B�b�N�̕��������[�X���
	};

	//�}�N����`
	static const int JOYPAD_ZONE = 1;
	static const int JOYPAD_SPEED = 15;

	/**
	 * @brief �R���X�g���N�^
	 */
	CInputPad();
	/**
	 * @brief �f�X�g���N�^
	 */
	~CInputPad();
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
	 * @brief �ڑ�����Ă��邩�擾
	 * @return �ڑ�����Ă邩
	 */
	inline bool GetConnet()
	{
		return m_Connect;
	}

	/**
	 * @brief �v���X���擾
	 * @param [in]�L�[
	 * @return ������Ă��邩
	 */
	inline bool GetPress(JOYKEY Key)
	{
		return (m_joyKeyState & (0x01 << Key)) ? true : false;
	}

	/**
	 * @brief �g���K�[���擾
	 * @param [in]�L�[
	 * @return ������Ă��邩
	 */
	inline bool GetTrigger(JOYKEY Key)
	{
		return (m_joyKeyStateTrigger & (0x01 << Key)) ? true : false;
	}

	/**
	 * @brief �����[�X���擾
	 * @param [in]�L�[
	 * @return ������Ă��邩
	 */
	inline bool GetRelease(JOYKEY Key)
	{
		return(m_ajoyKeyStateRelease & (0x01 << Key)) ? true : false;
	}

	/**
	 * @brief �X�e�[�g�擾
	 * @return �X�e�[�g
	 */
	inline XINPUT_STATE* GetXInputState(void)
	{
		return &m_XInput;
	}

	/**
	 * @brief �X�e�B�b�N�X�V
	 * @param [in]���
	 */
	void UpdateStick(XINPUT_STATE state);
	/**
	 * @brief �X�e�B�b�N�擾
	 * @return �X�e�B�b�N�̃C���v�b�g���
	 */
	STICKINPUT GetStick(void);
	/**
	 * @brief �p�x�v�Z
	 * @param [in]�ʒu
	 * @param [in]�ړI�̈ʒu
	 * @return �p�x
	 */
	float FindAngle(D3DXVECTOR3 pos, D3DXVECTOR3 TargetPos);
	/**
	 * @brief �X�e�B�b�N���擾
	 * @param [in]X�̓|���x
	 * @param [in]X�̓|���x
	 * @param [in]�f�b�h�]�[��
	 * @return ����
	 */
	WORD GetJoypadStick(SHORT sThumbX, SHORT sThumbY, SHORT sDeadZone);
private:
	//�R���g���[���[
	bool m_Connect; //�ڑ�����Ă邩�ǂ���
	WORD m_joyKeyState; //�W���C�p�b�h�̃v���X���
	WORD m_joyKeyStateTrigger; //�W���C�p�b�h�̃g���K�[���
	WORD m_joyKeyStateRepeat; //�W���C�p�b�h�̃��s�[�g���
	WORD m_ajoyKeyStateRelease; //�R���g���[���[�̃����[�X���
	WORD m_aJoypadCurrentTime; //�R���g���[���[�̌��݂̎���
	WORD m_aJoypadExecLastTime; //�R���g���[���[�̍Ō�ɐ^��Ԃ�������
	WORD m_JoypadInput; //�R���g���[���[�̓��͏��
	D3DXVECTOR3 m_joyStickPos; //�X�e�B�b�N�̌X��
	bool m_bAngle[STICKTYPE_MAX][STICKANGLE_MAX]; //�X�e�B�b�N�̓��͏��
	DWORD m_aStickCurrentTime[STICKTYPE_MAX][STICKANGLE_MAX]; //�X�e�B�b�N�̌��݂̎���
	DWORD m_aStickExecLastTime[STICKTYPE_MAX][STICKANGLE_MAX]; //�X�e�B�b�N�̌��݂̎���
	STICKINPUT m_stick; //�X�e�B�b�N�̓��͏��
	XINPUT_STATE m_XInput; //���͏��
	XINPUT_VIBRATION m_JoypadMotor;
	int m_nCntkey;
};
#endif // _INPUT_H_ //��`����ĂȂ�������