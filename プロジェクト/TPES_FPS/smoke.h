//=============================================
//
//�X���[�N����[somoke.h]
//Auther Matsuda Towa
//
//=============================================
#include "main.h"
#include "billboard.h"

#ifndef _SMOKE_H_ //���ꂪ��`����ĂȂ��Ƃ�

#define _SMOKE_H_

class CSmoke : public CBillboard
{
public:
	static const std::string SMOKE_TEXTURE_NAME; //�e�N�X�`���̖��O
	static const int SMOKE_LIFE = 300; //�X���[�N�̎�������

	static const int SMOKE_PRIORITY = 10; //�`�揇

	enum SMOKE_TYPE
	{
		SMOKE_TYPE_TACTICAL	= 0,
		SMOKE_TYPE_BROKEN
	};

	CSmoke(int nPriority = SMOKE_PRIORITY);
	~CSmoke()override;
	HRESULT Init()override;
	void Uninit()override;
	void Update()override;
	void Draw()override;

	//�X���[�N�쐬
	static CSmoke* Create(D3DXVECTOR3 pos, SMOKE_TYPE type);

	inline void SetMove(D3DXVECTOR3 move)
	{
		m_move = move;
	}

	inline D3DXVECTOR3& GetMove()
	{
		return m_move;
	}

private:
	static constexpr float FADE_VALUE = 0.1f;  //�A���t�@�l������

	void Move();

	void FadeOut();

	int m_nLife;
	D3DXVECTOR3 m_move;
};

#endif