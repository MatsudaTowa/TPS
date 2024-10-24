//=============================================
//
//3DTemplate[input.h]
//Auther Matsuda Towa
//
//=============================================
#ifndef _INPUT_H_ //��`����ĂȂ�������
#define _INPUT_H_ //�Q��C���N���[�h�h�~
#include "main.h"

//�C���v�b�g�N���X
class CInput
{
public:
	CInput();
	~CInput();
	virtual HRESULT Init(HINSTANCE hInstance, HWND hWnd);
	virtual void Uninit();
	virtual void Update() = 0;//�[�����Ƃ�
protected:
	static LPDIRECTINPUT8 m_pInput;
	LPDIRECTINPUTDEVICE8 m_pDevice;
};

//�L�[�{�[�h�N���X
class CInputKeyboard:public CInput
{
public:
	static const int NUM_KEY_MAX = 256; //�L�[�{�[�h�̃L�[��
	CInputKeyboard();
	~CInputKeyboard();
	HRESULT Init(HINSTANCE hInstance, HWND hWnd) override;
	void Uninit() override;
	void Update() override;//�[�����Ƃ�
	bool GetPress(int nKey);
	bool GetTrigger(int nKey);
	bool GetRelease(int nKey);
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
	CInputMouse();
	~CInputMouse();
	HRESULT Init(HINSTANCE hInstance, HWND hWnd) override;
	void Uninit() override;
	void Update() override;//�[�����Ƃ�
	bool GetPress(int nKey);
	bool GetTrigger(int nKey);
	bool GetRelease(int nKey);
	D3DXVECTOR3 GetMouseMove(void);
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
	typedef enum
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
	}JOYKEY;

	//�X�e�B�b�N�̔ԍ�
	typedef enum
	{
		STICKTYPE_LEFT = 0, // ���X�e�B�b�N
		STICKTYPE_RIGHT, // �E�X�e�B�b�N
		STICKTYPE_MAX
	}STICKTYPE;

	//�X�e�B�b�N�̕���
	typedef enum
	{
		STICKANGLE_UP = 0, // ��
		STICKANGLE_DOWN,   // ��
		STICKANGLE_LEFT,   // ��
		STICKANGLE_RIGHT,  // �E
		STICKANGLE_MAX,
	}STICKANGLE;

	//�X�e�B�b�N�̓��͏��
	typedef struct
	{
		float afTplDiameter[STICKTYPE_MAX];                      // �X�e�B�b�N�̓|���
		float afAngle[STICKTYPE_MAX];                            // �X�e�B�b�N�̊p�x
		bool abAnglePress[STICKTYPE_MAX][STICKANGLE_MAX];        // �X�e�B�b�N�̕����v���X���
		bool abAngleTrigger[STICKTYPE_MAX][STICKANGLE_MAX];      // �X�e�B�b�N�̕����g���K�[���
		bool abAngleRepeat[STICKTYPE_MAX][STICKANGLE_MAX];       // �X�e�B�b�N�̕������s�[�g���
		bool abAngleRelease[STICKTYPE_MAX][STICKANGLE_MAX];      // �X�e�B�b�N�̕��������[�X���
	}STICKINPUT;

	//�}�N����`
	static const int JOYPAD_ZONE = 1;
	static const int JOYPAD_SPEED = 15;

	CInputPad();
	~CInputPad();
	HRESULT Init(HINSTANCE hInstance, HWND hWnd) override;
	void Uninit() override;
	void Update() override;//�[�����Ƃ�
	bool GetConnet();
	bool GetPress(JOYKEY Key);
	bool GetTrigger(JOYKEY Key);
	bool GetRelease(JOYKEY Key);
	XINPUT_STATE* GetXInputState(void);
	void UpdateStick(XINPUT_STATE state);
	STICKINPUT GetStick(void);
	float FindAngle(D3DXVECTOR3 pos, D3DXVECTOR3 TargetPos);
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