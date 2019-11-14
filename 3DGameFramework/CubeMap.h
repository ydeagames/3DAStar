#ifndef CUBEMAP_DEFINED
#define CUBEMAP_DEFINED

#include <d3d11.h>
#include <memory>
#include <wrl.h>
#include <wrl/client.h>
#include <SimpleMath.h>
#include <GeometricPrimitive.h>
#include <WICTextureLoader.h>
#include <Effects.h>

#include "DirectX11.h"
#include "Scene.h"
#include "ITiledMap.h"
#include "TiledMap.h"


class Scene;

class CubeMap
{
public:
	// �R���X�g���N�^
	CubeMap(Scene* scene) noexcept;
	// ����������
	void Initialize(const std::string& mapFile) noexcept;
	// �X�V����
	void Update(const DX::StepTimer& timer) noexcept;
	// �`�悷��
	void Render(const DX::StepTimer& timer, const DirectX::SimpleMath::Matrix& view, const DirectX::SimpleMath::Matrix& projection) noexcept;
	// ��n��������
	void Finalize() noexcept;

private:
	// �e�N�X�`��
	Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> m_grass;
	Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> m_corkBoard;
	// �x�C�V�b�N�G�t�F�N�g
	DirectX::BasicEffect* m_basicEffect;
	// �C���v�b�g���C�A�E�g
	//Microsoft::WRL::ComPtr<ID3D11InputLayout> m_inputLayout;
	ID3D11InputLayout* m_inputLayout;

	// �L���[�u���f��
	std::unique_ptr<DirectX::GeometricPrimitive> m_cube;
	
	// Scene�I�u�W�F�N�g�ւ̃|�C���^
	Scene* m_scene;
	// �}�b�v
	std::unique_ptr<ITiledMap> m_tiledMap;

	// DirectX11�N���X�̃C���X�^���X���擾����
	DirectX11& m_directX = DirectX11::Get();
};

#endif	// CUBEMAP_DEFINED

