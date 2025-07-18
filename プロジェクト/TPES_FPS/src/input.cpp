//=============================================
//
//�C���v�b�g[input.cpp]
//Author Matsuda Towa
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
		for (nCntKey = INT_ZERO; nCntKey < NUM_KEY_MAX; nCntKey++)
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
	m_MousePos = VEC3_RESET_ZERO;
	m_MouseMove = VEC3_RESET_ZERO;
	diprop.diph.dwSize = sizeof(diprop);
	diprop.diph.dwHeaderSize = sizeof(diprop.diph);
	diprop.diph.dwObj = INT_ZERO;
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
		for (nCntMouse = INT_ZERO; nCntMouse < NUM_MOUSE_MAX; nCntMouse++)
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
	POINT pMousePos;
	GetCursorPos(&pMousePos);
	ScreenToClient(CManager::GetInstance()->GetHWnd(), &pMousePos);
	sprintf(&aStr[0], "[mouse]\nmove:%.1f,%.1f,%.1f\npos%.1f,%.1f"
		, m_MouseMove.x, m_MouseMove.y, m_MouseMove.z,(float)pMousePos.x,(float)pMousePos.y);
	//�e�L�X�g�̕`��
	pFont->DrawText(NULL, &aStr[0], -1, &rect, DT_RIGHT, D3DCOLOR_RGBA(255, 0, 0, 255));
#endif // _DEBUG


}