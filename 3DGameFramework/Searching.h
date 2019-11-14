#ifndef SEARCHING_DEFINED
#define SEARCHING_DEFINED

#include "TiledMap.h"
#include "IShortestPath.h"
#include "AStar.h"
#include "StepTimer.h"

#include "Enemy.h"
#include "IState.h"
#include "Position.h"

class Enemy;

class Searching : public IState
{
public:
	IShortestPath* GetAstar()
	{
		return m_pathFinding.get();
	}
	// 開始位置を取得する
	Position GetStartPosition() const
	{
		return m_startPosition;
	}

	// 終了位置を取得する
	Position GetEndPosition() const
	{
		return m_endPosition;
	}

	// 最短経路を取得する
	std::vector<Position> GetRoute() const
	{
		return m_route;
	}

	// コンストラクタ
	Searching(const std::string& mapFile) noexcept;
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

	// マップファイル
	std::string m_mapFile;
	// タイルドマップ
	std::unique_ptr<ITiledMap> m_tiledMap;
	// 最短経路探索
	std::unique_ptr<IShortestPath> m_pathFinding;
	// 最短経路
	std::vector<Position> m_route;
	// 開始位置
	Position m_startPosition;
	// 終了位置
	Position m_endPosition;
};

#endif	// SEARCH_DEFINED
