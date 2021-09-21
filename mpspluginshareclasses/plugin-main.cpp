#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "mpsapi.h"
/* GENERATOR PLUGIN METHODS */
extern "C" OPCMP_PLUGIN_EXPORT OpcMP_plugin_info_t * OPCMP_PLUGIN_CREATE( void * pool );
extern "C" OPCMP_PLUGIN_EXPORT OpcMP_status_t OPCMP_PLUGIN_INIT( OpcMP_plugin_t * plugin );
extern "C" OPCMP_PLUGIN_EXPORT OpcMP_status_t OPCMP_PLUGIN_RUN( OpcMP_plugin_t * plugin );
extern "C" OPCMP_PLUGIN_EXPORT OpcMP_status_t OPCMP_PLUGIN_READ( OpcMP_plugin_t * plugin );
extern "C" OPCMP_PLUGIN_EXPORT OpcMP_status_t OPCMP_PLUGIN_SLAVEPROCESSING( OpcMP_plugin_t * plugin );
extern "C" OPCMP_PLUGIN_EXPORT OpcMP_status_t OPCMP_PLUGIN_WRITE( OpcMP_plugin_t * plugin );
extern "C" OPCMP_PLUGIN_EXPORT OpcMP_status_t OPCMP_PLUGIN_CLOSE( OpcMP_plugin_t * plugin );
extern OpcMP_plugin_info_t *PLUGIN_CREATE(void * data);
#define OPCMP_PLUGINIS_USERS	2048
OpcMP_plugin_info_t *OPCMP_PLUGIN_CREATE(void * data )
{
	OpcMP_plugin_info_t *Plugin = PLUGIN_CREATE(data); 
	return Plugin;
}

extern OpcMP_status_t PLUGIN_INIT( OpcMP_plugin_t * plugin );
OpcMP_status_t OPCMP_PLUGIN_INIT( OpcMP_plugin_t * plugin )
{
	return PLUGIN_INIT(plugin);
}

OpcMP_status_t OPCMP_PLUGIN_RUN( OpcMP_plugin_t * plugin )
{
    return OPCMP_SUCCESS;
}
extern OpcMP_status_t PLUGIN_READ( OpcMP_plugin_t * plugin );
OpcMP_status_t OPCMP_PLUGIN_READ( OpcMP_plugin_t * plugin )
{
	return PLUGIN_READ(plugin );
};
extern OpcMP_status_t PLUGIN_WRITE( OpcMP_plugin_t * plugin );
OpcMP_status_t OPCMP_PLUGIN_WRITE( OpcMP_plugin_t * plugin )
{
	return PLUGIN_WRITE(plugin );
};
extern OpcMP_status_t PLUGIN_CLOSE( OpcMP_plugin_t * plugin );
OpcMP_status_t OPCMP_PLUGIN_CLOSE( OpcMP_plugin_t * plugin )
{
	return  PLUGIN_CLOSE(plugin);
}
extern OpcMP_status_t PLUGIN_SLAVEPROCESSING( OpcMP_plugin_t * plugin );
OpcMP_status_t OPCMP_PLUGIN_SLAVEPROCESSING( OpcMP_plugin_t * plugin )
{
	return PLUGIN_SLAVEPROCESSING(plugin );
};
