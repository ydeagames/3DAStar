#ifndef IOBJECT_DEFINED
#define IOBJECT_DEFINED

#include <SimpleMath.h>
#include "StepTimer.h"

class IObject
{
	// ����������
	virtual int Initialize() noexcept = 0;
	// �X�V����
	virtual int Update(const DX::StepTimer& timer) noexcept = 0;
	// �`�悷��
	virtual void Render(const DX::StepTimer& timer, 
		const DirectX::SimpleMath::Matrix& view, 
		const DirectX::SimpleMath::Matrix& projection) noexcept = 0;
	// ��n��������
	virtual void Finalize() = 0;
};

#endif	// IOBJECT_DEFINED

