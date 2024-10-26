//=============================================
//
//3DTemplate[object.cpp]
//Auther Matsuda Towa
//
//=============================================
#include "object.h"
#include "object2D.h"
#include "object3D.h"

//����������
int CObject::m_nNumAll = 0;

//�I�u�W�F�N�g�|�C���^������
CObject* CObject::m_apObject[MAX_PRIORITY][CObject::MAX_OBJECT] = {};

//=============================================
//�R���X�g���N�^
//=============================================
CObject::CObject(int nPriority)
{
	m_nPriority = nPriority; //�`��D��x�ݒ�

	for (int nCnt = 0; nCnt < CObject::MAX_OBJECT; nCnt++)
	{
		if (m_apObject[m_nPriority][nCnt] == nullptr)
		{
			m_apObject[m_nPriority][nCnt] = this; //�������g����
			m_nID = nCnt; //ID���
			m_type = OBJECT_TYPE_NONE;
			m_nNumAll++; //��������
			break;
		}
	}
}

//=============================================
//�f�X�g���N�^
//=============================================
CObject::~CObject()
{
	m_nNumAll--;
}

//=============================================
//�S�폜
//=============================================
void CObject::ReleaseAll()
{
	for (int nCntPri = 0; nCntPri < MAX_PRIORITY; nCntPri++)
	{
		for (int nCntObj = 0; nCntObj < CObject::MAX_OBJECT; nCntObj++)
		{

			if (m_apObject[nCntPri][nCntObj] != nullptr)
			{
				if (m_apObject[nCntPri][nCntObj]->m_type != CObject::OBJECT_TYPE::OBJECT_TYPE_FADE)
				{
					//�I������
					m_apObject[nCntPri][nCntObj]->Uninit();
					m_apObject[nCntPri][nCntObj] = nullptr;
				}
			}

		}
	}

}

//=============================================
//�S�X�V
//=============================================
void CObject::UpdateAll()
{
	for (int nCntPri = 0; nCntPri < MAX_PRIORITY; nCntPri++)
	{
		for (int nCntObj = 0; nCntObj < CObject::MAX_OBJECT; nCntObj++)
		{
			if (m_apObject[nCntPri][nCntObj] != nullptr)
			{
				//�X�V����
				m_apObject[nCntPri][nCntObj]->Update();
			}
		}
	}
}

//=============================================
//�S�`��
//=============================================
void CObject::DrawAll()
{
	for (int nCntPri = 0; nCntPri < MAX_PRIORITY; nCntPri++)
	{
		for (int nCntObj = 0; nCntObj < CObject::MAX_OBJECT; nCntObj++)
		{
			if (m_apObject[nCntPri][nCntObj] != nullptr)
			{
				//�I������
				m_apObject[nCntPri][nCntObj]->Draw();
			}
		}
	}
}


//=============================================
//�������g�̍폜
//=============================================
void CObject::Release()
{
	int nID = m_nID;
	int nPri = m_nPriority;
	if (m_apObject[nPri][nID] != nullptr)
	{
		delete m_apObject[nPri][nID];
		m_apObject[nPri][nID] = nullptr;
	}
}

//=============================================
//�I�u�W�F�N�g�擾
//=============================================
CObject* CObject::Getobject(int nPri, int nIdx)
{
	return m_apObject[nPri][nIdx];
}

//=============================================
//�^�C�v�擾
//=============================================
CObject::OBJECT_TYPE CObject::GetType()
{
	return m_type;
}

//=============================================
//�^�C�v�ݒ�
//=============================================
void CObject::SetType(OBJECT_TYPE type)
{
	m_type = type;
}

