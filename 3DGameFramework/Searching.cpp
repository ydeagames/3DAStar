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
	// �J�n�ʒu���擾����
	m_startPosition = m_enemy->GetStartPosition();
	// �I���ʒu���v�Z����
	m_endPosition = m_enemy->GetEndPosition();

	// �ŒZ�o�H��T������
	if (m_pathFinding->Search(m_startPosition, m_endPosition))
	{
		// �ŒZ�o�H���擾����
		m_route = m_pathFinding->GetShortestPath(m_startPosition, m_endPosition);
		// �}�b�v���N���A����
		m_pathFinding->ClearMap();
		// �T���ɐ�������
		return SUCCESS;
	}

	// �T���Ɏ��s����
	return FAILURE;
}

void Searching::Render(const DX::StepTimer& timer) noexcept
{
}

void Searching::Finalize() noexcept
{
	// �}�b�v���N���A����
	m_pathFinding->ClearMap();
	// AStar�I�u�W�F�N�g���������
	m_pathFinding.reset();
	// Map�I�u�W�F�N�g���������
}
