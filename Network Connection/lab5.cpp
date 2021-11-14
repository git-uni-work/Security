#include <openssl/evp.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <openssl/ssl.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <iostream>
using namespace std;

#define ADDY "147.32.232.212"
#define HOSTNAME "fit.cvut.cz"
#define HTTP_REQUEST \
        "GET /en/student/forms HTTP/1.1\r\n"\
        "Host: " HOSTNAME "\r\n"\
        "Connection: close\r\n\r\n"

int main()
{
  int sockfd;
  int check;
 struct sockaddr_in servaddr;

 sockfd=socket(AF_INET,SOCK_STREAM,0);

 bzero(&servaddr,sizeof(servaddr));
 servaddr.sin_family = AF_INET;
 servaddr.sin_addr.s_addr=inet_addr(ADDY);
 servaddr.sin_port=htons(443);

 if ( connect(sockfd, (struct sockaddr *)&servaddr, sizeof(servaddr)) != 0 )
 {
   cout << "ERROR CONNECTING..." << endl;
   exit(1);
 }

 SSL_library_init();
 OpenSSL_add_ssl_algorithms();

 SSL_CTX * ctx = NULL;
 ctx = SSL_CTX_new(SSLv23_client_method());
 if( !ctx )
 {
   cout << "CONTEXT INIT FAILED" << endl;
   exit(2);
 }

  SSL_CTX_set_options(ctx, SSL_OP_NO_SSLv2 | SSL_OP_NO_SSLv3 | SSL_OP_NO_TLSv1);

  SSL * ssl = SSL_new(ctx);
  if( !ssl )
  {
    cout << "SSL INIT FAILED" << endl;
    exit(3);
  }

  check = SSL_set_tlsext_host_name(ssl, HOSTNAME);
  if( check != 1 )
  {
    cout << "SERVER SNI MECHANISM SETTING FAILED" << endl;
    exit(4);
  }

  check = SSL_set_fd(ssl, sockfd);
  if( check != 1 )
  {
    cout << "OPENING SSL CONNECTION FAILED" << endl;
    exit(5);
  }

  check = SSL_connect(ssl);
  if( check != 1 )
  {
    cout << "STARTING SSL CONNECTION FAILED" << endl;
    exit(6);
  }

  X509 * certificate = SSL_get_peer_certificate(ssl);
  if( !certificate )
  {
    cout << "REQUESTING CERTIFICATE FROM SERVER FAILED" << endl;
    exit(7);
  }

  FILE * certfile = fopen("certf.pem","wb");
  if( !certfile )
  {
    cout << "OPENING CERTIFICATE FILE FAILED" << endl;
    exit(8);
  }
  
  check = PEM_write_X509(certfile, certificate);
  if( check != 1 )
  {
    cout << "SENDING HTTP REQUEST FAILED" << endl;
    exit(9);
  }
  fclose(certfile);

  char buffer[1024] = HTTP_REQUEST;
  check = SSL_write(ssl, buffer, strlen(buffer));
  if( check < 0 )
  {
    cout << "SENDING HTTP REQUEST FAILED" << endl;
    exit(10);
  }

  FILE * output = fopen("htmlpage.txt","w");
  while( ( check = SSL_read(ssl, buffer, strlen(buffer)) ) > 0 )
  {
    fwrite(buffer, check, 1, output);
  }


  SSL_shutdown(ssl);
  SSL_free(ssl);
  SSL_CTX_free(ctx);
  return 0;
}
