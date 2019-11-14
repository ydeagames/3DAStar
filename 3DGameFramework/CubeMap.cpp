#include "CubeMap.h"

// �R���X�g���N�^
CubeMap::CubeMap(Scene* scene) noexcept : m_scene(scene)
{
}

// ����������
void CubeMap::Initialize(const std::string& mapFile) noexcept
{
	// �e�N�X�`���t�@�C��
	wstring textureFile[] =
	{
		L"resources\\texture\\concrete.png",	// �R���N���[�g
		L"resources\\texture\\corkBoard.png",	// �R���N�{�[�h
		L"resources\\texture\\grass.png",		// �O���X
		L"resources\\texture\\substance.png"	// �T�u�X�^���X
	};

	// �e�N�X�`���𐶐�����
	DirectX::CreateWICTextureFromFile(m_directX.GetDevice().Get(), textureFile[2].c_str(), nullptr, m_grass.ReleaseAndGetAddressOf());
	DirectX::CreateWICTextureFromFile(m_directX.GetDevice().Get(), textureFile[1].c_str(), nullptr, m_corkBoard.ReleaseAndGetAddressOf());
	
	// Box���f���𐶐�����
	m_cube = DirectX::GeometricPrimitive::CreateBox(m_directX.GetContext().Get(), DirectX::XMFLOAT3(0.99f, 0.2f, 0.99f), true, true);
	// BasicEffect�I�u�W�F�N�g���Q�Ƃ���
	m_basicEffect = m_scene->GetBasicEffect();
	// InputLayout�I�u�W�F�N�g�𐶐�����
	m_cube->CreateInputLayout(m_basicEffect, &m_inputLayout);
	
	// TiledMap�I�u�W�F�N�g�𐶐�����
	m_tiledMap = std::make_unique<TiledMap>();
	// �}�b�v�����[�h����
	m_tiledMap->Load(mapFile);
}

// �X�V����
void CubeMap::Update(const DX::StepTimer& timer) noexcept
{
}

// �`�悷��
void CubeMap::Render(const DX::StepTimer& timer, const DirectX::SimpleMath::Matrix& view, const DirectX::SimpleMath::Matrix& projection) noexcept
{
	// �ʒu
	DirectX::SimpleMath::Vector3 position = DirectX::SimpleMath::Vector3::Zero;
	// �ړ��s��
	DirectX::SimpleMath::Matrix translation = DirectX::SimpleMath::Matrix::Identity;

	for (int row = 0; row < m_tiledMap->GetMapRow(); row++)
	{
		for (int column = 0; column < m_tiledMap->GetMapColumn(); column++)
		{
			// �ʒu���v�Z����
			position = DirectX::SimpleMath::Vector3(((float)column - 5.0f), 0.0f, ((float)row - 5.0f));
			// �ړ��s����쐬����
			translation = DirectX::SimpleMath::Matrix::CreateTranslation(position);
			// �ړ��s���ݒ肷��
			m_basicEffect->SetWorld(translation);
			// �r���[�s���ݒ肷��
			m_basicEffect->SetView(view);
			// �v���W�F�N�V�����s���ݒ肷��
			m_basicEffect->SetProjection(projection);

			// �}�b�v�̑����ɉ����ăe�N�X�`����I������
			switch (m_tiledMap->GetMap()[row][column])
			{
				case MAP_ATTRIBUTE::O:
					// ��Q���e�N�X�`����ݒ肷��
					m_basicEffect->SetTexture(m_corkBoard.Get());
					break;
				case MAP_ATTRIBUTE::P:
					// �ʘH�e�N�X�`����ݒ肷��
					m_basicEffect->SetTexture(m_grass.Get());
					break;
			}			
			// ���f����`�悷��
			m_cube->Draw(m_basicEffect, m_inputLayout);
		}
	}
}

// ��n��������
void CubeMap::Finalize() noexcept
{
	// CorkBoard�e�N�X�`�����������
	m_corkBoard.Reset();
	// Grass�e�N�X�`�����������
	m_grass.Reset();
	// GeometricPrimitive�I�u�W�F�N�g���������
	m_cube.reset();
}
