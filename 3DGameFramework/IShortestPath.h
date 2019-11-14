#ifndef ISHORTESTPATH_DEFINED
#define ISHORTESTPATH_DEFINED

#include <vector>
#include "Position.h"

class IShortestPath
{
public:
	// �����_���Ɉʒu���擾����
	Position virtual GetRandomPosition() = 0;
	// 2�_�Ԃ̋������v�Z����
	virtual float Distance(const Position& position, const Position& position1) = 0;
	// �ŒZ�o�H��T�����邽�߂̃}�b�v���N���A����
	virtual void ClearMap() = 0;
	// �ŒZ�o�H�I�u�W�F�N�g������������
	virtual bool Initialize() = 0;
	// �ŒZ�o�H�A���S���Y�������s����
	virtual bool Search(const Position& startPosition, const Position& endPosition) = 0;
	// �ŒZ�o�H���擾����
	virtual std::vector<Position> GetShortestPath(const Position& startPosition, const Position& endPosition) = 0;
	// ��n��������
	virtual void Finalize() = 0;
	// �������z�f�X�g���N�^
	virtual ~IShortestPath() = 0;
};

inline IShortestPath::~IShortestPath() {};
#endif	// ISHORTESTPATH_DEFINED

