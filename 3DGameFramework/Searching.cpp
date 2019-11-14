#include "Searching.h"

Searching::Searching(const std::string& mapFile) noexcept
	: m_mapFile(mapFile)
	, m_startPosition(0, 0)
	, m_endPosition(0, 0)
{
}

int Searching::Initialize(IObject* object) noexcept
{
	m_enemy = static_cast<Enemy*>(object);

	m_tiledMap = std::make_unique<TiledMap>();
	m_tiledMap->Load(m_mapFile);
	m_pathFinding = std::make_unique<AStar>(m_tiledMap.get());
	m_pathFinding->Initialize();

	return 0;
}

int Searching::Update(const DX::StepTimer& timer) noexcept
{
	// 開始位置を取得する
	m_startPosition = m_enemy->GetStartPosition();
	// 終了位置を計算する
	m_endPosition = m_enemy->GetEndPosition();

	// 最短経路を探索する
	if (m_pathFinding->Search(m_startPosition, m_endPosition))
	{
		// 最短経路を取得する
		m_route = m_pathFinding->GetShortestPath(m_startPosition, m_endPosition);
		// マップをクリアする
		m_pathFinding->ClearMap();
		// 探索に成功した
		return SUCCESS;
	}

	// 探索に失敗した
	return FAILURE;
}

void Searching::Render(const DX::StepTimer& timer) noexcept
{
}

void Searching::Finalize() noexcept
{
	// マップをクリアする
	m_pathFinding->ClearMap();
	// AStarオブジェクトを解放する
	m_pathFinding.reset();
	// Mapオブジェクトを解放する
}
