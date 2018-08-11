/*
 * ecdsa.cpp
 *
 *  Created on: 09/08/2018
 *      Author: manue
 */


// using figures on: https://en.bitcoin.it/wiki/Technical_background_of_version_1_Bitcoin_addresses
// gcc -Wall ecdsapubkey.c -o ecdsapubkey -lcrypto
#include "ecdsa.h"
#include <stdio.h>
#include <stdlib.h>
#include <openssl/ec.h>
#include <openssl/obj_mac.h>
#include <openssl/bn.h>
#include <openssl/aes.h>
#include <iostream>
#include <string>
#include <cstdio>
#include <cstdlib>


ecdsa::ecdsa() {

}

//ecdsa::getpubkey(std::string *privKey)
//{
//     EC_KEY *eckey = NULL;
//     EC_POINT *pub_key = NULL;
//     const EC_GROUP *group = NULL;
//     BIGNUM start;
//     BIGNUM *res;
//     BN_CTX *ctx;
//
//     BN_init(&start);
//     ctx = BN_CTX_new(); // ctx is an optional buffer to save time from allocating and deallocating memory whenever required
//
//     res = &start;
////     BN_hex2bn(&res,"3D79F601620A6D05DB7FED883AB8BCD08A9101B166BC60166869DA5FC08D936E");
//   //  BN_hex2bn(&res,"18E14A7B6A307F426A94F8114701E7C8E774E7F9A47E2C2035DB29A206321725");
//       BN_hex2bn(&res, privKey);
//
//     eckey = EC_KEY_new_by_curve_name(NID_secp256k1);
//     group = EC_KEY_get0_group(eckey);
//     pub_key = EC_POINT_new(group);
//
//     EC_KEY_set_private_key(eckey, res);
//
//     /* pub_key is a new uninitialized `EC_POINT*`.  priv_key res is a `BIGNUM*`. */
//     if (!EC_POINT_mul(group, pub_key, res, NULL, NULL, ctx))
//       printf("Error at EC_POINT_mul.\n");
//
////     assert(EC_POINT_bn2point(group, &res, pub_key, ctx)); // Null here
//
//     EC_KEY_set_public_key(eckey, *pub_key);
//
//     char *cc = EC_POINT_point2hex(group, pub_key, 4, ctx);
//
//     char *c=cc;
//
//     int i;
//    std::string pubkey;
//     for (i=0; i<130; i++) // 1 byte 0x42, 32 bytes for X coordinate, 32 bytes for Y coordinate
//     {
//    	 pubkey+=*c++;
//
//     }
//      return pubkey;
// }


ecdsa::encrypt(string &filename,string &privkey)
{



/* ... */

  int bytes_read, bytes_written;
  unsigned char indata[AES_BLOCK_SIZE];
  unsigned char outdata[AES_BLOCK_SIZE];

  /* ckey and ivec are the two 128-bits keys necesary to
     en- and recrypt your data.  Note that ckey can be
     192 or 256 bits as well */
  unsigned char ckey[] =  privkey;
  unsigned char ivec[] = privkey;

  /* data structure that contains the key itself */
  AES_KEY key;

  /* set the encryption key */
  AES_set_encrypt_key(ckey, 256, &key);

  /* set where on the 128 bit encrypted block to begin encryption*/
  int num = 0;

  *ifp = fopen(filename, "rb");


  filename->insert(filename->size()-5, 1 , "EN" );

  FILE *ofp = fopen(filename, "wb");

  while (1) {
    bytes_read = fread(indata, 1, AES_BLOCK_SIZE, ifp);

    AES_cfb256_encrypt(indata, outdata, bytes_read, &key, ivec, &num,
           AES_ENCRYPT);

    bytes_written = fwrite(outdata, 1, bytes_read, ofp);
    if (bytes_read < AES_BLOCK_SIZE)
  break;
  }
}


}

ecdsa::decrypt(string &filename,string &privkey)
{


	/* ... */

	  int bytes_read, bytes_written;
	  unsigned char indata[AES_BLOCK_SIZE];
	  unsigned char outdata[AES_BLOCK_SIZE];

	  /* ckey and ivec are the two 128-bits keys necesary to
	     en- and recrypt your data.  Note that ckey can be
	     192 or 256 bits as well */
	  unsigned char ckey[] =  privkey;
	  unsigned char ivec[] = privkey;

	  /* data structure that contains the key itself */
	  AES_KEY key;

	  /* set the encryption key */
	  AES_set_encrypt_key(ckey, 256, &key);

	  /* set where on the 128 bit encrypted block to begin encryption*/
	  int num = 0;

	  *ifp = fopen(filename, "rb");

	  filename->insert(filename->size() - 5, 1 , "DE" );

	  FILE *ofp = fopen(filename, "wb");

	  while (1) {
	    bytes_read = fread(indata, 1, AES_BLOCK_SIZE, ifp);

	    AES_cfb256_encrypt(indata, outdata, bytes_read, &key, ivec, &num,
	           AES_DECRYPT);

	    bytes_written = fwrite(outdata, 1, bytes_read, ofp);
	    if (bytes_read < AES_BLOCK_SIZE)
	  break;
	  }

}


}
