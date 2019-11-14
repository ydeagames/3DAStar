#include "AStar.h"

// 2点間の距離を計算する
float AStar::Distance(const Position& position, const Position& position1)
{
	// 行差を計算する
	int deltaRow = position1.row - position.row;
	// 列差を計算する
	int deltaColumn = position1.column - position.column;
	// 計算結果を返す
	return sqrtf((float)(deltaRow * deltaRow) + (float)(deltaColumn * deltaColumn));
}

// コンストラクタ
AStar::AStar(ITiledMap* tiledMap) : m_tiledMap(tiledMap)
{
	// マップ行を設定する
	m_mapRow = m_tiledMap->GetMapRow();
	// マップ列を設定する
	m_mapColumn = m_tiledMap->GetMapColumn();
}

// 最短経路オブジェクトを初期化する
bool AStar::Initialize()
{
	// astarMap配列を確保する
	m_astarMap.resize(m_mapRow, std::vector<Node*>(m_mapColumn));

	// Nodeオブジェクトを生成しマップに格納する
	for (int row = 0; row < m_mapRow; row++)
	{
		for (int column = 0; column < m_mapColumn; column++)
		{
			if (m_astarMap[row][column] == nullptr)
			{
				// Nodeオブジェクトを生成する
				m_astarMap[row][column] = new Node(row, column, m_tiledMap->GetMap()[row][column]);
				if (m_astarMap[row][column] == nullptr)
					return false;
			}
		}
	}
	return true;
}

// Nodeオブジェクトマップをクリアする
void AStar::ClearMap()
{
	// オープンリストをクリアする
	m_openList.clear();
	// クローズドリストをクリアする
	m_closedList.clear();

	for (int row = 0; row < m_mapRow; row++)
	{
		for (int column = 0; column < m_mapColumn; column++)
		{
			// コストをクリアする
			m_astarMap[row][column]->SetCost(0.0f);
			// ヒューリスティックをクリアする
			m_astarMap[row][column]->SetHeuristic(0.0f);
			// スコアをクリアする
			m_astarMap[row][column]->SetScore(0.0f);
		}
	}
}

// 最短経路アルゴリズムを実行する
bool AStar::Search(const Position& startPosition, const Position& endPosition)
{
	// 開始位置と終了位置が等しい場合は処理しない
	if (startPosition == endPosition)
		return false;

	// 親行を設定する
	int parentRow = endPosition.row;
	// 親列を設定する
	int parentColumn = endPosition.column;

	for (;;)
	{	// オープンリストに近隣ノードを追加する
		for (int index = 0; index < NEIGHBOR_ROW4_NUM; index++)
		{
			// 近隣ノードの行位置を決定する
			int neighborRow = parentRow + OFFSET4[index][ROW];
			// 近隣ノードの列位置を決定する
			int neighborColumn = parentColumn + OFFSET4[index][COLUMN];

			// マップの行位置の範囲をチェックする
			if (neighborRow < 0 || neighborRow > m_mapRow - 1)
				continue;
			// マップの列位置の範囲をチェックする
			if (neighborColumn < 0 || neighborColumn > m_mapColumn - 1)
				continue;
			// 近隣ノードのスコアが計算済みの場合はオープンリストに追加しない
			if (m_astarMap[neighborRow][neighborColumn]->GetScore() != 0.0f)
				continue;
			// 終了ノードをオープンリストに追加しない
			if (neighborRow == endPosition.row && neighborColumn == endPosition.column)
				continue;
			// ノードがパスの場合オープンリストにノードを追加する
			if (m_astarMap[neighborRow][neighborColumn]->GetAttribute() == MAP_ATTRIBUTE::P)
			{
				// オープンリストにノードを追加する
				m_openList.push_back(m_astarMap[neighborRow][neighborColumn]);
				// ノードの親ノードを設定する
				m_astarMap[neighborRow][neighborColumn]->SetParent(m_astarMap[parentRow][parentColumn]);
			}
		}
		// オープンリストが空になる場合、経路が存在しない
		if (m_openList.size() == 0)
			return false;

		// オープンリストイテレータを宣言する
		std::vector<Node*>::iterator openListItr;
		// オープンリストに追加されたノードのスコアを計算する
		for (openListItr = m_openList.begin(); openListItr < m_openList.end(); openListItr++)
		{
			// スコア計算済みノードは再計算しない
			if ((*openListItr)->GetScore() != 0.0f)
				continue;
			// ノードのコストを計算する
			(*openListItr)->SetCost(Distance(Position(endPosition.row, endPosition.column), Position((*openListItr)->GetRow(), (*openListItr)->GetColumn())));
			// ノードのヒューリスティックを計算する
			(*openListItr)->SetHeuristic(Distance(Position(startPosition.row, startPosition.column), Position((*openListItr)->GetRow(), (*openListItr)->GetColumn())));
			// ノードのスコアを計算する
			(*openListItr)->SetScore((*openListItr)->GetCost() + (*openListItr)->GetHeuristic());
		}

		// クローズドリストイテレータを宣言する
		std::vector<Node*>::iterator closedListItr = m_openList.begin();
		// 最小スコア
		float minimum = 0.0f;
		// 最小スコアのノードを探索する
		for (openListItr = m_openList.begin(), minimum = (*openListItr)->GetScore(); openListItr < m_openList.end(); openListItr++)
		{
			// 最小値とオープンリストイテレータが指示すノードのスコアと比較する
			if (minimum > (*openListItr)->GetScore())
			{
				// 最小スコアを設定する
				minimum = (*openListItr)->GetScore();
				// オープンリストイテレータをクローズドリストイテレータに代入する
				closedListItr = openListItr;
			}
		}

		// 新しい親行を設定する
		parentRow = (*closedListItr)->GetRow();
		// 新しい親列を設定する
		parentColumn = (*closedListItr)->GetColumn();
		// 新しい親ノード(最小スコアのノード)をクローズドリストイテレータに追加する
		m_closedList.push_back(*closedListItr);
		// クローズドリストイテレータが指示すノードをオープンリストから削除する
		m_openList.erase(closedListItr);
		// 新しい親ノードがスタートノードに到達したかどうかを判定する
		if (parentRow == startPosition.row && parentColumn == startPosition.column)
			break;
	}
	return true;
}

// 最短経路のPosition配列を返す
std::vector<Position> AStar::GetShortestPath(const Position& startPosition, const Position& endPosition) 
{
	std::vector<Position> shortestPath;
	// ノードに開始ノードを設定する
	Node* node = m_astarMap[startPosition.row][startPosition.column];
	// ノードが終了ノードに到達したかどうかを判定する
	while (node != m_astarMap[endPosition.row][endPosition.column])
	{
		// 最短経路の位置をPosition配列に追加する
		shortestPath.push_back(Position(node->GetRow(), node->GetColumn()));
		// 親ノードを辿る
		node = node->GetParent();
	}
	// 最短経路の位置をPosition配列に追加する
	shortestPath.push_back(Position(node->GetRow(), node->GetColumn()));
	// 最短経路のPosition配列を返す
	return shortestPath;
}

// 後始末をする
void AStar::Finalize()
{
	// マップ内部のすべてのNodeオブジェクトを破棄する
	for (int row = 0; row < m_mapRow; row++)
	{
		for (int column = 0; column < m_mapColumn; column++)
		{
			// Nodeオブジェクトを破棄する
			if (m_astarMap[row][column] != nullptr)
			{
				delete m_astarMap[row][column];
				m_astarMap[row][column] = nullptr;
			}
		}
	}

	// マップデータを破棄する
	m_astarMap.clear();
}

// デストラクタ
AStar::~AStar()
{
	// 後始末をする
	Finalize();
}

// ランダムに開始位置を取得する
Position AStar::GetRandomPosition()
{
	// 非決定論的な乱数生成クラス
	std::random_device random{};
	// mt19937クラス
	std::mt19937 mt(random());
	// パスリスト配列
	std::vector<Position> pathList;

	for (int row = 0; row < m_mapRow; row++)
	{
		for (int column = 0; column < m_mapColumn; column++)
		{
			// ノード属性がP属性かどうか
			if (m_astarMap[row][column]->GetAttribute() == MAP_ATTRIBUTE::P)
			{
				// パスリストにP属性の位置を追加する
				pathList.emplace_back(Position(row, column));
			}
		}
	}
	// 離散一様分布クラス
	std::uniform_int_distribution<int> position(0, pathList.size() - 1);
	// ランダムに開始位置を取得する
	return pathList.at(position(mt));
}
