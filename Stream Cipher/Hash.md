-   User logged in [samymbas](https://courses.fit.cvut.cz/BI-BEZ/tutorials/05.html#)
    -   Log out
-   Log in

[FIT CTU Course Pages](https://courses.fit.cvut.cz/)

BI-BEZ Security-

-   [](https://courses.fit.cvut.cz/BI-BEZ/tutorials/05.html#)
     Past semesters
    -   [B102](https://courses.fit.cvut.cz/BI-BEZ/@B102/)
    -   [B111](https://courses.fit.cvut.cz/BI-BEZ/@B111/)
    -   [B121](https://courses.fit.cvut.cz/BI-BEZ/@B121/)
    -   [B122](https://courses.fit.cvut.cz/BI-BEZ/@B122/)
    -   [B131](https://courses.fit.cvut.cz/BI-BEZ/@B131/)
    -   [B132](https://courses.fit.cvut.cz/BI-BEZ/@B132/)
    -   [B141](https://courses.fit.cvut.cz/BI-BEZ/@B141/)
    -   [B142](https://courses.fit.cvut.cz/BI-BEZ/@B142/)
    -   [B151](https://courses.fit.cvut.cz/BI-BEZ/@B151/)
    -   [B152](https://courses.fit.cvut.cz/BI-BEZ/@B152/)
    -   [B161](https://courses.fit.cvut.cz/BI-BEZ/@B161/)
    -   [B162](https://courses.fit.cvut.cz/BI-BEZ/@B162/)
    -   [B171](https://courses.fit.cvut.cz/BI-BEZ/@B171/)
    -   [B172](https://courses.fit.cvut.cz/BI-BEZ/@B172/)
    -   [B192](https://courses.fit.cvut.cz/BI-BEZ/@B192/)
    -   [master](https://courses.fit.cvut.cz/BI-BEZ/)
    -   [B202](https://courses.fit.cvut.cz/BI-BEZ/@B202/)
-   [](https://gitlab.fit.cvut.cz/BI-BEZ/bi-bez/blob/master/tutorials/05.adoc)
     View on GitLab
-   [](https://gitlab.fit.cvut.cz/BI-BEZ/bi-bez/issues/new?issue[title]=tutorials/05.adoc:%20)
     Report an error

[Go to subject navigation](https://courses.fit.cvut.cz/BI-BEZ/tutorials/05.html#nav)

5. OpenSSL: Introduction to the library, hash functions, stream ciphers
=======================================================================

Content
-------

1.  [What is OpenSSL](https://courses.fit.cvut.cz/BI-BEZ/tutorials/05.html#_co-je-openssl)
    1.  [Command line tool](https://courses.fit.cvut.cz/BI-BEZ/tutorials/05.html#_command-line-tool)
    2.  [SSL library](https://courses.fit.cvut.cz/BI-BEZ/tutorials/05.html#_ssl-library)
    3.  [Crypto library](https://courses.fit.cvut.cz/BI-BEZ/tutorials/05.html#_crypto-library)

2.  [Task assignment](https://courses.fit.cvut.cz/BI-BEZ/tutorials/05.html#_zad%C3%A1n%C3%AD-%C3%BAkolu)
3.  [Code samples](https://courses.fit.cvut.cz/BI-BEZ/tutorials/05.html#_uk%C3%A1zky-k%C3%B3du)
    1.  [Example of hash functions](https://courses.fit.cvut.cz/BI-BEZ/tutorials/05.html#_p%C5%99%C3%ADklad-na-hashovac%C3%AD-funkce)
    2.  [Example of a stream cipher](https://courses.fit.cvut.cz/BI-BEZ/tutorials/05.html#_p%C5%99%C3%ADklad-na-proudovou-%C5%A1ifru)
    3.  [Tips for creating a makefile](https://courses.fit.cvut.cz/BI-BEZ/tutorials/05.html#_tipy-pro-vytvo%C5%99en%C3%AD-makefile)
    4.  [Tips for using CLion (if you use for development)](https://courses.fit.cvut.cz/BI-BEZ/tutorials/05.html#_tipy-pro-pou%C5%BEit%C3%AD-clion-pokud-pou%C5%BE%C3%ADv%C3%A1te-pro-v%C3%BDvoj)

4.  [Resources](https://courses.fit.cvut.cz/BI-BEZ/tutorials/05.html#_zdroje)

[](https://courses.fit.cvut.cz/BI-BEZ/tutorials/05.html#_co-je-openssl)What is OpenSSL
--------------------------------------------------------------------------------------

[OpenSSL](http://www.openssl.org/) is a library working with SSL (Secure Socket Layer) and TLS (Transport Layer Security) protocols. This library has been under development since 1998 and is based on the older SSLeay library. OpenSSL consists of three main parts:

![openssl](./Hash_files/openssl.png)

### [](https://courses.fit.cvut.cz/BI-BEZ/tutorials/05.html#_command-line-tool)Command line tool

OpenSSL includes a command line tool that allows you to quickly and easily encrypt text (DES, 3DES, RC4…), create certificates (X.509), compute hashes (SHA1, SHA256, MD5…) and other functions from the Crypto library . Example of SHA1 calculation for entered text in the command line:

``` {.highlightjs-ext .highlight}
echo -n "Hashovany text." | openssl sha1
```

### [](https://courses.fit.cvut.cz/BI-BEZ/tutorials/05.html#_ssl-library)SSL library

The SSL library is a library that implements the Secure Sockets Layer (SSL v2 / v3) and Transport Layer Security (TLS v1) network communication layers. It covers the use of hash and encryption functions to establish a secure session and also implements several types of structures that ssl functions work with, such as SSL\_CTX, SSL\_METHOD, and more.

### [](https://courses.fit.cvut.cz/BI-BEZ/tutorials/05.html#_crypto-library)Crypto library

The crypto library provides an implementation of specific cryptographic functions, data structures for storing keys and formatting messages and working with certificates. In addition to the low-level implementation of individual algorithms, it also provides a higher-level interface, the so-called EVP (envelope) function.

[](https://courses.fit.cvut.cz/BI-BEZ/tutorials/05.html#_zad%C3%A1n%C3%AD-%C3%BAkolu)Task assignment
----------------------------------------------------------------------------------------------------

**Task2\_hash (3 points):**

Write a program that finds any message whose **hash (SHA-384) starts** from the left in the sequence of zero bits:

-   The number of zero bits is specified by an integer as a parameter on the command line.
-   The bit order is big-endian: Byte 0 from MSB to LSB, Byte 1 from MSB to LSB,…, last byte from MSB to LSB.
-   **Write the** found **message in hexadecimal form** .

[](https://courses.fit.cvut.cz/BI-BEZ/tutorials/05.html#_uk%C3%A1zky-k%C3%B3du)Code samples
-------------------------------------------------------------------------------------------

### [](https://courses.fit.cvut.cz/BI-BEZ/tutorials/05.html#_p%C5%99%C3%ADklad-na-hashovac%C3%AD-funkce)Example of hash functions

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
gcc -Wall -pedantic nazevSouboru.c -o nazevVystupu -lcrypto
```

### [](https://courses.fit.cvut.cz/BI-BEZ/tutorials/05.html#_p%C5%99%C3%ADklad-na-proudovou-%C5%A1ifru)Example of a stream cipher

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
gcc -Wall -pedantic nazevSouboru.c -o nazevVystupu -lcrypto
```

### [](https://courses.fit.cvut.cz/BI-BEZ/tutorials/05.html#_tipy-pro-vytvo%C5%99en%C3%AD-makefile)Tips for creating a makefile

See, for example, the [instructions from MIT](http://web.mit.edu/gnu/doc/html/make_2.html) , or repeat the information from [BI-PA2](https://courses.fit.cvut.cz/BI-PA2/tutorials/texts/makefile.html#_kompilace-modul%C5%AF-a-makefile) .

###### Tip:

All commands are indented with a TAB character.

``` {.highlightjs-ext .highlight}
CC = gcc
CFLAGS = -g
LDFLAGS = -lcrypto

all: hash
run:
    #run your tests here...
hash: hash.o
    $(CC) -o $@ $< $(LDFLAGS)
%.o: %.c
    $(CC) -c -o $@ $< $(CFLAGS)
```

### [](https://courses.fit.cvut.cz/BI-BEZ/tutorials/05.html#_tipy-pro-pou%C5%BEit%C3%AD-clion-pokud-pou%C5%BE%C3%ADv%C3%A1te-pro-v%C3%BDvoj)Tips for using CLion (if you use for development)

In CLion, open `CMakeLists.txt`, add the following line, and then reload the CMake project:

    target_link_libraries ($ {PROJECT_NAME} crypto)

[](https://courses.fit.cvut.cz/BI-BEZ/tutorials/05.html#_zdroje)Resources
-------------------------------------------------------------------------

-   Official OpenSSL website: [http://www.openssl.org/](http://www.openssl.org/)
-   Secure programming with the OpenSSL API: [http://ibm.co/ZYsHLO](http://ibm.co/ZYsHLO)
-   John Viega, Matt Messier, Pravir Chandra: Network Security with OpenSSL, [Link](https://books.google.cz/books?id=IIqwAy4qEl0C)
-   OpenSSL Wiki [http://wiki.openssl.org/index.php/Main\_Page](http://wiki.openssl.org/index.php/Main_Page)

Prohlížíte verzi **...**.
 [Přejděte na aktuální verzi.](https://courses.fit.cvut.cz/BI-BEZ/)

Subject navigation
==================

-   [](https://courses.fit.cvut.cz/BI-BEZ/index.html)
    Homepage
-   [](https://courses.fit.cvut.cz/BI-BEZ/en/index.html)
    BIE-BEZ - Security
    -   [](https://courses.fit.cvut.cz/BI-BEZ/en/classification.html)
        Classification
    -   [](https://courses.fit.cvut.cz/BI-BEZ/en/exam.html)
        Exam information
    -   [](https://courses.fit.cvut.cz/BI-BEZ/en/labs/index.html)
        Labs
        -   [](https://courses.fit.cvut.cz/BI-BEZ/en/labs/01/index.html)
            Lab 1 - Substitution ciphers: Caesar cipher, affine cipher. Transposition ciphers
        -   [](https://courses.fit.cvut.cz/BI-BEZ/en/labs/02/index.html)
            Lab 2 - OpenSSL: Introduction to the library, hash functions, stream ciphers
        -   [](https://courses.fit.cvut.cz/BI-BEZ/en/labs/03/index.html)
            Lab 3 - Block ciphers and modes of operation, implementation in OpenSSL
        -   [](https://courses.fit.cvut.cz/BI-BEZ/en/labs/04/index.html)
            Lab 4 - OpenSSL: Asymmetric cryptography - key generation, elementary RSA operations
        -   [](https://courses.fit.cvut.cz/BI-BEZ/en/labs/05/index.html)
            Lab 5 - OpenSSL: Network connection, certificate verification, ciphersuite selection
        -   [](https://courses.fit.cvut.cz/BI-BEZ/en/labs/06/index.html)
            Lab 6 - Consultation
    -   [](https://courses.fit.cvut.cz/BI-BEZ/en/seminars/index.html)
        Seminars
        -   [](https://courses.fit.cvut.cz/BI-BEZ/en/seminars/01/index.html)
            Seminar 1 - Arithmetic modulo m - recap
            -   [](https://courses.fit.cvut.cz/BI-BEZ/en/seminars/01/exponentiation.html)
                Solved examples: Exponentiation
        -   [](https://courses.fit.cvut.cz/BI-BEZ/en/seminars/02/index.html)
            Seminar 2 - Hill cipher, Diffie-Hellman algorithm and the discrete logarithm problem
        -   [](https://courses.fit.cvut.cz/BI-BEZ/en/seminars/03/index.html)
            Seminar 3 - Unicity distance, Birthday paradox
        -   [](https://courses.fit.cvut.cz/BI-BEZ/en/seminars/05/index.html)
            Seminar 5 - Primality testing, Rabin-Miller test. RSA, RSA-CRT
            -   [](https://courses.fit.cvut.cz/BI-BEZ/en/seminars/05/liars_p.svg)
                Liars p
-   [](https://courses.fit.cvut.cz/BI-BEZ/bonus/index.html)
    Bonus tasks
-   [](https://courses.fit.cvut.cz/BI-BEZ/tutorials/index.html)
    Exercises
    -   [](https://courses.fit.cvut.cz/BI-BEZ/tutorials/01.html)
        1. Repetition of arithmetic modulo m, modular exponentiation
    -   [](https://courses.fit.cvut.cz/BI-BEZ/tutorials/02.html)
        2. Substitution ciphers
    -   [](https://courses.fit.cvut.cz/BI-BEZ/tutorials/03.html)
        3. Block ciphers, Hill cipher
    -   [](https://courses.fit.cvut.cz/BI-BEZ/tutorials/04.html)
        4. Exponential cipher, Diffie-Hellman and the discrete logarithm problem
    -   [](https://courses.fit.cvut.cz/BI-BEZ/tutorials/05.html)
        5. OpenSSL: Introduction to the library, hash functions, stream ciphers
    -   [](https://courses.fit.cvut.cz/BI-BEZ/tutorials/06.html)
        6. Block ciphers and operating modes, implementation in OpenSSL
    -   [](https://courses.fit.cvut.cz/BI-BEZ/tutorials/07.html)
        7. Birthday paradox, distance of uniqueness
    -   [](https://courses.fit.cvut.cz/BI-BEZ/tutorials/08.html)
        8. OpenSSL: Asymmetric cryptography - key generation, elementary RSA operations
    -   [](https://courses.fit.cvut.cz/BI-BEZ/tutorials/09.html)
        9. Tests of prime numbers - Rabin-Miller test, RSA, RSA-CRT
    -   [](https://courses.fit.cvut.cz/BI-BEZ/tutorials/10.html)
        10. OpenSSL: Network connection, certificate verification, cipher settings
-   [](https://courses.fit.cvut.cz/BI-BEZ/classification/index.html)
    Evaluation
    -   [](https://courses.fit.cvut.cz/BI-BEZ/classification/exam.html)
        Informace ke zkoušce
-   [](https://courses.fit.cvut.cz/BI-BEZ/parttime.html)
    Combined Studies
-   [](https://courses.fit.cvut.cz/BI-BEZ/lectures.html)
    Lectures
-   [](https://courses.fit.cvut.cz/BI-BEZ/teacher/index.html)
    Teachers
    -   [](https://courses.fit.cvut.cz/BI-BEZ/teacher/pokord11/index.html)
        David Pokorný
        -   [](https://courses.fit.cvut.cz/BI-BEZ/teacher/pokord11/task4.html)
            Upřesnění zadání 4. úkolu
    -   [](https://courses.fit.cvut.cz/BI-BEZ/teacher/kodytfil/index.html)
        Filip Kodýtek
        -   [](https://courses.fit.cvut.cz/BI-BEZ/teacher/kodytfil/bonus_aes_hash/index.html)
            AES as insecure hash (bonusová úloha)
        -   [](https://courses.fit.cvut.cz/BI-BEZ/teacher/kodytfil/bonus_rsa_crt_attack/index.html)
            CRT útok na RSA (bonusová úloha)
        -   [](https://courses.fit.cvut.cz/BI-BEZ/teacher/kodytfil/bonus_dh/index.html)
            Diffie-Hellman (bonusová úloha)
        -   [](https://courses.fit.cvut.cz/BI-BEZ/teacher/kodytfil/bonus_ecdsa/index.html)
            ECDSA (bonusová úloha)
        -   [](https://courses.fit.cvut.cz/BI-BEZ/teacher/kodytfil/bonus_hill/index.html)
            Kryptoanalýza - Hillova šifra (bonusová úloha)
            -   [](https://courses.fit.cvut.cz/BI-BEZ/teacher/kodytfil/bonus_hill/CT.txt)
                CT
        -   [](https://courses.fit.cvut.cz/BI-BEZ/teacher/kodytfil/task1/index.html)
            Úloha 1 - Mathematica
            -   [](https://courses.fit.cvut.cz/BI-BEZ/teacher/kodytfil/task1/cv1_zadani.txt)
                Cv1 zadani
            -   [](https://courses.fit.cvut.cz/BI-BEZ/teacher/kodytfil/task1/cv2_zadani.txt)
                Cv2 zadani
            -   [](https://courses.fit.cvut.cz/BI-BEZ/teacher/kodytfil/task1/cv3_zadani.txt)
                Cv3 zadani
            -   [](https://courses.fit.cvut.cz/BI-BEZ/teacher/kodytfil/task1/cv4_zadani.txt)
                Cv4 zadani
        -   [](https://courses.fit.cvut.cz/BI-BEZ/teacher/kodytfil/task2/index.html)
            Úloha 2 - Hash
        -   [](https://courses.fit.cvut.cz/BI-BEZ/teacher/kodytfil/task3/index.html)
            Úloha 3 - Bloková šifra
            -   [](https://courses.fit.cvut.cz/BI-BEZ/teacher/kodytfil/task3/task3-test-input.zip)
                Task3 test input
        -   [](https://courses.fit.cvut.cz/BI-BEZ/teacher/kodytfil/task4/index.html)
            Úloha 4 - Asymetrická kryptografie
    -   [](https://courses.fit.cvut.cz/BI-BEZ/teacher/kovarfr3/index.html)
        František Kovář
    -   [](https://courses.fit.cvut.cz/BI-BEZ/teacher/krizjar5/index.html)
        Jaroslav Kříž
        -   [](https://courses.fit.cvut.cz/BI-BEZ/teacher/krizjar5/homeworks.html)
            Odevzdání domácích úkolů
        -   [](https://courses.fit.cvut.cz/BI-BEZ/teacher/krizjar5/hw2.html)
            Úkol 2: Hashovací funkce
        -   [](https://courses.fit.cvut.cz/BI-BEZ/teacher/krizjar5/hw4.html)
            Úkol 4: Asymetrická kryptografie
    -   [](https://courses.fit.cvut.cz/BI-BEZ/teacher/dostaji2/index.html)
        Jiří Dostál
    -   [](https://courses.fit.cvut.cz/BI-BEZ/teacher/shchamar/index.html)
        Shchavleva Marina

5. OpenSSL: Introduction to the library, hash functions, stream ciphers
 [tutorials / 05.adoc](https://gitlab.fit.cvut.cz/BI-BEZ/bi-bez/blob/master/tutorials/05.adoc) , [last change 0976554c (16. 3. 2021 at 16:30, Jaroslav Kříž)](https://gitlab.fit.cvut.cz/BI-BEZ/bi-bez/commit/0976554c8a0cc29a86c9b627aa5c704812e914f2 "Tutorial 5: Move codes to media folder")

Generated by [**FIT CTU Course Pages**](https://gitlab.fit.cvut.cz/course-pages/course-pages/) v0.8.0
 Page generated28. 5. 2021 at 16:14

[![Build status](./Hash_files/pipeline.svg)](https://gitlab.fit.cvut.cz/BI-BEZ/bi-bez/pipelines)

![Google Translate](./Hash_files/translate_24dp.png)

Original text
=============

Contribute a better translation

* * * * *
