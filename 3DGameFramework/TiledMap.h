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
	// マップ行を取得する
	int GetMapRow() const override;
	// マップ列を取得する
	int GetMapColumn() const override;
	// マップ配列へのアドレスを取得する
	std::vector<std::vector<int>>& GetMap()  override;
	// 文字列をint型配列に変換する
	std::vector<int> Split(const std::string& line, const char separator) noexcept override;

	// コンストラクタ
	TiledMap() = default;
	// マップを読み込む
	bool Load(const std::string& mapFile) noexcept override;
	// マップサイズをセット
	void SetSize(int col, int row) noexcept override;
	// マップを生成
	void GenerateImpl(int x, int y, int length, int& lengthMax, Position& posMax) noexcept;
	// マップを生成
	Position Generate(int x, int y) noexcept override;
	// マップをリセットする
	void ResetMap() noexcept override;
	// デストラクタ
	~TiledMap() noexcept override;

private:
	// マップ行数
	int m_rowNum;
	// マップ列数
	int m_columnNum;
	// int型のvector配列を宣言する
	std::vector<std::vector<int>> m_map;
};

#endif	// TILEDMAP_DEFINED

