#pragma once
#include <DirectXMath.h>
#include "Matrix4.h"

using namespace DirectX;

class ConvertXM
{

public:
	static Matrix4 ConvertXMMATtoMat4( XMMATRIX XMMat);
	static XMMATRIX ConvertMat4toXMMAT(Matrix4 Mat4);
private:
	
	XMMATRIX xmMat;
	Matrix4 mat4;

};

