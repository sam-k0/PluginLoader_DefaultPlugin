#include "gms.h"
#include "InterfaceLoading.h"
#include <iostream>

using namespace std;
// Typedefs and constants for easier understanding
#define PLUGIN_NOT_INITIALIZED 0.0
#define PLUGIN_SUCCESS 1.0
typedef double PLUGIN_RESULT;

// The function pointer for allocating the interface (IYYC_Callback)
typedef IYYC_Callback* (*gI)();
gI getImplementation = NULL;

// Global plugin variables needed to function
IYYC_Callback* gYYC_CallbackHandler = NULL; // the "connection" to the plugin loader
string         gPluginName          = NULL; // the ID-Name as which the loader knows this plugin. DO NOT CHANGE THIS MANUALLY!
bool           gInitialized         = false;// a simple boolean that gets set to true if the init() method ran successfully

/** \brief This method gets called only once upon initializing the plugin. Do not call this method manually.
 *
 * \param loaderpath The full filepath of the PluginLoader.dll
 * \param pluginName The plugin name set by the PluginLoader. Do not change this manually.
 * \return Wether the plugin was loaded successfully.
 *
 */
gmx PLUGIN_RESULT init(const char* loaderpath, const char* pluginName)
{
    gPluginName = gmu::string_to_constcharptr(pluginName); // convert the name to a string for easier use
    if(gInitialized) //If the plugin is already initialized return with no error. Usually this method shouldn't be called twice.
    {
        cout << "Plugin " << gPluginName << " already initialized." << endl;
        return PLUGIN_SUCCESS;
    }
    cout << "Hello from plugin init!"<<endl;

    HMODULE hmod = LoadLibraryA(loaderpath); // Load the parent PluginLoader.dll
    if(!hmod)
    {
        cout << "Plugin " << gPluginName << ": Could not get HMODULE." <<endl;
        return PLUGIN_NOT_INITIALIZED;
    }

    getImplementation = (gI)GetProcAddress(hmod, "getImplementation"); // Get a reference to the getImplementation method

    if(getImplementation == NULL) // failed to get the implementation method.
    {
        cout << "Plugin " << gPluginName << ": Could not GetProcAddress."<<endl;
        return PLUGIN_NOT_INITIALIZED;
    }

    gYYC_CallbackHandler = getImplementation(); // Allocate the interface pointer to actually communicate this Plugin <--> PluginLoader
    gInitialized = true;                        // Set the flag to true
    cout << "Successfully initialized Plugin " << gPluginName << endl;
    return PLUGIN_SUCCESS;
}


/** \brief This method gets called periodically by the host application (the PluginLoader) to update the plugin.
 *
 * \param arg The host can pass for example the step time. The game runs with 60fps, so this value can range from 0.0 - 60.0
 * \return The exit code of this plugin for this frame. If it doesnt return PLUGIN_SUCCESS, the Loader might eject this plugin to prevent a crash.
 *
 */
gmx PLUGIN_RESULT call(double arg)
{
    if(!gInitialized) // If not initialized, don't go further.
    {
        return PLUGIN_NOT_INITIALIZED;
    }

    cout << "Called plugin with arg: "<< arg << endl;
    // Set some data to this plugin's storage (dsMap).
	gYYC_CallbackHandler->setData(gmu::string_to_constcharptr(gPluginName), "amogu", "amogu");
	cout << "Exiting plugin call." << endl;
	return PLUGIN_SUCCESS;
}

