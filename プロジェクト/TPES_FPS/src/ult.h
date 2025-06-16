//=============================================
//
//�A���e�B���b�g[ult.h]
//Author Matsuda Towa
//
//=============================================
#ifndef _ULT_
#define _ULT_
#include "character_behavior.h"
#include "active_player.h"
#include "ult_icon.h"
#include "ult_range.h"
#include "ult_camera_effect.h"

//=============================================
//�A���e�B���b�g�����X�g���e�W�[
//=============================================
class CUlt
{
public:
	/**
	 * @brief �R���X�g���N�^
	 */
	CUlt();
	/**
	 * @brief �f�X�g���N�^
	 */
	virtual ~CUlt();
	/**
	 * @brief ������
	 * @return ����������
	 */
	virtual HRESULT Init();
	/**
	 * @brief �I��
	 */
	virtual void Uninit();
	/**
	 * @brief �X�V
	 */
	virtual void Update();
	/**
	 * @brief ���s
	 * @param [in]�v���C���[�̃|�C���^
	 * @return �I�������
	 */
	virtual bool Action(CActivePlayer* player) = 0;

	/**
	 * @brief �N�[���^�C�����
	 * @param [in]�N�[���^�C��
	 */
	inline void SetCoolTime(int CoolTime)
	{
		m_CoolTime = CoolTime;
	}

	/**
	 * @brief �N�[���^�C���v���ϐ����
	 * @param [in]�N�[���^�C���v���ϐ�
	 */
	inline void SetCoolTimeCnt(int CoolTimeCnt)
	{
		m_CoolTimeCnt = CoolTimeCnt;
	}

	/**
	 * @brief �N�[���^�C���擾
	 * @return �N�[���^�C��
	 */
	inline int& GetCoolTime()
	{
		return m_CoolTime;
	}

	/**
	 * @brief �N�[���^�C���v���ϐ��擾
	 * @return �N�[���^�C���v���ϐ�
	 */
	inline int& GetCoolTimeCnt()
	{
		return m_CoolTimeCnt;
	}
protected:
	bool m_isFinish;
private:
	int m_CoolTime;
	int m_CoolTimeCnt;
};

//=============================================
//�~�f�B�A���L�����A���e�B���b�g�����X�g���e�W�[
//=============================================
class CMediumUlt:public CUlt
{
public:
	/**
	 * @brief �R���X�g���N�^
	 */
	CMediumUlt();
	/**
	 * @brief �f�X�g���N�^
	 */
	~CMediumUlt() override;
	/**
	 * @brief ������
	 * @return ����������
	 */
	HRESULT Init() override;
	/**
	 * @brief �I��
	 */
	void Uninit() override;
	/**
	 * @brief �X�V
	 */
	void Update() override;
	/**
	 * @brief ���s
	 * @param [in]�v���C���[�̃|�C���^
	 * @return �I��������
	 */
	bool Action(CActivePlayer* player) override;
private:
	static const int MEDIUM_ULT_COOL_TIME = 900;
	static constexpr float FLYING_HIGHT = 400.0f; //�ǂ��܂Ŕ�Ԃ�
	static const D3DXVECTOR3 SPEED;

	float m_move_y; //y���̈ړ���
	CUltRange* m_pUltRange; //�E���g�̔���
	CUltCameraEffect* m_pUltCameraEffect; //�E���g�̃J�����G�t�F�N�g
};

#endif // !_ULT_
