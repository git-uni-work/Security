#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <openssl/evp.h>

#define LENF 10
//function to generate all combinations of a string of certain length by modifying the string
int modifystring( char * x )
{
  int i;
  // starts from the right most charecter and iterates to the first charecter
	for( i = LENF-2 ; i >= 0 ; i-- )
	{
    // modifies the charecter to iterate through the alphabet from a->z
		if(x[i] != 'z')
		{
			x[i]++;
			break;
		}
    // once 'z' is reached the current charecter is reset to 'a' and the charecter to the left is now modified
		else
    { x[i] = 'a'; }
	}
	return ( i != -1 );
}

void printHex(const char *s)
{
  printf("### 0x");
  while(*s)
    printf("%02x", (unsigned int) *s++);
  printf(" ###\n");
}

int main(int argc, char *argv[]){

  char text[LENF]; // PT initialised with fixed length
  char hashFunction[] = "sha256"; // HASH FUNCTION (SHA256) for encryption

  // INITIALISATION
  EVP_MD_CTX *ctx;
  const EVP_MD *type;
  unsigned char hash[EVP_MAX_MD_SIZE];
  int length;
  OpenSSL_add_all_digests();
  type = EVP_get_digestbyname(hashFunction);
  if(!type)
  {
    printf("HASH %s ! EXIST\n", hashFunction);
    exit(1);
  }
  ctx = EVP_MD_CTX_create();
  if(ctx == NULL) exit(2);

  int flag = 0;
  // initial PT string of a's
	for( int i = 0; i < LENF-1; i++)
		text[i] = 'a';
	text[LENF-1] = '\0';

	do
	{
    // encrypt the PT and store the CT in "hash"
		EVP_DigestInit(ctx, type);
		EVP_DigestUpdate(ctx, text, LENF);
		EVP_DigestFinal(ctx, hash, (unsigned int *) &length);

    // IF the hashed CT's starts with the 2 byte sequence 0xCAFE then it is a match and the PT generated is the result
		if(hash[0] == 0xCA && hash[1] == 0xFE )
		{
      // print the PT string
      printf("### \" %s \" ###\n",text);
      // print the string in hexadecimal form
      printHex(text);
      // print the resulting HASH in hexadecimal and break
      printf("0x");
      for( int i = 0; i < length; i++)
        printf("%02x", hash[i]);
			printf("\n");
			flag = 1;
			break;
		}
	}
  // while there's no match keep modifying the string charecter by charecter
  while(modifystring(text));

	if(!flag)
  { printf("Hash !EXIST\n"); }
  EVP_MD_CTX_destroy(ctx);
  exit(0);
}
