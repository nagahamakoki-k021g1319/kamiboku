#include "Matrix4.h"
#include "Affin.h"


Matrix4::Matrix4() {

	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			m[i][j] = 0.0f;
		}
	}

}

Matrix4::Matrix4(float num) {

	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			m[i][j] = num;
		}
	}

}

// �������w�肵�Ă̐���
Matrix4::Matrix4(
	float m00, float m01, float m02, float m03,
	float m10, float m11, float m12, float m13,
	float m20, float m21, float m22, float m23,
	float m30, float m31, float m32, float m33) {
	m[0][0] = m00; m[0][1] = m01; m[0][2] = m02; m[0][3] = m03;
	m[1][0] = m10; m[1][1] = m11; m[1][2] = m12; m[1][3] = m13;
	m[2][0] = m20; m[2][1] = m21; m[2][2] = m22; m[2][3] = m23;
	m[3][0] = m30; m[3][1] = m31; m[3][2] = m32; m[3][3] = m33;
}


Vector3 Matrix4::transform(const Vector3& v, const Matrix4& m) {

	float w = v.x * m.m[0][3] + v.y * m.m[1][3] + v.z * m.m[2][3] + m.m[3][3];

	Vector3 result{
		(v.x * m.m[0][0] + v.y * m.m[1][0] + v.z * m.m[2][0] + m.m[3][0]) / w,
		(v.x * m.m[0][1] + v.y * m.m[1][1] + v.z * m.m[2][1] + m.m[3][1]) / w,
		(v.x * m.m[0][2] + v.y * m.m[1][2] + v.z * m.m[2][2] + m.m[3][2]) / w,
	};

	return result;
}

Matrix4 Matrix4::MakeInverse(const Matrix4* mat)
{
	assert(mat);

	//�|���o���@���s���s��
	float sweep[4][8]{};
	//�萔�{�p
	float constTimes = 0.0f;
	//���e����덷
	float MAX_ERR = 1e-10f;
	//�߂�l�p
	Matrix4 retMat;

	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			//weep�̍����ɋt�s������߂�s����Z�b�g
			sweep[i][j] = mat->m[i][j];

			//sweep�̉E���ɒP�ʍs����Z�b�g
			sweep[i][4 + j] = MakeIdentity().m[i][j];
		}
	}

	//�S�Ă̗�̑Ίp�����ɑ΂���J��Ԃ�
	for (int i = 0; i < 4; i++)
	{
		//�ő�̐�Βl�𒍖ڑΊp�����̐�Βl�Ɖ���
		float max = fabs(sweep[i][i]);
		int maxIndex = i;

		//i��ڂ��ő�̐�Βl�ƂȂ�s��T��
		for (int j = i + 1; j < 4; j++)
		{
			if (fabs(sweep[j][i]) > max)
			{
				max = fabs(sweep[j][i]);
				maxIndex = j;
			}
		}

		if (fabs(sweep[maxIndex][i]) <= MAX_ERR)
		{
			//�t�s��͋��߂��Ȃ�
			return MakeIdentity();
		}

		//����(1):i�s�ڂ�maxIndex�s�ڂ����ւ���
		if (i != maxIndex)
		{
			for (int j = 0; j < 8; j++)
			{
				float tmp = sweep[maxIndex][j];
				sweep[maxIndex][j] = sweep[i][j];
				sweep[i][j] = tmp;
			}
		}

		//sweep[i][i]�Ɋ|�����1�ɂȂ�l�����߂�
		constTimes = 1 / sweep[i][i];

		//����(2):p�s�ڂ�a�{����
		for (int j = 0; j < 8; j++)
		{
			//����ɂ��sweep[i][i]��1�ɂȂ�
			sweep[i][j] *= constTimes;
		}

		//����(3)�ɂ��i�s�ڈȊO�̍s��i��ڂ�0�ɂ���
		for (int j = 0; j < 4; j++)
		{
			if (j == i)
			{
				//i�s�ڂ͂��̂܂�
				continue;
			}

			//i�s�ڂɊ|����l�����߂�
			constTimes = -sweep[j][i];

			for (int k = 0; k < 8; k++)
			{
				//j�s�ڂ�i�s�ڂ�a�{�����s�𑫂�
				//����ɂ��sweep[j][i]��0�ɂȂ�
				sweep[j][k] += sweep[i][k] * constTimes;
			}
		}
	}

	//sweep�̉E������mat�̋t�s��
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			retMat.m[i][j] = sweep[i][4 + j];
		}
	}

	return retMat;
}

void Matrix4::MakeOrthogonalL(float left, float right, float bottom, float top, float near_, float far_, Matrix4& matrix)
{

	float width = 1.0f / (right - left);
	float height = 1.0f / (top - bottom);
	float range = 1.0f / (far_ - near_);

	matrix.m[0][0] = width * 2;

	matrix.m[1][1] = height * 2;

	matrix.m[2][2] = range;

	matrix.m[3][0] = -(left + right) * width;
	matrix.m[3][1] = -(top + bottom) * height;
	matrix.m[3][2] = range * -near_;
	matrix.m[3][3] = 1.0f;

	matrix.m[0][1] = matrix.m[0][2] = matrix.m[0][3] =
		matrix.m[1][0] = matrix.m[1][2] = matrix.m[1][3] =
		matrix.m[2][0] = matrix.m[2][1] = matrix.m[2][3] = 0.0f;
}

void Matrix4::MakePerspectiveL(float fovAngleY, float aspect, float near_, float far_, Matrix4& matrix)
{

	float sinFov = 0.0f;
	float cosFov = 0.0f;
	Affin::SinCos(sinFov, cosFov, 0.5f * fovAngleY);

	float range = far_ / (far_ - near_);
	float height = cosFov / sinFov;

	matrix.m[0][0] = height / aspect;

	matrix.m[1][1] = cosFov / sinFov;

	matrix.m[2][2] = range;
	matrix.m[2][3] = 1.0f;

	matrix.m[3][2] = -range * near_;

	matrix.m[0][1] = matrix.m[0][2] = matrix.m[0][3] =
		matrix.m[1][0] = matrix.m[1][2] = matrix.m[1][3] =
		matrix.m[2][0] = matrix.m[2][1] =
		matrix.m[3][0] = matrix.m[3][1] = matrix.m[3][3] = 0.0f;
}

void Matrix4::MakeLookL(const Vector3& eye, const Vector3& target, const Vector3& up, Matrix4& mat)
{
	Vector3 zVec = target - eye;
	zVec.nomalize();

	Vector3 xVec = up.cross(zVec);
	xVec.nomalize();

	Vector3 yVec = zVec.cross(xVec);
	yVec.nomalize();

	mat.m[0][0] = xVec.x;
	mat.m[0][1] = xVec.y;
	mat.m[0][2] = xVec.z;
	mat.m[1][0] = yVec.x;
	mat.m[1][1] = yVec.y;
	mat.m[1][2] = yVec.z;
	mat.m[2][0] = zVec.x;
	mat.m[2][1] = zVec.y;
	mat.m[2][2] = zVec.z;
	mat.m[3][0] = eye.x;
	mat.m[3][1] = eye.y;
	mat.m[3][2] = eye.z;
}


//	--		 --			--		 --
//	| a b c d |			| A B C D |
//	| e f g h |	   X	| E F G H |
//	| i j k l |			| I J K L |
//	| m n o p |			| M N O P |
//	--		 --			--		 --



Matrix4& operator*=(Matrix4& m1, const Matrix4& m2) {

	Matrix4 result{ 0 };

	for (int i = 0; i < 4; i++) {
		for (int k = 0; k < 4; k++) {
			result.m[i][k] =
				m1.m[i][0] * m2.m[0][k] +
				m1.m[i][1] * m2.m[1][k] +
				m1.m[i][2] * m2.m[2][k] +
				m1.m[i][3] * m2.m[3][k];
		}
	}
	m1 = result;
	return m1;
}



// 2�����Z�q�I�[�o�[���[�h ( �s��ƍs��̐� )
const Matrix4 operator*(const Matrix4& m1, const Matrix4& m2) {
	Matrix4 result = m1;

	return result *= m2;
}
//2�����Z�q�I�[�o�[���[�h ( �x�N�g���ƍs��̐� )
const Vector3 operator*(const Vector3& v, const Matrix4& m2) {
	Matrix4 mat = Affin::matUnit();
	Vector3 result = mat.transform(v, m2);
	return result;
}
