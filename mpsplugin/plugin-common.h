#ifndef _PLUGINCOMMON_H
#define _PLUGINCOMMON_H
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "mpsapi.h"
#include "usclasses.h"
#include "usfunc.h"
typedef struct 
{
    const char * region;
	float Min;
	float Max;
	bool  Vib;
	float SinVal;
	OpcMP_Float OldValue;
	USString OldString;
} my_tagdata;

typedef struct {
    void * oid2var;
} my_plugin_data;
void read_one_variable(OpcMP_plugin_t * plugin,struct variable_list * vars,OpcMP_tag_t *tag);
OpcMP_status_t  simulate(OpcMP_plugin_t * plugin,USList *variables);
bool WriteTagToHDA(OpcMP_plugin_t *Plugin,OpcMP_tag_t *Tag);
#endif
