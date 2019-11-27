#pragma once
#ifndef TILEDMAP_DEFINED
#define TILEDMAP_DEFINED

#include <vector>
#include <string>
#include <fstream>
#include <sstream>
#include <string>

#include "ITiledMap.h"
#include "Node.h"

class Position;

class TiledMap : public ITiledMap
{
public:
	// �}�b�v�s���擾����
	int GetMapRow() const override;
	// �}�b�v����擾����
	int GetMapColumn() const override;
	// �}�b�v�z��ւ̃A�h���X���擾����
	std::vector<std::vector<int>>& GetMap()  override;
	// �������int�^�z��ɕϊ�����
	std::vector<int> Split(const std::string& line, const char separator) noexcept override;

	// �R���X�g���N�^
	TiledMap() = default;
	// �}�b�v��ǂݍ���
	bool Load(const std::string& mapFile) noexcept override;
	// �}�b�v�T�C�Y���Z�b�g
	void SetSize(int col, int row) noexcept override;
	// �}�b�v�𐶐�
	void GenerateImpl(int x, int y, int length, int& lengthMax, Position& posMax) noexcept;
	// �}�b�v�𐶐�
	Position Generate(int x, int y) noexcept override;
	// �}�b�v�����Z�b�g����
	void ResetMap() noexcept override;
	// �f�X�g���N�^
	~TiledMap() noexcept override;

private:
	// �}�b�v�s��
	int m_rowNum;
	// �}�b�v��
	int m_columnNum;
	// int�^��vector�z���錾����
	std::vector<std::vector<int>> m_map;
};

#endif	// TILEDMAP_DEFINED

