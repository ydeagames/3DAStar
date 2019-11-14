#pragma once
#ifndef POSITION_DEFINED
#define POSITION_DEFINED

class Position 
{
public:
	// ==比較演算子オーバーロード
	bool operator == (const Position& rhs) const
	{
		return row == rhs.row && column == rhs.column;
	}

	// コンストラクタ
	Position() : row(0), column(0)
	{
	}

	Position(const int& row, const int& column) : row(row), column(column)
	{
	}

public:
	int row;	// 行
	int column;	// 列
};

#endif	// POSITION_DEFINED
