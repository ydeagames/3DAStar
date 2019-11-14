#include "DebugCamera.h"

const float DebugCamera::CAMERA_DISTANCE = 15.0f;

// コンストラクタ
DebugCamera::DebugCamera(int width, int height) noexcept
	: m_yAngle(0.0f), m_xAngle(0.0f), 
	  m_xTmp(0.0f),   m_yTmp(0.0f), 
	  m_x(0), m_y(0), m_scrollWheelValue(0)
{
	// ウィンドウスケールを計算する
	CalculateWindowScale(width, height);
}

// 更新する
void DebugCamera::Update() noexcept
{
	// 視点ベクトル
	DirectX::SimpleMath::Vector3 eye(0.0f, 0.0f, 1.0f);
	// 注視点ベクトル
	DirectX::SimpleMath::Vector3 target(0.0f, 0.0f, 0.0f);
	// 上向きベクトル
	DirectX::SimpleMath::Vector3 up(0.0f, 1.0f, 0.0f);

	// マウスの状態を取得する
	DirectX::Mouse::State state = DirectX::Mouse::Get().GetState();

	// 相対モードの場合に戻る
	if (state.positionMode == DirectX::Mouse::MODE_RELATIVE)
		return;

	// トラッキングを更新する
	m_tracker.Update(state);

	// マウスの左ボタンが押された場合
	if (m_tracker.leftButton == DirectX::Mouse::ButtonStateTracker::ButtonState::PRESSED)
	{
		// マウスの座標を取得する
		m_x = state.x;
		m_y = state.y;
	}
	// マウスの左ボタンが解放された場合
	else if (m_tracker.leftButton == DirectX::Mouse::ButtonStateTracker::ButtonState::RELEASED)
	{
		// 現在の回転を保存する
		m_xAngle = m_xTmp;
		m_yAngle = m_yTmp;
	}
	// マウスのボタンが押されていたらカメラを移動させる
	if (state.leftButton)
	{
		Motion(state.x, state.y);
	}

	// マウスのホイール値を取得する
	m_scrollWheelValue = state.scrollWheelValue;
	if (m_scrollWheelValue > 0)
	{
		// ホイール値を初期化する
		m_scrollWheelValue = 0;
		// スクロールホイール値をリセットする
		DirectX::Mouse::Get().ResetScrollWheelValue();
	}

	// Y軸の回転行列を生成する
	DirectX::SimpleMath::Matrix rotateY = DirectX::SimpleMath::Matrix::CreateRotationY(m_yTmp);
	// X軸の回転行列を生成する
	DirectX::SimpleMath::Matrix rotateX = DirectX::SimpleMath::Matrix::CreateRotationX(m_xTmp);
	// X軸とY軸の回転行列を合成する
	DirectX::SimpleMath::Matrix rotate = rotateY * rotateX;
	// 視点ベクトルを計算する
	eye = DirectX::SimpleMath::Vector3::Transform(eye, rotate.Invert());
	// スクロールホイール値を視点ベクトルに掛ける
	eye *= (CAMERA_DISTANCE - m_scrollWheelValue / 100.0f);
	// 上方向ベクトルとXY軸の変換行列から上方向ベクトルを変換する
	up = DirectX::SimpleMath::Vector3::Transform(up, rotate.Invert());
	
	// 視点ベクトルを更新する
	m_eye = eye;
	// 注視点ベクトルを更新する
	m_target = target;
	// ビュー行列を生成する
	m_view = DirectX::SimpleMath::Matrix::CreateLookAt(eye, target, up);
}

// 行列を生成する
void DebugCamera::Motion(int x, int y) noexcept
{
	// マウスポインタの位置のドラッグ開始位置からの変位(相対値)を計算する
	float dx = (x - m_x) * m_xScale;
	float dy = (y - m_y) * m_yScale;

	if (dx != 0.0f || dy != 0.0f)
	{
		// Ｙ軸の回転を計算する
		float yAngle = dx * DirectX::XM_PI;
		// Ｘ軸の回転を計算する
		float xAngle = dy * DirectX::XM_PI;

		m_xTmp = m_xAngle + xAngle;
		m_yTmp = m_yAngle + yAngle;
	}
}

// ビュー行列を取得する
DirectX::SimpleMath::Matrix DebugCamera::GetViewMatrix() const
{
	return m_view;
}

// 視点を取得する
DirectX::SimpleMath::Vector3 DebugCamera::GetEyePosition() const
{
	return m_eye;
}

// 注視点を取得する
DirectX::SimpleMath::Vector3 DebugCamera::GetTargetPosition() const
{
	return m_target;
}

// スケールを計算する
void DebugCamera::CalculateWindowScale(int width, int height) noexcept
{
	// 画面サイズに対する相対的なスケールを計算する
	m_xScale = 1.0f / float(width);
	m_yScale = 1.0f / float(height);
}
