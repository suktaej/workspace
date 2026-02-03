#pragma once

#include "GameInfo.h"

class CDevice
{
public:
	DECLARE_SINGLE(CDevice);

private:
	ID3D11Device* mDevice = nullptr;
	ID3D11DeviceContext* mContext = nullptr;
	IDXGISwapChain* mSwapChain = nullptr;

	HWND mhWnd;
	FResolution mResolution;

public:
	bool init(HWND hWnd, unsigned int width, unsigned int height, bool mode);


};

