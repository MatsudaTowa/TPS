//=============================================
//
//�V�ׂ�V�[��[active_scene.h]
//Author Matsuda Towa
//
//=============================================
#ifndef _ACTIVE_SCENE_H_ //���ꂪ��`����ĂȂ��Ƃ�

#define _ACTIVE_SCENE_H_
#include "scene.h"
#include "block.h"
#include "active_scene_state.h"

//=============================================
// �V�[���N���X
//=============================================
class CActiveScene : public CScene
{
public:
	//�ǂݍ��ނƂ��ɕK�v�ȃu���b�N�̍\����
	struct LOAD_BLOCK
	{
		D3DXVECTOR3 pos;
		D3DXVECTOR3 rot;
		CBlock::BLOCKTYPE type;
	};

	/**
	 * @brief �R���X�g���N�^
	 */
	CActiveScene();
	/**
	 * @brief �f�X�g���N�^
	 */
	~CActiveScene() override;

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
	 * @brief �`��
	 */
	void Draw() override;

	/**
	 * @brief �I�u�W�F�N�g�̍X�V���s��������
	 * @param [in]���������ǂ���
	 */
	void UpdateObjectDecision(bool isActive); 

	/**
	 * @brief ���͉\���擾
	 * @param ���͉\��
	 */
	inline bool GetPauseKey()
	{
		return m_nPauseCnt >= PAUSE_POSSIBLE_FLAME;
	}

	/**
	 * @brief �J�E���g���Z�b�g
	 */
	inline void ResetPauseCnt()
	{
		m_nPauseCnt = 0;
	}

	/**
	 * @brief �u���b�N�ǂݍ���
	 * @param [in]�t�@�C���l�[��
	 */
	void LoadBlock(const std::string& pFileName);

	/**
	 * @brief �X�e�[�g�ύX
	 * @param [in]���̃X�e�[�g
	 */
	void ChangeState(CActiveSceneState* state);

private:
	static const int PAUSE_POSSIBLE_FLAME = 1;	//�|�[�Y��L����������t���[��

	LOAD_BLOCK m_LoadBlock; //�ǂݍ��ނƂ��ɕK�v�ȃu���b�N�̏��

	int m_nPauseCnt;	//�|�[�Y��L�������鎞�ɗp����J�E���g

	CActiveSceneState* m_pState;
};
#endif