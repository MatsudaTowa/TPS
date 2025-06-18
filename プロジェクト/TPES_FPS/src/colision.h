//=============================================
//
//�����蔻��Ǘ�[colision.h]
//Author Matsuda Towa
//
//=============================================
#ifndef _COLISION_H_ //���ꂪ��`����ĂȂ��Ƃ�

#define _COLISION_H_

//=============================================
//�����蔻��N���X
//=============================================
class CColision
{
public:
	enum COLISION
	{
		COLISON_NONE = 0, //���ɂ��������ĂȂ�
		COLISON_X, //X�����ɓ������Ă�
		COLISON_Z, //X�����ɓ������Ă�
		COLISON_UNDER_Y, //Y����(��)�ɓ������Ă�
		COLISON_TOP_Y, //X����(��)�������Ă�
		COLISION_CIRCLE,
	};

	struct CIRCLE
	{
		COLISION colision; //�ǂ�����������
		float CenterDistance; //���S�_�Ƃ̋���
	};
	/**
	 * @brief �R���X�g���N�^
	 */
	CColision();
	/**
	 * @brief �f�X�g���N�^
	 */
	~CColision();
	/**
	 * @brief �|���S�����m�̔���_X
	 * @param [in]�����鑤�̉ߋ��̈ʒu
	 * @param [in]�����鑤�̈ʒu
	 * @param [in]�����鑤�̃T�C�Y
	 * @param [in]�������鑤�̈ʒu
	 * @param [in]�������鑤�̃T�C�Y
	 * @return �ǂ̕����ɓ���������
	 */
	COLISION CheckColision_X(D3DXVECTOR3 Aoldpos, D3DXVECTOR3 Apos, D3DXVECTOR3 Asize, D3DXVECTOR3 Bpos, D3DXVECTOR3 Bsize);
	/**
	 * @brief ���f���ƃ|���S���̔���_X
	 * @param [in]�����鑤�̉ߋ��̈ʒu
	 * @param [in]�����鑤�̈ʒu
	 * @param [in]�����鑤�̍ŏ����W
	 * @param [in]�����鑤�̍ő���W
	 * @param [in]�������鑤�̈ʒu
	 * @param [in]�������鑤�̃T�C�Y
	 * @return �ǂ̕����ɓ���������
	 */
	COLISION CheckColision_X(D3DXVECTOR3 Aoldpos, D3DXVECTOR3 Apos, D3DXVECTOR3 AMinpos, D3DXVECTOR3 AMaxpos, D3DXVECTOR3 Bpos, D3DXVECTOR3 Bsize);
	/**
	 * @brief ���f�����m�����蔻��_X
	 * @param [in]�����鑤�̉ߋ��̈ʒu
	 * @param [in]�����鑤�̈ʒu
	 * @param [in]�����鑤�̍ŏ����W
	 * @param [in]�����鑤�̍ő���W
	 * @param [in]�������鑤�̈ʒu
	 * @param [in]�������鑤�̍ŏ����W
	 * @param [in]�������鑤�̍ő���W
	 * @return �ǂ̕����ɓ���������
	 */
	COLISION CheckColision_X(D3DXVECTOR3 Aoldpos, D3DXVECTOR3 Apos, D3DXVECTOR3 AMinpos, D3DXVECTOR3 AMaxPos,
		D3DXVECTOR3 Bpos, D3DXVECTOR3 BMinpos, D3DXVECTOR3 BMaxpos);

	/**
	 * @brief �|���S�����m�̔���_Y
	 * @param [in]�����鑤�̉ߋ��̈ʒu
	 * @param [in]�����鑤�̈ʒu
	 * @param [in]�����鑤�̃T�C�Y
	 * @param [in]�������鑤�̈ʒu
	 * @param [in]�������鑤�̃T�C�Y
	 * @return �ǂ̕����ɓ���������
	 */
	COLISION CheckColision_Y(D3DXVECTOR3 Aoldpos, D3DXVECTOR3 Apos, D3DXVECTOR3 Asize, D3DXVECTOR3 Bpos, D3DXVECTOR3 Bsize);
	/**
	 * @brief ���f���ƃ|���S���̔���_Y
	 * @param [in]�����鑤�̉ߋ��̈ʒu
	 * @param [in]�����鑤�̈ʒu
	 * @param [in]�����鑤�̍ŏ����W
	 * @param [in]�����鑤�̍ő���W
	 * @param [in]�������鑤�̈ʒu
	 * @param [in]�������鑤�̃T�C�Y
	 * @return �ǂ̕����ɓ���������
	 */
	COLISION CheckColision_Y(D3DXVECTOR3 Aoldpos, D3DXVECTOR3 Apos, D3DXVECTOR3 AMinpos, D3DXVECTOR3 AMaxpos, D3DXVECTOR3 Bpos, D3DXVECTOR3 Bsize);
	/**
	 * @brief ���f�����m�����蔻��_Y
	 * @param [in]�����鑤�̉ߋ��̈ʒu
	 * @param [in]�����鑤�̈ʒu
	 * @param [in]�����鑤�̍ŏ����W
	 * @param [in]�����鑤�̍ő���W
	 * @param [in]�������鑤�̈ʒu
	 * @param [in]�������鑤�̍ŏ����W
	 * @param [in]�������鑤�̍ő���W
	 * @return �ǂ̕����ɓ���������
	 */
	COLISION CheckColision_Y(D3DXVECTOR3 Aoldpos, D3DXVECTOR3 Apos, D3DXVECTOR3 AMinpos, D3DXVECTOR3 AMaxPos,
		D3DXVECTOR3 Bpos, D3DXVECTOR3 BMinpos, D3DXVECTOR3 BMaxpos);

	/**
	 * @brief �|���S�����m�̔���_Z
	 * @param [in]�����鑤�̉ߋ��̈ʒu
	 * @param [in]�����鑤�̈ʒu
	 * @param [in]�����鑤�̃T�C�Y
	 * @param [in]�������鑤�̈ʒu
	 * @param [in]�������鑤�̃T�C�Y
	 * @return �ǂ̕����ɓ���������
	 */
	COLISION CheckColision_Z(D3DXVECTOR3 Aoldpos, D3DXVECTOR3 Apos, D3DXVECTOR3 Asize, D3DXVECTOR3 Bpos, D3DXVECTOR3 Bsize);
	/**
	 * @brief ���f���ƃ|���S���̔���_Z
	 * @param [in]�����鑤�̉ߋ��̈ʒu
	 * @param [in]�����鑤�̈ʒu
	 * @param [in]�����鑤�̍ŏ����W
	 * @param [in]�����鑤�̍ő���W
	 * @param [in]�������鑤�̈ʒu
	 * @param [in]�������鑤�̃T�C�Y
	 * @return �ǂ̕����ɓ���������
	 */
	COLISION CheckColision_Z(D3DXVECTOR3 Aoldpos, D3DXVECTOR3 Apos, D3DXVECTOR3 AMinpos, D3DXVECTOR3 AMaxpos, D3DXVECTOR3 Bpos, D3DXVECTOR3 Bsize);
	/**
	 * @brief ���f�����m�����蔻��_Z
	 * @param [in]�����鑤�̉ߋ��̈ʒu
	 * @param [in]�����鑤�̈ʒu
	 * @param [in]�����鑤�̍ŏ����W
	 * @param [in]�����鑤�̍ő���W
	 * @param [in]�������鑤�̈ʒu
	 * @param [in]�������鑤�̍ŏ����W
	 * @param [in]�������鑤�̍ő���W
	 * @return �ǂ̕����ɓ���������
	 */
	COLISION CheckColision_Z(D3DXVECTOR3 Aoldpos, D3DXVECTOR3 Apos, D3DXVECTOR3 AMinpos, D3DXVECTOR3 AMaxPos,
		D3DXVECTOR3 Bpos, D3DXVECTOR3 BMinpos, D3DXVECTOR3 BMaxpos);

	/**
	 * @brief ���f�����m�̔���_��
	 * @param [in]�����鑤�̈ʒu
	 * @param [in]�����鑤�̍ŏ����W
	 * @param [in]�����鑤�̍ő���W
	 * @param [in]�������鑤�̈ʒu
	 * @param [in]�������鑤�̍ŏ����W
	 * @param [in]�������鑤�̍ő���W
	 * @return �ǂ̕����ɓ���������
	 */
	COLISION CheckColisionSphere(D3DXVECTOR3 Apos, D3DXVECTOR3 AMinpos, D3DXVECTOR3 AMaxpos, D3DXVECTOR3 Bpos, D3DXVECTOR3 BMinpos, D3DXVECTOR3 BMaxpos);

	/**
	 * @brief �~�̔���
	 * @param [in]�����鑤�̈ʒu
	 * @param [in]���a
	 * @param [in]�������鑤�̈ʒu
	 * @return �~�̃q�b�g���
	 */
	CIRCLE CheckColisionCircle(D3DXVECTOR3 Apos, float Radius, D3DXVECTOR3 Bpos);

	/**
	 * @brief �|���S���ƃ��f�������蔻��`�F�b�N�֐�_��
	 * @param [in]�����鑤�̈ʒu
	 * @param [in]�����鑤�̃T�C�Y
	 * @param [in]�������鑤�̈ʒu
	 * @param [in]�������鑤�̍ŏ����W
	 * @param [in]�������鑤�̍ő���W
	 * @return �ǂ̕����ɓ���������
	 */
	COLISION CheckPolygonModelColisionSphere(D3DXVECTOR3 Apos, D3DXVECTOR3 ASize, D3DXVECTOR3 Bpos, D3DXVECTOR3 BMinpos, D3DXVECTOR3 BMaxpos);
	/**
	 * @brief �|���S���ƃ��f���̓����蔻��_X
	 * @param [in]�����鑤�̈ʒu
	 * @param [in]�����鑤�̃T�C�Y
	 * @param [in]�������鑤�̈ʒu
	 * @param [in]�������鑤�̍ŏ����W
	 * @param [in]�������鑤�̍ő���W
	 * @return �ǂ̕����ɓ���������
	 */
	COLISION CheckPolygonModelColision_X(D3DXVECTOR3 Apos, D3DXVECTOR3 ASize, D3DXVECTOR3 Bpos, D3DXVECTOR3 BMinpos, D3DXVECTOR3 BMaxpos);
	/**
	 * @brief �|���S���ƃ��f���̓����蔻��_Z
	 * @param [in]�����鑤�̈ʒu
	 * @param [in]�����鑤�̃T�C�Y
	 * @param [in]�������鑤�̈ʒu
	 * @param [in]�������鑤�̍ŏ����W
	 * @param [in]�������鑤�̍ő���W
	 * @return �ǂ̕����ɓ���������
	 */
	COLISION CheckPolygonModelColision_Z(D3DXVECTOR3 Apos, D3DXVECTOR3 ASize, D3DXVECTOR3 Bpos, D3DXVECTOR3 BMinpos, D3DXVECTOR3 BMaxpos);
	/**
	 * @brief �|���S���ƃ��f���̓����蔻��_���܂��Ă邩
	 * @param [in]�����鑤�̈ʒu
	 * @param [in]�����鑤�̃T�C�Y
	 * @param [in]�������鑤�̈ʒu
	 * @param [in]�������鑤�̍ŏ����W
	 * @param [in]�������鑤�̍ő���W
	 * @return �ǂ̕����ɓ���������
	 */
	COLISION CheckPolygonFillColision(D3DXVECTOR3 Apos, D3DXVECTOR3 ASize, D3DXVECTOR3 Bpos, D3DXVECTOR3 BMinpos, D3DXVECTOR3 BMaxpos);

	/**
	 * @brief �|���S���ƃ��f���ђʔ���`�F�b�N�֐�_x
	 * @param [in]�����鑤�̉ߋ��̈ʒu
	 * @param [in]�����鑤�̈ʒu
	 * @param [in]�������鑤�̈ʒu
	 * @param [in]�������鑤�̍ŏ����W
	 * @param [in]�������鑤�̍ő���W
	 * @return �ǂ̕����ɓ���������
	 */
	COLISION CheckPolygonModelPenetration_X(D3DXVECTOR3 Aoldpos, D3DXVECTOR3 Apos, D3DXVECTOR3 Bpos, D3DXVECTOR3 BMinpos, D3DXVECTOR3 BMaxpos);

	/**
	 * @brief �|���S���ƃ��f���ђʔ���`�F�b�N�֐�_z
	 * @param [in]�����鑤�̉ߋ��̈ʒu
	 * @param [in]�����鑤�̈ʒu
	 * @param [in]�������鑤�̈ʒu
	 * @param [in]�������鑤�̍ŏ����W
	 * @param [in]�������鑤�̍ő���W
	 * @return �ǂ̕����ɓ���������
	 */
	COLISION CheckPolygonModelPenetration_Z(D3DXVECTOR3 Aoldpos, D3DXVECTOR3 Apos, D3DXVECTOR3 Bpos, D3DXVECTOR3 BMinpos, D3DXVECTOR3 BMaxpos);

	/**
	 * @brief 2D�|���S�������蔻��`�F�b�N�֐�
	 * @param [in]�����鑤�̌��݂̈ʒu
	 * @param [in]�����鑤�̃T�C�Y
	 * @param [in]�������鑤�̈ʒu
	 * @param [in]�������鑤�̃T�C�Y
	 * @return �������Ă��邩
	 */
	bool Check2DPolygonColision(D3DXVECTOR3 Apos, D3DXVECTOR2 ASize, D3DXVECTOR3 Bpos, D3DXVECTOR2 BSize);
};
#endif