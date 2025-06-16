//=============================================
//
//�e[bullet.h]
//Author Matsuda Towa
//
//=============================================
#include "main.h"
#include "attack_manager.h"

#ifndef _BULLET_H_ //���ꂪ��`����ĂȂ��Ƃ�

#define _BULLET_H_

//=============================================
//�e�N���X
//=============================================
class CBullet : public CAttack_Manager
{
public:
	static const int BULLET_PRIORITY = 10; //�`�揇

	//�G���������̔��f�����
	enum BULLET_ALLEGIANCE
	{
		BULLET_ALLEGIANCE_PLAYER = 0,
		BULLET_ALLEGIANCE_ENEMY,
		BULLET_ALLEGIANCE_MAX,
	};

	/**
	 * @brief �R���X�g���N�^
	 * @param [in]�v���C�I���e�B
	 */
	CBullet(int nPriority = BULLET_PRIORITY);
	/**
	 * @brief �f�X�g���N�^
	 */
	~CBullet()override;
	/**
	 * @brief ������
	 * @return ����������
	 */
	HRESULT Init()override;
	/**
	 * @brief �I��
	 */
	void Uninit()override;
	/**
	 * @brief �X�V
	 */
	void Update()override;
	/**
	 * @brief �`��
	 */
	void Draw()override;

	/**
	 * @brief �e�̐���
	 * @param [in]�ʒu
	 * @param [in]�ړ���
	 * @param [in]����
	 * @param [in]�T�C�Y
	 * @param [in]����
	 * @param [in]�_���[�W��
	 * @param [in]�G�̂������̂�
	 * @return �e�̃|�C���^
	 */
	static CBullet* Create(D3DXVECTOR3 pos,D3DXVECTOR3 move,D3DXVECTOR3 rot,
	D3DXVECTOR3 size,int nLife,int nDamage, BULLET_ALLEGIANCE Allegiance);

	/**
	 * @brief �ړ��ʐݒ�
	 * @param [in]�ړ���
	 */
	inline void SetMove(D3DXVECTOR3 move)
	{
		m_move = move;
	}
	/**
	 * @brief �ǂ����̒e���ݒ�
	 * @param [in]�ǂ����̒e��
	 */
	inline void SetBulletAllegiance(BULLET_ALLEGIANCE Allegiance)
	{
		m_Allegiance = Allegiance;
	}
	/**
	 * @brief �ړ��ʎ擾
	 * @return �ړ���
	 */
	inline D3DXVECTOR3 GetMove()
	{
		return m_move;
	}
	/**
	 * @brief �ǂ����̒e���擾
	 * @return �ǂ����̒e��
	 */
	inline BULLET_ALLEGIANCE GetBulletAllegiance()
	{
		return m_Allegiance;
	}
private:
	static const std::string BULLET_TEXTURE_NAME;	//�e�N�X�`���̖��O
	/**
	 * @brief �g�p����Ă鎞�̏���
	 */
	void OnActive();
	/**
	 * @brief �q�b�g�}�[�J�[�ݒ�
	 */
	void SetHitMaker();
	/**
	 * @brief �u���b�N�ɓ���������
	 * @return ����������
	 */
	bool PenetrationBlock();
	BULLET_ALLEGIANCE m_Allegiance; //�G���������𔻒f����񋓌^�ϐ�
	D3DXVECTOR3 m_move; //�ړ���
};

#endif