#pragma once

#include <Windows.h>
#include <list>
#include <vector>
#include <unordered_map>
#include <d3d11.h>
#include <d3dcompiler.h>

#include "include/Math/Vector2D.h"
#include "include/Math/Vector3D.h"
#include "include/Math/Vector4D.h"

#pragma comment(lib,"d3d11.lib")
#pragma comment(lib,"d3d11complier.lib")
#pragma comment(lib,"dxguid.lib")

#define	DECLARE_SINGLE(Type)	\
private:\
	Type();\
	~Type();\
private:\
	static Type*	mInst;\
public:\
	static Type* GetInst()\
	{\
		if(!mInst)\
			mInst = new Type;\
		return mInst;\
	}\
	static void DestroyInst()\
	{\
		SAFE_DELETE(mInst);\
	}
#define	DEFINITION_SINGLE(Type)	Type* Type::mInst = nullptr;
#define	SAFE_DELETE(p)	if(p)	{ delete p; p = nullptr; }
#define	SAFE_RELEASE(p)	if(p)	{ p->Release(); p = nullptr; }

#define GETSET(name, type, val) \
public:\
	void Set##name(type mem) { val = mem; }\
	const type& Get##name() const { return val; }

#define FDT CTimeMgr::GetInst()->GetFDT()
#define DT CTimeMgr::GetInst()->GetDT()

struct FResolution
{
	unsigned int	width = 0;
	unsigned int	height = 0;
};
