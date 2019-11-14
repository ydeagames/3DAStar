#pragma once
#ifndef POSITION_DEFINED
#define POSITION_DEFINED

class Position 
{
public:
	// ==��r���Z�q�I�[�o�[���[�h
	bool operator == (const Position& rhs) const
	{
		return row == rhs.row && column == rhs.column;
	}

	// �R���X�g���N�^
	Position() : row(0), column(0)
	{
	}

	Position(const int& row, const int& column) : row(row), column(column)
	{
	}

public:
	int row;	// �s
	int column;	// ��
};

#endif	// POSITION_DEFINED
