-   User logged in [samymbas](https://courses.fit.cvut.cz/BI-BEZ/tutorials/06.html#)
    -   Log out
-   Log in

[FIT CTU Course Pages](https://courses.fit.cvut.cz/)

BI-BEZ Security-

-   [](https://courses.fit.cvut.cz/BI-BEZ/tutorials/06.html#)
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
-   [](https://gitlab.fit.cvut.cz/BI-BEZ/bi-bez/blob/master/tutorials/06.adoc)
     View on GitLab
-   [](https://gitlab.fit.cvut.cz/BI-BEZ/bi-bez/issues/new?issue[title]=tutorials/06.adoc:%20)
     Report an error

[Go to subject navigation](https://courses.fit.cvut.cz/BI-BEZ/tutorials/06.html#nav)

6. Block ciphers and operating modes, implementation in OpenSSL
===============================================================

The purpose of today's exercise is to get acquainted with the use of block ciphers and their operating modes. We will also show the encryption of a longer file. You will receive **5 points** for completing the entire assignment .

[](https://courses.fit.cvut.cz/BI-BEZ/tutorials/06.html#_zad%C3%A1n%C3%AD)Assignment
------------------------------------------------------------------------------------

1.  For example, download this TGA image (unzip): [obrazek.zip](https://courses.fit.cvut.cz/BI-BEZ/media/tutorials/06/obrazek_tga.zip) . ( [homer-simpson.zip](https://courses.fit.cvut.cz/BI-BEZ/media/tutorials/06/homer-simpson_tga.zip) , [ucm8.tga](https://courses.fit.cvut.cz/BI-BEZ/media/tutorials/06/UCM8.TGA) )
2.  Write a program that copies the header and **encrypts** part of the image data file using AES in ECB mode. The output file will be named `(původní_jméno)_ecb.tga`.
3.  Write a program that **decrypts the** image encrypted by the first program. The output file will be named`(původní_jméno)_dec.tga`
    -   Compare the original image and its encrypted form and explain your findings.

4.  Change the operating mode used for both encryption and decryption to **CBC** and create `(původní_jméno)_cbc.tga`a `(původní_jméno)_cbc_dec.tga`(specified by the trainee).
    -   Compare the original image and its encrypted form and explain your findings.

5.  **Leave a comment with the author's name on the first line of the source** !

###### Tip:

See the documentation `EVP_EncryptInit_ex`( `man EVP_EncryptInit_ex`) for the choice of cipher and operating mode .

### [](https://courses.fit.cvut.cz/BI-BEZ/tutorials/06.html#_form%C3%A1t-obr%C3%A1zk%C5%AF-tga-zjednodu%C5%A1eno)TGA image format (simplified)

Units: bytes (syllables)

Position

Length

Importance

0

1

Image ID length

1

1

Color map type

2

1

Image type

3

2

The beginning of the color map

5

2

Length of color map

7

1

Bit depth of color map items

8

10

Image specification

18

…

Image identifier (optional)
 Color map (optional)

**x**

to the end of the file

**Image data**

The order of the flats is little-endian. There is no need to further process the color map or the image ID, you just need to skip them correctly and not encrypt them. The image data itself must be encrypted, nothing else.

###### Tip:

A detailed description of the image format is available, for example, [here](http://www.paulbourke.net/dataformats/tga/) .

### [](https://courses.fit.cvut.cz/BI-BEZ/tutorials/06.html#_postup-%C5%A1ifrov%C3%A1n%C3%AD-del%C5%A1%C3%ADho-souboru-pole-atd)How to encrypt a longer file, field, etc.

1.  Library initialization, context allocation (see previous exercise)
2.  `EVP_EncryptInit_ex(ctx, type, NULL, key, iv);`
3.  Cycle: as long as I have the data
    1.  Read image data into the field `ot`(eg `fread`,…), the length of the read data is `otLength`.
    2.  `EVP_EncryptUpdate(ctx,  st, &stLength, ot, otLength);`
    3.  Write the contents of the `st`length field to the output file `stLength`(may differ from `otLength`).

4.  `EVP_EncryptFinal_ex(ctx,  st, &stLength);` - completion of last block encryption
5.  Write the contents of the `st`length field to the output file`stLength`

###### Tip:

Padding is enabled for block ciphers by default. Therefore, the encrypted file may be larger than the original.

You are viewing version **...** .
 [Switch to the current version.](https://courses.fit.cvut.cz/BI-BEZ/)

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

6. Block ciphers and operating modes, implementation in OpenSSL
 [tutorials / 06.adoc](https://gitlab.fit.cvut.cz/BI-BEZ/bi-bez/blob/master/tutorials/06.adoc) , [last modified 21aa5778 (8. 4. 2021 at 21:15, Jaroslav Kříž)](https://gitlab.fit.cvut.cz/BI-BEZ/bi-bez/commit/21aa5778bdf78332d99447ea9d4fa5e65ac8f83d "Add tip for third task")

Generated by [**FIT CTU Course Pages**](https://gitlab.fit.cvut.cz/course-pages/course-pages/) v0.8.0
 Page generated28. 5. 2021 at 16:14

[![Build status](./Block%20Cipher_files/pipeline.svg)](https://gitlab.fit.cvut.cz/BI-BEZ/bi-bez/pipelines)

![Google Translate](./Block%20Cipher_files/translate_24dp.png)

Original text
=============

Contribute a better translation

* * * * *
