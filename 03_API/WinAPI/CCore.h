#pragma once

class CCore
{
private:
	CCore();
	~CCore();

private:
	// static member variable
	static CCore* inst;
	HWND mhWnd;
	POINT mPtResolution;

public:
	int init(HWND _hwnd, POINT _ptResolution);
	void progress();

	// static member function
	static CCore* GetInstance()
	{
		// 최초 호출
		if (nullptr == inst)
			inst = new CCore;

		return inst;
	}
	
	// static member function
	static void Release()
	{
		delete inst;
		inst = nullptr;
	}
};
