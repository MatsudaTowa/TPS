//=============================================
//
//�q�b�g���̃J�����G�t�F�N�g(�y����)�uhit_camera_effect_mild.h�v
// Author���c�i�v
//
//=============================================
#ifndef _HIT_CAMERA_EFFECT_MILD_H_ //���ꂪ��`����ĂȂ��Ƃ�
#define _HIT_CAMERA_EFFECT_MILD_H_
#include "main.h"
#include "hit_camera_effect.h"

//=============================================
//�q�b�g���̃J�����G�t�F�N�g�N���X
//=============================================
class CHitCameraEffectMild :public CHitCameraEffect
{
public:
	/**
	 * @brief �R���X�g���N�^
	 * @param [in]�v���C�I���e�B
	 */
	CHitCameraEffectMild(int nPriority = PRIORITY);
	/**
	 * @brief �f�X�g���N�^
	 */
	~CHitCameraEffectMild() override;
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

private:
	static const std::string TEXTURE_NAME;	//�y�x�e�N�X�`���̖��O

};
#endif // _HIT_CAMERA_EFFECT_MILD_H_