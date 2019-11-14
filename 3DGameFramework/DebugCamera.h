#ifndef DEBUG_CAMERA
#define DEBUG_CAMERA

#include <d3d11.h>
#include <Mouse.h>
#include <SimpleMath.h>

class DebugCamera
{
private:
	// モーション
	void Motion(int x, int y) noexcept;

public:
	// ビュー行列を取得する
	DirectX::SimpleMath::Matrix GetViewMatrix() const;
	// デバッグカメラの位置ベクトルを取得する
	DirectX::SimpleMath::Vector3 GetEyePosition() const;
	// 注視点の位置ベクトルを返す
	DirectX::SimpleMath::Vector3 GetTargetPosition() const;

	// コンストラクタ
	DebugCamera(int width, int height) noexcept;
	// デバッグカメラを更新する
	void Update() noexcept;
	// ウィンドウスケールを調整する
	void CalculateWindowScale(int width, int height) noexcept;

private:
	// カメラの距離
	static const float CAMERA_DISTANCE;
	// 横回転
	float m_yAngle, m_yTmp;
	// 縦回転
	float m_xAngle, m_xTmp;
	// ドラッグされた座標
	int m_x, m_y;
	// スケール
	float m_xScale, m_yScale;

	// ビュー行列
	DirectX::SimpleMath::Matrix m_view;
	// スクロールホイール値
	int m_scrollWheelValue;
	// 視点
	DirectX::SimpleMath::Vector3 m_eye;
	// 注視点
	DirectX::SimpleMath::Vector3 m_target;
	// マウストラッカー
	DirectX::Mouse::ButtonStateTracker m_tracker;
};

#endif	// DEBUG_CAMERA

