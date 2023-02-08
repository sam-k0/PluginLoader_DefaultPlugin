// dllmain.cpp : Defines the entry point for the DLL application.
#include "gms.h"
#include "InterfaceLoading.h"
#include <iostream>
// This function is polled by the process during execution
using namespace std;


typedef IYYC_Callback* (*gI)();

gI getImplementation = NULL;


gmx double init()
{
    cout << "Hello from plugin init!"<<endl;

    HMODULE hmod = LoadLibraryA("E:\\GameMaker Studio\\RegisterCallbackGM.gmx\\extensions\\Extension13\\PluginLoader.dll");

    if(!hmod)
    {
        cout << "no hmod" << endl;
    }

    getImplementation = (gI)GetProcAddress(hmod, "getImplementation");

    if(getImplementation == NULL)
    {
        cout << "Error getprocaddr"<<endl;
    }

    return 1.0;
}

gmx double call(double arg, stringToDLL loaderpath)
{
    init();

    cout << "called plugin with arg "<<arg << endl;

	IYYC_Callback* impl = getImplementation();
	cout << "setting data.." << endl;
	impl->setData("0", "amogu");
	cout << "trigger..." << endl;
	impl->trigger();
	cout << "end." << endl;
	return impl->getData();
}

