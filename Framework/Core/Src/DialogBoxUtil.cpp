#include "Precompiled.h"
#include "DialogBoxUtil.h"

bool Omega::Core::OpenFileDialog(char fileName[MAX_PATH], const char* title, const char* filter)
{
	bool result = false;
	if (HRESULT hr = CoInitializeEx(NULL, COINIT_APARTMENTTHREADED | COINIT_DISABLE_OLE1DDE); 
		SUCCEEDED(hr))
	{
		IFileOpenDialog* pFileOpen = nullptr;

		// Create the FileOpenDialog object.
		hr = CoCreateInstance(CLSID_FileOpenDialog, NULL, CLSCTX_ALL,
			IID_IFileOpenDialog, reinterpret_cast<void**>(&pFileOpen));

		if (SUCCEEDED(hr))
		{
			wchar_t wtext[20]{};
			// convert a character string to a wide-character string with additional safety checks
			size_t outSize;
			mbstowcs_s(&outSize, wtext, filter, strnlen_s(filter, 5) + 1); //Plus null
			COMDLG_FILTERSPEC ComDlgFS[2] = { {L"Text Document (*.txt)", wtext }, {L"No Filter", L"*.*"} };
			pFileOpen->SetFileTypes(2, ComDlgFS);

			mbstowcs_s(&outSize, wtext, title, strlen(title) + 1); //Plus null
			pFileOpen->SetTitle(wtext);
			// Show the Open dialog box.
			hr = pFileOpen->Show(0);
			// Get the file name from the dialog box.
			if (SUCCEEDED(hr))
			{
				IShellItem* pItem;
				hr = pFileOpen->GetResult(&pItem);
				if (SUCCEEDED(hr))
				{
					PWSTR pszFilePath;
					hr = pItem->GetDisplayName(SIGDN_FILESYSPATH, &pszFilePath);

					// Display the file name to the user.
					if (SUCCEEDED(hr))
					{
						// convert wide-character to char
						wcstombs_s(&outSize, fileName, MAX_PATH, pszFilePath, static_cast<size_t>(lstrlenW(pszFilePath)));
						CoTaskMemFree(pszFilePath);
						result = true;
					}
					pItem->Release();
				}
			}
			pFileOpen->Release();
		}
		CoUninitialize();
	}
	return result;

}

bool Omega::Core::SaveFileDialog(char fileName[MAX_PATH], const char* title, const char* filter)
{
	bool result = false;
	if (HRESULT hr = CoInitializeEx(NULL, COINIT_APARTMENTTHREADED | COINIT_DISABLE_OLE1DDE);
		SUCCEEDED(hr))
	{
		IFileSaveDialog* pFileSave = nullptr;

		// Create the FileOpenDialog object.
		hr = CoCreateInstance(CLSID_FileSaveDialog, NULL, CLSCTX_ALL,
			IID_IFileSaveDialog, reinterpret_cast<void**>(&pFileSave));
		if (SUCCEEDED(hr))
		{
			if (SUCCEEDED(hr))
			{
				wchar_t wtext[20]{};
				// convert a character string to a wide-character string with additional safety checks
				size_t outSize;
				mbstowcs_s(&outSize, wtext, filter, strnlen_s(filter, 5) + 1); //Plus null
				COMDLG_FILTERSPEC ComDlgFS[2] = { {L"Text Document (*.txt)", wtext }, {L"No Filter", L"*.*"} };
				pFileSave->SetFileTypes(2, ComDlgFS);

				mbstowcs_s(&outSize, wtext, title, strlen(title) + 1); //Plus null
				pFileSave->SetTitle(wtext);
				// Show the Open dialog box.
				hr = pFileSave->Show(0);

				// Get the file name from the dialog box.
				if (SUCCEEDED(hr))
				{
					IShellItem* pItem;
					hr = pFileSave->GetResult(&pItem);
					if (SUCCEEDED(hr))
					{
						PWSTR pszFilePath;
						hr = pItem->GetDisplayName(SIGDN_FILESYSPATH, &pszFilePath);
						// Display the file name to the user.
						if (SUCCEEDED(hr))
						{
							wcstombs_s(&outSize, fileName, MAX_PATH, pszFilePath, static_cast<size_t>(lstrlenW(pszFilePath)));
							CoTaskMemFree(pszFilePath);
							result = true;
						}
						pItem->Release();
					}
				}
				pFileSave->Release();
			}
		}
		CoUninitialize();
	}
	return result;
}
