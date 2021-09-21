#include <stdio.h>
#include <stdlib.h>
#include <time.h>
//#include "config.h"
#include "mpsapi.h"
#include "usclasses.h"
#include "usfunc.h"
#include "plugin-common.h"
/* METHOD BODY */
//
// This function is called by the server to create any data of device
//
OpcMP_status_t PLUGIN_INIT( OpcMP_plugin_t * plugin )
{
	// get plugin specific data 
	int maxoids;
	const char *tmp;
	char errbuf[256];
    // blocking others threads of plugin 
	mps_mutex_lock(plugin);
	mps_DebugMessage(plugin,"plugin :init");
	// Allocates memory for own data
	my_plugin_data * data = (my_plugin_data * )mps_malloc(plugin,sizeof( my_plugin_data ) );
    // get number of device properties
	int countdevice_properties	= mps_getNumberDeviceProperties(plugin);
	//
	// mps_getDeviceProperties
	// Returns node device's properties
	//
	mps_Object	*propdevicenode = mps_getDeviceProperties(plugin);
	//
	// Put the own data into plugin
	mps_setPluginData(plugin,(void *)data);
	char rb[80];
	int counttags_properties	= mps_getNumberTagsProperties(plugin);
	// Wolking by tags properties
	for(int i=0;i<counttags_properties;i++)
	{
		mps_Object	*propnode;
		OpcMP_tag_t *tag;
	    my_tagdata *mytagdata;
        // variable to the min value 
		//get tag by number
		tag = (OpcMP_tag_t *)mps_getPluginTag(plugin,i);
		//
		// mps_getTagProperties
		// Returns the tag's properties
		//
		propnode = mps_getTagProperties(plugin,i);
        // allocate varable limits structure and fill it with defaults 
		mytagdata = (my_tagdata*)mps_malloc(plugin,sizeof( my_tagdata ) );
		// reading of property and filling the working structure
		mytagdata->region = mps_property_as_string(propnode, "_region_", "" );
		// string property must be free after work (mpsFree(mytagdata->region))
		mytagdata->Min	  = mps_property_as_int(propnode, "MIN",0);
		mytagdata->Max	  = mps_property_as_int(propnode, "MAX",10);
		mytagdata->SinVal = 0;
   		mytagdata->Vib    = false;
		mps_setTagData(tag,mytagdata);
	}
    // initialize random engine 
    // unblocking
	mps_mutex_unlock(plugin);
	return OPCMP_SUCCESS;
}
