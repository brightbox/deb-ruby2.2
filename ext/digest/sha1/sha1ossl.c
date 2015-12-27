/* $Id: sha1ossl.c 52743 2015-11-24 16:09:58Z nagachika $ */

#include "../defs.h"
#include "sha1ossl.h"

void
SHA1_Finish(SHA1_CTX *ctx, char *buf)
{
	SHA1_Final((unsigned char *)buf, ctx);
}
