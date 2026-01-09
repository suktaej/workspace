#pragma once
#include "pch.h"

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

#define GETSET(type, name) \
public:\
	void Set##name(type val) { name = val; }\
	type Get##name() const { return name; }

#define FDT CTimerMgr::GetInst()->GetFDT()
#define DT CTimerMgr::GetInst()->GetDT()
