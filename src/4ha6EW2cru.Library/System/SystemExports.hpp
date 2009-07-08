#include "ISystem.hpp"

extern "C"
{
	typedef void ( __stdcall* InitializeSystemFunction ) ( Management* management, Logger* logger );
	typedef ISystem* ( __stdcall* CreateSystemFunction ) ( );
	typedef void ( __stdcall* DestroySystemFunction ) ( ISystem* system );
};