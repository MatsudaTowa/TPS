//=============================================
//
//�E���g���̃J�����G�t�F�N�g�uult_camera_effect.h�v
// Author���c�i�v
//
//=============================================
#ifndef _ULT_CAMERA_EFFECT_H_ //���ꂪ��`����ĂȂ��Ƃ�
#define _ULT_CAMERA_EFFECT_H_
#include "main.h"
#include "object2D.h"

//=============================================
//�E���g���̃J�����G�t�F�N�g�N���X
//=============================================
class CUltCameraEffect :public CObject2D
{
public:
	static const int PRIORITY = 25; //�`�揇

	/**
	 * @brief �R���X�g���N�^
	 * @param [in]�v���C�I���e�B
	 */
	CUltCameraEffect(int nPriority = PRIORITY);
	/**
	 * @brief �f�X�g���N�^
	 */
	~CUltCameraEffect() override;
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
	 * @return �E���g�̃J�����G�t�F�N�g�|�C���^
	 */
	static CUltCameraEffect* Create(D3DXVECTOR3 pos);

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
	static const std::string TEXTURE_NAME;	//�e�N�X�`���̖��O
	static const D3DXCOLOR COLOR;					//�����F
	static constexpr float SUB_ALPHA = 0.01f;		//�A���t�@�l���Z

	float m_alpha; //�A���t�@�l
};

#endif // _ULT_CAMERA_EFFECT_H_