#include <stdlib.h>
#include <openssl/evp.h>
#include <string.h>
#include <iostream>
#include <fstream>
using namespace std;

// function reads the header of the src file and writes it to the output file
// RETURNs an int to the current "cursor" position / end of the header
int copyheader( string srcfile , string outfile )
{
  FILE * img = fopen(srcfile.c_str(),"r+");
  FILE * out = fopen(outfile.c_str(),"wb");

  unsigned char header[10];
  unsigned char offset[4];

  // 1st 10 BYTES read ( Magic No / File Size / 2B Reserved )
  fread(header, 1, 10, img);

  // 4 BYTES indicating "offset" read and converted into an integer
  fread(offset, 1, 4, img);
  int num =
        (uint16_t)offset[0] << 0 |
        (uint16_t)offset[1] << 0 |
        (uint16_t)offset[2] << 0 |
        (uint16_t)offset[3];
  unsigned char remainder[num];

  // remainder of the header read
  fseek( img, 14, SEEK_SET );
  fread(remainder, 1, num, img);

  // writing the header to the output file and closing both streams
  fwrite(header, 1, 10, out);
  fwrite(offset, 1, 4, out);

  fseek( out, 14, SEEK_SET );
  fwrite(remainder, 1, num, out);

  fclose(img);
  fclose(out);
  return num;
}


// function encrypts the data of the src image and writes the resulting encrypted
// image data to the output file
void encryptimg( EVP_CIPHER_CTX * ctx , string srcfile , string outfile )
{
  FILE * img = fopen(srcfile.c_str(),"r+");
  FILE * out = fopen(outfile.c_str(),"wb");

  // copy the header and move the cursor to the start of the image data
  int point = copyheader( srcfile, outfile );
  fseek( img, point, SEEK_SET );
  fseek( out, point, SEEK_SET );

  // buffer of 1024 BYTES for the image
  unsigned char image[1024];
  // buffer of 1024 BYTES + extra allocated space for the encryption
  unsigned char encimg[1024+EVP_MAX_BLOCK_LENGTH];
  int imgbuffer = 1024;
  int outbuffer = 0;
  int check;

  while( 1 )
  {
    // reading from the source file into the image buffer
    imgbuffer = fread(image, 1, 1024, img);
    if (imgbuffer <= 0)
    { break; }
    // encrypting the image buffer data
    check = EVP_EncryptUpdate(ctx, encimg, &outbuffer, image, imgbuffer);
    if( check != 1 )
    { exit(4); }
    // writing the encrypted data to the output file
    fwrite(encimg, 1, outbuffer, out);
  }

  check = EVP_EncryptFinal_ex(ctx, encimg, &outbuffer);
  if(check != 1) exit(5);
  fwrite(encimg, 1, outbuffer, out);
  fclose(img);
  fclose(out);
}


// Same logic as the encryptimg() but for decryption
void decryptimg( EVP_CIPHER_CTX * ctx , string srcfile , string outfile )
{
  FILE * img = fopen(srcfile.c_str(),"r+");
  FILE * out = fopen(outfile.c_str(),"wb");

  int point = copyheader( srcfile, outfile );
  fseek( img, point, SEEK_SET );
  fseek( out, point, SEEK_SET );

  unsigned char image[1024];
  unsigned char decimg[1024+EVP_MAX_BLOCK_LENGTH];
  int imgbuffer = 1024;
  int outbuffer = 0;
  int check;

  while( 1 )
  {
    imgbuffer = fread(image, 1, 1024, img);
    if (imgbuffer <= 0)
    { break; }

    check = EVP_DecryptUpdate(ctx, decimg, &outbuffer, image, imgbuffer);
    if( check != 1 )
    { exit(4); }

    fwrite(decimg, 1, outbuffer, out);
  }

  check = EVP_DecryptFinal_ex(ctx, image , &imgbuffer);
  if(check != 1) exit(5);
}


// initialises the cipher to encrypt/decrypt with the passed "mode"
// RETURNs the context structure
EVP_CIPHER_CTX * init( int encrypt , const char mode[] )
{
  unsigned char key[EVP_MAX_KEY_LENGTH] = "KEY";
  unsigned char iv[EVP_MAX_IV_LENGTH] = "moi vector";

  const EVP_CIPHER * cipher = EVP_get_cipherbyname(mode);
  if(!cipher)
  { exit(1); }

  EVP_CIPHER_CTX * ctx;
  ctx = EVP_CIPHER_CTX_new();
  if(ctx == NULL) exit(2);

  if( encrypt )
  {
    int check = EVP_EncryptInit_ex(ctx, cipher, NULL, key, iv);
    if(check != 1) exit(3);
  }
  else
  {
    int check = EVP_DecryptInit_ex(ctx, cipher, NULL, key, iv);
    if(check != 1) exit(3);
  }

  return ctx;
}


int main()
{

  OpenSSL_add_all_ciphers();

  // "ECB" MODE
  const char ecbmode[] = "DES-ECB";

  EVP_CIPHER_CTX * ECB_ctx_encrypt1 = init( 1 , ecbmode );
  encryptimg( ECB_ctx_encrypt1 , "homer-simpson.bmp" , "homer-simpson_ecb.bmp" );
  EVP_CIPHER_CTX * ECB_ctx_encrypt2 = init( 1 , ecbmode );
  encryptimg( ECB_ctx_encrypt2 , "Mad_scientist.bmp" , "Mad_scientist_ecb.bmp" );

  EVP_CIPHER_CTX * ECB_ctx_decrypt1 = init( 0 , ecbmode );
  decryptimg( ECB_ctx_decrypt1 , "homer-simpson_ecb.bmp" , "homer-simpson_ecb_dec.bmp" );
  EVP_CIPHER_CTX * ECB_ctx_decrypt2 = init( 0 , ecbmode );
  decryptimg( ECB_ctx_decrypt2 , "Mad_scientist_ecb.bmp" , "Mad_scientist_ecb_dec.bmp" );



  // "CBC" MODE
  const char cbcmode[] = "DES-CBC";

  EVP_CIPHER_CTX * CBC_ctx_encrypt1 = init( 1 , cbcmode );
  encryptimg( CBC_ctx_encrypt1 , "homer-simpson.bmp" , "homer-simpson_cbc.bmp" );
  EVP_CIPHER_CTX * CBC_ctx_encrypt2 = init( 1 , cbcmode );
  encryptimg( CBC_ctx_encrypt2 , "Mad_scientist.bmp" , "Mad_scientist_cbc.bmp" );

  EVP_CIPHER_CTX * CBC_ctx_decrypt1 = init( 0 , cbcmode );
  decryptimg( CBC_ctx_decrypt1 , "homer-simpson_cbc.bmp" , "homer-simpson_cbc_dec.bmp" );
  EVP_CIPHER_CTX * CBC_ctx_decrypt2 = init( 0 , cbcmode );
  decryptimg( CBC_ctx_decrypt2 , "Mad_scientist_cbc.bmp" , "Mad_scientist_cbc_dec.bmp" );



  return 0;
}
