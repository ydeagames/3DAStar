#include "TiledMap.h"
#include "Position.h"

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

void TiledMap::SetSize(int col, int row) noexcept
{
	m_columnNum = col;
	m_rowNum = row;
	m_map.clear();
	m_map.resize(m_rowNum, std::vector<int>(m_columnNum, MAP_ATTRIBUTE::O));
}

void TiledMap::GenerateImpl(int x, int y, int length, int& lengthMax, Position& posMax) noexcept
{
	static struct {
		int x;
		int y;
	} dir[] = {
		{0, -1}, /** UP */
		{0, 1},  /** DOWN */
		{-1, 0}, /** LEFT */
		{1, 0}   /** RIGHT */
	};

	int d = rand() % 4;
	int dd = d;
	while (1) {
		int px = x + dir[d].x * 2;
		int py = y + dir[d].y * 2;
		if (px < 0 || px >= m_columnNum || py < 0 || py >= m_rowNum || m_map[py][px] != MAP_ATTRIBUTE::O) {
			d++;
			if (d == 4)
				d = 0;
			if (d == dd)
			{
				return;
			}
			continue;
		}
		m_map[y + dir[d].y][x + dir[d].x] = MAP_ATTRIBUTE::P;
		m_map[py][px] = MAP_ATTRIBUTE::P;
		if (length > lengthMax)
		{
			lengthMax = length;
			posMax = Position(py, px);
		}
		GenerateImpl(px, py, length + 1, lengthMax, posMax);
		d = dd = rand() % 4;
	}
}

Position TiledMap::Generate(int x, int y) noexcept
{
	int lengthMax = 0;
	Position posMax;
	GenerateImpl(x, y, 0, lengthMax, posMax);
	return posMax;
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
