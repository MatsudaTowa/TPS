//=============================================
//
//�����Ǘ��unumber.h�v
// Author���c�i�v
//
//=============================================
#ifndef _NUMBER_H_ //���ꂪ��`����ĂȂ��Ƃ�
#define _NUMBER_H_
#include "main.h"
#include "object2D.h"
#include "billboard.h"

//=============================================
//�i���o�[�N���X2D
//=============================================
class CNumber_2D:public CObject2D
{
public:
	static const std::string TEXTURE_NAME;	//�e�N�X�`���̖��O
	static const int NUMBER_PRIORITY = 60;  //�`�揇
	CNumber_2D(int nPriority = NUMBER_PRIORITY);
	~CNumber_2D()override;
	HRESULT Init()override;
	void Uninit()override;
	void Update()override;
	void Draw()override;

	//�����̃|���S����������
	static CNumber_2D* Create(D3DXVECTOR3 pos ,D3DXVECTOR2 size);

	void SetNumber(float fNumPos1,float fNumPos2,D3DXCOLOR col);

	void NumberVtx();

private:
	D3DXVECTOR2 m_mintex; //�e�N�X�`���̍ŏ����W
	D3DXVECTOR2 m_maxtex; //�e�N�X�`���̍ő���W
	D3DXCOLOR m_col; //�J���[
};

//=============================================
//�i���o�[�N���X3D
//=============================================
class CNumber_3D :public CBillboard
{
public:
	static const std::string TEXTURE_NAME;	//�e�N�X�`���̖��O
	static const int NUMBER_PRIORITY = 20;  //�`�揇
	CNumber_3D(int nPriority = NUMBER_PRIORITY);
	~CNumber_3D()override;
	HRESULT Init()override;
	void Uninit()override;
	void Update()override;
	void Draw()override;

	//�����̃|���S����������
	static CNumber_3D* Create(D3DXVECTOR3 pos, D3DXVECTOR3 size);

	void SetNumber(float fNumPos1, float fNumPos2, D3DXCOLOR col);

	void NumberVtx();

private:
	D3DXVECTOR2 m_mintex; //�e�N�X�`���̍ŏ����W
	D3DXVECTOR2 m_maxtex; //�e�N�X�`���̍ő���W
	D3DXCOLOR m_col; //�J���[
};

#endif // DEBUG