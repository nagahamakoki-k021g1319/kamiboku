#pragma once
#include <Windows.h>
//WindowsAPI
class WinApp
{
public:
	static LRESULT WindowProcedure(HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam);

	//getter
	HWND GetHwnd() const { return hwnd; }

	HINSTANCE GetHInstance() const { return w.hInstance; }

	int GetWindowWidth() {
		return window_width;
	}
	int GetWindowHeight() {
		return window_height;
	}

	bool ProcessMessage();

	// �E�B���h�E����
	static const int window_width = 1280;
	// �E�B���h�E�c��
	static const int window_height = 720;

	static WinApp* GetInstance() {
		static WinApp instance;
		return &instance;
	}

public: //�����o�֐�
	//������
	void Initialize();

	//�X�V
	void Update();

	//�I��
	void Finalize();
private:
	//�E�B���h�E�n���h��
	HWND hwnd = nullptr;

	//�E�B���h�E�N���X�̐ݒ�
	WNDCLASSEX w{};

};