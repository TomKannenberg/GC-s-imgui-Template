#pragma once

#include <d3d9.h>
#include <d3dx9.h>
#include <imgui.h>
#include <imgui_impl_win32.h>
#include <imgui_impl_dx9.h>

#include <Windows.h>
#include <dwmapi.h>
#include <iostream>
#include <string>

#include "gfont.hpp"

#pragma comment(lib, "d3d9.lib")
#pragma comment(lib, "d3dx9.lib")
#pragma comment(lib, "imgui.lib")
#pragma comment(lib, "dwmapi.lib")

extern IMGUI_IMPL_API LRESULT ImGui_ImplWin32_WndProcHandler(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);
LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam);
void SetRoundedEdges(HWND hwnd, int width, int height);
void ResetDevice();

namespace Gui {
    static ImVec2 Size = { 500 , 370 };
}

static IDirect3DDevice9* pDevice = nullptr;
static D3DPRESENT_PARAMETERS d3dpp = {};

class gcGui {

	public:
        gcGui(std::string pname, std::string version, bool* done);
        ~gcGui();
        void initHWND();

        void Initialize();
        void Render();
        void Shutdown();

        float menucolor[4] = { 0.204f, 0.000f, 0.990f };
        RECT rc;
        HWND hwnd;

    private:

        std::string name = "";

        ImFont* medium;
        ImFont* semibold;

        ImTextureID        LogoI = NULL;
        ImTextureID        ExitLogoI = NULL;
        ImTextureID        ExitLogoII = NULL;
        LPDIRECT3DTEXTURE9 newTexture = NULL;

        void cSprite(IDirect3DDevice9* m_pD3Ddev, LPWSTR szFilePath) {
            D3DXIMAGE_INFO pInfo;

            ZeroMemory(&pInfo, sizeof(D3DXIMAGE_INFO));
            D3DXGetImageInfoFromFile(szFilePath, &pInfo);

            if (FAILED(D3DXCreateTextureFromFileEx(m_pD3Ddev, szFilePath, pInfo.Width, pInfo.Height,
                pInfo.MipLevels, NULL, pInfo.Format, D3DPOOL_MANAGED, D3DX_DEFAULT, NULL, NULL,
                NULL, NULL, &newTexture)))
                MessageBox(NULL, L"Cannot create image texture", L"Error", MB_ICONERROR);

        }

        ImVec4 c1(const double& r, const double& b, const double& g, const double& a) {
            return ImVec4(r / 256, b / 256, g / 256, a / 256);
        }

        const ImVec4 purple = c1(83, 82, 237, 64);
        const ImVec4 purple2 = c1(83 * 1.1, 82 * 1.1, 237 * 1.1, 96);
        const ImVec4 purple3 = c1(83 * 1.08, 82 * 1.08, 237 * 1.08, 140);

        ImVec2 cp;

        bool* done;
        bool inBox = false;

        bool wasDragged = false;
        bool mouseRecent = false;
        POINT cursorpos;
        DWORD lastTime;
        DWORD doubleClickTime = GetDoubleClickTime();
        POINT lastMousePos;

        void CreateDeviceObjects();
        void InvalidateDeviceObjects();

        void FrontEnd();
        void UpdateWindowLocation();
        void windowMove();
        bool isInsideBox(const ImVec2& cursorpos);

        void RenderBlur();
};
