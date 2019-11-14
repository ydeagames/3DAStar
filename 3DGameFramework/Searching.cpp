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
	// äJénà íuÇéÊìæÇ∑ÇÈ
	m_startPosition = m_enemy->GetStartPosition();
	// èIóπà íuÇåvéZÇ∑ÇÈ
	m_endPosition = m_enemy->GetEndPosition();

	// ç≈íZåoòHÇíTçıÇ∑ÇÈ
	if (m_pathFinding->Search(m_startPosition, m_endPosition))
	{
		// ç≈íZåoòHÇéÊìæÇ∑ÇÈ
		m_route = m_pathFinding->GetShortestPath(m_startPosition, m_endPosition);
		// É}ÉbÉvÇÉNÉäÉAÇ∑ÇÈ
		m_pathFinding->ClearMap();
		// íTçıÇ…ê¨å˜ÇµÇΩ
		return SUCCESS;
	}

	// íTçıÇ…é∏îsÇµÇΩ
	return FAILURE;
}

void Searching::Render(const DX::StepTimer& timer) noexcept
{
}

void Searching::Finalize() noexcept
{
}
