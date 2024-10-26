//=============================================
//
//�����Ǘ��unumber.cpp�v
// Author���c�i�v
//
//=============================================
#include "number.h"
#include "manager.h"

//tex�p�X
const std::string CNumber::TEXTURE_NAME = "data\\TEXTURE\\number_000.png";

//=============================================
//�R���X�g���N�^
//=============================================
CNumber::CNumber(int nPriority) : CObject2D(nPriority), m_mintex(D3DXVECTOR2(0.0f,0.0f)),m_maxtex(D3DXVECTOR2(0.0f, 0.0f)), m_col(D3DXCOLOR(0.0f,0.0f,0.0f,0.0f))
{
}

//=============================================
//�f�X�g���N�^
//=============================================
CNumber::~CNumber()
{
}

//=============================================
//������
//=============================================
HRESULT CNumber::Init()
{
	//�e�N���X�̏�����
	CObject2D::Init();

	//���_����
	NumberVtx();

	return S_OK;
}

//=============================================
//�I��
//=============================================
void CNumber::Uninit()
{
	//�e�N���X�̏I��
	CObject2D::Uninit();
}

//=============================================
//�X�V
//=============================================
void CNumber::Update()
{
	//�e�N���X�̍X�V
	CObject2D::Update();

	//���_����
	NumberVtx();
}

//=============================================
//�`��
//=============================================
void CNumber::Draw()
{
	//�e�N���X�̕`��
	CObject2D::Draw();
}

//=============================================
//����
//=============================================
CNumber* CNumber::Create(D3DXVECTOR3 pos, D3DXVECTOR2 size)
{
	CTexture* pTexture = CManager::GetTexture();
	CNumber* pNumber = new CNumber;

	// null�Ȃ�null��Ԃ�
	if (pNumber == nullptr) { return nullptr; }

	pNumber->SetPos(pos); //pos�ݒ�

	pNumber->SetSize(size); //size�ݒ�

	pNumber->SetType(OBJECT_TYPE_NUMBER); //�^�C�v�ݒ�

	pNumber->BindTexture(pTexture->GetAddress(pTexture->Regist(&TEXTURE_NAME))); //�e�N�X�`���ݒ�

	pNumber->Init(); //����������

	return pNumber;
}

//=============================================
//�����̐ݒ�
//=============================================
void CNumber::SetNumber(float fNumPos1, float fNumPos2, D3DXCOLOR col)
{
	m_mintex.x = fNumPos1;
	m_maxtex.x = fNumPos2;
	m_col =col;
}

//=============================================
//������p�̒��_����
//=============================================
void CNumber::NumberVtx()
{
	CRenderer* pRender = CManager::GetRenderer();

	LPDIRECT3DDEVICE9 pDevice = pRender->GetDevice();

	LPDIRECT3DVERTEXBUFFER9 pBuff = GetVtxBuff();

	if (pBuff == nullptr)
	{
		pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4, D3DUSAGE_WRITEONLY, FVF_VERTEX_2D, D3DPOOL_MANAGED, &pBuff, NULL);
	}
	VERTEX_2D* pVtx;

	//���_�o�b�t�@�����b�N�����_���ւ̃|�C���^���擾
	pBuff->Lock(0, 0, (void**)&pVtx, 0);

	//���_���W�̐ݒ�
	pVtx[0].pos = D3DXVECTOR3(GetPos().x-GetSize().x
		, GetPos().y -GetSize().y
		, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(GetPos().x + GetSize().x
		, GetPos().y -GetSize().y
		, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(GetPos().x -GetSize().x
		, GetPos().y + GetSize().y
		, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(GetPos().x+GetSize().x
		, GetPos().y + GetSize().y
		, 0.0f);

	//rhw�̐ݒ�
	pVtx[0].rhw = 1.0f;
	pVtx[1].rhw = 1.0f;
	pVtx[2].rhw = 1.0f;
	pVtx[3].rhw = 1.0f;

	//���_�J���[�̐ݒ�
	pVtx[0].col = m_col;
	pVtx[1].col = m_col;
	pVtx[2].col = m_col;
	pVtx[3].col = m_col;

	pVtx[0].tex = D3DXVECTOR2(m_mintex.x, 0.0f);
	pVtx[1].tex = D3DXVECTOR2(m_maxtex.x, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(m_mintex.x, 1.0f);
	pVtx[3].tex = D3DXVECTOR2(m_maxtex.x, 1.0f);

	//�A�����b�N
	pBuff->Unlock();

	SetVtxBuff(pBuff);
}
