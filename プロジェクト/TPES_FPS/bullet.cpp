//=============================================
//
//�e[bullet.cpp]
//Auther Matsuda Towa
//
//=============================================
#include "bullet.h"
#include "manager.h"
#include "game.h"
#include "player.h"

//�e�N�X�`���p�X
const std::string CBullet::BULLET_TEXTURE_NAME ="data\\TEXTURE\\bullet.png";

//=============================================
//�R���X�g���N�^
//=============================================
CBullet::CBullet(int nPriority):CAttack_Manager(nPriority)
{
}

//=============================================
//�f�X�g���N�^
//=============================================
CBullet::~CBullet()
{
}

//=============================================
//������
//=============================================
HRESULT CBullet::Init()
{
	//�e�N���X�̏�����
	CAttack_Manager::Init();

	return S_OK;
}

//=============================================
//�I��
//=============================================
void CBullet::Uninit()
{
	//�e�N���X�̏I��
	CAttack_Manager::Uninit();
}

//=============================================
//�X�V
//=============================================
void CBullet::Update()
{
	//�e�N���X�̍X�V
	CAttack_Manager::Update();
	
	//�g�p���Ă���Ƃ�
	OnActive();

}

//=============================================  
//�`��
//=============================================
void CBullet::Draw()
{
	//�e�N���X�̕`��
	CAttack_Manager::Draw();
}

//=============================================
//�g�p����Ă鎞�̏���
//=============================================
void CBullet::OnActive()
{
	//�̗͎擾
	int nLife = GetLife();

	if (nLife <= 0)
	{
		//�I��
		Uninit();
		return;
	}

	//���C�t������Ώ������s
	D3DXVECTOR3 pos = GetPos();
	pos += m_move;
	//���W���X�V
	SetPos(pos);
	//���_���W
	SetVtx(D3DXVECTOR3(0.0f, 0.0f, -1.0f));

	//�����蔻��`�F�b�N�ϐ�
	bool bHitCheck = false;

	switch (m_Allegiance)
	{
	case BULLET_ALLEGIANCE_PLAYER:
		bHitCheck = HitEnemy();
		if (bHitCheck)
		{
			SetHitMaker();
		}
		break;

	case BULLET_ALLEGIANCE_ENEMY:
		bHitCheck = HitPlayer();
		break;

	default:
		assert(false);
		break;
	}

	//�����蔻��`�F�b�NTODO:���C�ł��
	bHitCheck = HitBlock();

	//�����蔻��`�F�b�N�ϐ�
	bool bPenetration = false;

	bPenetration = PenetrationBlock();

	if (bHitCheck == true || bPenetration == true)
	{//�������Ă���
		Uninit();
	}
}

//=============================================
//�q�b�g�}�[�J�[�쐬
//=============================================
void CBullet::SetHitMaker()
{
	for (int nCnt = 0; nCnt < MAX_OBJECT; nCnt++)
	{
		//�I�u�W�F�N�g�擾
		CObject* pObj = CObject::Getobject(CPlayer::PLAYER_PRIORITY, nCnt);
		if (pObj == nullptr)
		{//�k���|�C���^�Ȃ�
			//�I�u�W�F�N�g��T��������
			continue;
		}
		 //�^�C�v�擾
		CObject::OBJECT_TYPE type = pObj->GetType();

		//�v���C���[��T��
		if (type != CObject::OBJECT_TYPE::OBJECT_TYPE_PLAYER)
		{//�v���C���[����Ȃ����
			//�v���C���[��T��������
			continue;
		}

		CPlayer* pPlayer = dynamic_cast<CPlayer*>(pObj);

		if (pPlayer->m_Raticle != nullptr)
		{
			if (pPlayer->m_Raticle->m_pHitMaker != nullptr)
			{
				pPlayer->m_Raticle->m_pHitMaker->SetColor(COLOR_WHITE);
			}
		}
	}
}

//=============================================
//�e�쐬
//=============================================
CBullet* CBullet::Create(D3DXVECTOR3 pos, D3DXVECTOR3 move, D3DXVECTOR3 rot, D3DXVECTOR3 size
,int nLife, int nDamage, BULLET_ALLEGIANCE Allegiance,BULLET_TYPE type)
{
	CBullet* pBullet = nullptr;

	switch (type)
	{
	case CBullet::BULLET_TYPE::BULLET_TYPE_NORMAL:
		pBullet = new CBullet;
		break;

	default:
		break;
	}

	if (pBullet == nullptr) {return nullptr;}

	CTexture* pTexture = CManager::GetInstance()->GetTexture();

	pBullet->SetPos(pos); //pos�ݒ�
	pBullet->SetSize(size); //�T�C�Y�ݒ�
	pBullet->SetRot(rot);	//�����ݒ�
	pBullet->m_move = move; //�ړ��ʑ��
	pBullet->SetLife(nLife); //�������
	pBullet->SetDamage(nDamage); //�З͑��

	switch (type)
	{
	case CBullet::BULLET_TYPE::BULLET_TYPE_NORMAL:
		pBullet->BindTexture(pTexture->GetAddress(pTexture->Regist(&BULLET_TEXTURE_NAME)));
		break;
	default:
		assert(false);
		break;
	}
	pBullet->m_type = type;
	pBullet->m_Allegiance = Allegiance; //�e�̐ݒ�
	pBullet->SetType(OBJECT_TYPE_BULLET); //�^�C�v�ݒ�
	pBullet->Init();

	return pBullet;
}

//=============================================
//�u���b�N�ɓ����������ǂ���
//=============================================
bool CBullet::PenetrationBlock()
{
	//�ʒu�擾
	D3DXVECTOR3 Attackpos = GetPos();
	//�T�C�Y�擾
	D3DXVECTOR3 Attacksize = GetSize();

	for (int nCnt = 0; nCnt < MAX_OBJECT; nCnt++)
	{
		//�I�u�W�F�N�g�擾
		CObject* pObj = CObject::Getobject(CBlock::BLOCK_PRIORITY, nCnt);
		if (pObj == nullptr)
		{//�k���|�C���^�Ȃ�
			//�I�u�W�F�N�g��T��������
			continue;
		}
		//�^�C�v�擾
		CObject::OBJECT_TYPE type = pObj->GetType();

		//�u���b�N��T��
		if (type != CObject::OBJECT_TYPE::OBJECT_TYPE_BLOCK)
		{//�u���b�N����Ȃ����
			//�u���b�N��T��������
			continue;
		}

		//�u���b�N�Ƃ̓����蔻��
		CBlock* pBlock = dynamic_cast<CBlock*>(pObj);

		CColision::COLISION ColisionCheck_X = CManager::GetInstance()->GetColision()->CheckPolygonModelPenetration_X(Attackpos - m_move, Attackpos, pBlock->GetPos(), pBlock->GetMinPos(), pBlock->GetMaxPos());
		CColision::COLISION ColisionCheck_Z = CManager::GetInstance()->GetColision()->CheckPolygonModelPenetration_Z(Attackpos - m_move, Attackpos, pBlock->GetPos(), pBlock->GetMinPos(), pBlock->GetMaxPos());

		if (ColisionCheck_X != CColision::COLISION::COLISON_NONE || ColisionCheck_Z != CColision::COLISION::COLISON_NONE)
		{//�������Ă���
			//�U���̍폜
			return true;
		}
	}
	return false;
}
