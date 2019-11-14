#include "TiledMap.h"

// マップ行を取得する
int TiledMap::GetMapRow() const
{
	return m_rowNum;
}

// マップ列を取得する
int TiledMap::GetMapColumn() const
{
	return m_columnNum;
}

// マップへのポインタを取得する
std::vector<std::vector<int>>& TiledMap::GetMap()
{
	return m_map;
}

// 文字列をint型配列に変換する
std::vector<int> TiledMap::Split(const std::string& line, const char separator) noexcept
{
	std::stringstream stringStream(line);
	std::vector<int> elements;
	std::string element;

	// ストリームからセパレータで区切られた文字列を読み込む
	while (getline(stringStream, element, separator))
	{
		// 文字列をint型の数値に変換して配列に追加する
		elements.emplace_back(stoi(element));
	}
	// int型配列を返す
	return elements;
}

// マップを読み込む
bool TiledMap::Load(const std::string& mapFile) noexcept
{
	// 入力ストリーム
	std::ifstream wifs;
	// ストリームから入力された文字列
	std::string line;

	// マップファイルをオープンする
	wifs.open(mapFile);
	// マップファイルをオープンできたかどうか検証する
	if (wifs.is_open())
	{
		// マップの行数を読み込む
		getline(wifs, line);
		// 行数を設定する
		m_rowNum = stoi(line);
		// マップの列数を読み込む
		getline(wifs, line);
		// 列数を設定する
		m_columnNum = stoi(line);
		// マップをリセットする
		ResetMap();
		// マップ配列の要素数を設定する
		m_map.resize(m_rowNum, std::vector<int>(m_columnNum));

		// マップファイルからマップデータを読み込む
		for (int row = 0; row < m_rowNum; row++)
		{
			// 一行分の文字列を読み込む
			getline(wifs, line);
			// 文字列をint型配列に変換する
			m_map[row] = Split(line, ',');
			// 読み込んだマップデータ数をチェックする
			if (m_map[row].size() != m_columnNum)
			{
				// ストリームをクローズする
				wifs.close();
				return false;
			}
		}
		// ストリームをクローズする
		wifs.close();
		return true;
	}
	return false;
}

// マップをリセットする
void TiledMap::ResetMap() noexcept
{
	// マップを破棄する
	m_map.clear();
}

// デストラクタ
TiledMap::~TiledMap() noexcept
{
	// マップを破棄する
	m_map.clear();
}
