//=============================================
//
//3DTemplate[camera.cpp]
//Auther Matsuda Towa
//
//=============================================
#include "camera.h"
#include "renderer.h"
#include "manager.h"
#include "object.h"
#include "player.h"
#include "player_test.h"

//�ʏ�̈ړ����x
const float CCamera::DEFAULT_MOVE = 1.0f;

//�ʏ�̈ړ����x
const float CCamera::DAMPING_COEFFICIENT = 0.2f;

//�ʏ��Ԃ�Y�̋���
const float CCamera::DEFAULT_LENGTH_Y = 200.0f;

//�ʏ��Ԃ�Z�̋���
const float CCamera::DEFAULT_LENGTH_Z = 500.0f;

//�o�[�h�r���[����Y�̋���
const float CCamera::BIRDVIEW_LENGTH_Y = 300.0f;

//�T�C�h�r���[����X�̋���
const float CCamera::SIDEVIEW_LENGTH_X = 20.0f;

//�T�C�h�r���[����Y�̋���
const float CCamera::SIDEVIEW_LENGTH_Y = 50.0f;

//�T�C�h�r���[����Z�̋���
const float CCamera::SIDEVIEW_LENGTH_Z = 200.0f;

//�T�[�h�r���[���̋���
const float CCamera::THIRDVIEW_LENGTH = 110.0f;

//�T�[�h�r���[���̕␳�l
const float CCamera::THIRDVIEW_CORRECT_X = 20.0f;
const float CCamera::THIRDVIEW_CORRECT_Y = 80.0f;
const float CCamera::THIRDVIEW_CORRECT_Z = 20.0f;

//�T�[�h�p�[�\���r���[����X�̍ő����
const float CCamera::MAX_TURN_X = 0.5f;
//�T�[�h�p�[�\���r���[����X�̍ŏ�����
const float CCamera::MIN_TURN_X = -0.15f;

CCamera::CANERA_TYPE CCamera::m_type = TYPE_THIRDVIEW;

//=============================================
//�R���X�g���N�^
//=============================================
CCamera::CCamera()
{
}

//=============================================
//�f�X�g���N�^
//=============================================
CCamera::~CCamera()
{
}

//=============================================
//������
//=============================================
HRESULT CCamera::Init()
{
	
	m_posV = D3DXVECTOR3(0.0f, 200.0f, -180.0f); //���_
	m_posR = D3DXVECTOR3(0.0f, 0.0f, 0.0f); //����

	m_vecU = D3DXVECTOR3(0.0f, 1.0f, 0.0f); //������x�N�g��

	m_moveV = D3DXVECTOR3(0.0f, 0.0f, 0.0f); //���_�ړ���
	m_moveR = D3DXVECTOR3(0.0f, 0.0f, 0.0f); //�����_�ړ���

	m_rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f); //�p�x
	m_rotmove = D3DXVECTOR3(0.0f, 0.0f, 0.0f); //��]��

	D3DXVECTOR3 vecCamera = m_posR - m_posV;
	m_fLength = sqrtf(vecCamera.y * vecCamera.y + vecCamera.z * vecCamera.z);

	//�Ίp���̊p�x���Z�o����
	m_fAngle = atan2f(vecCamera.y, vecCamera.z);
	return S_OK;
}

//=============================================
//�I��
//=============================================
void CCamera::Uninit()
{
}

//=============================================
//�X�V
//=============================================
void CCamera::Update()
{
	//�L�[�{�[�h���擾
	CInputKeyboard* pKeyboard = CManager::GetKeyboard();

	if (pKeyboard->GetTrigger(DIK_F1))
	{
		m_type = TYPE_BIRDVIEW;
	}
	else if (pKeyboard->GetTrigger(DIK_F2))
	{
		m_type = TYPE_SIDEVIEW;
	}
	else if (pKeyboard->GetTrigger(DIK_F3))
	{
		m_type = TYPE_DEBUG;
	}
	else if (pKeyboard->GetTrigger(DIK_F6))
	{
		m_type = TYPE_THIRDVIEW;
	}

	switch (m_type)
	{
	case TYPE_BIRDVIEW:
		BirdViewCamera();
		break;
	case TYPE_SIDEVIEW:
		SideViewCamera();
		break;
	case TYPE_PARALLEL_SIDEVIEW:
		SideViewCamera();
		break;
	case TYPE_THIRDVIEW:
		ThirdViewCamera();
		CameraTurn();
		break;
	case TYPE_DEBUG:
		CameraTurn();
		CameraMove();
		break;
	default:
		break;
	}

	if (m_rot.y > D3DX_PI)
	{
		m_rot.y = -D3DX_PI;
		//		m_rot.y -= D3DX_PI* 2.0f;
	}

	if (m_rot.y < -D3DX_PI)
	{
		m_rot.y = D3DX_PI;
	}

	if (m_rot.x > D3DX_PI)
	{
		m_rot.x = -D3DX_PI;
		//		m_rot.y -= D3DX_PI* 2.0f;
	}

	if (m_rot.x < -D3DX_PI)
	{
		m_rot.x = D3DX_PI;
	}

	m_posV += m_moveV;
	m_posR += m_moveR;

	//�ړ��ʂ��X�V(�����j
	m_moveV.x += (0.0f - m_moveV.x) * DAMPING_COEFFICIENT;
	m_moveV.y += (0.0f - m_moveV.y) * DAMPING_COEFFICIENT;
	m_moveV.z += (0.0f - m_moveV.z) * DAMPING_COEFFICIENT;

	m_moveR.x += (0.0f - m_moveR.x) * DAMPING_COEFFICIENT;
	m_moveR.y += (0.0f - m_moveR.y) * DAMPING_COEFFICIENT;
	m_moveR.z += (0.0f - m_moveR.z) * DAMPING_COEFFICIENT;

}

//=============================================
//�J�����ݒ�
//=============================================
void CCamera::SetCamera()
{
	CRenderer* pRender = CManager::GetRenderer();
	LPDIRECT3DDEVICE9 pDevice = pRender->GetDevice();

	//�v���W�F�N�V�����}�g���b�N�X�̏�����
	D3DXMatrixIdentity(&m_mtxProjection);

	switch (m_type)
	{
	case TYPE_PARALLEL_SIDEVIEW:
		//���s���e
		D3DXMatrixOrthoLH(&m_mtxProjection,
		(float)SCREEN_WIDTH * 0.2f,
		(float)SCREEN_HEIGHT* 0.2f,
		5.0f,
		500.0f);
		break;
	default:
		//�v���W�F�N�V�����}�g���b�N�X���쐬
		D3DXMatrixPerspectiveFovLH(&m_mtxProjection,
			D3DXToRadian(45.0f),
			(float)SCREEN_WIDTH / (float)SCREEN_HEIGHT,
			10.0f,
			2000.0f);
		break;
	}

	//�v���W�F�N�V�����}�g���b�N�X�̐ݒ�
	pDevice->SetTransform(D3DTS_PROJECTION, &m_mtxProjection);

	//�r���[�}�g���b�N�X�̏�����
	D3DXMatrixIdentity(&m_mtxView);

	D3DXVECTOR3 posV = m_posV;
	D3DXVECTOR3 posR = m_posR;

	posV.y += -15.0f;
	posR.y += -15.0f;

	//�r���[�}�g���b�N�X�̍쐬
	D3DXMatrixLookAtLH(&m_mtxView,
		&posV,
		&posR,
		&m_vecU);

	//�r���[�}�g���b�N�X�̐ݒ�
	pDevice->SetTransform(D3DTS_VIEW, &m_mtxView);
}

//======================================
//�J�������Z�b�g
//======================================
void CCamera::ResetCamera()
{
	m_posV = D3DXVECTOR3(0.0f, 30.0f, -180.0f); //���_
	m_posR = D3DXVECTOR3(0.0f, 0.0f, 0.0f); //����

	m_vecU = D3DXVECTOR3(0.0f, 1.0f, 0.0f); //������x�N�g��

	m_moveV = D3DXVECTOR3(0.0f, 0.0f, 0.0f); //���_�ړ���
	m_moveR = D3DXVECTOR3(0.0f, 0.0f, 0.0f); //�����_�ړ���

	m_rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f); //�p�x
	m_rotmove = D3DXVECTOR3(0.0f, 0.0f, 0.0f); //��]��

	D3DXVECTOR3 vecCamera = m_posR - m_posV;
	m_fLength = sqrtf(vecCamera.y * vecCamera.y + vecCamera.z * vecCamera.z);

	//�Ίp���̊p�x���Z�o����
	m_fAngle = atan2f(vecCamera.y, vecCamera.z);

	m_type = TYPE_DEBUG;
}

//=============================================
//�J�����^�C�v�擾
//=============================================
CCamera::CANERA_TYPE CCamera::GetType()
{
	return m_type;
}

//=============================================
//�J�����ړ���
//=============================================
void CCamera::CameraMove()
{
	//�L�[�{�[�h���擾
	CInputKeyboard* pKeyboard = CManager::GetKeyboard();
	D3DXVECTOR3 vecDirection(0.0f, 0.0f, 0.0f);

	if (pKeyboard->GetPress(DIK_J) == true)
	{
		m_moveV.x -= sinf(D3DX_PI / 2 + m_rot.y) * DEFAULT_MOVE;
		m_moveR.x -= sinf(D3DX_PI / 2 + m_rot.y) * DEFAULT_MOVE;

		m_moveV.z -= cosf(D3DX_PI / 2 + m_rot.y) * DEFAULT_MOVE;
		m_moveR.z -= cosf(D3DX_PI / 2 + m_rot.y) * DEFAULT_MOVE;

	}

	if (pKeyboard->GetPress(DIK_L) == true)
	{
		m_moveV.x += sinf(D3DX_PI / 2 + m_rot.y) * DEFAULT_MOVE;
		m_moveR.x += sinf(D3DX_PI / 2 + m_rot.y) * DEFAULT_MOVE;

		m_moveV.z += cosf(D3DX_PI / 2 + m_rot.y) * DEFAULT_MOVE;
		m_moveR.z += cosf(D3DX_PI / 2 + m_rot.y) * DEFAULT_MOVE;

	}

	if (pKeyboard->GetPress(DIK_I) == true)
	{
		m_moveV.x -= sinf(D3DX_PI + m_rot.y) * DEFAULT_MOVE;
		m_moveR.x -= sinf(D3DX_PI + m_rot.y) * DEFAULT_MOVE;

		m_moveV.z -= cosf(D3DX_PI + m_rot.y) * DEFAULT_MOVE;
		m_moveR.z -= cosf(D3DX_PI + m_rot.y) * DEFAULT_MOVE;

	}

	if (pKeyboard->GetPress(DIK_K) == true)
	{
		m_moveV.x += sinf(D3DX_PI + m_rot.y) * DEFAULT_MOVE;
		m_moveR.x += sinf(D3DX_PI + m_rot.y) * DEFAULT_MOVE;

		m_moveV.z += cosf(D3DX_PI + m_rot.y) * DEFAULT_MOVE;
		m_moveR.z += cosf(D3DX_PI + m_rot.y) * DEFAULT_MOVE;

	}

}

//=============================================
//�J������]��
//=============================================
void CCamera::CameraTurn()
{
	//�L�[�{�[�h���擾
	CInputKeyboard* pKeyboard = CManager::GetKeyboard();
	if (pKeyboard->GetPress(DIK_Q) == true)
	{
		m_rot.y -= 0.02f;

		m_posR.x = m_posV.x + sinf(m_rot.y) * m_fLength;
		m_posR.z = m_posV.z + cosf(m_rot.y) * m_fLength;

	}

	if (pKeyboard->GetPress(DIK_E) == true)
	{
		m_rot.y += 0.02f;
		m_posR.x = m_posV.x + sinf(m_rot.y) * m_fLength;
		m_posR.z = m_posV.z + cosf(m_rot.y) * m_fLength;
	}

	if (pKeyboard->GetPress(DIK_U) == true)
	{
		m_rot.y -= 0.02f;

		m_posV.x = m_posR.x - sinf(m_rot.y) * m_fLength;

		m_posV.z = m_posR.z - cosf(m_rot.y) * m_fLength;
	}

	if (pKeyboard->GetPress(DIK_O) == true)
	{
		m_rot.y += 0.02f;

		m_posV.x = m_posR.x - sinf(m_rot.y) * m_fLength;

		m_posV.z = m_posR.z - cosf(m_rot.y) * m_fLength;
	}
}

//=============================================
//�o�[�h�r���[����
//=============================================
void CCamera::BirdViewCamera()
{
	for (int nCnt = 0; nCnt < CObject::MAX_OBJECT; nCnt++)
	{
		//�I�u�W�F�N�g�擾
		CObject* pObj = CObject::Getobject(CPlayer::PLAYER_PRIORITY, nCnt);
		if (pObj != nullptr)
		{//�k���|�C���^����Ȃ����
			//�^�C�v�擾
			CObject::OBJECT_TYPE type = pObj->GetType();
			if (type == CObject::OBJECT_TYPE::OBJECT_TYPE_PLAYER)
			{
				CPlayer* pPlayer = dynamic_cast<CPlayer*>(pObj);
				m_posR =pPlayer->GetPos();
				m_posV.x = m_posR.x - sinf(m_rot.y);
				m_posV.y = BIRDVIEW_LENGTH_Y;
				m_posV.z = m_posR.z - cosf(m_rot.y);
				break;
			}
		}
	}
}

//=============================================
//�T�C�h�r���[����
//=============================================
void CCamera::SideViewCamera()
{
	for (int nCnt = 0; nCnt < CObject::MAX_OBJECT; nCnt++)
	{
		//�L�[�{�[�h���擾
		CInputKeyboard* pKeyboard = CManager::GetKeyboard();
		if (pKeyboard->GetTrigger(DIK_F4))
		{
			m_type = TYPE_PARALLEL_SIDEVIEW;
		}

		//�I�u�W�F�N�g�擾
		CObject* pObj = CObject::Getobject(CPlayer::PLAYER_PRIORITY, nCnt);
		if (pObj != nullptr)
		{//�k���|�C���^����Ȃ����
			//�^�C�v�擾
			CObject::OBJECT_TYPE type = pObj->GetType();
			if (type == CObject::OBJECT_TYPE::OBJECT_TYPE_PLAYER)
			{
				CPlayer* pPlayer = dynamic_cast<CPlayer*>(pObj);
				m_posR.x = pPlayer->GetPos().x;
				m_posR.y = 20.0f;
				m_posR.z = pPlayer->GetPos().z;
				m_posV.x = m_posR.x - sinf(m_rot.y)* SIDEVIEW_LENGTH_X;
				m_posV.y = SIDEVIEW_LENGTH_Y;
				m_posV.z = m_posR.z - cosf(m_rot.y) * SIDEVIEW_LENGTH_Z;
				break;
			}
		}
	}
}

//=============================================
//�T�[�h�p�[�\���r���[����
//=============================================
void CCamera::ThirdViewCamera()
{
	for (int nCnt = 0; nCnt < CObject::MAX_OBJECT; nCnt++)
	{

		//�I�u�W�F�N�g�擾
		CObject* pObj = CObject::Getobject(CPlayer_test::PLAYER_PRIORITY, nCnt);
		if (pObj != nullptr)
		{//�k���|�C���^����Ȃ����
			//�^�C�v�擾
			CObject::OBJECT_TYPE type = pObj->GetType();
			if (type == CObject::OBJECT_TYPE::OBJECT_TYPE_PLAYER)
			{
				CPlayer_test* pPlayer = dynamic_cast<CPlayer_test*>(pObj);

				m_posR.x = pPlayer->GetPos().x;
				m_posR.y = pPlayer->GetPos().y + THIRDVIEW_CORRECT_Y;
				m_posR.z = pPlayer->GetPos().z;

				m_posV = m_posR + D3DXVECTOR3(-THIRDVIEW_LENGTH * cosf(m_rot.x) * sinf(m_rot.y), 
				THIRDVIEW_LENGTH * sinf(m_rot.x), 
				-THIRDVIEW_LENGTH * cosf(m_rot.x) * cosf(m_rot.y));

				// �J�������v���C���[�̉E�ɂ��鏈��:TODO
				//m_posR.x = pPlayer->GetPos().x + THIRDVIEW_CORRECT_X;
				//m_posR.y = pPlayer->GetPos().y + THIRDVIEW_CORRECT_Y;
				//m_posR.z = pPlayer->GetPos().z + THIRDVIEW_CORRECT_Z;

				//m_posV = m_posR + D3DXVECTOR3(-THIRDVIEW_LENGTH * cosf(m_rot.x) * sinf(m_rot.y), 
				//THIRDVIEW_LENGTH * sinf(m_rot.x), 
				//-THIRDVIEW_LENGTH * cosf(m_rot.x) * cosf(m_rot.y));

				//�}�E�X���擾
				CInputMouse* pMouse = CManager::GetMouse();
				//���݂̃V�[�����擾 TODO:�V�[���Q�Ƃ����
				CScene::MODE pScene = CScene::GetSceneMode();
				if (pScene != CScene::MODE::MODE_TITLE)
				{
					m_rot.y += pMouse->GetMouseMove().x * 0.001f;
					m_rot.x += pMouse->GetMouseMove().y * 0.001f;
				}
				//�L�[�{�[�h���擾
				CInputKeyboard* pKeyboard = CManager::GetKeyboard();
				
				if (m_rot.x <= MIN_TURN_X)
				{
					m_rot.x = MIN_TURN_X;
				}
				if (m_rot.x >= MAX_TURN_X)
				{
					m_rot.x = MAX_TURN_X;
				}
			}
		}
	}
}

//=============================================
//�J�����̕����擾
//=============================================
D3DXVECTOR3 CCamera::GetRot()
{
	return m_rot;
}

//=============================================
//�J�����̎��_�擾
//=============================================
D3DXVECTOR3 CCamera::GetPosV()
{
	return m_posV;
}

//=============================================
//�J�����̒����_�擾
//=============================================
D3DXVECTOR3 CCamera::GetPosR()
{
	return m_posR;
}

//=============================================
//�J�����̃f�o�b�O�\��
//=============================================
void CCamera::DebugCameraDraw()
{
#ifdef _DEBUG
	LPD3DXFONT pFont = CManager::GetRenderer()->GetFont();
	RECT rect = { 0,0,SCREEN_WIDTH,SCREEN_HEIGHT };
	char aStr[256];

	sprintf(&aStr[0], "\n\n\n\n\n\n\n\n[camera]\nposR:%.1f,%.1f,%.1f\nposV:%.1f,%.1f,%.1f\nrot:%.1f,%.1f,%.1f"
		, m_posR.x, m_posR.y, m_posR.z, m_posV.x, m_posV.y, m_posV.z, m_rot.x, m_rot.y, m_rot.z);
	//�e�L�X�g�̕`��
	pFont->DrawText(NULL, &aStr[0], -1, &rect, DT_LEFT, D3DCOLOR_RGBA(255, 0, 0, 255));
#endif // _DEBUG
}
