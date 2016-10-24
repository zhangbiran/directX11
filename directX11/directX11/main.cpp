#include <D3D11.h>
#include <DXGI.h>
#include <windows.h>
#include <cstdio>

ID3D11Device * IDevice = NULL;
IDXGISwapChain * ISwapChain = NULL;
ID3D11DeviceContext * IContext = NULL;


LRESULT CALLBACK WindowProc(
	HWND hwnd,      // handle to window
	UINT uMsg,      // message identifier
	WPARAM wParam,  // first message parameter
	LPARAM lParam   // second message parameter
	);


int WINAPI WinMain(
	HINSTANCE hInstance,      // handle to current instance
	HINSTANCE hPrevInstance,  // handle to previous instance
	LPSTR lpCmdLine,          // command line
	int nCmdShow              // show state
	)
{
	WNDCLASSEX wndClass = { 0 };
	wndClass.cbSize = sizeof(WNDCLASSEX);
	wndClass.style = CS_VREDRAW | CS_HREDRAW;
	wndClass.hbrBackground = HBRUSH(COLOR_WINDOW + 1);
	wndClass.hCursor = LoadCursor(NULL, IDC_ARROW);
	wndClass.hInstance = hInstance;
	wndClass.lpfnWndProc = WindowProc;
	wndClass.lpszClassName = "directX11";
	wndClass.lpszMenuName = NULL;

	ATOM atom = RegisterClassEx(&wndClass);
	if (atom == 0)
	{
		return -1;
	}

	HWND hwnd = CreateWindow("directX11", "directX11", WS_OVERLAPPEDWINDOW, 0, 0, 640, 480, NULL, NULL, hInstance, NULL);
	if (NULL == hwnd)
	{
		char buf[100] = { 0 };
		sprintf_s(buf, "%d", GetLastError());
		MessageBox(NULL, buf, "error", MB_OK);
	}

	ShowWindow(hwnd, SW_SHOW);

	DXGI_SWAP_CHAIN_DESC desc;
	ZeroMemory(&desc, sizeof(DXGI_SWAP_CHAIN_DESC));
	desc.BufferCount = 1;
	desc.OutputWindow = hwnd;
	desc.Windowed = true;
	desc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
	desc.BufferDesc.Width = 480;
	desc.BufferDesc.Height = 640;
	desc.BufferDesc.RefreshRate.Numerator = 60;
	desc.BufferDesc.RefreshRate.Denominator = 1;
	desc.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
	desc.SampleDesc.Count = 1;
	desc.SampleDesc.Quality = 0;
	desc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
	desc.BufferCount = 1;
	desc.OutputWindow = hwnd;
	desc.Windowed = true;

	HRESULT ret = D3D11CreateDeviceAndSwapChain(
		NULL,
		D3D_DRIVER_TYPE_HARDWARE,
		NULL,
		0,
		NULL,
		0,
		D3D11_SDK_VERSION,
		&desc,
		&ISwapChain,
		&IDevice,
		NULL,
		&IContext);

	if (S_OK == ret)
	{
		MessageBox(NULL, "D3D11CreateDeviceAndSwapChain", "success", MB_OK);
	}




	MSG msg = { 0 };
	while (msg.message != WM_QUIT)
	{
		if (PeekMessage(&msg, 0, 0, 0, PM_REMOVE))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
	}


	return static_cast<int>(msg.wParam);
}


LRESULT CALLBACK WindowProc(
	HWND hwnd,      // handle to window
	UINT uMsg,      // message identifier
	WPARAM wParam,  // first message parameter
	LPARAM lParam   // second message parameter
	)
{
	PAINTSTRUCT paintStruct;
	HDC hDC;

	switch (uMsg)
	{
	case WM_PAINT:
		hDC = BeginPaint(hwnd, &paintStruct);
		LineTo(hDC, 100, 100);
		EndPaint(hwnd, &paintStruct);
		break;

	case WM_DESTROY:
		PostQuitMessage(0);
		break;

	default:
		return DefWindowProc(hwnd, uMsg, wParam, lParam);
	}

	return 0;
}
