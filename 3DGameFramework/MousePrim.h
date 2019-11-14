#pragma once
#ifndef MOUSE_PRIM_DEFINED
#define MOUSE_PRIM_DEFINED

#include "Windows.h"
#include "Mouse.h"

class MousePrim
{
private:
	MousePrim()
	{}
public:
	// Mouseオブジェクトへのポインタを取得する
	static DirectX::Mouse& Get() noexcept
	{
		if (m_mouse.get() == nullptr)
			m_mouse.reset(new DirectX::Mouse());
		return *m_mouse.get();
	}
private:
	// マウス
	static std::unique_ptr<DirectX::Mouse> m_mouse;
};

#endif // MOUSE_PRIM_DEFINED
