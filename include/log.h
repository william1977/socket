#ifndef _LOG_H_
#define _LOG_H_

#include <stdio.h>

#define LOG_VERBOSE  60
#define LOG_DEBUG   50
#define LOG_INFO    40
#define LOG_WARNING 30
#define LOG_ERROR   20
#define LOG_FATAL   10

#ifndef LOG_LEVEL
#define LOG_LEVEL LOG_WARNING
#endif

#if LOG_LEVEL >= LOG_VERBOSE
#define _LOGV(args...) printf(args)
#else
#define _LOGV(args...) 
#endif
#if LOG_LEVEL >= LOG_DEBUG
#define _LOGD(args...) printf(args)
#else
#define _LOGD(args...) 
#endif
#if LOG_LEVEL >= LOG_INFO
#define _LOGI(args...) printf(args)
#else
#define _LOGI(args...) 
#endif
#if LOG_LEVEL >= LOG_WARNING
#define _LOGW(args...) printf(args)
#else
#define _LOGW(args...) 
#endif
#if LOG_LEVEL >= LOG_ERROR
#define _LOGE(args...) printf(args)
#else
#define _LOGE(args...) 
#endif
#if LOG_LEVEL >= LOG_FATAL
#define _LOGF(args...) printf(args)
#else
#define _LOGF(args...) 
#endif

#define LOGV(fmt, args...) _LOGV("[V][%p:%s][%s:%d]" fmt "\n", this, __FUNCTION__, __FILE__, __LINE__, args)
#define LOGD(fmt, args...) _LOGD("[D][%p:%s][%s:%d]" fmt "\n", this, __FUNCTION__, __FILE__, __LINE__, args)
#define LOGI(fmt, args...) _LOGI("[I][%p:%s][%s:%d]" fmt "\n", this, __FUNCTION__, __FILE__, __LINE__, args)
#define LOGW(fmt, args...) _LOGW("[W][%p:%s][%s:%d]" fmt "\n", this, __FUNCTION__, __FILE__, __LINE__, args)
#define LOGE(fmt, args...) _LOGE("[E][%p:%s][%s:%d]" fmt "\n", this, __FUNCTION__, __FILE__, __LINE__, args)
#define LOGF(fmt, args...) _LOGF("[F][%p:%s][%s:%d]" fmt "\n", this, __FUNCTION__, __FILE__, __LINE__, args)

#endif  //_LOG_H_

