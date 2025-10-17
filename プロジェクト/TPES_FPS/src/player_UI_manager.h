//=============================================
//
//�v���C���[UI�}�l�[�W���[[player_UI_maneger.h]
//Auther MatsudaTowa
//
//=============================================

#ifndef _PLAYER_UI_MANAGER_H_	//���ꂪ��`����ĂȂ��Ƃ�
#define _PLAYER_UI_MANAGER_H_	//��d�}�N���h�~

//�w�b�_�[�̃C���N���[�h
#include "active_player.h"
#include"ammo_UI.h"
#include"life_UI.h"
#include "ult_UI.h"
#include "gun_icon.h"
#include "gauge.h"
#include "smoke_UI.h"
#include "blink_UI.h"
#include "reload_UI.h"

/** @brief My ���O��� */
/** @brief �Q�[���}�l�[�W���[�N���X */
class CPlayerUIManager
{
public:
	/**
	* @brief �R���X�g���N�^
	*/
	CPlayerUIManager();

	/**
	* @brief �f�X�g���N�^
	*/
	~CPlayerUIManager();

	/**
	* @brief �I��
	*/
	void Uninit();

	/**
	* @brief �������g�̃C���X�^���X�𐶐����擾
	*/
	static CPlayerUIManager* GetInstance()
	{
		//�ÓI�C���X�^���X
		static CPlayerUIManager instance;
		return &instance;
	}

	/**
	* @brief UI�𐶐�
	* @param [in]�v���C���[
	*/
	void CreateUI(CActivePlayer* player);

	/**
	* @brief UI��ݒ�
	* @param [in]�v���C���[
	*/
	void SetUI(CActivePlayer* player);

	/**
	 * @brief �e��UI�擾
	 * @return �e��UI
	 */
	CAmmo_UI* GetAmmoUI()
	{
		return m_pAmmoUI;
	}

	/**
	 * @brief ���C�tUI�擾
	 * @return ���C�tUI
	 */
	CLife_UI* GetLifeUI()
	{
		return m_pLifeUI;
	}

	/**
	 * @brief �E���gUI�擾
	 * @return �E���g
	 */
	CUlt_UI* GetUltUI()
	{
		return m_pUltUI;
	}

	/**
	 * @brief �X���[�NUI�擾
	 * @return �X���[�NUI
	 */
	CSmoke_UI* GetSmokeUI()
	{
		return m_pSmokeUI;
	}

	/**
	 * @brief �u�����NUI�擾
	 * @return �u�����NUI
	 */
	CBlink_UI* GetBlinkUI()
	{
		return m_pBlinkUI;
	}

	/**
	 * @brief �����[�hUI�擾
	 * @return �����[�h
	 */
	CReload_UI* GetReloadUI()
	{
		return m_pReloadUI;
	}

	/**
	 * @brief �e�̃A�C�R���擾
	 * @return 
	 */
	CGunIcon* GetGunIcon()
	{
		return m_pGunIcon;
	}

	/**
	 * @brief �e��UI�擾
	 * @param [in]�e��UI
	 */
	void SetAmmoUI(CAmmo_UI* pAmmoUI)
	{
		m_pAmmoUI = pAmmoUI;
	}

	/**
	 * @brief ���C�tUI�擾
	 * @param [in]���C�tUI
	 */
	void SetLifeUI(CLife_UI* pLifeUI)
	{
		m_pLifeUI = pLifeUI;
	}

	/**
	 * @brief �E���gUI�擾
	 * @param [in]�E���g
	 */
	void SetUltUI(CUlt_UI* pUltUI)
	{
		m_pUltUI = pUltUI;
	}

	/**
	 * @brief �X���[�NUI�擾
	 * @param [in]�X���[�NUI
	 */
	void SetSmokeUI(CSmoke_UI* pSmokeUI)
	{
		m_pSmokeUI = pSmokeUI;
	}

	/**
	 * @brief �u�����NUI�擾
	 * @param [in]�u�����NUI
	 */
	void SetBlinkUI(CBlink_UI* pBlinkUI)
	{
		m_pBlinkUI = pBlinkUI;
	}

	/**
	 * @brief �����[�hUI�擾
	 * @param [in]�����[�h
	 */
	void SetReloadUI(CReload_UI* pReloadUI)
	{
		m_pReloadUI = pReloadUI;
	}

	/**
	 * @brief �e�̃A�C�R���擾
	 * @param [in]�A�C�R��
	 */
	void SetGunIcon(CGunIcon* pGunIcon)
	{
		m_pGunIcon = pGunIcon;
	}
private:
	static const D3DXVECTOR3 GUN_UI_POS;//�e��UI�̈ʒu
	static const D3DXVECTOR2 GUN_UI_SIZE;//�e��UI�̃T�C�Y

	CAmmo_UI* m_pAmmoUI;	//�c�eUI

	CLife_UI* m_pLifeUI;	//�̗�UI

	CUlt_UI* m_pUltUI;		//�E���gUI

	CSmoke_UI* m_pSmokeUI;	//�X���[�NUI

	CBlink_UI* m_pBlinkUI;	//�u�����NUI

	CReload_UI* m_pReloadUI;	//�����[�hUI

	CGunIcon* m_pGunIcon;	//�e�̃A�C�R��
};

#endif