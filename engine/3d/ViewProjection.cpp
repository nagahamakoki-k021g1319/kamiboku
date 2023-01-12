#include "DirectXCommon.h"
#include "ViewProjection.h"
#include "WinApp.h"
#include <cassert>
#include <d3dx12.h>

using namespace DirectX;

void ViewProjection::Initialize() {
	CreateConstBuffer();
	Map();
	UpdateMatrix();
}

void ViewProjection::CreateConstBuffer() {
	HRESULT result;

	// �q�[�v�v���p�e�B
	CD3DX12_HEAP_PROPERTIES heapProps = CD3DX12_HEAP_PROPERTIES(D3D12_HEAP_TYPE_UPLOAD);
	// ���\�[�X�ݒ�
	CD3DX12_RESOURCE_DESC resourceDesc =
		CD3DX12_RESOURCE_DESC::Buffer((sizeof(ConstBufferDataViewProjection) + 0xff) & ~0xff);

	// �萔�o�b�t�@�̐���
	result = DirectXCommon::GetInstance()->GetDevice()->CreateCommittedResource(
		&heapProps, // �A�b�v���[�h�\
		D3D12_HEAP_FLAG_NONE, &resourceDesc, D3D12_RESOURCE_STATE_GENERIC_READ, nullptr,
		IID_PPV_ARGS(&constBuff_));
	assert(SUCCEEDED(result));
}

void ViewProjection::Map() {
	// �萔�o�b�t�@�Ƃ̃f�[�^�����N
	HRESULT result = constBuff_->Map(0, nullptr, (void**)&constMap);
	assert(SUCCEEDED(result));
}

void ViewProjection::UpdateMatrix() {
	// �r���[�s��̐���
	matView = XMMatrixLookAtLH(XMLoadFloat3(&eye), XMLoadFloat3(&target), XMLoadFloat3(&up));

	// �������e�ɂ��ˉe�s��̐���
	matProjection = XMMatrixPerspectiveFovLH(fovAngleY, aspectRatio, nearZ, farZ);

	// �萔�o�b�t�@�ɏ�������
	constMap->view = matView;
	constMap->projection = matProjection;
	constMap->cameraPos = eye;
}
