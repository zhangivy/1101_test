#ifndef  _MAKE_LOG_H_
#define  _MAKE_LOG_H
#include "pthread.h"


#ifndef _LOG
#define LOG(module_name, proc_name, x...) \
        do{ \
		dumpmsg_to_file(module_name, proc_name, __FILE__, __LINE__, __FUNCTION__, ##x);\
	}while(0)
#else
#define LOG(module_name, proc_name, x...)
#endif

extern pthread_mutex_t ca_log_lock;

#endif
