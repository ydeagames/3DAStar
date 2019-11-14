#ifndef ISHORTESTPATH_DEFINED
#define ISHORTESTPATH_DEFINED

#include <vector>
#include "Position.h"

class IShortestPath
{
public:
	// ランダムに位置を取得する
	Position virtual GetRandomPosition() = 0;
	// 2点間の距離を計算する
	virtual float Distance(const Position& position, const Position& position1) = 0;
	// 最短経路を探索するためのマップをクリアする
	virtual void ClearMap() = 0;
	// 最短経路オブジェクトを初期化する
	virtual bool Initialize() = 0;
	// 最短経路アルゴリズムを実行する
	virtual bool Search(const Position& startPosition, const Position& endPosition) = 0;
	// 最短経路を取得する
	virtual std::vector<Position> GetShortestPath(const Position& startPosition, const Position& endPosition) = 0;
	// 後始末をする
	virtual void Finalize() = 0;
	// 純粋仮想デストラクタ
	virtual ~IShortestPath() = 0;
};

inline IShortestPath::~IShortestPath() {};
#endif	// ISHORTESTPATH_DEFINED

