//=============================================
//
//�����蔻��Ǘ�[colision.cpp]
//Auther Matsuda Towa
//
//=============================================
#include "colision.h"
//=============================================
//�R���X�g���N�^
//=============================================
CColision::CColision()
{
}

//=============================================
//�f�X�g���N�^
//=============================================
CColision::~CColision()
{
}

//=============================================
//�����蔻��_X�`�F�b�N�֐�
//=============================================
CColision::COLISION CColision::CheckColision_X(D3DXVECTOR3 Aoldpos, D3DXVECTOR3 Apos, D3DXVECTOR3 Asize, D3DXVECTOR3 Bpos, D3DXVECTOR3 Bsize)
{
	if (Aoldpos.x + Asize.x <= Bpos.x - Bsize.x
		&& Apos.x + Asize.x > Bpos.x - Bsize.x)
	{
		if (Aoldpos.z - Asize.z < Bpos.z + Bsize.z
			&& Aoldpos.z + Asize.z > Bpos.z - Bsize.z
			&& Aoldpos.y - Asize.y < Bpos.y + Bsize.y
			&& Aoldpos.y + Asize.y > Bpos.y - Bsize.y)
		{//�����蔻��(X)
			return CColision::COLISION::COLISON_X;
		}
		else
		{
			return CColision::COLISION::COLISON_NONE;
		}
	}
	else if (Aoldpos.x - Asize.x >= Bpos.x + Bsize.x
		&& Apos.x - Asize.x < Bpos.x + Bsize.x)
	{
		if (Aoldpos.z - Asize.z < Bpos.z + Bsize.z
			&& Aoldpos.z + Asize.z > Bpos.z - Bsize.z
			&& Aoldpos.y - Asize.y < Bpos.y + Bsize.y
			&& Aoldpos.y + Asize.y > Bpos.y - Bsize.y)
		{//�����蔻��(X)
			return CColision::COLISION::COLISON_X;
		}
		else
		{
			return CColision::COLISION::COLISON_NONE;
		}
	}
	else
	{
		return CColision::COLISION::COLISON_NONE;
	}
}

//=============================================
//���f���ƃ|���S�������蔻��_X�`�F�b�N�֐�
//=============================================
CColision::COLISION CColision::CheckColision_X(D3DXVECTOR3 Aoldpos, D3DXVECTOR3 Apos, D3DXVECTOR3 AMinpos, D3DXVECTOR3 AMaxpos, D3DXVECTOR3 Bpos, D3DXVECTOR3 Bsize)
{
	//if (Aoldpos.x + AMaxpos.x <= Bpos.x
	//	&& Apos.x + AMaxpos.x > Bpos.x
	//	&& Apos.z + AMinpos.z > Bpos.z - Bsize.z
	//	&& Apos.z + AMaxpos.z < Bpos.z + Bsize.z)
	//{
	//	return CColision::COLISION::COLISON_X;
	//}
	//else if (Aoldpos.x + AMaxpos.x >= Bpos.x
	//	&& Apos.x + AMaxpos.x < Bpos.x
	//	&& Apos.z + AMinpos.z > Bpos.z - Bsize.z
	//	&& Apos.z + AMaxpos.z < Bpos.z + Bsize.z)
	//{
	//	return CColision::COLISION::COLISON_X;
	//}
	//else
	{
		return CColision::COLISION::COLISON_NONE;
	}
}

//=============================================
//���f�����m�����蔻��_X�`�F�b�N�֐�
//=============================================
CColision::COLISION CColision::CheckColision_X(D3DXVECTOR3 Aoldpos, D3DXVECTOR3 Apos, D3DXVECTOR3 AMinpos, D3DXVECTOR3 AMaxpos, D3DXVECTOR3 Bpos, D3DXVECTOR3 BMinpos, D3DXVECTOR3 BMaxpos)
{
	if (Aoldpos.x + AMaxpos.x <= Bpos.x + BMinpos.x
		&& Apos.x + AMaxpos.x > Bpos.x + BMinpos.x)
	{
		if (Aoldpos.z + AMinpos.z < Bpos.z + BMaxpos.z
			&& Aoldpos.z + AMaxpos.z > Bpos.z + BMinpos.z
			&& Aoldpos.y + AMinpos.y < Bpos.y + BMaxpos.y
			&& Aoldpos.y + AMaxpos.y > Bpos.y + BMinpos.y)
		{//�����蔻��(X)
			return CColision::COLISION::COLISON_X;
		}
	}
	else if (Aoldpos.x + AMinpos.x >= Bpos.x + BMaxpos.x
		&& Apos.x + AMinpos.x < Bpos.x + BMaxpos.x)
	{
		if (Aoldpos.z + AMinpos.z < Bpos.z + BMaxpos.z
			&& Aoldpos.z + AMaxpos.z > Bpos.z + BMinpos.z
			&& Aoldpos.y + AMinpos.y < Bpos.y + BMaxpos.y
			&& Aoldpos.y + AMaxpos.y > Bpos.y + BMinpos.y)
		{//�����蔻��(X)
			return CColision::COLISION::COLISON_X;
		}
		else
		{
			return CColision::COLISION::COLISON_NONE;
		}
	}
	else
	{
		return CColision::COLISION::COLISON_NONE;
	}
}

//=============================================
//�����蔻��_Y�`�F�b�N�֐�
//=============================================
CColision::COLISION CColision::CheckColision_Y(D3DXVECTOR3 Aoldpos, D3DXVECTOR3 Apos, D3DXVECTOR3 Asize, D3DXVECTOR3 Bpos, D3DXVECTOR3 Bsize)
{
	if (Aoldpos.y + Asize.y <= Bpos.y - Bsize.y
		&& Apos.y + Asize.y > Bpos.y - Bsize.y)
	{//�����蔻��(Y)��
		if (Aoldpos.x - Asize.x < Bpos.x + Bsize.x
			&& Aoldpos.x + Asize.x > Bpos.x - Bsize.x
			&& Aoldpos.z - Asize.z < Bpos.z + Bsize.z
			&& Aoldpos.z + Asize.z > Bpos.z - Bsize.z)
		{
			return CColision::COLISION::COLISON_UNDER_Y;
		}
		else
		{
			return CColision::COLISION::COLISON_NONE;
		}
	}
	else if (Aoldpos.y - Asize.y >= Bpos.y + Bsize.y
		&& Apos.y - Asize.y < Bpos.y + Bsize.y)
	{//�����蔻��(Y)��
		if (Aoldpos.x - Asize.x < Bpos.x + Bsize.x
			&& Aoldpos.x + Asize.x > Bpos.x - Bsize.x
			&& Aoldpos.z - Asize.z < Bpos.z + Bsize.z
			&& Aoldpos.z + Asize.z > Bpos.z - Bsize.z)
		{
			return CColision::COLISION::COLISON_TOP_Y;
		}
		else
		{
			return CColision::COLISION::COLISON_NONE;
		}
	}
	else
	{
		return CColision::COLISION::COLISON_NONE;
	}
}

//=============================================
//���f���ƃ|���S�������蔻��_Y�`�F�b�N�֐�
//=============================================
CColision::COLISION CColision::CheckColision_Y(D3DXVECTOR3 Aoldpos, D3DXVECTOR3 Apos, D3DXVECTOR3 AMinpos, D3DXVECTOR3 AMaxpos, D3DXVECTOR3 Bpos, D3DXVECTOR3 Bsize)
{
	if (Aoldpos.y + AMaxpos.y <= Bpos.y - Bsize.y
		&& Apos.y + AMaxpos.y > Bpos.y - Bsize.y)
	{//�����蔻��(Y)��
		if (Aoldpos.x + AMinpos.x < Bpos.x + Bsize.x
			&& Aoldpos.x + AMaxpos.x > Bpos.x - Bsize.x
			&& Aoldpos.z + AMinpos.z < Bpos.z + Bsize.z
			&& Aoldpos.z + AMaxpos.z > Bpos.z - Bsize.z)
		{
			CColision::COLISION::COLISON_UNDER_Y;
		}
		else
		{
			return CColision::COLISION::COLISON_NONE;
		}
	}
	else if (Aoldpos.y + AMinpos.y >= Bpos.y + Bsize.y
		&& Apos.y + AMinpos.y < Bpos.y + Bsize.y)
	{//�����蔻��(Y)��
		if (Aoldpos.x + AMinpos.x < Bpos.x + Bsize.x
			&& Aoldpos.x + AMaxpos.x > Bpos.x - Bsize.x
			&& Aoldpos.z + AMinpos.z < Bpos.z + Bsize.z
			&& Aoldpos.z + AMaxpos.z > Bpos.z - Bsize.z)
		{
			return CColision::COLISION::COLISON_TOP_Y;
		}
		else
		{
			return CColision::COLISION::COLISON_NONE;
		}
	}
	else
	{
		return CColision::COLISION::COLISON_NONE;
	}
}

//=============================================
//���f�����m�����蔻��_Y�`�F�b�N�֐�
//=============================================
CColision::COLISION CColision::CheckColision_Y(D3DXVECTOR3 Aoldpos, D3DXVECTOR3 Apos, D3DXVECTOR3 AMinpos, D3DXVECTOR3 AMaxpos, D3DXVECTOR3 Bpos, D3DXVECTOR3 BMinpos, D3DXVECTOR3 BMaxpos)
{
	if (Aoldpos.y + AMaxpos.y <= Bpos.y + BMinpos.y
		&& Apos.y + AMaxpos.y > Bpos.y + BMinpos.y)
	{//�����蔻��(Y)��
		if (Aoldpos.x + AMinpos.x < Bpos.x + BMaxpos.x
			&& Aoldpos.x + AMaxpos.x > Bpos.x + BMinpos.x
			&& Aoldpos.z + AMinpos.z < Bpos.z + BMaxpos.z
			&& Aoldpos.z + AMaxpos.z > Bpos.z + BMinpos.z)
		{
			return CColision::COLISION::COLISON_UNDER_Y;
		}
		else
		{
			return CColision::COLISION::COLISON_NONE;
		}
	}
	else if (Aoldpos.y + AMinpos.y >= Bpos.y + BMaxpos.y
		&& Apos.y + AMinpos.y < Bpos.y + BMaxpos.y)
	{//�����蔻��(Y)��
		if (Aoldpos.x + AMinpos.x < Bpos.x + BMaxpos.x
			&& Aoldpos.x + AMaxpos.x > Bpos.x + BMinpos.x
			&& Aoldpos.z + AMinpos.z < Bpos.z + BMaxpos.z
			&& Aoldpos.z + AMaxpos.z > Bpos.z + BMinpos.z)
		{
			return CColision::COLISION::COLISON_TOP_Y;
		}
		else
		{
			return CColision::COLISION::COLISON_NONE;
		}
	}
	else
	{
		return CColision::COLISION::COLISON_NONE;
	}
}


//=============================================
//�����蔻��_Z�`�F�b�N�֐�
//=============================================
CColision::COLISION CColision::CheckColision_Z(D3DXVECTOR3 Aoldpos, D3DXVECTOR3 Apos, D3DXVECTOR3 Asize, D3DXVECTOR3 Bpos, D3DXVECTOR3 Bsize)
{
	if (Aoldpos.z + Asize.z <= Bpos.z - Bsize.z
		&& Apos.z + Asize.z > Bpos.z - Bsize.z)
	{
		if (Aoldpos.x - Asize.x < Bpos.x + Bsize.x
			&& Aoldpos.x + Asize.x > Bpos.x - Bsize.x
			&& Aoldpos.y - Asize.y < Bpos.y + Bsize.y
			&& Aoldpos.y + Asize.y > Bpos.y - Bsize.y
			)
		{//�����蔻��(Z)
			return CColision::COLISION::COLISON_Z;
		}
		else
		{
			return CColision::COLISION::COLISON_NONE;
		}
	}
	else if (Aoldpos.z - Asize.z >= Bpos.z + Bsize.z
		&& Apos.z - Asize.z < Bpos.z + Bsize.z)
	{
		if (Aoldpos.x - Asize.x < Bpos.x + Bsize.x
			&& Aoldpos.x + Asize.x > Bpos.x - Bsize.x
			&& Aoldpos.y - Asize.y < Bpos.y + Bsize.y
			&& Aoldpos.y + Asize.y > Bpos.y - Bsize.y
			)
		{//�����蔻��(Z)
			return CColision::COLISION::COLISON_Z;
		}
		else
		{
			return CColision::COLISION::COLISON_NONE;
		}
	}
	else
	{
		return CColision::COLISION::COLISON_NONE;
	}
}

//=============================================
//���f���ƃ|���S�������蔻��_Z�`�F�b�N�֐�
//=============================================
CColision::COLISION CColision::CheckColision_Z(D3DXVECTOR3 Aoldpos, D3DXVECTOR3 Apos, D3DXVECTOR3 AMinpos, D3DXVECTOR3 AMaxpos, D3DXVECTOR3 Bpos, D3DXVECTOR3 Bsize)
{
	if (Aoldpos.z + AMaxpos.z <= Bpos.z
		&& Apos.z + AMaxpos.z > Bpos.z
		&&Apos.x + AMinpos.x > Bpos.x - Bsize.x
		&& Apos.x + AMaxpos.x < Bpos.x + Bsize.x)
	{
		return CColision::COLISION::COLISON_Z;
	}
	else if (Aoldpos.z + AMaxpos.z >= Bpos.z
		&& Apos.z + AMaxpos.z < Bpos.z
		&& Apos.x + AMinpos.x > Bpos.x - Bsize.x
		&& Apos.x + AMaxpos.x < Bpos.x + Bsize.x)
	{
		return CColision::COLISION::COLISON_Z;
	}
	else
	{
		return CColision::COLISION::COLISON_NONE;
	}
}

//=============================================
//���f�����m�����蔻��_Z�`�F�b�N�֐�
//=============================================
CColision::COLISION CColision::CheckColision_Z(D3DXVECTOR3 Aoldpos, D3DXVECTOR3 Apos, D3DXVECTOR3 AMinpos, D3DXVECTOR3 AMaxpos, D3DXVECTOR3 Bpos, D3DXVECTOR3 BMinpos, D3DXVECTOR3 BMaxpos)
{
	if (Aoldpos.z + AMaxpos.z <= Bpos.z + BMinpos.z
		&& Apos.z + AMaxpos.z > Bpos.z + BMinpos.z)
	{
		if (Aoldpos.x + AMinpos.x < Bpos.x + BMaxpos.x
			&& Aoldpos.x + AMaxpos.x > Bpos.x + BMinpos.x
			&& Aoldpos.y + AMinpos.y < Bpos.y + BMaxpos.y
			&& Aoldpos.y + AMaxpos.y > Bpos.y + BMinpos.y
			)
		{//�����蔻��(Z)
			return CColision::COLISION::COLISON_Z;

		}
		else
		{
			return CColision::COLISION::COLISON_NONE;
		}
	}
	else if (Aoldpos.z + AMinpos.z >= Bpos.z + BMaxpos.z
		&& Apos.z + AMinpos.z < Bpos.z + BMaxpos.z)
	{
		if (Aoldpos.x + AMinpos.x < Bpos.x + BMaxpos.x
			&& Aoldpos.x + AMaxpos.x > Bpos.x + BMinpos.x
			&& Aoldpos.y + AMinpos.y < Bpos.y + BMaxpos.y
			&& Aoldpos.y + AMaxpos.y > Bpos.y + BMinpos.y
			)
		{//�����蔻��(Z)
			return CColision::COLISION::COLISON_Z;

		}
		else
		{
			return CColision::COLISION::COLISON_NONE;
		}
	}
	else
	{
		return CColision::COLISION::COLISON_NONE;
	}
}

//=============================================
//���f�����̓����蔻��`�F�b�N�֐�
//=============================================
CColision::COLISION CColision::CheckColisionSphere(D3DXVECTOR3 Apos, D3DXVECTOR3 AMinpos, D3DXVECTOR3 AMaxpos, D3DXVECTOR3 Bpos, D3DXVECTOR3 BMinpos, D3DXVECTOR3 BMaxpos)
{
	//���������߂�
	D3DXVECTOR3 Length = Apos - Bpos;

	float CenterDistance = sqrtf((Length.x * Length.x) + (Length.y * Length.y) + (Length.z * Length.z));

	//�p�[�c�̒��S�����߂�
	D3DXVECTOR3 originA = (AMaxpos - AMinpos) * 0.5f;

	//�p�[�c�̒��S�����߂�
	D3DXVECTOR3 originB = (BMaxpos - BMinpos) * 0.5f;

	float Radius = (originB.x + originA.x) + (originB.y + originA.y) + (originB.z + originA.z) * 0.5f;

	if (CenterDistance <= Radius)
	{
		// ���K���i�P�ʃx�N�g�����j
		D3DXVECTOR3 normalizedVec = Length / CenterDistance;

		//��Βl�œx�̌����ɓ����������擾
		if (fabs(normalizedVec.x) > fabs(normalizedVec.y) && fabs(normalizedVec.x) > fabs(normalizedVec.z)) 
		{
			return CColision::COLISION::COLISON_X;
		}
		else if (fabs(normalizedVec.y) > fabs(normalizedVec.x) && fabs(normalizedVec.y) > fabs(normalizedVec.z))
		{
			return CColision::COLISION::COLISON_NONE;
		}
		else 
		{
			return CColision::COLISION::COLISON_Z;
		}
	}
	else
	{
		return CColision::COLISION::COLISON_NONE;
	}
}


//=============================================
//�~�̒��ɓ����Ă��邩
//=============================================
CColision::CIRCLE CColision::CheckColisionCircle(D3DXVECTOR3 Apos, float Radius, D3DXVECTOR3 Bpos)
{
	CIRCLE circle; //�~�̔���A�E�g�v�b�g���
	circle.colision = COLISON_NONE; //�����蔻���񏉊���
	circle.CenterDistance = 0.0f; //����������

	//���������߂�
	D3DXVECTOR3 Length = Bpos - Apos;

	circle.CenterDistance = sqrtf((Length.x * Length.x) + (Length.y * Length.y) + (Length.z * Length.z));

	if (circle.CenterDistance <= Radius*Radius)
	{
		circle.colision = COLISION_CIRCLE;
	}
	else
	{
		circle.colision = COLISON_NONE;
	}
	return circle;
}

//=============================================
//�|���S���ƃ��f�������蔻��`�F�b�N�֐�
//=============================================
CColision::COLISION CColision::CheckPolygonModelColisionSphere(D3DXVECTOR3 Apos, D3DXVECTOR3 ASize, D3DXVECTOR3 Bpos, D3DXVECTOR3 BMinpos, D3DXVECTOR3 BMaxpos)
{
	//���������߂�
	D3DXVECTOR3 Length = Apos - Bpos;

	float CenterDistance = sqrtf((Length.x*Length.x) + (Length.y * Length.y) + (Length.z * Length.z));

	//�p�[�c�̒��S�����߂�
	D3DXVECTOR3 origin = (BMaxpos - BMinpos) * 0.5f;

	float Radius = (ASize.x + origin.x) + (ASize.y + origin.y) + (ASize.z + origin.z) * 0.5f;

	if (CenterDistance <= Radius)
	{
		return COLISION_CIRCLE;
	}
	else
	{
		return COLISON_NONE;
	}
}

//=============================================
//�|���S���ƃ��f�������蔻��`�F�b�NX
//=============================================
CColision::COLISION CColision::CheckPolygonModelColision_X(D3DXVECTOR3 Apos, D3DXVECTOR3 ASize, D3DXVECTOR3 Bpos, D3DXVECTOR3 BMinpos, D3DXVECTOR3 BMaxpos)
{
	if (Apos.x + ASize.x > Bpos.x + BMinpos.x
		&& Apos.x - ASize.x < Bpos.x + BMaxpos.x)
	{
		if (Apos.z - ASize.z < Bpos.z + BMaxpos.z
			&& Apos.z + ASize.z > Bpos.z + BMinpos.z
			&& Apos.y - ASize.y < Bpos.y + BMaxpos.y
			&& Apos.y + ASize.y > Bpos.y + BMinpos.y
			)
		{
			return CColision::COLISION::COLISON_X;
		}
		else
		{
			return CColision::COLISION::COLISON_NONE;
		}
	}
	else
	{
		return CColision::COLISION::COLISON_NONE;
	}
}

//=============================================
//�|���S���ƃ��f�������蔻��`�F�b�N�֐�Z
//=============================================
CColision::COLISION CColision::CheckPolygonModelColision_Z(D3DXVECTOR3 Apos, D3DXVECTOR3 ASize, D3DXVECTOR3 Bpos, D3DXVECTOR3 BMinpos, D3DXVECTOR3 BMaxpos)
{
	if (Apos.z + ASize.z > Bpos.z + BMinpos.z
		&& Apos.z - ASize.z < Bpos.z + BMaxpos.z)
	{
		if (Apos.x - ASize.x < Bpos.x + BMaxpos.x
			&& Apos.x + ASize.x > Bpos.x + BMinpos.x
			&& Apos.y - ASize.y < Bpos.y + BMaxpos.y
			&& Apos.y + ASize.y > Bpos.y + BMinpos.y
			)
		{//�����蔻��(Z)
			return CColision::COLISION::COLISON_Z;
		}
		else
		{
			return CColision::COLISION::COLISON_NONE;
		}
	}
	else
	{
		return CColision::COLISION::COLISON_NONE;
	}
}

//=============================================
//�|���S���ƃ��f�������蔻��`�F�b�N�֐�Z
//=============================================
CColision::COLISION CColision::CheckPolygonFillColision(D3DXVECTOR3 Apos, D3DXVECTOR3 ASize, D3DXVECTOR3 Bpos, D3DXVECTOR3 BMinpos, D3DXVECTOR3 BMaxpos)
{
	if (Apos.y - ASize.y < Bpos.x + BMaxpos.x)
	{
		if (Apos.z - ASize.z< Bpos.z + BMaxpos.z
			&& Apos.z + ASize.z > Bpos.z + BMinpos.z
			&& Apos.y - ASize.y < Bpos.y + BMaxpos.y
			&& Apos.y + ASize.y > Bpos.y + BMinpos.y)
		{//�����蔻��(X)
			return CColision::COLISION::COLISON_TOP_Y;
		}
		else
		{
			return CColision::COLISION::COLISON_NONE;
		}
	}
}

//=============================================
//�|���S���ƃ��f���ђʔ���`�F�b�N�֐�X
//=============================================
CColision::COLISION CColision::CheckPolygonModelPenetration_X(D3DXVECTOR3 Aoldpos, D3DXVECTOR3 Apos, D3DXVECTOR3 Bpos, D3DXVECTOR3 BMinpos, D3DXVECTOR3 BMaxpos)
{
	if (Aoldpos.x < Bpos.x + BMinpos.x
		&& Apos.x > Bpos.x + BMaxpos.x)
	{
		if (Apos.z < Bpos.z + BMaxpos.z
			&& Apos.z > Bpos.z + BMinpos.z
			&& Apos.y < Bpos.y + BMaxpos.y
			&& Apos.y > Bpos.y + BMinpos.y
			)
		{//�����蔻��(Z)
			return CColision::COLISION::COLISON_X;
		}
		else
		{
			return CColision::COLISION::COLISON_NONE;
		}
	}
	else if (Aoldpos.x > Bpos.x + BMinpos.x
		&& Apos.x < Bpos.x + BMaxpos.x)
	{
		if (Apos.z < Bpos.z + BMaxpos.z
			&& Apos.z > Bpos.z + BMinpos.z
			&& Apos.y < Bpos.y + BMaxpos.y
			&& Apos.y > Bpos.y + BMinpos.y
			)
		{//�����蔻��(Z)
			return CColision::COLISION::COLISON_X;
		}
		else
		{
			return CColision::COLISION::COLISON_NONE;
		}
	}
	else
	{
		return CColision::COLISION::COLISON_NONE;
	}
}

//=============================================
//�|���S���ƃ��f���ђʔ���`�F�b�N�֐�Z
//=============================================
CColision::COLISION CColision::CheckPolygonModelPenetration_Z(D3DXVECTOR3 Aoldpos,D3DXVECTOR3 Apos, D3DXVECTOR3 Bpos, D3DXVECTOR3 BMinpos, D3DXVECTOR3 BMaxpos)
{
	if (Aoldpos.z  < Bpos.z + BMinpos.z
		&& Apos.z > Bpos.z + BMaxpos.z)
	{
		if (Apos.x < Bpos.x + BMaxpos.x
			&& Apos.x > Bpos.x + BMinpos.x
			&& Apos.y < Bpos.y + BMaxpos.y
			&& Apos.y > Bpos.y + BMinpos.y
			)
		{//�����蔻��(Z)
			return CColision::COLISION::COLISON_Z;
		}
		else
		{
			return CColision::COLISION::COLISON_NONE;
		}
	}
	else if (Aoldpos.z > Bpos.z + BMinpos.z
		&& Apos.z < Bpos.z + BMaxpos.z)
	{
		if (Apos.x < Bpos.x + BMaxpos.x
			&& Apos.x > Bpos.x + BMinpos.x
			&& Apos.y < Bpos.y + BMaxpos.y
			&& Apos.y > Bpos.y + BMinpos.y
			)
		{//�����蔻��(Z)
			return CColision::COLISION::COLISON_Z;
		}
		else
		{
			return CColision::COLISION::COLISON_NONE;
		}
	}
	else
	{
		return CColision::COLISION::COLISON_NONE;
	}
}

