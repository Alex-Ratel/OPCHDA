#include <stdio.h>
#include <stdlib.h>
#include <time.h>
//#include "config.h"
#include "mpsapi.h"
#include "plugin-common.h"
//
// This function is called by the server to read the tag's value
//

OpcMP_status_t PLUGIN_READ( OpcMP_plugin_t * plugin )
{
	int NumberTags;
	my_plugin_data * data;
	OpcMP_status_t status = OPCMP_SUCCESS;
	char errbuf[1024];
	char rb[80];
	// get plugin specific data 
	USList *readvar = NULL;
	mps_DebugMessage(plugin,"plugin :read");
	//
	// mps_getPluginData
	// Returns the device's working structure 
	//
	data			= (my_plugin_data*)mps_getPluginData( plugin );
	//
	// mps_getPluginNumberReadTags
	// Returns the driver's number tags for reading 
	//
	NumberTags = mps_getPluginNumberReadTags(plugin);
	readvar = new USList();
	for(int i=0;i < NumberTags;i++) 
	{
      const char * varname = NULL;
	  //
	  // mps_getPluginReadTag(
	  // Returns the driver's tag by number
	  //
	  OpcMP_tag_t *tag = mps_getPluginReadTag(plugin,i);
	  //
	  // mps_getTagData
	  // Returns the tag's working structure
	  //
	  my_tagdata * mytagdata = (my_tagdata *)mps_getTagData(tag);
  	  if(mytagdata == NULL)
	  {
		//
		// mps_setTagQwality
		// This function allows the qwality for tag to be set
		//
		mps_setTagQwality(tag,OPCMP_QUALITY_BAD);
		continue;
	  }
	  readvar->add(tag);
	}
    if(readvar->count() != 0)
	{
		status = simulate(plugin,readvar);
		readvar->clear();
	}
	delete readvar;
	return status;
};
