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

	//���擾
	static int& GetNumPoint()
	{
		return m_NumPoint;
	};
private:
	static constexpr float POINT_SIZE = 10.0f; //�T�C�Y

	static int m_NumPoint; //�����邩
};
#endif