#include "m2tweopStarter.h"
#include <string>
#include <fstream>
#include <windows.h>
#include "helpers.h"
using namespace std;

namespace m2tweopStarter
{

	typedef void (*m2tweopInit)(const char*, int);
	typedef void (*m2tweopD3DCreate)(IDirect3DDevice9*);
	typedef void (*m2tweopEndScene)(IDirect3DDevice9*);

	typedef void (*m2tweopOnReset)(IDirect3DDevice9*, D3DPRESENT_PARAMETERS*);
	typedef void (*m2tweopAfterReset)(IDirect3DDevice9*, D3DPRESENT_PARAMETERS*);
	struct
	{
		HMODULE hmtw = nullptr;
		m2tweopEndScene onEndScene=nullptr;

		m2tweopOnReset onReset = nullptr;
		m2tweopAfterReset afterReset = nullptr;

		m2tweopInit eopInitF = nullptr;


		bool isEOP = false;

		bool isEOPipe = false;


		string modPath;
		int gameVer=0;
	}dataEOP;

	bool parsePipeMessage(const string&msg)
	{
		vector<string>args=helpers::splitString(msg, "\n");
		if (args.size() != 5)
		{
			return false;
		}

		if (args[0] != "m2tweopStartCommand")
		{
			return false;
		}

		if (args[1] != "eopModFolder:")
		{
			return false;
		}
		dataEOP.modPath = args[2];

		if (args[3] != "GameVer:")
		{
			return false;
		}

		dataEOP.gameVer = stoi(args[4]);
		return true;
	}

	void doM2TWEOP()
	{
		string resMsg = helpers::doEOPPipe(5, true);
		dataEOP.isEOPipe=parsePipeMessage(resMsg);

		if (dataEOP.isEOPipe == false)
		{
			dataEOP.isEOP = false;
			return;
		}


		string libPath = dataEOP.modPath+"\\M2TWEOPLibrary.dll";
		dataEOP.hmtw=LoadLibraryA(libPath.c_str());
		if (dataEOP.hmtw == NULL)
		{
			DWORD error = GetLastError();
			string errmsg = "Cannot load DLL: " + libPath + "\n";
			errmsg += "\nError code: " + to_string(error) + "\n";
			
			// Check if file exists
			DWORD fileAttr = GetFileAttributesA(libPath.c_str());
			if (fileAttr == INVALID_FILE_ATTRIBUTES) {
				errmsg += "File does not exist or is inaccessible\n";
			} else {
				errmsg += "File exists but failed to load\n";
			}
			
			// Common error explanations
			switch (error) {
				case 126: errmsg += "Missing dependencies or invalid DLL"; break;
				case 127: errmsg += "Procedure not found"; break;
				case 193: errmsg += "Not a valid Win32 application (architecture mismatch)"; break;
				case 2: errmsg += "File not found"; break;
				case 5: errmsg += "Access denied"; break;
				default: errmsg += "Unknown error"; break;
			}
			
			MessageBoxA(NULL, errmsg.c_str(), "DLL Load Error", MB_OK | MB_ICONERROR);
			exit(0);
		}
		dataEOP.eopInitF = (m2tweopInit)GetProcAddress(dataEOP.hmtw, "initEOP");
		if (dataEOP.eopInitF == NULL)
		{
			MessageBoxA(NULL, "Cannot find initEOP function!", "ATTENTION!", NULL);
			exit(0);
		}

		dataEOP.onEndScene = (m2tweopEndScene)GetProcAddress(dataEOP.hmtw, "onEndScene");
		if (dataEOP.onEndScene == NULL)
		{
			MessageBoxA(NULL, "Cannot find onEndScene function!", "ATTENTION!", NULL);
			exit(0);
		}
		
		dataEOP.onReset = (m2tweopOnReset)GetProcAddress(dataEOP.hmtw, "onReset");
		if (dataEOP.onReset == NULL)
		{
			MessageBoxA(NULL, "Cannot find onReset function!", "ATTENTION!", NULL);
			exit(0);
		}		

		dataEOP.afterReset = (m2tweopAfterReset)GetProcAddress(dataEOP.hmtw, "afterReset");
		if (dataEOP.afterReset == NULL)
		{
			MessageBoxA(NULL, "Cannot find afterReset function!", "ATTENTION!", NULL);
			exit(0);
		}


		dataEOP.eopInitF(dataEOP.modPath.c_str(),dataEOP.gameVer);
		dataEOP.isEOP = true;
	}

	void onCreateDevice(IDirect3DDevice9* pDevice)
	{
		doM2TWEOP();
		if (dataEOP.isEOP == false)
		{
			return;
		}
		m2tweopD3DCreate eopD3DCreate = (m2tweopD3DCreate)GetProcAddress(dataEOP.hmtw, "onCreateDevice");
		if (eopD3DCreate == NULL)
		{
			MessageBoxA(NULL, "Cannot find onCreateDevice M2TWEOP function!", "ATTENTION!", NULL);
			exit(0);
		}

		eopD3DCreate(pDevice);
	}

	void onEndScene(IDirect3DDevice9* pDevice)
	{
		if (dataEOP.isEOP == false)
		{
			return;
		}
		dataEOP.onEndScene(pDevice);
	}

	void onReset(IDirect3DDevice9* pDevice, D3DPRESENT_PARAMETERS* pPresentationParameters)
	{
		if (dataEOP.isEOP == false)
		{
			return;
		}
		dataEOP.onReset(pDevice, pPresentationParameters);
	}

	void afterReset(IDirect3DDevice9* pDevice, D3DPRESENT_PARAMETERS* pPresentationParameters)
	{
		if (dataEOP.isEOP == false)
		{
			return;
		}
		dataEOP.afterReset(pDevice, pPresentationParameters);
	}

};

