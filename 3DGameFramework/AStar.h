#pragma once
#ifndef ASTAR_DEFINED
#define ASTAR_DEFINED

#include <vector>
#include <cmath>
#include <random>

#include "IShortestPath.h"
#include "TiledMap.h"

class AStar : public IShortestPath
{
public:
	// �T���ߗ׍s��
	static const int NEIGHBOR_ROW4_NUM = 4;
	static const int NEIGHBOR_ROW8_NUM = 8;
	// �T���ߗח�
	static const int NEIGHBOR_COLUMN_NUM = 2;
	// �s��
	enum ROW_COLUMN { ROW = 0, COLUMN = 1 };
	// �s��I�t�Z�b�g
	const int OFFSET4[NEIGHBOR_ROW4_NUM][NEIGHBOR_COLUMN_NUM] = {{-1,  0},
																 { 0, -1},
																 { 0,  1},
																 { 1,  0}
	};
	const int OFFSET8[NEIGHBOR_ROW8_NUM][NEIGHBOR_COLUMN_NUM] = {{-1,  0},
																 {-1,  1},
																 { 0, -1},
																 { 0,  1},
																 { 1, -1},
																 { 1,  0},
																 { 1,  1}
	};

public:
	// 2�_�Ԃ̋������v�Z����
	float Distance(const Position& position, const Position& position1) override;
	// �R���X�g���N�^
	AStar(ITiledMap* tiledMap);
	// �ŒZ�o�H�I�u�W�F�N�g������������
	bool Initialize() override;
	// Node�I�u�W�F�N�g�}�b�v���N���A����
	void ClearMap() override;
	// �ŒZ�o�H�A���S���Y�������s����
	bool Search(const Position& startPosition, const Position& endPosition) override;
	// �ŒZ�o�H��Ԃ�
	std::vector<Position> GetShortestPath(const Position& startPosition, const Position& endPosition) override;
	// ��n��������
	void Finalize() override;
	// �f�X�g���N�^
	~AStar() override;
	// �����_���Ɉʒu���擾����
	Position GetRandomPosition();


private:
	// �}�b�v�s
	int m_mapRow;
	// �}�b�v��
	int m_mapColumn;
	// �I�[�v�����X�g
	std::vector<Node*> m_openList;
	// �N���[�Y�h���X�g
	std::vector<Node*> m_closedList;

	// TiledMap�I�u�W�F�N�g�ւ̃|�C���^
	ITiledMap* m_tiledMap;
	// Node�I�u�W�F�N�g�ւ̃|�C���^���i�[����}�b�v�z��
	std::vector<std::vector<Node*>> m_astarMap;
};

#endif	// ASTAR_DEFINED
