#include "DirectXCommon.h"
#include "WorldTransform.h"
#include <cassert>
#include <d3dx12.h>

using namespace DirectX;

void WorldTransform::Initialize() {
	CreateConstBuffer();
	Map();
	UpdateMatrix();
}

void WorldTransform::CreateConstBuffer() {
	HRESULT result;

	// �q�[�v�v���p�e�B
	CD3DX12_HEAP_PROPERTIES heapProps = CD3DX12_HEAP_PROPERTIES(D3D12_HEAP_TYPE_UPLOAD);
	// ���\�[�X�ݒ�
	CD3DX12_RESOURCE_DESC resourceDesc =
		CD3DX12_RESOURCE_DESC::Buffer((sizeof(ConstBufferDataWorldTransform) + 0xff) & ~0xff);

	// �萔�o�b�t�@�̐���
	result = DirectXCommon::GetInstance()->GetDevice()->CreateCommittedResource(
		&heapProps, // �A�b�v���[�h�\
		D3D12_HEAP_FLAG_NONE, &resourceDesc, D3D12_RESOURCE_STATE_GENERIC_READ, nullptr,
		IID_PPV_ARGS(&constBuff_));
	assert(SUCCEEDED(result));
}

void WorldTransform::Map() {
	// �萔�o�b�t�@�Ƃ̃f�[�^�����N
	HRESULT result = constBuff_->Map(0, nullptr, (void**)&constMap);
	assert(SUCCEEDED(result));
}

void WorldTransform::UpdateMatrix() {
	XMMATRIX matScale, matRot, matTrans;

	// �X�P�[���A��]�A���s�ړ��s��̌v�Z
	matScale = XMMatrixScaling(scale_.x, scale_.y, scale_.z);
	matRot = XMMatrixIdentity();
	matRot *= XMMatrixRotationZ(rotation_.z);
	matRot *= XMMatrixRotationX(rotation_.x);
	matRot *= XMMatrixRotationY(rotation_.y);
	matTrans = XMMatrixTranslation(translation_.x, translation_.y, translation_.z);

	// ���[���h�s��̍���
	matWorld_ = XMMatrixIdentity(); // �ό`�����Z�b�g
	matWorld_ *= matScale;          // ���[���h�s��ɃX�P�[�����O�𔽉f
	matWorld_ *= matRot;            // ���[���h�s��ɉ�]�𔽉f
	matWorld_ *= matTrans;          // ���[���h�s��ɕ��s�ړ��𔽉f

	// �e�s��̎w�肪����ꍇ�́A�|���Z����
	if (parent_) {
		matWorld_ *= parent_->matWorld_;
	}

	// �萔�o�b�t�@�ɏ�������
	constMap->matWorld = matWorld_;
}
