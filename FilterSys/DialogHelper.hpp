#pragma once
#include "Includes.h"

namespace Ex {
    inline std::wstring OpenFileDialog(const std::vector<std::pair<std::wstring, std::wstring>>& filters) {
        HRESULT hr = CoInitializeEx(NULL, COINIT_APARTMENTTHREADED | COINIT_DISABLE_OLE1DDE);
        if (FAILED(hr)) return L"";

        IFileOpenDialog* pFileOpen;
        std::wstring filePath = L"";

        hr = CoCreateInstance(CLSID_FileOpenDialog, NULL, CLSCTX_ALL, IID_IFileOpenDialog, reinterpret_cast<void**>(&pFileOpen));

        if (SUCCEEDED(hr)) {
            std::vector<COMDLG_FILTERSPEC> fileTypes(filters.size());
            for (size_t i = 0; i < filters.size(); ++i) {
                fileTypes[i].pszName = filters[i].first.c_str();
                fileTypes[i].pszSpec = filters[i].second.c_str();
            }

            pFileOpen->SetFileTypes(static_cast<UINT>(fileTypes.size()), fileTypes.data());

            hr = pFileOpen->Show(NULL);

            if (SUCCEEDED(hr)) {
                IShellItem* pItem;
                hr = pFileOpen->GetResult(&pItem);
                if (SUCCEEDED(hr)) {
                    PWSTR pszFilePath;
                    pItem->GetDisplayName(SIGDN_FILESYSPATH, &pszFilePath);
                    filePath = pszFilePath;
                    CoTaskMemFree(pszFilePath);
                    pItem->Release();
                }
            }
            pFileOpen->Release();
        }
        CoUninitialize();
        return filePath;
    }
}