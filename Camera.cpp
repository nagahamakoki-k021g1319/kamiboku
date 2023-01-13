#include "Camera.h"
#include"WinApp.h"

void Camera::Initialize(UpdateProjMatrixFunc matFunc)
{
	//�A�X�y�N�g����v�Z����
	aspect =
		static_cast<float>(WinApp::GetInstance()->GetWindowWidth()) /
		static_cast<float>(WinApp::GetInstance()->GetWindowHeight());

	matrixFunc = matFunc;

	if (matFunc == UpdateProjMatrixFunc_Ortho)//���s���e
	{
		if (far_ == 0.0f)
		{
			far_ = 1.0f;
		}
		right = static_cast<float>(WindowsApp::GetInstance()->GetWindowSize().width);
		bottom = static_cast<float>(WindowsApp::GetInstance()->GetWindowSize().height);

		//���s���e�̌v�Z
		MakeOrthogonalL(left, right, bottom, top, near_, far_, projectionMatrix);

	}
	else//�������e
	{
		if (near_ == 0.0f)
		{
			near_ = 0.1f;
		}
		if (far_ == 0.0f)
		{
			far_ = 1000.0f;
		}
		if (fovAngleY == 0.0f)
		{
			fovAngleY = AX_PI / 4;
		}

		//�������e�s��̌v�Z
		MakePerspectiveL(fovAngleY, aspect, near_, far_, projectionMatrix);

	}

	updateProjMatrix = false;

	//�r���[�s��̎Z�o
	MakeLookL(eye, target, up, viewMatrix);
	//�r���[�s��̋t�s����v�Z
	viewMatrixInv = MakeInverse(&viewMatrix);
	//�r���[�v���W�F�N�V�����s��̍쐬
	viewProjectionMatrix = viewMatrix * projectionMatrix;

	//�J�����̑O�x�N�g���擾
	forward = { viewMatrixInv.m[2][0], viewMatrixInv.m[2][1], viewMatrixInv.m[2][2] };
	forward.Normal();

	//�����_�Ǝ��_�̋����擾
	Vector3 toPos;
	toPos = eye - target;
	tgtToPosLen = toPos.Length();

	updateViewMatrix = false;
}

void Camera::Update()
{

	if (oldEye != eye || oldTarget != target || oldUp != up)
	{
		updateViewMatrix = true;

		oldEye = eye;
		oldTarget = target;
		oldUp = up;
	}


	if (updateProjMatrix)
	{
		if (matrixFunc == UpdateProjMatrixFunc_Ortho)
		{
			if (far_ == 0.0f)
			{
				far_ = 1.0f;
			}

			right = static_cast<float>(WindowsApp::GetInstance()->GetWindowSize().width);
			bottom = static_cast<float>(WindowsApp::GetInstance()->GetWindowSize().height);
			MakeOrthogonalL(left, right, bottom, top, near_, far_, projectionMatrix);

		}
		else
		{
			if (near_ == 0.0f)
			{
				near_ = 0.1f;
			}
			if (far_ == 0.0f)
			{
				far_ = 1000.0f;
			}
			if (fovAngleY == 0.0f)
			{
				fovAngleY = AX_PI / 4;
			}

			MakePerspectiveL(fovAngleY, aspect, near_, far_, projectionMatrix);
		}
		updateProjMatrix = false;
	}

	if (updateViewMatrix)
	{
		//�r���[�s��̎Z�o
		MakeLookL(eye, target, up, viewMatrix);
		//�r���[�v���W�F�N�V�����s��̍쐬
		viewProjectionMatrix = viewMatrix * projectionMatrix;
		//�r���[�s��̋t�s����v�Z
		viewMatrixInv = MakeInverse(&viewMatrix);

		forward = { viewMatrixInv.m[2][0], viewMatrixInv.m[2][1], viewMatrixInv.m[2][2] };

		Vector3 toPos;
		toPos = eye - target;
		tgtToPosLen = toPos.Length();

		updateViewMatrix = false;
	}

	if (simpleFollowWithWorldUp)
	{

	}
}

void Camera::Move(const Vector3& move)
{
	eye += move;
	target += move;
	updateViewMatrix = true;
}

void Camera::MoveTarget(const Vector3& move)
{
	target += move;
	updateViewMatrix = true;
}

void Camera::MovePosition(const Vector3& move)
{
	eye += move;
	updateViewMatrix = true;
}

#pragma region �Z�b�^�[

void Camera::SetAspect(float aspect_)
{
	aspect = aspect_;
	updateViewMatrix = true;
}

void Camera::SetFar(float fFar)
{
	far_ = fFar;
	updateProjMatrix = true;
}

void Camera::SetNear(float fNear)
{
	near_ = fNear;
	updateProjMatrix = true;
}

void Camera::SetFovAngleY(float fovAngle)
{
	this->fovAngleY = fovAngle;
	updateProjMatrix = true;
}

void Camera::SetUpdateProjMatrixFunc(UpdateProjMatrixFunc func)
{
	matrixFunc = func;
	updateProjMatrix = true;
}

void Camera::SetLeft(float left_)
{
	left = left_;
	updateProjMatrix = true;
}
void Camera::SetRight(float right_)
{
	right = right_;
	updateProjMatrix = true;
}

void Camera::SetTop(float top_)
{
	top = top_;
	updateProjMatrix = true;
}

void Camera::SetBottom(float bottom_)
{
	bottom = bottom_;
	updateProjMatrix = true;
}

#pragma endregion

#pragma region �Q�b�^�[

const Matrix4& Camera::GetViewMatrix()
{
	//�X�V
	Update();
	return viewMatrix;
}

const Matrix4& Camera::GetViewMatrixInv()
{
	//�X�V
	Update();
	return viewMatrixInv;
}

const Matrix4& Camera::GetProjectionMatrix()
{
	//�X�V
	Update();
	return projectionMatrix;
}

const Matrix4& Camera::GetViewProjectionMatrix()
{
	//�X�V
	Update();
	return viewProjectionMatrix;
}

const Matrix4& Camera::GetCameraRotation()
{
	//�X�V
	Update();
	return cameraRotation;
}

float Camera::GetFar() const
{
	return far_;
}

float Camera::GetNear() const
{
	return near_;
}

float Camera::GetFovAngleY() const
{
	return fovAngleY;
}

float Camera::GetTargetToPositionLength() const
{
	return tgtToPosLen;
}

const Vector3& Camera::GetForward() const
{
	return forward;
}

float Camera::GetAspect() const
{
	return aspect;
}

float Camera::GetLeft()
{
	return left;
}

float Camera::GetRight()
{
	return right;
}

float Camera::GetTop()
{
	return top;
}

float Camera::GetBottom()
{
	return bottom;
}

#pragma endregion