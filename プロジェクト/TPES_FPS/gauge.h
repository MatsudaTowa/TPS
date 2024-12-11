//=============================================
//
//�Q�[�W�Ǘ�[gauge.h]
//Auther Matsuda Towa
//
//=============================================
#ifndef _GAUGE_H_ //���ꂪ��`����ĂȂ��Ƃ�

#define _GAUGE_H_
#include "main.h"
#include "object2D.h"

//=============================================
//�Q�[�W�N���X
//=============================================
class CGauge : public CObject2D
{
public:
	static const std::string TEXTURE_NAME;	//�e�N�X�`���̖��O

	enum GAUGE_TYPE
	{
		GAUGE_TYPE_LIFE,
		GAUGE_TYPE_MAX,
	};
	static const int GAUGE_PRIORITY = 81;  //�`�揇
	static const float MAX_GAUGE_WIDE;  //�Q�[�W�̍ő�l
	CGauge(int nPriority = GAUGE_PRIORITY);
	~CGauge()override;
	HRESULT Init()override;
	void Uninit()override;
	void Update()override;
	void Draw()override;
	void SetGauge(D3DXVECTOR2 size);
	static CGauge* Create(D3DXVECTOR3 pos, D3DXVECTOR2 size, GAUGE_TYPE type, D3DXCOLOR col);
private:
	GAUGE_TYPE m_type;
};

//=============================================
//�̗̓Q�[�W�N���X
//=============================================
class CGauge_Life : public CGauge
{
public:
	CGauge_Life(int nPriority = GAUGE_PRIORITY);
	~CGauge_Life()override;
	HRESULT Init()override;
	void Uninit()override;
	void Update()override;
	void Draw()override;
};
#endif