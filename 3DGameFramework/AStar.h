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
	// 探索近隣行数
	static const int NEIGHBOR_ROW4_NUM = 4;
	static const int NEIGHBOR_ROW8_NUM = 8;
	// 探索近隣列数
	static const int NEIGHBOR_COLUMN_NUM = 2;
	// 行列
	enum ROW_COLUMN { ROW = 0, COLUMN = 1 };
	// 行列オフセット
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
	// 2点間の距離を計算する
	float Distance(const Position& position, const Position& position1) override;
	// コンストラクタ
	AStar(ITiledMap* tiledMap);
	// 最短経路オブジェクトを初期化する
	bool Initialize() override;
	// Nodeオブジェクトマップをクリアする
	void ClearMap() override;
	// 最短経路アルゴリズムを実行する
	bool Search(const Position& startPosition, const Position& endPosition) override;
	// 最短経路を返す
	std::vector<Position> GetShortestPath(const Position& startPosition, const Position& endPosition) override;
	// 後始末をする
	void Finalize() override;
	// デストラクタ
	~AStar() override;
	// ランダムに位置を取得する
	Position GetRandomPosition();


private:
	// マップ行
	int m_mapRow;
	// マップ列
	int m_mapColumn;
	// オープンリスト
	std::vector<Node*> m_openList;
	// クローズドリスト
	std::vector<Node*> m_closedList;

	// TiledMapオブジェクトへのポインタ
	ITiledMap* m_tiledMap;
	// Nodeオブジェクトへのポインタを格納するマップ配列
	std::vector<std::vector<Node*>> m_astarMap;
};

#endif	// ASTAR_DEFINED
