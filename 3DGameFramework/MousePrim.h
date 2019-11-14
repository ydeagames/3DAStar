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
	// Mouse�I�u�W�F�N�g�ւ̃|�C���^���擾����
	static DirectX::Mouse& Get() noexcept
	{
		if (m_mouse.get() == nullptr)
			m_mouse.reset(new DirectX::Mouse());
		return *m_mouse.get();
	}
private:
	// �}�E�X
	static std::unique_ptr<DirectX::Mouse> m_mouse;
};

#endif // MOUSE_PRIM_DEFINED
