//=============================================
//
//�����[�h�󋵕\���ureload_UI.h�v
// Author���c�i�v
//
//=============================================
#ifndef _RELOAD_UI_H_ //���ꂪ��`����ĂȂ��Ƃ�
#define _RELOAD_UI_H_
#include "main.h"
#include "active_player.h"
#include "reload_Txt.h"

//=============================================
//�����[�hUI�N���X
//=============================================
class CReload_UI
{
public:
	/**
	 * @brief �R���X�g���N�^
	 */
	CReload_UI();
	/**
	 * @brief �f�X�g���N�^
	 */
	~CReload_UI();
	/**
	 * @brief ������
	 * @return ����������
	 */
	HRESULT Init();
	/**
	 * @brief �I��
	 */
	void Uninit();
	/**
	 * @brief �X�V
	 */
	void Update();
private:
	static const D3DXVECTOR3 TXT_POS; //�����[�h�e�L�X�g�̈ʒu
	static const D3DXVECTOR2 TXT_SIZE; //�����[�h�e�L�X�g�̃T�C�Y

	CReloatTxt* m_pTxt;
};

#endif