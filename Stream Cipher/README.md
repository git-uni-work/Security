# " STREAM CIPHER "

What is OpenSSL
--------------------------------------------------------------------------------------

[OpenSSL](http://www.openssl.org/) is a library working with SSL (Secure Socket Layer) and TLS (Transport Layer Security) protocols. This library has been under development since 1998 and is based on the older SSLeay library. OpenSSL consists of three main parts:

### Command line tool

OpenSSL includes a command line tool that allows you to quickly and easily encrypt text (DES, 3DES, RC4…), create certificates (X.509), compute hashes (SHA1, SHA256, MD5…) and other functions from the Crypto library . Example of SHA1 calculation for entered text in the command line:

``` {.highlightjs-ext .highlight}
echo -n "Hashovany text." | openssl sha1
```

### SSL library

The SSL library is a library that implements the Secure Sockets Layer (SSL v2 / v3) and Transport Layer Security (TLS v1) network communication layers. It covers the use of hash and encryption functions to establish a secure session and also implements several types of structures that ssl functions work with, such as SSL\_CTX, SSL\_METHOD, and more.

### Crypto library

The crypto library provides an implementation of specific cryptographic functions, data structures for storing keys and formatting messages and working with certificates. In addition to the low-level implementation of individual algorithms, it also provides a higher-level interface, the so-called EVP (envelope) function.

### Task assignment
----------------------------------------------------------------------------------------------------

Write a program that finds any message whose **hash (SHA-384) starts** from the left in the sequence of zero bits:

-   The number of zero bits is specified by an integer as a parameter on the command line.
-   The bit order is big-endian: Byte 0 from MSB to LSB, Byte 1 from MSB to LSB,…, last byte from MSB to LSB.
-   **Write the** found **message in hexadecimal form** .

### Code samples
-------------------------------------------------------------------------------------------

### Example of hash functions

This code quenches the `text`hash stored in the variable `hashFunction`.

``` {.highlightjs-ext .highlight}
#include <stdio.h>
#include <string.h>
#include <openssl/evp.h>

int main (int argc, char * argv[]) {
    char text[] = "Text pro hash.";
    char hashFunction[] = "sha1";  // zvolena hashovaci funkce ("sha1", "md5", ...)

    EVP_MD_CTX * ctx;  // struktura kontextu
    const EVP_MD * type; // typ pouzite hashovaci funkce
    unsigned char hash[EVP_MAX_MD_SIZE]; // char pole pro hash - 64 bytu (max pro sha 512)
    unsigned int length;  // vysledna delka hashe

    /* Inicializace OpenSSL hash funkci */
    OpenSSL_add_all_digests();
    /* Zjisteni, jaka hashovaci funkce ma byt pouzita */
    type = EVP_get_digestbyname(hashFunction);

    /* Pokud predchozi prirazeni vratilo -1, tak nebyla zadana spravne hashovaci funkce */
    if (!type) {
        printf("Hash %s neexistuje.\n", hashFunction);
        return 1;
    }

    ctx = EVP_MD_CTX_new(); // create context for hashing
    if (ctx == NULL)
        return 2;

    /* Hash the text */
    if (!EVP_DigestInit_ex(ctx, type, NULL)) // context setup for our hash type
        return 3;

    if (!EVP_DigestUpdate(ctx, text, strlen(text))) // feed the message in
        return 4;

    if (!EVP_DigestFinal_ex(ctx, hash, &length)) // get the hash
        return 5;

    EVP_MD_CTX_free(ctx); // destroy the context

    /* Vypsani vysledneho hashe */
    printf("Hash textu \"%s\" je: ", text);
    for (unsigned int i = 0; i < length; i++)
        printf("%02x", hash[i]);
    printf("\n");
    return 0;
}
```

Use the following command to compile the source code. We recommend writing a makefile.

``` {.highlightjs-ext .highlight}
gcc -Wall -pedantic ye.c -o ye -lcrypto
```

### Example of a stream cipher

This code uses a stream cipher to encrypt `rc4`open text `ot`using a key `key`and an initialization vector `iv`.

``` {.highlightjs-ext .highlight}
#include <stdlib.h>
#include <string.h>
#include <openssl/evp.h>

int main (void) {
    unsigned char ot[1024] = "Text pro rc4.";  // open text
    unsigned char st[1024];  // sifrovany text
    unsigned char key[EVP_MAX_KEY_LENGTH] = "Muj klic";  // klic pro sifrovani
    unsigned char iv[EVP_MAX_IV_LENGTH] = "inicial. vektor";  // inicializacni vektor
    const char cipherName[] = "RC4";
    const EVP_CIPHER * cipher;

    OpenSSL_add_all_ciphers();
    /* sifry i hashe by se nahraly pomoci OpenSSL_add_all_algorithms() */
    cipher = EVP_get_cipherbyname(cipherName);
    if (!cipher) {
        printf("Sifra %s neexistuje.\n", cipherName);
        return 1;
    }

    int otLength = strlen((const char *) ot), stLength = 0, tmpLength = 0;

    EVP_CIPHER_CTX * ctx; // context structure
    ctx = EVP_CIPHER_CTX_new();
    if (ctx == NULL)
        return 2;

    printf("OT: %s\n", ot);

    /* Sifrovani */
    if (!EVP_EncryptInit_ex(ctx, cipher, NULL, key, iv)) // context init - set cipher, key, init vector
        return 3;

    if (!EVP_EncryptUpdate(ctx,  st, &tmpLength, ot, otLength)) // encryption of pt
        return 4;

    stLength += tmpLength;

    if (!EVP_EncryptFinal_ex(ctx, st + stLength, &tmpLength)) // get the remaining ct
        return 5;

    stLength += tmpLength;

    printf ("Zasifrovano %d znaku.\n", stLength);

    /* Desifrovani */
    if (!EVP_DecryptInit_ex(ctx, cipher, NULL, key, iv)) // nastaveni kontextu pro desifrovani
        return 6;

    if (!EVP_DecryptUpdate(ctx, ot, &tmpLength,  st, stLength)) // desifrovani st
        return 7;

    otLength += tmpLength;

    if (!EVP_DecryptFinal_ex(ctx, ot + otLength, &tmpLength)) // dokonceni (ziskani zbytku z kontextu)
        return 8;

    otLength += tmpLength;

    /* Clean up */
    EVP_CIPHER_CTX_free(ctx);

    /* Vypsani zasifrovaneho a rozsifrovaneho textu. */
    printf("ST: %s\nDT: %s\n", st, ot);
    return 0;
}
```

Use the following command to compile the source code. However, we recommend that you write a makefile.

``` {.highlightjs-ext .highlight}
gcc -Wall -pedantic ye.c -o ye -lcrypto
```
