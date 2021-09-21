#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "usclasses.h"
#include "usfunc.h"
#include "mpsapi.h"
#include "plugin-common.h" 
//
// This function is called by the server to halt and delete any data of device
//
OpcMP_status_t PLUGIN_CLOSE( OpcMP_plugin_t * plugin )
{
 	my_plugin_data * data = (my_plugin_data*)mps_getPluginData( plugin );
	mps_free(plugin,(void *)data);
	int NumberTags = mps_getPluginNumberTags(plugin);
	for(int i=0;i < NumberTags;i++) 
	{
     OpcMP_tag_t *tag = (OpcMP_tag_t *)mps_getPluginTag(plugin,i);
 	 
	 my_tagdata * tagdata = (my_tagdata *)mps_getTagData(tag);
	 if(tagdata != NULL)	 	 
	 {
	 if(tagdata->region != NULL)
		 	 mps_free(plugin,(void *)tagdata->region);
	 mps_free(plugin,(void *)tagdata);
	 }
	}
 if( mps_isEnabledDebugMessages(plugin) )
 {
  mps_Message(plugin,"plugin :close");
 }
 return OPCMP_SUCCESS;
}
