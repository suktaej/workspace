#pragma once
#include "pch.h"

#define SINGLE(type) static type* GetInst() { static type mgr; return &mgr;}
