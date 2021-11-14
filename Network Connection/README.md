# " NETWORK CERTIFICATES "

-   connects to a web server (see url below)
-   verifies the server certificate
-   sets and lists the type of cipher used
-   download page [https://fit.cvut.cz/cs/fakulta/o-fakulte](https://fit.cvut.cz/cs/fakulta/o-fakulte) to file,
-   lists information about the fit.cvut.cz server certificate,
-   saves it to a PEM file.

Documentation for the openssl library can be found on the project website: [http://www.openssl.org/docs/](http://www.openssl.org/docs/) , [https://wiki.openssl.org/index.php/SSL/TLS\_Client](https://wiki.openssl.org/index.php/SSL/TLS_Client) , instructions for working with X.509 certificates, e.g. at [https://zakird.com/2013/10/13/certificate-parsing-with-openssl](https://zakird.com/2013/10/13/certificate-parsing-with-openssl) . Remember to refer to resources properly.

### Basic procedure

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

### Cipher used

-   Find out which ciphers the client and server agree on by default
    -   after establishing an encrypted connection, make a call `SSL_get_cipher_name`
-   Before calling, `SSL_connect`disable the specific cipher that you found when you first started (we simulate a case where a cipher vulnerability is found and needs to be disabled), find out which cipher the client and server will agree on after this change.
    -   **TLS \<= 1.2** If, for example `SEED`, we want to disable the cipher , we write`SSL_set_cipher_list(ssl, "DEFAULT:!SEED");`
    -   **TLS 1.3** uses a different set of ciphers (ciphersuites) and other API ( `SSL_set_ciphersuites`) functions , only a list of allowed ciphers is listed (you don't specify the one you don't want)
    -   Write down the name of the cipher you disabled and the name of the cipher that was chosen instead.
    -   Explain what the individual identifiers that make up the name of the cipher used in this way mean. Write down your findings.

### Server certificate verification

-   After creating a new context ( `SSL_CTX`), call `SSL_CTX_load_verify_locations`or `SSL_CTX_set_default_verify_paths` (and check the result) - this will set where the library should look for root certificates.
-   After creating the SSL connection ( `SSL_connect`), get the result of the verification using `SSL_get_verify_result`and test it.
-   Write down whether the verification was successful.

###### Note:

Certificate verification must be performed each time a connection is established.

### Read the certificate from the server

-   Get a certificate from ( `SSL_get_peer_certificate`)
-   Summarize the information on the certificate to the terminal (eg. `X509_get_subject_name`, `X509_get_issuer_name`, `X509_NAME_oneline`)
-   and write it to a file ( `PEM_write_X509`).

### Example code for creating a connection

If we know the IPv4 address of the server, we only need a few commands to create a TCP connection.

``` {.highlightjs-ext .highlight}
struct sockaddr_in servaddr;
int sockfd = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);

memset(&servaddr, 0, sizeof(servaddr));
servaddr.sin_family = AF_INET;
servaddr.sin_addr.s_addr = inet_addr("111.111.111.111"); // ip address
servaddr.sin_port = htons(443);                          // port


if (connect(sockfd, (struct sockaddr *)&servaddr, sizeof(servaddr)) != 0) {
    error...
}
```

###### Tip:

If you want to know both name resolution (DNS) and IPv4 and IPv6, we recommend it `man getaddrinfo`.
