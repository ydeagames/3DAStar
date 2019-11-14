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
	// �J�n�ʒu���擾����
	Position GetStartPosition() const
	{
		return m_startPosition;
	}

	// �I���ʒu���擾����
	Position GetEndPosition() const
	{
		return m_endPosition;
	}

	// �ŒZ�o�H���擾����
	std::vector<Position> GetRoute() const
	{
		return m_route;
	}

	// �R���X�g���N�^
	Searching(const std::string& mapFile) noexcept;
	// ����������
	int Initialize(IObject* object) noexcept;
	// �X�V����
	int Update(const DX::StepTimer& timer) noexcept;
	// �`�悷��
	void Render(const DX::StepTimer& timer) noexcept;
	// ��n��������
	void Finalize() noexcept;

private:
	// Enemy�I�u�W�F�N�g�ւ̃|�C���^
	Enemy* m_enemy;

	// �}�b�v�t�@�C��
	std::string m_mapFile;
	// �^�C���h�}�b�v
	std::unique_ptr<ITiledMap> m_tiledMap;
	// �ŒZ�o�H�T��
	std::unique_ptr<IShortestPath> m_pathFinding;
	// �ŒZ�o�H
	std::vector<Position> m_route;
	// �J�n�ʒu
	Position m_startPosition;
	// �I���ʒu
	Position m_endPosition;
};

#endif	// SEARCH_DEFINED
