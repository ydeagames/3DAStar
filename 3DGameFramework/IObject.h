#ifndef IOBJECT_DEFINED
#define IOBJECT_DEFINED

#include <SimpleMath.h>
#include "StepTimer.h"

class IObject
{
	// 初期化する
	virtual int Initialize() noexcept = 0;
	// 更新する
	virtual int Update(const DX::StepTimer& timer) noexcept = 0;
	// 描画する
	virtual void Render(const DX::StepTimer& timer, 
		const DirectX::SimpleMath::Matrix& view, 
		const DirectX::SimpleMath::Matrix& projection) noexcept = 0;
	// 後始末をする
	virtual void Finalize() = 0;
};

#endif	// IOBJECT_DEFINED

