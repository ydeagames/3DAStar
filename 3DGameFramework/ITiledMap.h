#pragma once
#ifndef ITILEDMAP_DEFINED
#define ITILEDMAP_DEFINED

#include <vector>

// �}�b�v����
enum MAP_ATTRIBUTE { O = -1, P = 0 };

class ITiledMap
{
public:
	// �}�b�v�s���擾����
	virtual int GetMapRow() const = 0;
	// �}�b�v����擾����
	virtual int GetMapColumn() const = 0;
	// �}�b�v�ւ̃|�C���^���擾����
	virtual std::vector<std::vector<int>>& GetMap() = 0;
	// �������int�^�z��ɕϊ�����
	virtual std::vector<int> Split(const std::string& line, const char separator) = 0;
	// �}�b�v��ǂݍ���
	virtual bool Load(const std::string& filename) = 0;
	// �}�b�v�����Z�b�g����
	virtual void ResetMap() = 0;
	// �������z�f�X�g���N�^
	virtual ~ITiledMap() = 0;
};

inline ITiledMap::~ITiledMap() {};

#endif	// ITILEDMAP_DEFINED
