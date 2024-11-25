//=============================================
//
//3DTemplate[input.cpp]
//Auther Matsuda Towa
//
//=============================================
#include "input.h"
#include "manager.h"

//�ÓI�����o������
LPDIRECTINPUT8 CInput::m_pInput = nullptr;

//=============================================
//�R���X�g���N�^
//=============================================
CInput::CInput()
{
	m_pDevice = nullptr;
}

//=============================================
//�f�X�g���N�^
//=============================================
CInput::~CInput()
{
}

//=============================================
//������
//=============================================
HRESULT CInput::Init(HINSTANCE hInstance, HWND hWnd)
{
	if (m_pInput == nullptr)
	{
		if (FAILED(DirectInput8Create(hInstance, DIRECTINPUT_VERSION, IID_IDirectInput8, (void**)&m_pInput, NULL)))
		{
			return E_FAIL;
		}
	}
	return S_OK;
}

//=============================================
//�I��
//=============================================
void CInput::Uninit()
{
	//���̓f�o�C�X�̔j��
	if (m_pDevice != nullptr)
	{
		m_pDevice->Unacquire();
		m_pDevice = nullptr;
	}

	//DirectInput�I�u�W�F�N�g�̔j��
	if (m_pInput != nullptr)
	{
		m_pInput->Release();
		m_pInput = nullptr;
	}
}

//������L�[�{�[�h

//=============================================
//�R���X�g���N�^
//=============================================
CInputKeyboard::CInputKeyboard()
{
}

//=============================================
//�f�X�g���N�^
//=============================================
CInputKeyboard::~CInputKeyboard()
{
}


//=============================================
//������
//=============================================
HRESULT CInputKeyboard::Init(HINSTANCE hInstance, HWND hWnd)
{
	CInput::Init(hInstance,hWnd);
	//���̓f�o�C�X�̐���
	if (FAILED(m_pInput->CreateDevice(GUID_SysKeyboard, &m_pDevice, NULL)))
	{
		return E_FAIL;
	}
	//�f�[�^�t�H�[�}�b�g��ݒ�
	if (FAILED(m_pDevice->SetDataFormat(&c_dfDIKeyboard)))
	{
		return E_FAIL;
	}
	//�������[�h��ݒ�
	if (FAILED(m_pDevice->SetCooperativeLevel(hWnd, (DISCL_FOREGROUND | DISCL_NONEXCLUSIVE))))
	{
		return E_FAIL;
	}
	//�L�[�{�[�h�̃A�N�Z�X�����l��
	m_pDevice->Acquire();
	return S_OK;
}

//=============================================
//�I��
//=============================================
void CInputKeyboard::Uninit()
{
	CInput::Uninit();
}

//=============================================
//�X�V
//=============================================
void CInputKeyboard::Update()
{
	BYTE aKeyState[NUM_KEY_MAX]; //���͏��
	int nCntKey;
	//���̓f�o�C�X����f�[�^���擾
	if (SUCCEEDED(m_pDevice->GetDeviceState(sizeof(aKeyState), &aKeyState[0])))
	{
		for (nCntKey = 0; nCntKey < NUM_KEY_MAX; nCntKey++)
		{
			m_aKeyStateRelease[nCntKey] = (m_aKeyState[nCntKey] ^ aKeyState[nCntKey]) & ~aKeyState[nCntKey]; //�����[�X
			m_aKeyStateTrigger[nCntKey] = (m_aKeyState[nCntKey] ^ aKeyState[nCntKey]) & aKeyState[nCntKey];
			m_aKeyState[nCntKey] = aKeyState[nCntKey]; //�L�[�{�[�h�̃v���X����ۑ�
		}
	}
	else
	{
		m_pDevice->Acquire(); //�L�[�{�[�h�̃A�N�Z�X�����l��
	}
}

//=============================================
//�L�[�{�[�h�̏����擾
//=============================================
bool CInputKeyboard::GetPress(int nKey)
{
	return(m_aKeyState[nKey] & 0x80) != 0;
}
bool CInputKeyboard::GetTrigger(int nKey)
{
	return(m_aKeyStateTrigger[nKey] & 0x80) != 0;
}
bool CInputKeyboard::GetRelease(int nKey)
{
	return(m_aKeyStateRelease[nKey] & 0x80) != 0;
}

//������}�E�X

//=============================================
//�R���X�g���N�^
//=============================================
CInputMouse::CInputMouse()
{
}

//=============================================
//�f�X�g���N�^
//=============================================
CInputMouse::~CInputMouse()
{
}

//=============================================
//������
//=============================================
HRESULT CInputMouse::Init(HINSTANCE hInstance, HWND hWnd)
{
	//DirectInput�I�u�W�F�N�g�̐���
	if (FAILED(DirectInput8Create(hInstance, DIRECTINPUT_VERSION, IID_IDirectInput8, (void**)&m_pInput, NULL)))
	{
		return E_FAIL;
	}
	//���̓f�o�C�X�̐���
	if (FAILED(m_pInput->CreateDevice(GUID_SysMouse, &m_pDevice, NULL)))
	{
		return E_FAIL;
	}
	//�f�[�^�t�H�[�}�b�g��ݒ�
	if (FAILED(m_pDevice->SetDataFormat(&c_dfDIMouse)))
	{
		return E_FAIL;
	}
	//�������[�h��ݒ�
	if (FAILED(m_pDevice->SetCooperativeLevel(hWnd, (DISCL_FOREGROUND | DISCL_NONEXCLUSIVE))))
	{
		return E_FAIL;
	}
	// �f�o�C�X�̐ݒ�
	DIPROPDWORD diprop;
	m_MousePos = { 0.0f,0.0f,0.0f };
	m_MouseMove = { 0.0f,0.0f,0.0f };
	diprop.diph.dwSize = sizeof(diprop);
	diprop.diph.dwHeaderSize = sizeof(diprop.diph);
	diprop.diph.dwObj = 0;
	diprop.diph.dwHow = DIPH_DEVICE;
	diprop.dwData = DIPROPAXISMODE_REL;


	if (FAILED(m_pDevice->SetProperty(DIPROP_AXISMODE, &diprop.diph)))
	{
		// �f�o�C�X�̐ݒ�Ɏ��s
		return E_FAIL;
	}

	//�}�E�X�̃A�N�Z�X�����l��
	m_pDevice->Acquire();
	return S_OK;
}

//=============================================
//�I��
//=============================================
void CInputMouse::Uninit()
{
	CInput::Uninit();
}

//=============================================
//�X�V
//=============================================
void CInputMouse::Update()
{

	DIMOUSESTATE zdiMouseState;
	int nCntMouse;
	
	//���̓f�o�C�X����f�[�^���擾
	if (SUCCEEDED(m_pDevice->GetDeviceState(sizeof(zdiMouseState), &zdiMouseState)))
	{
		for (nCntMouse = 0; nCntMouse < NUM_MOUSE_MAX; nCntMouse++)
		{
			m_KeyStateRelease.rgbButtons[nCntMouse] = (m_KeyState.rgbButtons[nCntMouse] ^ zdiMouseState.rgbButtons[nCntMouse]) & ~zdiMouseState.rgbButtons[nCntMouse];
			m_KeyStateTrigger.rgbButtons[nCntMouse] = (m_KeyState.rgbButtons[nCntMouse] ^ zdiMouseState.rgbButtons[nCntMouse]) & zdiMouseState.rgbButtons[nCntMouse];
			m_KeyState.rgbButtons[nCntMouse] = zdiMouseState.rgbButtons[nCntMouse]; //�L�[�{�[�h�̃v���X����ۑ�
		}
		
		m_MouseMove.x = (float)zdiMouseState.lX;
		m_MouseMove.y = (float)zdiMouseState.lY;
	}
	else
	{
		m_pDevice->Acquire(); //�L�[�{�[�h�̃A�N�Z�X�����l��
	}

	//ZeroMemory(&pMouseMove, sizeof(POINT));

	/*D3DXVECTOR3 OldMousePos = m_MousePos;

	POINT pMouseMove;

	GetCursorPos(&pMouseMove);*/

	/*m_MousePos.x = (float)zdiMouseState.lX;
	m_MousePos.y = (float)zdiMouseState.lY;*/

	//m_MouseMove.z = m_MousePos.z - OldMousePos.z;
}

//=============================================
//�}�E�X�̏����擾
//=============================================
bool CInputMouse::GetPress(int nKey)
{
	return(m_KeyState.rgbButtons[nKey] & 0x80) != 0;
}
//=============================================
//�}�E�X�̃g���K�[�擾
//=============================================
bool CInputMouse::GetTrigger(int nKey)
{
	return(m_KeyStateTrigger.rgbButtons[nKey] & 0x80) != 0;
}
//=============================================
//�}�E�X�̃����[�X�擾
//=============================================
bool CInputMouse::GetRelease(int nKey)
{
	return(m_KeyStateRelease.rgbButtons[nKey] & 0x80) != 0;
}
//=============================================
//�}�E�X�̃��[�u�l�擾
//=============================================
D3DXVECTOR3 CInputMouse::GetMouseMove(void)
{
	return(m_MouseMove);
}

//=============================================
//�}�E�X�̃f�o�b�O�\��
//=============================================
void CInputMouse::Debug()
{
#ifdef _DEBUG
	LPD3DXFONT pFont = CManager::GetInstance()->GetRenderer()->GetFont();
	RECT rect = { 0,0,SCREEN_WIDTH,SCREEN_HEIGHT };
	char aStr[256];

	sprintf(&aStr[0], "\n\n\n\n\n\n\n\n\n\n\n\n[mouse]\nmove:%.1f,%.1f,%.1f"
		, m_MouseMove.x, m_MouseMove.y, m_MouseMove.z);
	//�e�L�X�g�̕`��
	pFont->DrawText(NULL, &aStr[0], -1, &rect, DT_LEFT, D3DCOLOR_RGBA(255, 0, 0, 255));
#endif // _DEBUG


}

//������pad

//=============================================
//�R���X�g���N�^
//=============================================
CInputPad::CInputPad():m_Connect(false)
{
}

//=============================================
//�f�X�g���N�^
//=============================================
CInputPad::~CInputPad()
{
}

//=============================================
//������
//=============================================
HRESULT CInputPad::Init(HINSTANCE hInstance, HWND hWnd)
{
	m_Connect = false;

	XINPUT_STATE joykeyState; //�W���C�p�b�h�̓��͏��

	//�������̃N���A
	memset(&m_joyKeyState, 0, sizeof(XINPUT_STATE));

	//�������̃N���A
	memset(&m_JoypadMotor, 0, sizeof(XINPUT_VIBRATION));

	//XInput�̃X�e�[�g��ݒ�(�L���ɂ���)
	XInputEnable(true);

	//�W���C�p�b�h�̏�Ԃ��擾
	if (XInputGetState(0, &joykeyState) == ERROR_SUCCESS)
	{
		m_Connect = true;
	}
	return S_OK;
}

//=============================================
//�I��
//=============================================
void CInputPad::Uninit()
{
	//XInput�̃X�e�[�g��ݒ�(�����ɂ���)
	XInputEnable(false);
}

//=============================================
//�X�V
//=============================================
void CInputPad::Update()
{
	XINPUT_STATE joykeyState; //�W���C�p�b�h�̓��͏��

		//�W���C�p�b�h�̏�Ԃ��擾
	if (XInputGetState(0, &joykeyState) == ERROR_SUCCESS)
	{
		//�ڑ�����Ă��邩�ǂ���
		m_Connect = true;

		//�X�e�B�b�N�̍X�V
		UpdateStick(joykeyState);

		joykeyState.Gamepad.wButtons |= GetJoypadStick(joykeyState.Gamepad.sThumbLX, joykeyState.Gamepad.sThumbLY, JOYPAD_ZONE);

		WORD Button = joykeyState.Gamepad.wButtons;
		WORD OldButton = m_joyKeyState;
		m_joyKeyStateTrigger = Button & ~OldButton;    // �g���K�[����
		m_ajoyKeyStateRelease = ~Button & OldButton;    // �����[�X����

		// ���݂̎��Ԃ��擾����
		m_aJoypadCurrentTime = timeGetTime();

		if (joykeyState.Gamepad.wButtons && ((m_aJoypadCurrentTime - m_aJoypadExecLastTime) > JOYPAD_SPEED))
		{
			// �Ō�ɐ^��Ԃ������Ԃ�ۑ�
			m_aJoypadExecLastTime = m_aJoypadCurrentTime;

			// �L�[�{�[�h�̃��s�[�g����ۑ�
			m_joyKeyStateRepeat = joykeyState.Gamepad.wButtons;
		}
		else
		{
			// �L�[�{�[�h�̃��s�[�g����ۑ�
			m_joyKeyStateRepeat = 0;
		}

		m_joyKeyState = joykeyState.Gamepad.wButtons;                // �v���X����
	}
	else
	{
		m_Connect = false;
	}
}

//=============================================
//�ڑ�����Ă邩�擾
//=============================================
bool CInputPad::GetConnet()
{
	return m_Connect;
}

//=============================================
//�v���X���擾
//=============================================
bool CInputPad::GetPress(JOYKEY Key)
{
	return (m_joyKeyState & (0x01 << Key)) ? true : false;
}

//=============================================
//�g���K�[���擾
//=============================================
bool CInputPad::GetTrigger(JOYKEY Key)
{
	return (m_joyKeyStateTrigger & (0x01 << Key)) ? true : false;
}

//=============================================
//�����[�X���擾
//=============================================
bool CInputPad::GetRelease(JOYKEY Key)
{
	return(m_ajoyKeyStateRelease & (0x01 << Key)) ? true : false;
}

//=============================================
//��Ԏ擾
//=============================================
XINPUT_STATE* CInputPad::GetXInputState(void)
{
	return &m_XInput;
}

//=============================================
//�X�e�B�b�N�̍X�V
//=============================================
void CInputPad::UpdateStick(XINPUT_STATE state)
{
	for (int nCntStick = 0; nCntStick < STICKTYPE_MAX; nCntStick++)
	{
		float fX, fY; //�X�e�B�b�N��X���AY��

		switch (nCntStick)
		{
		case STICKTYPE_LEFT:
			fX = (state.Gamepad.sThumbLX);
			fY = (state.Gamepad.sThumbLY);
			break;
		case STICKTYPE_RIGHT:
			fX = (state.Gamepad.sThumbRX);
			fY = (state.Gamepad.sThumbRY);
			break;
		}

		//�p�x���擾
		m_stick.afAngle[nCntStick] = FindAngle(D3DXVECTOR3(fX, fY, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f)) * -1;

		//�X�e�B�b�N�̓|������擾
		m_stick.afTplDiameter[nCntStick] = fabsf(fX);

		if (m_stick.afTplDiameter[nCntStick] < fabsf(fY))
		{
			m_stick.afTplDiameter[nCntStick] = fabsf(fY);
		}

		m_stick.afTplDiameter[nCntStick] /= 32768.0f; //�|���Ă����Ԃ̏����l

		//�������̓t���O��������
		for (int nCntAngle = 0; nCntAngle < STICKANGLE_MAX; nCntAngle++)
		{
			m_bAngle[nCntStick][nCntAngle] = false;
		}

		if (m_stick.afTplDiameter[nCntStick] > 0.1f)
		{
			//�p�x���l�����ŏ�Ɉʒu���鎞�A��t���O��^�ɂ���
			if ((m_stick.afAngle[nCntStick] < D3DX_PI * -0.75) || (m_stick.afAngle[nCntStick] > D3DX_PI * 0.75))
			{
				m_bAngle[nCntStick][STICKANGLE_UP] = true;
			}

			//�p�x���l�����ŉ��Ɉʒu���鎞�A���t���O��^�ɂ���
			else if ((m_stick.afAngle[nCntStick] > D3DX_PI * -0.25) && (m_stick.afAngle[nCntStick] < D3DX_PI * 0.25))
			{
				m_bAngle[nCntStick][STICKANGLE_DOWN] = true;
			}

			//�p�x���l�����ō��Ɉʒu���鎞�A���t���O��^�ɂ���
			else if ((m_stick.afAngle[nCntStick] > D3DX_PI * -0.75) && (m_stick.afAngle[nCntStick] < D3DX_PI * -0.25))
			{
				m_bAngle[nCntStick][STICKANGLE_LEFT] = true;
			}

			//�p�x���l�����ŉE�Ɉʒu���鎞�A�E�t���O��^�ɂ���
			else if ((m_stick.afAngle[nCntStick] > D3DX_PI * 0.25) && (m_stick.afAngle[nCntStick] < D3DX_PI * 0.75))
			{
				m_bAngle[nCntStick][STICKANGLE_RIGHT] = true;
			}
		}

		//�p�x�ɉ��������͏���
		for (int nCntAngle = 0; nCntAngle < STICKANGLE_MAX; nCntAngle++)
		{
			//�X�e�B�b�N�̃g���K�[����ۑ�
			m_stick.abAngleTrigger[nCntStick][nCntAngle] = (m_stick.abAnglePress[nCntStick][nCntAngle] ^ m_bAngle[nCntStick][nCntAngle]) & m_bAngle[nCntStick][nCntAngle];

			//�X�e�B�b�N�̃����[�X����ۑ�
			m_stick.abAngleRelease[nCntStick][nCntAngle] = (m_stick.abAnglePress[nCntStick][nCntAngle] ^ m_bAngle[nCntStick][nCntAngle]) & ~m_bAngle[nCntStick][nCntAngle];

			//���݂̎��Ԃ��擾
			m_aStickCurrentTime[nCntStick][nCntAngle] = timeGetTime();

			if (m_bAngle[nCntStick][nCntAngle] && ((m_aStickCurrentTime[nCntStick][nCntAngle] - m_aStickExecLastTime[nCntStick][nCntAngle]) > JOYPAD_SPEED))
			{
				//�Ō�ɐ^��Ԃ������Ԃ�ۑ�
				m_aStickExecLastTime[nCntStick][nCntAngle] = m_aStickCurrentTime[nCntStick][nCntAngle];

				//�X�e�B�b�N�̃��s�[�g����ۑ�
				m_stick.abAngleRepeat[nCntStick][nCntAngle] = m_bAngle[nCntStick][nCntAngle];
			}
			else
			{
				//�X�e�B�b�N�̃��s�[�g����ۑ�
				m_stick.abAngleRepeat[nCntStick][nCntAngle] = 0;
			}

			//�X�e�B�b�N�̃v���X����ۑ�
			m_stick.abAnglePress[nCntStick][nCntAngle] = m_bAngle[nCntStick][nCntAngle];
		}
	}
}

//=============================================
//�X�e�B�b�N�̃����o�ϐ��擾
//=============================================
CInputPad::STICKINPUT CInputPad::GetStick(void)
{
	return m_stick;
}

//=============================================
//�p�x�v�Z
//=============================================
float CInputPad::FindAngle(D3DXVECTOR3 pos, D3DXVECTOR3 TargetPos)
{
	float fAngle; //�p�x

	fAngle = atan2f(TargetPos.y - pos.y, TargetPos.x - pos.x);

	fAngle -= (D3DX_PI * 0.5f);
	fAngle *= -1.0f;

	return fAngle;
}

//=============================================
//�X�e�B�b�N�̎擾
//=============================================
WORD CInputPad::GetJoypadStick(SHORT sThumbX, SHORT sThumbY, SHORT sDeadZone)
{
	WORD wButtons = 0;

	if (sThumbY >= sDeadZone)
	{
		wButtons |= XINPUT_GAMEPAD_DPAD_UP;
	}
	else if (sThumbY <= -sDeadZone)
	{
		wButtons |= XINPUT_GAMEPAD_DPAD_DOWN;
	}

	if (sThumbX <= -sDeadZone)
	{
		wButtons |= XINPUT_GAMEPAD_DPAD_LEFT;
	}
	else if (sThumbX >= sDeadZone)
	{
		wButtons |= XINPUT_GAMEPAD_DPAD_RIGHT;
	}

	return wButtons;
}
