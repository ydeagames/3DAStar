#pragma once
#ifndef NODE_DEFINED

class Node 
{
public:
	// �s���擾����
	int  GetRow() const 
	{ 
		return m_row; 
	}
	// �s��ݒ肷��
	int  GetColumn() const 
	{ 
		return m_column; 
	}
	// �������擾����
	int  GetAttribute() const 
	{ 
		return m_attribute; 
	}

	// �R�X�g���擾����
	float GetCost() const 
	{ 
		return m_cost; 
	}
	// �R�X�g��ݒ肷��
	void  SetCost(float cost) 
	{ 
		m_cost = cost; 
	}

	// �q���[���X�e�B�b�N���擾����
	float GetHeuristic() const 
	{ 
		return m_heuristic; 
	}
	// �q���[���X�e�B�b�N��ݒ肷��
	void  SetHeuristic(float heuristic) 
	{ 
		m_heuristic = heuristic; 
	}

	// �X�R�A���擾����
	float GetScore() const 
	{ 
		return m_score; 
	}
	// �X�R�A��ݒ肷��
	void  SetScore(float score) 
	{ 
		m_score = score; 
	}

	// �e���擾����
	Node* GetParent() const 
	{ 
		return m_parent; 
	}
	// �e��ݒ肷��
	void  SetParent(Node* parent) 
	{ 
		m_parent = parent; 
	}

	// �R���X�g���N�^
	Node(int row, int column, int attribute)
		: m_row(row), m_column(column), m_attribute(attribute),
		m_cost(0.0f), m_heuristic(0.0f), m_score(0.0f),
		m_parent(nullptr)
	{
	}

	// �f�X�g���N�^
	~Node()
	{
	}

private:
	int   m_row;		// �s
	int   m_column;		// ��
	int   m_attribute;	// ����

	float m_cost;		// �R�X�g
	float m_heuristic;	// �q���[���X�e�B�b�N
	float m_score;		// �X�R�A
	Node* m_parent;		// �e�m�[�h�ւ̃|�C���^
};

#endif // NODE_DEFINED
