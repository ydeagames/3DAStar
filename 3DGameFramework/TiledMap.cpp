#include "TiledMap.h"

// �}�b�v�s���擾����
int TiledMap::GetMapRow() const
{
	return m_rowNum;
}

// �}�b�v����擾����
int TiledMap::GetMapColumn() const
{
	return m_columnNum;
}

// �}�b�v�ւ̃|�C���^���擾����
std::vector<std::vector<int>>& TiledMap::GetMap()
{
	return m_map;
}

// �������int�^�z��ɕϊ�����
std::vector<int> TiledMap::Split(const std::string& line, const char separator) noexcept
{
	std::stringstream stringStream(line);
	std::vector<int> elements;
	std::string element;

	// �X�g���[������Z�p���[�^�ŋ�؂�ꂽ�������ǂݍ���
	while (getline(stringStream, element, separator))
	{
		// �������int�^�̐��l�ɕϊ����Ĕz��ɒǉ�����
		elements.emplace_back(stoi(element));
	}
	// int�^�z���Ԃ�
	return elements;
}

// �}�b�v��ǂݍ���
bool TiledMap::Load(const std::string& mapFile) noexcept
{
	// ���̓X�g���[��
	std::ifstream wifs;
	// �X�g���[��������͂��ꂽ������
	std::string line;

	// �}�b�v�t�@�C�����I�[�v������
	wifs.open(mapFile);
	// �}�b�v�t�@�C�����I�[�v���ł������ǂ������؂���
	if (wifs.is_open())
	{
		// �}�b�v�̍s����ǂݍ���
		getline(wifs, line);
		// �s����ݒ肷��
		m_rowNum = stoi(line);
		// �}�b�v�̗񐔂�ǂݍ���
		getline(wifs, line);
		// �񐔂�ݒ肷��
		m_columnNum = stoi(line);
		// �}�b�v�����Z�b�g����
		ResetMap();
		// �}�b�v�z��̗v�f����ݒ肷��
		m_map.resize(m_rowNum, std::vector<int>(m_columnNum));

		// �}�b�v�t�@�C������}�b�v�f�[�^��ǂݍ���
		for (int row = 0; row < m_rowNum; row++)
		{
			// ��s���̕������ǂݍ���
			getline(wifs, line);
			// �������int�^�z��ɕϊ�����
			m_map[row] = Split(line, ',');
			// �ǂݍ��񂾃}�b�v�f�[�^�����`�F�b�N����
			if (m_map[row].size() != m_columnNum)
			{
				// �X�g���[�����N���[�Y����
				wifs.close();
				return false;
			}
		}
		// �X�g���[�����N���[�Y����
		wifs.close();
		return true;
	}
	return false;
}

// �}�b�v�����Z�b�g����
void TiledMap::ResetMap() noexcept
{
	// �}�b�v��j������
	m_map.clear();
}

// �f�X�g���N�^
TiledMap::~TiledMap() noexcept
{
	// �}�b�v��j������
	m_map.clear();
}
