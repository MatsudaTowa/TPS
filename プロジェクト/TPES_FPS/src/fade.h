//=============================================
//
//�t�F�[�h����[fade.h]
//Author Matsuda Towa
//
//=============================================
#ifndef _FADE_H_ //���ꂪ��`����ĂȂ��Ƃ�

#define _FADE_H_
#include "main.h"
#include "scene.h"
#include "object2D.h"

//=============================================
//fade�N���X
//=============================================
class CFade : public CObject2D
{
public:
	//�t�F�[�h�̏��
	enum FADE
	{
		FADE_NONE = 0, //�������Ă��Ȃ����
		FADE_IN, //�t�F�[�h�C��
		FADE_OUT, //�t�F�[�h�A�E�g
		FADE_MAX,
	};

	static const int FADE_PRIORITY = 28;  //�`�揇

	/**
	 * @brief �R���X�g���N�^
	 * @param [in]�v���C�I���e�B
	 */
	CFade(int nPriority = FADE_PRIORITY);
	/**
	 * @brief �f�X�g���N�^
	 */
	~CFade()override;
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
	 * @brief �t�F�[�h�ݒ�
	 * @param [in]���̃V�[��
	 */
	void SetFade(CScene::MODE modeNext);

	/**
	 * @brief �t�F�[�h�̐F�擾
	 * @return �t�F�[�h�̐F
	 */
	float FadeColor(void);
	/**
	 * @brief ����
	 * @param [in]�ʒu
	 * @return �t�F�[�h�̃|�C���^
	 */
	static CFade* Create(D3DXVECTOR3 pos);
private:
	static constexpr float FADE_VALUE = 0.05f;  //�A���t�@�l������
	FADE m_fade;
	CScene::MODE m_fademode;
	float m_colorFade;
};
#endif