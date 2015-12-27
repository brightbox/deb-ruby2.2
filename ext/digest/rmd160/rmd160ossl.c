/* $Id: rmd160ossl.c 52743 2015-11-24 16:09:58Z nagachika $ */

#include "../defs.h"
#include "rmd160ossl.h"

void RMD160_Finish(RMD160_CTX *ctx, char *buf) {
	RIPEMD160_Final((unsigned char *)buf, ctx);
}
