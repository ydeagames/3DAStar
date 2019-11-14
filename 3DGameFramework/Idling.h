#ifndef IDLING_DEFINED
#define IDLING_DEFINED

#include "StepTimer.h"

#include "Enemy.h"
#include "IState.h"

class Enemy;

class Idling : public IState
{
public:
	// コンストラクタ
	Idling() noexcept;
	// 初期化する
	int Initialize(IObject* object) noexcept;
	// 更新する
	int Update(const DX::StepTimer& timer) noexcept;
	// 描画する
	void Render(const DX::StepTimer& timer) noexcept;
	// 後始末をする
	void Finalize() noexcept;
private:
	// Enemyオブジェクトへのポインタ
	Enemy* m_enemy;
};

#endif	// IDLING_DEFINED

