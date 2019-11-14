#ifndef CHASING_DEFINED
#define CHASING_DEFINED

#include "math.h"
#include "Enemy.h"
#include "IState.h"
#include "StepTimer.h"

class Enemy;

class Chasing : public IState
{
public:
	// コンストラクタ
	Chasing() noexcept;
	// 初期化する
	int Initialize(IObject* object) noexcept;
	// 更新する
	int Update(const DX::StepTimer& timer) noexcept;
	// 描画する
	void Render(const DX::StepTimer& timer) noexcept;
	// 後始末をする
	void Finalize() noexcept;
private:
	// 最短経路
	std::vector<Position> m_route;
	// 位置
	DirectX::SimpleMath::Vector3 m_position;
	// Enemyオブジェクトへのポインタ
	Enemy* m_enemy;
};

#endif	// CHASING_DEFINED
