//=============================================
//
//�q�b�g���̃J�����G�t�F�N�g�uhit_camera_effect.h�v
// Author���c�i�v
//
//=============================================
#ifndef _HIT_CAMERA_EFFECT_H_ //���ꂪ��`����ĂȂ��Ƃ�
#define _HIT_CAMERA_EFFECT_H_
#include "main.h"
#include "object2D.h"

//=============================================
//�q�b�g���̃J�����G�t�F�N�g�N���X
//=============================================
class CHitCameraEffect:public CObject2D
{
public:
	static const int PRIORITY = 27; //�`�揇

	enum HIT_EFFECT_STAGE
	{
		MILD, //�y�x
		MODERATE, //��
		SEVERE, //�d��
	};

	/**
	 * @brief �R���X�g���N�^
	 * @param [in]�v���C�I���e�B
	 */
	CHitCameraEffect(int nPriority = PRIORITY);
	/**
	 * @brief �f�X�g���N�^
	 */
	~CHitCameraEffect() override;
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
	 * @brief ����
	 * @param [in]�ʒu
	 * @param [in]�_���[�W�̗�
	 * @return �J�����̃q�b�g�G�t�F�N�g
	 */
	static CHitCameraEffect* Create(D3DXVECTOR3 pos, HIT_EFFECT_STAGE stage);

	/**
	 * @brief �A���t�@�l����
	 */
	void SubAlpha();

	/**
	 * @brief �A���t�@�l�擾
	 * @return �A���t�@�l
	 */
	inline float& GetAlpha()
	{
		return m_alpha;
	}
private:
	static const std::string TEXTURE_NAME_SEVERE;	//�d�ǃe�N�X�`���̖��O
	static const D3DXCOLOR COLOR;					//�����F
	static constexpr float SUB_ALPHA = 0.01f;		//�A���t�@�l���Z

	float m_alpha; //�A���t�@�l
};

#endif // _HIT_CAMERA_EFFECT_H_