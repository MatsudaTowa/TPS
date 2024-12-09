//=============================================
//
//3DTemplate[bullet.cpp]
//Auther Matsuda Towa
//
//=============================================
#include "bullet.h"
#include "manager.h"
#include "game.h"

//�e�N�X�`��������
const std::string CBullet::BULLET_TEXTURE_NAME ="data\\TEXTURE\\effect000.jpg";

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

	if (nLife > 0)
	{//���C�t������Ώ������s
		D3DXVECTOR3 pos = GetPos();
		pos += m_move;
		//���W���X�V
		SetPos(pos);
		//���_���W
		SetVtx(D3DXVECTOR3(0.0f, 0.0f, -1.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));

		//�����蔻��`�F�b�N�ϐ�
		bool bHitCheck = false;

		switch (m_Allegiance)
		{
		case BULLET_ALLEGIANCE_PLAYER:
			bHitCheck = HitEnemy();
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

		if (bHitCheck == true)
		{//�������Ă���
			Uninit();
		}
	}
	else
	{
		//�I��
		Uninit();
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
	pBullet->SetRot(rot);
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
//�ړ��ʎ擾
//=============================================
D3DXVECTOR3 CBullet::GetMove()
{
	return m_move;
}

//=============================================
//�G���������擾
//=============================================
CBullet::BULLET_ALLEGIANCE CBullet::GetBulletAllegiance()
{
	return m_Allegiance;
}
