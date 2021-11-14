-   User logged in [samymbas](https://courses.fit.cvut.cz/BI-BEZ/tutorials/10.html#)
    -   Log out
-   Log in

[FIT CTU Course Pages](https://courses.fit.cvut.cz/)

BI-BEZ Security-

-   [](https://courses.fit.cvut.cz/BI-BEZ/tutorials/10.html#)
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
-   [](https://gitlab.fit.cvut.cz/BI-BEZ/bi-bez/blob/master/tutorials/10.adoc)
     View on GitLab
-   [](https://gitlab.fit.cvut.cz/BI-BEZ/bi-bez/issues/new?issue[title]=tutorials/10.adoc:%20)
     Report an error

[Go to subject navigation](https://courses.fit.cvut.cz/BI-BEZ/tutorials/10.html#nav)

10. OpenSSL: Network connection, certificate verification, cipher settings
==========================================================================

[](https://courses.fit.cvut.cz/BI-BEZ/tutorials/10.html#_komunikace-p%C5%99es-openssl)Communication via OpenSSL
---------------------------------------------------------------------------------------------------------------

You will receive **5 points** for completing the entire assignment .

Write a program in C language that:

-   connects to a web server (see url below)
-   verifies the server certificate
-   sets and lists the type of cipher used
-   download page [https://fit.cvut.cz/cs/fakulta/o-fakulte](https://fit.cvut.cz/cs/fakulta/o-fakulte) to file,
-   lists information about the fit.cvut.cz server certificate,
-   saves it to a PEM file.

Documentation for the openssl library can be found on the project website: [http://www.openssl.org/docs/](http://www.openssl.org/docs/) , [https://wiki.openssl.org/index.php/SSL/TLS\_Client](https://wiki.openssl.org/index.php/SSL/TLS_Client) , instructions for working with X.509 certificates, e.g. at [https://zakird.com/2013/10/13/certificate-parsing-with-openssl](https://zakird.com/2013/10/13/certificate-parsing-with-openssl) . Remember to refer to resources properly.

### [](https://courses.fit.cvut.cz/BI-BEZ/tutorials/10.html#_z%C3%A1kladn%C3%AD-postup)Basic procedure

1.  Create a TCP connection to the server fit.cvut.cz, port `443`(see `socket`, `connect`)
2.  Initialize OpenSSL library ( `SSL_library_init`)
3.  Create a new context ( `SSL_CTX_new`, use method `TLS_client_method`)
    1.  Disable obsolete and leaky protocols: `SSL_CTX_set_options(ctx, SSL_OP_NO_SSLv2 | SSL_OP_NO_SSLv3 | SSL_OP_NO_TLSv1 | SSL_OP_NO_TLSv1_1);`

4.  Create SSL structure ( `SSL_new`)
5.  Assign an open connection ( `SSL_set_fd`)
6.  Set the required server name for the SNI mechanism: ( `SSL_set_tlsext_host_name`)
7.  Start SSL communication ( `SSL_connect`)
    1.  Now that an SSL connection is established to the HTTPS server, you can send the request

8.  Send HTTP request over secure channel ( `SSL_write`)
    1.  Read the response in loops as they arrive over the network and store the resulting data in a file ( `SSL_read`)

9.  In the end, we clean up after each other
    1.  End SSL session on open socket ( `SSL_shutdown`)
    2.  Let's close the socket
    3.  Release the SSL structure and context ( `SSL_free`, `SSL_CTX_free`)

###### Tip:

Be sure to add the ssl library to the link `-lssl -lcrypto`.

### [](https://courses.fit.cvut.cz/BI-BEZ/tutorials/10.html#_pou%C5%BEit%C3%A1-%C5%A1ifra)Cipher used

-   Find out which ciphers the client and server agree on by default
    -   after establishing an encrypted connection, make a call `SSL_get_cipher_name`
-   Before calling, `SSL_connect`disable the specific cipher that you found when you first started (we simulate a case where a cipher vulnerability is found and needs to be disabled), find out which cipher the client and server will agree on after this change.
    -   **TLS \<= 1.2** If, for example `SEED`, we want to disable the cipher , we write`SSL_set_cipher_list(ssl, "DEFAULT:!SEED");`
    -   **TLS 1.3** uses a different set of ciphers (ciphersuites) and other API ( `SSL_set_ciphersuites`) functions , only a list of allowed ciphers is listed (you don't specify the one you don't want)
    -   Write down the name of the cipher you disabled and the name of the cipher that was chosen instead.
    -   Explain what the individual identifiers that make up the name of the cipher used in this way mean. Write down your findings.

### [](https://courses.fit.cvut.cz/BI-BEZ/tutorials/10.html#_verifikace-certifik%C3%A1tu-serveru)Server certificate verification

-   After creating a new context ( `SSL_CTX`), call `SSL_CTX_load_verify_locations`or `SSL_CTX_set_default_verify_paths` (and check the result) - this will set where the library should look for root certificates.
-   After creating the SSL connection ( `SSL_connect`), get the result of the verification using `SSL_get_verify_result`and test it.
-   Write down whether the verification was successful.

###### Note:

Certificate verification must be performed each time a connection is established.

### [](https://courses.fit.cvut.cz/BI-BEZ/tutorials/10.html#_p%C5%99e%C4%8Dten%C3%AD-certifik%C3%A1tu-ze-serveru)Read the certificate from the server

-   Get a certificate from ( `SSL_get_peer_certificate`)
-   Summarize the information on the certificate to the terminal (eg. `X509_get_subject_name`, `X509_get_issuer_name`, `X509_NAME_oneline`)
-   and write it to a file ( `PEM_write_X509`).

### [](https://courses.fit.cvut.cz/BI-BEZ/tutorials/10.html#_p%C5%99%C3%ADklad-k%C3%B3du-pro-vytvo%C5%99en%C3%AD-spojen%C3%AD)Example code for creating a connection

If we know the IPv4 address of the server, we only need a few commands to create a TCP connection.

``` {.highlightjs-ext .highlight}
struct sockaddr_in servaddr;
int sockfd = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);

memset(&servaddr, 0, sizeof(servaddr));
servaddr.sin_family = AF_INET;
servaddr.sin_addr.s_addr = inet_addr("111.111.111.111"); // ip address
servaddr.sin_port = htons(443);                          // port

// Pozor, nektere platformy maji jeste pole sin_len.

if (connect(sockfd, (struct sockaddr *)&servaddr, sizeof(servaddr)) != 0) {
    error...
}
```

###### Tip:

If you want to know both name resolution (DNS) and IPv4 and IPv6, we recommend it `man getaddrinfo`.

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

10. OpenSSL: Network connection, certificate verification, cipher setup
 [tutorials / 10.adoc](https://gitlab.fit.cvut.cz/BI-BEZ/bi-bez/blob/master/tutorials/10.adoc) , [last modified f10d3e76 (27. 4. 2021 at 13:14, Marina Shchavleva)](https://gitlab.fit.cvut.cz/BI-BEZ/bi-bez/commit/f10d3e76db1dafaa3f503a125559763f833edd87 "Update tutorials / 10.adoc")

Generated by [**FIT CTU Course Pages**](https://gitlab.fit.cvut.cz/course-pages/course-pages/) v0.8.0
 Page generated28. 5. 2021 at 16:14

[![Build status](./network_files/pipeline.svg)](https://gitlab.fit.cvut.cz/BI-BEZ/bi-bez/pipelines)

![Google Translate](./network_files/translate_24dp.png)

Original text
=============

Contribute a better translation

* * * * *
