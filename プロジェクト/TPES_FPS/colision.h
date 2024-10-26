//=============================================
//
//�����蔻��Ǘ�[colision.h]
//Auther Matsuda Towa
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
	typedef enum
	{
		COLISON_NONE = 0, //���ɂ��������ĂȂ�
		COLISON_X, //X�����ɓ������Ă�
		COLISON_Z, //X�����ɓ������Ă�
		COLISON_UNDER_Y, //Y����(��)�ɓ������Ă�
		COLISON_TOP_Y, //X����(��)�������Ă�
	}COLISION;
	CColision();
	~CColision();
	static COLISION CheckColision_X(D3DXVECTOR3 Aoldpos, D3DXVECTOR3 Apos, D3DXVECTOR3 Asize, D3DXVECTOR3 Bpos, D3DXVECTOR3 Bsize); //�|���S�����m�����蔻��`�F�b�N�֐�
	static COLISION CheckColision_X(D3DXVECTOR3 Aoldpos, D3DXVECTOR3 Apos, D3DXVECTOR3 AMinpos, D3DXVECTOR3 AMaxpos, D3DXVECTOR3 Bpos, D3DXVECTOR3 Bsize); //���f���ƃ|���S�������蔻��`�F�b�N�֐�
	static COLISION CheckColision_X(D3DXVECTOR3 Aoldpos, D3DXVECTOR3 Apos, D3DXVECTOR3 AMinpos,D3DXVECTOR3 AMaxPos,
		D3DXVECTOR3 Bpos, D3DXVECTOR3 BMinpos, D3DXVECTOR3 BMaxpos); //���f�����m�����蔻��`�F�b�N�֐�

	static COLISION CheckColision_Y(D3DXVECTOR3 Aoldpos, D3DXVECTOR3 Apos, D3DXVECTOR3 Asize, D3DXVECTOR3 Bpos, D3DXVECTOR3 Bsize); //�|���S�����m�����蔻��`�F�b�N�֐�
	static COLISION CheckColision_Y(D3DXVECTOR3 Aoldpos, D3DXVECTOR3 Apos, D3DXVECTOR3 AMinpos, D3DXVECTOR3 AMaxpos, D3DXVECTOR3 Bpos, D3DXVECTOR3 Bsize); //���f���ƃ|���S�������蔻��`�F�b�N�֐�
	static COLISION CheckColision_Y(D3DXVECTOR3 Aoldpos, D3DXVECTOR3 Apos, D3DXVECTOR3 AMinpos, D3DXVECTOR3 AMaxPos,
		D3DXVECTOR3 Bpos, D3DXVECTOR3 BMinpos, D3DXVECTOR3 BMaxpos); //���f�����m�����蔻��`�F�b�N�֐�

	static COLISION CheckColision_Z(D3DXVECTOR3 Aoldpos, D3DXVECTOR3 Apos, D3DXVECTOR3 Asize, D3DXVECTOR3 Bpos, D3DXVECTOR3 Bsize); //�|���S�����m�����蔻��`�F�b�N�֐�
	static COLISION CheckColision_Z(D3DXVECTOR3 Aoldpos, D3DXVECTOR3 Apos, D3DXVECTOR3 AMinpos, D3DXVECTOR3 AMaxpos, D3DXVECTOR3 Bpos, D3DXVECTOR3 Bsize); //���f���ƃ|���S�������蔻��`�F�b�N�֐�
	static COLISION CheckColision_Z(D3DXVECTOR3 Aoldpos, D3DXVECTOR3 Apos, D3DXVECTOR3 AMinpos, D3DXVECTOR3 AMaxPos,
		D3DXVECTOR3 Bpos, D3DXVECTOR3 BMinpos, D3DXVECTOR3 BMaxpos); //���f�����m�����蔻��`�F�b�N�֐�

	static COLISION CheckItemColision(D3DXVECTOR3 Apos, D3DXVECTOR3 ASize, D3DXVECTOR3 Bpos, D3DXVECTOR3 BMinpos, D3DXVECTOR3 BMaxpos); //�A�C�e���ƃ��f�������蔻��`�F�b�N�֐�
	static COLISION CheckItemFillColision(D3DXVECTOR3 Apos, D3DXVECTOR3 ASize, D3DXVECTOR3 Bpos, D3DXVECTOR3 BMinpos, D3DXVECTOR3 BMaxpos); //�A�C�e���ƃ��f�������蔻��(���܂��Ă邩)�`�F�b�N�֐�
	
	static COLISION CheckFlow_RangeColision(D3DXVECTOR3 Apos, D3DXVECTOR3 AMinpos, D3DXVECTOR3 AMaxpos, D3DXVECTOR3 Bpos, D3DXVECTOR3 BMinpos, D3DXVECTOR3 BMaxpos); //�A�C�e���ƃ��f�������蔻��`�F�b�N�֐�

};
#endif