//=============================================
// 
//�G���p�j����ۂɌ������|�C���g[move_point.h]
//Auther Matsuda Towa
//
//=============================================
#ifndef _MOVE_POINT_ //���ꂪ��`����ĂȂ��Ƃ�

#define _MOVE_POINT_
#include "main.h"
#include "billboard.h"

class CMovePoint : public CBillboard
{
public:
	static const int POINT_PRIORITY = 8; //�`�揇

	CMovePoint(int nPriority = POINT_PRIORITY);
	~CMovePoint() override;
	HRESULT Init() override;
	void Uninit() override;
	void Update() override;
	void Draw() override;
	static CMovePoint* Create(D3DXVECTOR3 pos);

	//�ԍ��ݒ�
	void SetIdx(int Idx)
	{
		m_Idx = Idx;
	}

	//�ԍ��擾
	int& GetIdx()
	{
		return m_Idx;
	}

private:
	int m_Idx; //���Ԗڂ̒n�_��
	static int m_NumPoint; //�����邩
};
#endif