// pcls_info.c
#include "pcls_info.h"
#include "system.h"

void PCLS_INFO_Initialize(void) {
    // allocate memory for PCLS info
    pclsInfo = (PCLSInfo*) malloc(sizeof(PCLSInfo)); 
}

