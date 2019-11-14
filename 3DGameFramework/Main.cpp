#include "MyGame.h"

// ウィンドウ幅
const int width = 1024;
// ウィンドウ高
const int height = 768;

// エントリポイント
int WINAPI wWinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance, _In_ LPWSTR lpCmdLine, _In_ int nCmdShow)
{
    UNREFERENCED_PARAMETER(hPrevInstance);
    UNREFERENCED_PARAMETER(lpCmdLine);

    if (!DirectX::XMVerifyCPUSupport())
        return 1;
	// COMライブラリを初期化する
    if (FAILED(CoInitializeEx(nullptr, COINITBASE_MULTITHREADED)))
        return 1;

	// MyGameオブジェクトを生成する
	MyGame myGame(width, height);
	// ゲームを実行する
	MSG msg = myGame.Run();

	// Comライブラリを終了処理する
    CoUninitialize();
    return (int) msg.wParam;
}
