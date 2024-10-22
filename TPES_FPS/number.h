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

//=============================================
//�i���o�[�N���X
//=============================================
class CNumber:public CObject2D
{
public:
	static const std::string TEXTURE_NAME;	//�e�N�X�`���̖��O
	static const int NUMBER_PRIORITY = 85;  //�`�揇
	CNumber(int nPriority = NUMBER_PRIORITY);
	~CNumber()override;
	HRESULT Init()override;
	void Uninit()override;
	void Update()override;
	void Draw()override;

	//�����̃|���S����������
	static CNumber* Create(D3DXVECTOR3 pos ,D3DXVECTOR2 size);

	void SetNumber(float fNumPos1,float fNumPos2,D3DXCOLOR col);

	void NumberVtx();

private:
	D3DXVECTOR2 m_mintex; //�e�N�X�`���̍ŏ����W
	D3DXVECTOR2 m_maxtex; //�e�N�X�`���̍ő���W
	D3DXCOLOR m_col; //�J���[
};

#endif // DEBUG