#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "usclasses.h"
#include "usfunc.h"
#include "mpsapi.h"
#include "plugin-common.h"
#include "math.h"
OpcMP_status_t  simulate(OpcMP_plugin_t * plugin,USList *variables)
{
	  float sinval = 0;
	  float delta  = 0.05;

	//my_plugin_data  * data = (my_plugin_data*)OpcMP_plugin_data_get( plugin );	
	int status = 0;
	int countforpdu =0;
Repeat:
	for(int i=0;i < variables->count();i++) 
	{
      const char * varname = NULL;
      OpcMP_tag_t *tag = (OpcMP_tag_t *)variables->getItem(i);
	  my_tagdata * tagdata = (my_tagdata *)mps_getTagData(tag);

	  if(tagdata == NULL)
		  continue;
	  OpcMP_Boolean HDAMode, HDATypeRecord;
	  OpcMP_UInt32 HDACountRecord;
	  OpcMP_Boolean IsHda = mps_getTagHDA(tag, &HDAMode, &HDATypeRecord, &HDACountRecord);
	  OpcMP_Boolean NeedHDA = false;
	  if (IsHda){
		  if (HDAMode == OPCMP_HDAMODEMANUAL){
			  NeedHDA = true;
		  }
		  else
			  NeedHDA = false;
	  }
#define OPCMP_HDAMODEAUTOMATIC    true
#define OPCMP_HDAMODEMANUAL       false
#define OPCMP_HDARECORDEVERYCYCLE false
#define OPCMP_HDARECORDBYCHANGE   true

      if (strcmp(tagdata->region, "My") == 0)
      {
          mps_setTagAsString(tag, "Hello Word!!");
      }
      else
	  if(strcmp(tagdata->region,"SAW")==0)
	  {
        mps_setTagAsFloat(tag, 500);
	  }
	  else
	  if(strcmp(tagdata->region,"SIN")==0)
	  {
  	   	  float val = mps_getTagAsFloat(tag);
		  if(val > 3.1415926*2)
			  tagdata->SinVal = 0;
		  val = sin(tagdata->SinVal)*10;
		  mps_setTagAsFloat(tag,val);
		  tagdata->SinVal = tagdata->SinVal + delta;
	  }
	  else
	  if(strcmp(tagdata->region,"VIB")==0)
	  {
  	   	  bool val = mps_getTagAsBoolean(tag);
		  if(tagdata->Vib == true)
		  {
			tagdata->Vib = false;
			mps_setTagAsBoolean(tag,false);
		  }
		  else
		  {
			tagdata->Vib = true;
			mps_setTagAsBoolean(tag,true);
		  }
	  }
	  else
	  if(strcmp(tagdata->region,"STRINGCONST")==0)
	  {
		  if (NeedHDA){
			  char *s = mps_getTagAsString(tag);
			  if (HDATypeRecord == OPCMP_HDARECORDEVERYCYCLE){
				  WriteTagToHDA(plugin, tag);
				  if (s != NULL)
					  mps_free(plugin, s);
			  }
			  else{
				  if (s != NULL){
					  if (tagdata->OldString.length() != 0){
						  if (strcmp(s, tagdata->OldString.getChars()) != 0){
							  WriteTagToHDA(plugin, tag);
						  }
					  }
					  else{
						  WriteTagToHDA(plugin, tag);
					  }
					  tagdata->OldString = s;
					  mps_free(plugin, s);
				  }

			  };
			  mps_setTagQwality(tag, OPCMP_QUALITY_GOOD);
		  }
		  else
			  mps_setTagQwality(tag, OPCMP_QUALITY_GOOD);
	  }
	  else
	  if(strcmp(tagdata->region,"ANALCONST")==0)
	  {
		  if (NeedHDA){
			  float f = mps_getTagAsFloat(tag);
			  if (HDATypeRecord == OPCMP_HDARECORDEVERYCYCLE){
				  WriteTagToHDA(plugin, tag);
			  }
			  else{
				  if (f != tagdata->OldValue){
					  WriteTagToHDA(plugin, tag);
				  }
				  tagdata->OldValue = f;
			  };
			  mps_setTagQwality(tag, OPCMP_QUALITY_GOOD);
		  }
		  else
			  mps_setTagQwality(tag, OPCMP_QUALITY_GOOD);

	  }

	}
  return OPCMP_SUCCESS;
};
	bool WriteTagToHDA(OpcMP_plugin_t *Plugin,OpcMP_tag_t *Tag)
	{
		int result;
		char WorkBuf[2048];	
		char WorkBufRecv[2048];	
		mps_writetohda_t writetohda;
		if(Plugin  == NULL)
			return -1;
		writetohda = mps_getWriteToHda(Plugin);
		if(writetohda == NULL)
			return false;
		return writetohda(Plugin,Tag);
	};
