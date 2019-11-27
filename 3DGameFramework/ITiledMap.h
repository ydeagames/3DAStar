#pragma once
#ifndef ITILEDMAP_DEFINED
#define ITILEDMAP_DEFINED

#include <vector>

class Position;

// マップ属性
enum MAP_ATTRIBUTE { O = -1, P = 0 };

class ITiledMap
{
public:
	// マップ行を取得する
	virtual int GetMapRow() const = 0;
	// マップ列を取得する
	virtual int GetMapColumn() const = 0;
	// マップへのポインタを取得する
	virtual std::vector<std::vector<int>>& GetMap() = 0;
	// 文字列をint型配列に変換する
	virtual std::vector<int> Split(const std::string& line, const char separator) = 0;
	// マップを読み込む
	virtual bool Load(const std::string& filename) = 0;
	// マップサイズをセット
	virtual void SetSize(int col, int row) noexcept = 0;
	// マップを生成
	virtual Position Generate(int x, int y) noexcept = 0;
	// マップをリセットする
	virtual void ResetMap() = 0;
	// 純粋仮想デストラクタ
	virtual ~ITiledMap() = 0;
};

inline ITiledMap::~ITiledMap() {};

#endif	// ITILEDMAP_DEFINED
