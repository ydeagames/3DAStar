#ifndef IOBJECT_DEFINED
#define IOBJECT_DEFINED

#include <SimpleMath.h>
#include "StepTimer.h"

class IObject
{
	// ‰Šú‰»‚·‚é
	virtual int Initialize() noexcept = 0;
	// XV‚·‚é
	virtual int Update(const DX::StepTimer& timer) noexcept = 0;
	// •`‰æ‚·‚é
	virtual void Render(const DX::StepTimer& timer, 
		const DirectX::SimpleMath::Matrix& view, 
		const DirectX::SimpleMath::Matrix& projection) noexcept = 0;
	// Œãn––‚ğ‚·‚é
	virtual void Finalize() = 0;
};

#endif	// IOBJECT_DEFINED

