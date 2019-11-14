#ifndef ISTATE_DEFINED
#define ISTATE_DEFINED

#include "StepTimer.h"
#include "IObject.h"

constexpr int SUCCESS = 0;
constexpr int FAILURE = -1;

class IObject;

class IState
{
public:
	// 初期化する
	virtual int Initialize(IObject* object) noexcept = 0;
	// 更新する
	virtual int Update(const DX::StepTimer& timer) noexcept = 0;
	// 描画する
	virtual void Render(const DX::StepTimer& timer) noexcept = 0;
	// 後始末をする
	virtual void Finalize() noexcept = 0;
	// デストラクタ
	virtual ~IState() = 0;
};
inline IState::~IState(){}

#endif	// ISTATE

