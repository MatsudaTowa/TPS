//=============================================
//
//3DTemplate[billboard.h]
//Auther Matsuda Towa
//
//=============================================
#include "billboard.h"
#include "manager.h"

//=============================================
//�R���X�g���N�^
//=============================================
CBillboard::CBillboard(int nPriority) :CObject3D(nPriority)
{
}

//=============================================
//�f�X�g���N�^
//=============================================
CBillboard::~CBillboard()
{
}

//=============================================
//�`��
//=============================================
void CBillboard::Draw()
{
	CRenderer* pRender = CManager::GetRenderer();

	LPDIRECT3DDEVICE9 pDevice = pRender->GetDevice();

	D3DXMATRIX mtxRot, mtxTrans; //�v�Z�p�}�g���b�N�X

	D3DXMATRIX mtxView; //�`��}�g���b�N�X

	D3DXMATRIX mtxWorld = GetMtxWorld(); //�`��}�g���b�N�X

	D3DXVECTOR3 pos = GetPos();	//�ꏊ�擾

	D3DXVECTOR3 rot = GetRot();	//�����擾

	LPDIRECT3DVERTEXBUFFER9 pVtxBuff = GetVtxBuff(); //���_���W�擾

	LPDIRECT3DTEXTURE9 pTexture = GetTexture(); //�e�N�X�`�����擾

	//�}�g���b�N�X�̏�����
	D3DXMatrixIdentity(&mtxWorld);

	//�r���[�}�g���b�N�X���擾
	pDevice->GetTransform(D3DTS_VIEW, &mtxView);

	//�|���S���̐��ʂ��J�����Ɍ�����
	D3DXMatrixInverse(&mtxWorld, NULL, &mtxView);

	mtxWorld._41 = 0.0f;
	mtxWorld._42 = 0.0f;
	mtxWorld._43 = 0.0f;

	//�ʒu�𔽉f
	D3DXMatrixTranslation(&mtxTrans, pos.x, pos.y, pos.z);

	D3DXMatrixMultiply(&mtxWorld, &mtxWorld, &mtxTrans);

	//���[���h�}�g���b�N�X�̐ݒ�
	pDevice->SetTransform(D3DTS_WORLD, &mtxWorld);

	//���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(0, pVtxBuff, 0, sizeof(VERTEX_3D));

	//���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_3D);

	//�e�N�X�`���̐ݒ�
	pDevice->SetTexture(0, pTexture);

	//�|���S���̕`��
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);

	SetMtxWorld(mtxWorld);
}
