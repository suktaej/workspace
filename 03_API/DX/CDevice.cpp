#include "CDevice.h"

DEFINITION_SINGLE(CDevice)

CDevice::CDevice()
{

}

CDevice::~CDevice()
{
	// COM(Component Object Model)의 pointer관리
	// smart pointer로 참조횟수를 count
	// instance 제거 시, 해당 pointer를 Release() function으로 해제
	SAFE_RELEASE(mSwapChain);

	// device context의 모든 설정을 초기화
	if (mContext)
		mContext->ClearState();

	SAFE_RELEASE(mContext);
	SAFE_RELEASE(mDevice);
}

bool CDevice::init(HWND hWnd, unsigned int width, unsigned int height, bool mode)
{
	mhWnd = hWnd;
	mResolution.width = width;
	mResolution.height = height;

	D3D11CreateDevice();

	return false;
}
