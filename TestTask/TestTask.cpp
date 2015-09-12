#include "HgeManager.h"

int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int)
{
	if (HgeManager::Instance()->Initiate())
	{
		HgeManager::Instance()->Start();
	}
	else
	{
		HgeManager::Instance()->ThrowMassage();
	}

	HgeManager::Instance()->Release();

	return 0;
}

