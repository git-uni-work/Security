#include <stdlib.h>
#include <openssl/evp.h>
#include <string.h>
#include <string>
#include <iostream>
#define MAX_LENF 1024
using namespace std;

// https://stackoverflow.com/questions/3381614/c-convert-string-to-hexadecimal-and-vice-versa
int Hex( char x )
{
    switch(x)
    {
    case '0': case '1': case '2': case '3': case '4':
    case '5': case '6': case '7': case '8': case '9':
        return x - '0';

    case 'A': case 'B': case 'C': case 'D': case 'E': case 'F':
        return x - 'A' + 10;

    case 'a': case 'b': case 'c': case 'd': case 'e': case 'f':
        return x - 'a' + 10;
    }
    cout << "Invalid HEX" << endl;
    return 0;
}
string HexToString( const string & x )
{
    const auto lenf = x.length();
    if( lenf & 1 )
    {cout << "odd length" << endl;}

    string result;
    result.reserve(lenf / 2);
    for (auto it = x.begin(); it != x.end(); )
    {
        int hi = Hex(*it++);
        int lo = Hex(*it++);
        result.push_back(hi << 4 | lo);
    }
    return result;
}

void decrypt ( unsigned char pt1 [] , unsigned char ct1 [] , unsigned char ct2 [] , int len1 , int len2)
{
  // X = PT1 (XOR) CT1
  unsigned char x[len1];
  for( int i = 0 ; i < len1 ; i++ )
    x[i] = pt1[i] ^ ct1[i];

  // PT2 = CT2 (XOR) X
  unsigned char result[len2];
  for(int i = 0; i < len2; i++)
    result[i] = ct2[i] ^ x[i];

  //Print the resulting de-ciphered string
  printf("================\n");
  printf("PT2 = %s\n",result);
  printf("================\n");
  printf("################\n################\n");
}

int main(void)
{
  unsigned char pt1[MAX_LENF] = "21Savage21Savage21Savage212121";  // PlainText1
  unsigned char pt2[MAX_LENF] = "BABYIMASAVAGEIAINTROMANTIC2121";  // PlainText2
  unsigned char ct1[MAX_LENF];  // CipherText1
  unsigned char ct2[MAX_LENF];  // CipherText2
  unsigned char key[EVP_MAX_KEY_LENGTH] = "ZINDEEEQZINDEEEQ";  // Encryption & Decryption KEY
  unsigned char iv[EVP_MAX_IV_LENGTH] = "VECTOR";
  const char cipherName[] = "RC4";

  // INITIALISATION
  const EVP_CIPHER * cipher;
  int pt1length = strlen((const char*) pt1);
  int pt2length = strlen((const char*) pt2);
  int ct1length = 0;
  int ct2length = 0;
  int tmpLength = 0;
  int res;
  OpenSSL_add_all_ciphers();
  cipher = EVP_get_cipherbyname(cipherName);
  if(!cipher)
  {
    printf("CIPHER %s !EXIST\n", cipherName);
    exit(1);
  }
  EVP_CIPHER_CTX *ctx;
  ctx = EVP_CIPHER_CTX_new();
  if(ctx == NULL) exit(2);

  // Encryption Of PT1 - storing encrypted text in CT1
  res = EVP_EncryptInit_ex(ctx, cipher, NULL, key, iv);
  if(res != 1) exit(3);
  res = EVP_EncryptUpdate(ctx,  ct1, &tmpLength, pt1, pt1length);
  if(res != 1) exit(4);
  ct1length += tmpLength;
  res = EVP_EncryptFinal_ex(ctx, ct1 + ct1length, &tmpLength);
  if(res != 1) exit(5);
  ct1length += tmpLength;

  //Encryption Of PT2 - storing encrypted text in CT2
  res = EVP_EncryptInit_ex(ctx, cipher, NULL, key, iv);
  if(res != 1) exit(3);
  res = EVP_EncryptUpdate(ctx,  ct2, &tmpLength, pt2, pt2length);
  if(res != 1) exit(4);
  ct2length += tmpLength;
  res = EVP_EncryptFinal_ex(ctx, ct2 + ct2length, &tmpLength);
  if(res != 1) exit(5);
  ct2length += tmpLength;

  // Print the cipher texts in HEX
  printf("================\n");
  printf("CT1 HEX = ");
  for(int i = 0; i < ct1length; i++)
    printf("%02hhx", ct1[i]);
  printf("\n");
  printf("CT2 HEX = ");
  for(int i = 0; i < ct2length; i++)
    printf("%02hhx", ct2[i]);
  // Print the known plain text (PT1)
  printf("\n================\n");
  printf("PT1 = %s\n", pt1);
  printf("================\n");
  printf("== DECRYPTION ==\n");

  // Function takes the known plain text (PT1) aswell as the 2 cipher texts and prints the second plain text (PT2)
  decrypt( pt1 , ct1 , ct2 , ct1length , ct2length );


  // Example from Lab Description page
  unsigned char pt [MAX_LENF] = "abcdefghijklmnopqrstuvwxyz0123";
  // reading hexadecimal strings from stdin
  string X = "";
  string Y = "";
  cout << "INPUT HEX : " << endl;
  cin >> X ;
  cin >> Y;
  string a = HexToString(X);
  string b = HexToString(Y);
  unsigned char ctX [MAX_LENF];
  unsigned char ctY [MAX_LENF];
  strcpy( (char *) ctX , a.c_str() );
  strcpy( (char *) ctY , b.c_str() );

  // Print the cipher texts in HEX
  printf("================\n");
  printf("CT1 HEX = ");
  for(int i = 0; i < ct1length; i++)
    printf("%02hhx", ctX[i]);
  printf("\n");
  printf("CT2 HEX = ");
  for(int i = 0; i < ct2length; i++)
    printf("%02hhx", ctY[i]);
  // Print the known plain text (PT1)
  printf("\n================\n");
  printf("PT1 = %s\n", pt);
  printf("================\n");
  printf("== DECRYPTION ==\n");

  decrypt(pt,ctX,ctY,30,30);

  // Free all used resources
  EVP_CIPHER_CTX_free(ctx);
  exit(0);
 }
;
