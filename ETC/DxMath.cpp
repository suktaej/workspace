#include <DirectXMath.h>
#include <windows.h>
#include <iostream>

std::ostream& operator<<(std::ostream& os, DirectX::FXMVECTOR vec)
{
	DirectX::XMFLOAT4 dest;
	DirectX::XMStoreFloat4(&dest, vec);

	os << "(" << dest.x << ", " << dest.y << ", " << dest.z << ", " << dest.w << ")";
	return os;
}

void vector()
{
    using DirectX::operator+;
    using DirectX::operator-;
    using DirectX::operator*;
    using DirectX::operator/;

	DirectX::XMVECTOR zero = DirectX::XMVectorZero();
	DirectX::XMVECTOR one = DirectX::XMVectorSplatOne();
	DirectX::XMVECTOR u = DirectX::XMVectorSet(1.f,2.f,3.f,0.f);
	DirectX::XMVECTOR v = DirectX::XMVectorReplicate(-2.f);
	DirectX::XMVECTOR w = DirectX::XMVectorSplatZ(u);

	std::cout << "Zero: " << zero << std::endl;
	std::cout << "One: " << one << std::endl;
	std::cout << "u: " << u << std::endl;
	std::cout << "v: " << v << std::endl;
	std::cout << "w: " << w << std::endl;

    DirectX::XMVECTOR n = u + v;
    DirectX::XMVECTOR m = u - v;
    DirectX::XMVECTOR len = DirectX::XMVector3Length(n);
    DirectX::XMVECTOR norm = DirectX::XMVector3Normalize(n);
    DirectX::XMVECTOR dot = DirectX::XMVector3Dot(n, m);
    DirectX::XMVECTOR cross = DirectX::XMVector3Cross(n, m);
    // 평행성분, 수직성분
    DirectX::XMVECTOR projM, perpM;
    // 분해 대상인 벡터(4번째 인자)는 정규화 되어 있어야 함
    DirectX::XMVector3ComponentsFromNormal(&projM, &perpM, m, norm);
    // 반환되는 값은 4차원 벡터, x,y,z에 동일한 값이 복사되며 w는 0으로 설정
    DirectX::XMVECTOR angleVec = DirectX::XMVector3AngleBetweenVectors(n, m);
    float radians = DirectX::XMVectorGetX(angleVec);

    std::cout << "n: " << n << std::endl;
    std::cout << "m: " << m << std::endl;
    std::cout << "Length of n: " << len << std::endl;
    std::cout << "Normalized n: " << norm << std::endl;
    std::cout << "Dot product of n and m: " << dot << std::endl;
    std::cout << "Cross product of n and m: " << cross << std::endl;
    std::cout << "Projection of m onto n: " << projM << std::endl;
    std::cout << "Perpendicular component of m to n: " << perpM << std::endl;
    std::cout << "Angle between n and m: " << angleVec << std::endl;
    std::cout << "Angle in radians: " << radians << std::endl;
}

std::ostream& operator<<(std::ostream& os, DirectX::FXMMATRIX mat)
{
    for(int i = 0; i < 4; ++i)
       os << mat.r[i] << std::endl;

    return os;
}

void matrix()
{
    using DirectX::operator+;
    using DirectX::operator-;
    using DirectX::operator*;
    using DirectX::operator/;

    DirectX::XMMATRIX m = DirectX::XMMatrixSet(
        1.f, 2.f, 3.f, 4.f,
        0.f, 1.f, 0.f, 0.f,
        0.f, 0.f, 1.f, 0.f,
        0.f, 0.f, 0.f, 3.f
    );
    DirectX::XMFLOAT4X4 storeM; 
    DirectX::XMStoreFloat4x4(&storeM, m);

    DirectX::XMMATRIX identity = DirectX::XMMatrixIdentity();
    DirectX::XMMATRIX add = m + identity;
    DirectX::XMMATRIX mul = m * identity;
    DirectX::XMMATRIX transpose = DirectX::XMMatrixTranspose(m);

    DirectX::XMVECTOR determinant = DirectX::XMMatrixDeterminant(m);
    DirectX::XMMATRIX inverse = DirectX::XMMatrixInverse(&determinant, m);

    std::cout << "Matrix m: \n" << m << std::endl;
    std::cout << "Identity Matrix: \n" << identity << std::endl;
    std::cout << "m + Identity: \n" << add << std::endl;
    std::cout << "m * Identity: \n" << mul << std::endl;
    std::cout << "Transpose of m: \n" << transpose << std::endl;
    std::cout << "Determinant of m: " << determinant << std::endl;
    std::cout << "Inverse of m: \n" << inverse << std::endl;
    
    DirectX::XMFLOAT3 baseInfo = { 1.f, 2.f, 3.f };
    DirectX::XMVECTOR baseVector = DirectX::XMLoadFloat3(&baseInfo);
    
    // 벡터와 행렬의 곱셈
    DirectX::XMVECTOR multiplyMatrix = DirectX::XMVector4Transform(baseVector, m);
    // 점 변환(w = 1)
    DirectX::XMVECTOR multiplyPoint = DirectX::XMVector3TransformCoord(baseVector, m);
    // 벡터 변환(w = 0)
    DirectX::XMVECTOR multiplyNormal = DirectX::XMVector3TransformNormal(baseVector, m);

    // 변환 행렬
    DirectX::XMMATRIX translation = DirectX::XMMatrixTranslation(baseInfo.x, baseInfo.y, baseInfo.z);
    DirectX::XMMATRIX translationFromVector = DirectX::XMMatrixTranslationFromVector(baseVector);
   
    // 스케일링 행렬
    DirectX::XMMATRIX scaling = DirectX::XMMatrixScaling(2.f, 2.f, 2.f);
    DirectX::XMMATRIX scalingFromVector = DirectX::XMMatrixScalingFromVector(baseVector);
    
    // 회전 행렬
    DirectX::XMMATRIX rotation = DirectX::XMMatrixRotationX(DirectX::XM_PIDIV4);
    DirectX::XMMATRIX rotationFromAxisAngle = DirectX::XMMatrixRotationAxis(baseVector, DirectX::XM_PIDIV4); 
    DirectX::XMVECTOR rotationQuaternion = DirectX::XMQuaternionRotationAxis(baseVector, DirectX::XM_PIDIV4);
    DirectX::XMMATRIX rotationFromQuaternion = DirectX::XMMatrixRotationQuaternion(rotationQuaternion);

    DirectX::XMMATRIX combined = translation * scaling * rotation;
    
    std::cout << "Translation Matrix: \n" << translation << std::endl;
    std::cout << "Scaling Matrix: \n" << scaling << std::endl;
    std::cout << "Rotation Matrix: \n" << rotation << std::endl;
    std::cout << "Combined Matrix: \n" << combined << std::endl;
}

int main()
{
	std::cout.setf(std::ios_base::boolalpha);
	
	// SSE2 지원여부 확인
	if(!DirectX::XMVerifyCPUSupport())
	{
		std::cout << "CPU does not support the required instruction set." << std::endl;
		return -1;
	}
	else
		std::cout << "CPU supports the required instruction set." << std::endl;

    matrix();

    return 0;
}