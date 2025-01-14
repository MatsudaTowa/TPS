//=============================================
// 
//�}�Y���t���b�V��[muzzle_flash.h]
//Auther Matsuda Towa
//
//=============================================
#ifndef _MUZZLE_FLASH_H_ //���ꂪ��`����ĂȂ��Ƃ�

#define _MUZZLE_FLASH_H_
#include "main.h"
#include "billboard.h"

class CMuzzleFlash : public CBillboard
{
public:
	static const std::string TEXTURE_NAME;	//�e�N�X�`���̖��O
	static const int PRIORITY = 10; //�`�揇
	static const int LIFE = 10; //���C�t
	static const D3DXVECTOR3 SIZE; //�T�C�Y

	CMuzzleFlash(int nPriority = PRIORITY);
	~CMuzzleFlash() override;
	HRESULT Init() override;
	void Uninit() override;
	void Update() override;
	void Draw() override;
	static CMuzzleFlash* Create(D3DXVECTOR3 pos);
private:
	int m_nLife;
};
#endif