# " BLOCK CIPHER "

------------------------------------------------------------------------------------

1.  Write a program that copies the header and **encrypts** part of the image data file using AES in ECB mode. The output file will be named `name_ecb.`.
2.  Write a program that **decrypts the** image encrypted by the first program. The output file will be named`_dec.`
    -   Compare the original image and its encrypted form and explain your findings.
3.  Change the operating mode used for both encryption and decryption to **CBC** and create `()_cbc.` and `()_cbc_dec.`
    -   Compare the original image and its encrypted form and explain your findings.


**Image data**

The order of the flats is little-endian. There is no need to further process the color map or the image ID, you just need to skip them correctly and not encrypt them. The image data itself must be encrypted, nothing else.

###### Tip:

A detailed description of the image format is available, for example, [here](http://www.paulbourke.net/dataformats/tga/) .

### How to encrypt a longer file, field, etc.

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

![img1] (homer-simpson.bmp?raw=true "Title")
![img2] (homer-simpson_ecb.bmp?raw=true "Title")
![img3] (homer-simpson_cbc.bmp?raw=true "Title")
