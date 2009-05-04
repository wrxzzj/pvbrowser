#ifndef __PV_TYPES_H__
#define __PV_TYPES_H__

#ifndef PVMOD_NAME
#define PVMOD_NAME "???"
#endif

#define DD(...) fprintf(stdout, "[" PVMOD_NAME "]" __VA_ARGS__)

#endif
