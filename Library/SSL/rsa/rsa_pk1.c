/* crypto/rsa/rsa_pk1.c */
/* Copyright (C) 1995-1998 Eric Young (eay@cryptsoft.com)
 * All rights reserved.
 *
 * This package is an SSL implementation written
 * by Eric Young (eay@cryptsoft.com).
 * The implementation was written so as to conform with Netscapes SSL.
 * 
 * This library is free for commercial and non-commercial use as long as
 * the following conditions are aheared to.  The following conditions
 * apply to all code found in this distribution, be it the RC4, RSA,
 * lhash, DES, etc., code; not just the SSL code.  The SSL documentation
 * included with this distribution is covered by the same copyright terms
 * except that the holder is Tim Hudson (tjh@cryptsoft.com).
 * 
 * Copyright remains Eric Young's, and as such any Copyright notices in
 * the code are not to be removed.
 * If this package is used in a product, Eric Young should be given attribution
 * as the author of the parts of the library used.
 * This can be in the form of a textual message at program startup or
 * in documentation (online or textual) provided with the package.
 * 
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 * 3. All advertising materials mentioning features or use of this software
 *    must display the following acknowledgement:
 *    "This product includes cryptographic software written by
 *     Eric Young (eay@cryptsoft.com)"
 *    The word 'cryptographic' can be left out if the rouines from the library
 *    being used are not cryptographic related :-).
 * 4. If you include any Windows specific code (or a derivative thereof) from 
 *    the apps directory (application code) you must include an acknowledgement:
 *    "This product includes software written by Tim Hudson (tjh@cryptsoft.com)"
 * 
 * THIS SOFTWARE IS PROVIDED BY ERIC YOUNG ``AS IS'' AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED.  IN NO EVENT SHALL THE AUTHOR OR CONTRIBUTORS BE LIABLE
 * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS
 * OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
 * LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY
 * OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF
 * SUCH DAMAGE.
 * 
 * The licence and distribution terms for any publically available version or
 * derivative of this code cannot be changed.  i.e. this code cannot simply be
 * copied and put under another distribution licence
 * [including the GNU Public Licence.]
 */

#ifndef COMPILE_OPTION_HOST_SERVICE_ONLY

#ifdef __GEOS__
#include <Ansi/stdio.h>
#else
#include <stdio.h>
#endif
#include "cryptlib.h"
#include "bn.h"
#include "rsa.h"
#include "rand.h"

#ifndef NOPROTO
int RSA_padding_add_PKCS1_type_1();
int RSA_padding_check_PKCS1_type_1();
int RSA_padding_add_PKCS1_type_2();
int RSA_padding_check_PKCS1_type_2();
int RSA_padding_add_SSLv23();
int RSA_padding_check_SSLv23();
int RSA_padding_add_none();
int RSA_padding_check_none();

#endif

int RSA_padding_add_PKCS1_type_1(to,tlen,from,flen)
unsigned char *to;
int tlen;
unsigned char *from;
int flen;
	{
	int j;
	unsigned char *p;

	if (flen > (tlen-11))
		{
		RSAerr(RSA_F_RSA_PADDING_ADD_PKCS1_TYPE_1,RSA_R_DATA_TOO_LARGE_FOR_KEY_SIZE);
		return(0);
		}
	
	p=(unsigned char *)to;

	*(p++)=0;
	*(p++)=1; /* Private Key BT (Block Type) */

	/* padd out with 0xff data */
	j=tlen-3-flen;
	memset(p,0xff,j);
	p+=j;
	*(p++)='\0';
	memcpy(p,from,(unsigned int)flen);
	return(1);
	}

int RSA_padding_check_PKCS1_type_1(to,tlen,from,flen)
unsigned char *to;
int tlen;
unsigned char *from;
int flen;
	{
	int i,j;
	unsigned char *p;

	p=from;
	if (*(p++) != 01)
		{
		RSAerr(RSA_F_RSA_PADDING_CHECK_PKCS1_TYPE_1,RSA_R_BLOCK_TYPE_IS_NOT_01);
		return(-1);
		}

	/* scan over padding data */
	j=flen-1; /* one for type. */
	for (i=0; i<j; i++)
		{
		if (*p != 0xff) /* should decrypt to 0xff */
			{
			if (*p == 0)
				{ p++; break; }
			else	{
				RSAerr(RSA_F_RSA_PADDING_CHECK_PKCS1_TYPE_1,RSA_R_BAD_FIXED_HEADER_DECRYPT);
				return(-1);
				}
			}
		p++;
		}

	if (i == j)
		{
		RSAerr(RSA_F_RSA_PADDING_CHECK_PKCS1_TYPE_1,RSA_R_NULL_BEFORE_BLOCK_MISSING);
		return(-1);
		}

	if (i < 8)
		{
		RSAerr(RSA_F_RSA_PADDING_CHECK_PKCS1_TYPE_1,RSA_R_BAD_PAD_BYTE_COUNT);
		return(-1);
		}
	i++; /* Skip over the '\0' */
	j-=i;
	memcpy(to,p,(unsigned int)j);

	return(j);
	}

int RSA_padding_add_PKCS1_type_2(to,tlen,from,flen)
unsigned char *to;
int tlen;
unsigned char *from;
int flen;
	{
	int i,j;
	unsigned char *p;
	
	if (flen > (tlen-11))
		{
		RSAerr(RSA_F_RSA_PADDING_ADD_PKCS1_TYPE_2,RSA_R_DATA_TOO_LARGE_FOR_KEY_SIZE);
		return(0);
		}
	
	p=(unsigned char *)to;

	*(p++)=0;
	*(p++)=2; /* Public Key BT (Block Type) */

	/* pad out with non-zero random data */
	j=tlen-3-flen;

	RAND_bytes(p,j);
	for (i=0; i<j; i++)
		{
		if (*p == '\0')
			do	{
				RAND_bytes(p,1);
				} while (*p == '\0');
		p++;
		}

	*(p++)='\0';

	memcpy(p,from,(unsigned int)flen);
	return(1);
	}

int RSA_padding_check_PKCS1_type_2(to,tlen,from,flen)
unsigned char *to;
int tlen;
unsigned char *from;
int flen;
	{
	int i,j;
	unsigned char *p;

	p=from;
	if (*(p++) != 02)
		{
		RSAerr(RSA_F_RSA_PADDING_CHECK_PKCS1_TYPE_2,RSA_R_BLOCK_TYPE_IS_NOT_02);
		return(-1);
		}

	/* scan over padding data */
	j=flen-1; /* one for type. */
	for (i=0; i<j; i++)
		if (*(p++) == 0) break;

	if (i == j)
		{
		RSAerr(RSA_F_RSA_PADDING_CHECK_PKCS1_TYPE_2,RSA_R_NULL_BEFORE_BLOCK_MISSING);
		return(-1);
		}

	if (i < 8)
		{
		RSAerr(RSA_F_RSA_PADDING_CHECK_PKCS1_TYPE_2,RSA_R_BAD_PAD_BYTE_COUNT);
		return(-1);
		}
	i++; /* Skip over the '\0' */
	j-=i;
	memcpy(to,p,(unsigned int)j);

	return(j);
	}

#endif
