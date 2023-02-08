// dllmain.cpp : Defines the entry point for the DLL application.
#include "gms.h"
#include "InterfaceLoading.h"
#include <iostream>
// This function is polled by the process during execution
using namespace std;


typedef IYYC_Callback* (*gI)();
gI getImplementation = NULL;
bool initialized = false;
const char* PLUGIN_NAME = "TEST";

gmx double init(const char* loaderpath) // TODO: use the loaderpath arg and change to init seperately
{
    if(initialized)
    {
        cout << "Plugin " << PLUGIN_NAME << " already initialized." << endl;
        return 1.0;
    }
    cout << "Hello from plugin init!"<<endl;

    HMODULE hmod = LoadLibraryA(loaderpath);
    if(!hmod)
    {
        cout << "Plugin " << PLUGIN_NAME << ": Could not get HMODULE." <<endl;
    }

    getImplementation = (gI)GetProcAddress(hmod, "getImplementation");

    if(getImplementation == NULL)
    {
        cout << "Plugin " << PLUGIN_NAME << ": Could not GetProcAddress."<<endl;
    }

    initialized = true;
    cout << "Successfully initialized Plugin " << PLUGIN_NAME << endl;
    return 1.0;
}

gmx double call(double arg)
{
    if(!initialized)// WRONG
    {
        return 0.0;
    }

    cout << "called plugin with arg "<<arg << endl;
	IYYC_Callback* impl = getImplementation();
	cout << "setting data.." << endl;
	impl->setData(PLUGIN_NAME, "0", "amogu");

	cout << "end." << endl;
	return arg;
}

