#pragma once
#ifndef NODE_DEFINED

class Node 
{
public:
	// 行を取得する
	int  GetRow() const 
	{ 
		return m_row; 
	}
	// 行を設定する
	int  GetColumn() const 
	{ 
		return m_column; 
	}
	// 属性を取得する
	int  GetAttribute() const 
	{ 
		return m_attribute; 
	}

	// コストを取得する
	float GetCost() const 
	{ 
		return m_cost; 
	}
	// コストを設定する
	void  SetCost(float cost) 
	{ 
		m_cost = cost; 
	}

	// ヒューリスティックを取得する
	float GetHeuristic() const 
	{ 
		return m_heuristic; 
	}
	// ヒューリスティックを設定する
	void  SetHeuristic(float heuristic) 
	{ 
		m_heuristic = heuristic; 
	}

	// スコアを取得する
	float GetScore() const 
	{ 
		return m_score; 
	}
	// スコアを設定する
	void  SetScore(float score) 
	{ 
		m_score = score; 
	}

	// 親を取得する
	Node* GetParent() const 
	{ 
		return m_parent; 
	}
	// 親を設定する
	void  SetParent(Node* parent) 
	{ 
		m_parent = parent; 
	}

	// コンストラクタ
	Node(int row, int column, int attribute)
		: m_row(row), m_column(column), m_attribute(attribute),
		m_cost(0.0f), m_heuristic(0.0f), m_score(0.0f),
		m_parent(nullptr)
	{
	}

	// デストラクタ
	~Node()
	{
	}

private:
	int   m_row;		// 行
	int   m_column;		// 列
	int   m_attribute;	// 属性

	float m_cost;		// コスト
	float m_heuristic;	// ヒューリスティック
	float m_score;		// スコア
	Node* m_parent;		// 親ノードへのポインタ
};

#endif // NODE_DEFINED
