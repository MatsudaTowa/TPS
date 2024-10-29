//=============================================
//
//3DTemplate[main.cpp]
//Auther Matsuda Towa
//
//=============================================
#pragma comment(lib,"winmm.lib")
#include "main.h"
#include "manager.h"

//=============================================
//�}�N����`
//=============================================
#define CLASS_NAME "WindowClass" //������
#define WINDOW_NAME "game" //�L���v�V�����ɕ\��

//=============================================
//�v���g�^�C�v�錾
//=============================================
LRESULT CALLBACK WindowProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
void ToggleFullscreen(HWND hWnd);// �E�B���h�E���t���X�N���[���ɂ�����@

//=============================================
//�O���[�o���ϐ�
//=============================================
CManager* g_pManager = nullptr;
int g_nCntFPS = 0; //FPS�J�E���^
bool g_isFullscreen = false;// �E�B���h�E��؂�ւ��邽�߂̃t���O
RECT g_windowRect;// �E�B���h�E��؂�ւ��邽�߂̕ϐ�

//=============================================
//���C���֐�
//=============================================
int WINAPI WinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hInstancePrev, _In_ LPSTR lpCmdLine, _In_ int nCmdShow)
{
	DWORD dwCurrentTime; //���ݎ���
	DWORD dwExecLastTime; //�Ō�ɏ��������Ƃ��̎���
	DWORD dwFrameCnt; //�t���[���J�E���g
	DWORD dwFPSLastTime; //�Ō�ɃJ�E���g����FPS

	WNDCLASSEX wcex =
	{
		sizeof(WNDCLASSEX), //�������T�C�Y
		CS_CLASSDC, //�E�B���h�E�̃X�^�C��
		WindowProc, //�E�B���h�E�v���V�[�W��
		0, //�ʏ�͎g�p���Ȃ�
		0, //�ʏ�͎g�p���Ȃ�
		hInstance, //�C���X�^���X�n���h��
		LoadIcon(NULL,IDI_APPLICATION), //�^�X�N�o�[�̃A�C�R��
		LoadCursor(NULL,IDC_ARROW), //�}�E�X�J�[�\��
		(HBRUSH)(COLOR_WINDOW + 1), //�w�i�F
		NULL, //���j���[�o�[
		CLASS_NAME, //�E�B���h�E�N���X�̖��O
		LoadIcon(NULL,IDI_APPLICATION), //�t�@�C���A�C�R��
	};
	HWND hWnd; //�E�B���h�E�n���h��
	MSG msg; //���b�Z�[�W���i�[����
	RECT rect = { 0,0,SCREEN_WIDTH,SCREEN_HEIGHT };

	//�E�B���h�E�N���X�̓o�^
	RegisterClassEx(&wcex);

	//�N���C�A���g�̈���w��̃T�C�Y�ɒ���
	AdjustWindowRect(&rect, WS_OVERLAPPEDWINDOW, FALSE);

	//�E�B���h�E�𐶐�
	hWnd = CreateWindowEx(0,	//�g���E�B���h�E�X�^�C��
		CLASS_NAME, //�N���X�̖��O
		WINDOW_NAME, //�E�B���h�E�̖��O
		WS_OVERLAPPEDWINDOW, //�E�B���h�E�X�^�C��
		CW_USEDEFAULT, //�E�B���h�E�̍����x���W
		CW_USEDEFAULT,//�E�B���h�E�̍����y���W
		SCREEN_WIDTH, //�E�B���h�E�̕�
		SCREEN_HEIGHT, //�E�B���h�E�̍���
		NULL, //�e�E�B���h�E�̃n���h��)
		NULL, //���j���[�n���h��
		hInstance, //�C���X�^���X�n���h��
		NULL); //�E�B���h�E�쐬�f�[�^

	//������������
	g_pManager = new CManager();

	//����������
	if (FAILED(g_pManager->Init(hInstance,hWnd, TRUE)))
	{//���������s�����Ƃ�
		return -1;
	}
	// �}�E�X�J�[�\���̔�\��
	ShowCursor(FALSE);

	timeBeginPeriod(1); //����\��ݒ�
	dwCurrentTime = 0; //������
	dwFrameCnt = 0;
	dwExecLastTime = timeGetTime(); //���ݎ���
	dwFPSLastTime = timeGetTime(); //���ݎ���
	//�E�B���h�E�̕\��
	ShowWindow(hWnd, nCmdShow); //�E�B���h�E�̕\����ݒ�
	UpdateWindow(hWnd); //�N���C�A���g�̈���X�V

	//���b�Z�[�W���[�v
	while (1)
	{
		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE) != 0)
		{//�E�B���h�E�̏���
			if (msg.message == WM_QUIT)
			{//WM_QUIT���󂯎�����烁�b�Z�[�W���[�v�𔲂���
				break;
			}
			else
			{
				//���b�Z�[�W�̐ݒ�
				TranslateMessage(&msg); //���z�L�[�𕶎��֕ϊ�
				DispatchMessage(&msg); //�E�B���h�E�v���V�[�W���փ��b�Z�[�W�𑗏o
			}
		}
		else
		{//DirectX�̏���
			dwCurrentTime = timeGetTime();
			if ((dwCurrentTime - dwFPSLastTime) >= 500)
			{//0.5�b�o��
				//FPS���v��
				g_nCntFPS = (dwFrameCnt * 1000) / (dwCurrentTime - dwFPSLastTime);
				dwFPSLastTime = dwCurrentTime; //FPS�𑪒肵��������ۑ�
				dwFrameCnt = 0; //�t���[���J�E���g
			}
			if ((dwCurrentTime - dwExecLastTime) >= (1000 / 60))
			{//60����1�b�o��
				dwExecLastTime = dwCurrentTime; //�ŏI�����̐ݒ�
				g_pManager->Update();
				g_pManager->Draw();
				dwFrameCnt++;
			}
		}
	}
	g_pManager->Uninit();
	delete g_pManager;
	//�E�B���h�E�N���X�̓o�^������
	UnregisterClass(CLASS_NAME, wcex.hInstance);
	return(int)msg.wParam;
}

//=============================================
//�E�B���h�E�v���V�[�W��
//=============================================
LRESULT CALLBACK WindowProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	int nID;


	switch (uMsg)
	{
	case WM_CLOSE:

		nID = MessageBox(hWnd, "�I�����܂����H", "�m�F", MB_YESNO | MB_ICONWARNING);
		if (nID == IDYES)
		{
			//�E�B���h�E��j������
			DestroyWindow(hWnd);
		}
		else
		{

			return 0; //0��Ԃ��Ȃ��ƏI�����Ă��܂�
		}
		break;

	case WM_DESTROY:
		//WM_QUIT���b�Z�[�W�𑗂�
		PostQuitMessage(0);
		break;

	case WM_KEYDOWN: //�L�[�������ꂽ���̃��b�Z�[�W
		switch (wParam)
		{
		case VK_ESCAPE: //esc�L�[�������ꂽ
			nID = MessageBox(hWnd, "�I�����܂����H", "�m�F", MB_YESNO | MB_ICONWARNING);
			if (nID == IDYES)
			{
				//�E�B���h�E��j������
				DestroyWindow(hWnd);
			}
			break;
		case VK_F11:
			ToggleFullscreen(hWnd);
			break;

		}
		break;
	case WM_LBUTTONDOWN:
		SetFocus(hWnd);
		break;
	}
	return DefWindowProc(hWnd, uMsg, wParam, lParam);
}

//=============================================
//�E�B���h�E�؂�ւ�����
//=============================================
void ToggleFullscreen(HWND hWnd)
{
	// ���݂̃E�B���h�E�X�^�C�����擾
	DWORD dwStyle = GetWindowLong(hWnd, GWL_STYLE);

	if (g_isFullscreen)
	{
		// �E�B���h�E���[�h�ɐ؂�ւ�
		SetWindowLong(hWnd, GWL_STYLE, dwStyle | WS_OVERLAPPEDWINDOW);
		SetWindowPos(hWnd, HWND_TOP, g_windowRect.left, g_windowRect.top,
			g_windowRect.right - g_windowRect.left, g_windowRect.bottom - g_windowRect.top,
			SWP_FRAMECHANGED | SWP_NOACTIVATE);
		ShowWindow(hWnd, SW_NORMAL);
	}
	else
	{
		// �t���X�N���[�����[�h�ɐ؂�ւ�
		GetWindowRect(hWnd, &g_windowRect);
		SetWindowLong(hWnd, GWL_STYLE, dwStyle & ~WS_OVERLAPPEDWINDOW);
		SetWindowPos(hWnd, HWND_TOP, 0, 0, GetSystemMetrics(SM_CXSCREEN), GetSystemMetrics(SM_CYSCREEN),
			SWP_FRAMECHANGED | SWP_NOACTIVATE);
		ShowWindow(hWnd, SW_MAXIMIZE);
	}

	g_isFullscreen = !g_isFullscreen;
}

//=============================================
//FPS�擾
//=============================================
int GetFps()
{
	return g_nCntFPS;
}
