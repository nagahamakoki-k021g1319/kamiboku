//���_�V�F�[�_�[�̏o�͍\����
//�i���_�V�F�[�_�[����s�N�Z���V�F�[�_�[�ւ̂����Ɏg�p����j
struct VSOutput
{
	//�V�X�e���p���_���W
	float4 svpos : SV_POSITION;
	// uv�l
	float2 uv :TEXCOORD;
};

cbuffer GPUData:register(b0)//�����Ă������
{
	int shadeNumber;
	int KernelSize;
	float2 center;
	float intensity;
	int samples;
	float _AngleDeg;
	float _AngleDeg2;
}