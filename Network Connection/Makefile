CXX = g++
CXXFLAGS = -Wall -lcrypto -lssl
FILE = lab5.cpp
OUT = ./a.out
HTML = htmlpage.txt
CERTIFICATE = certf.pem

run : $(OUT)
	$(OUT)
	openssl x509 -in $(CERTIFICATE) -noout -subject -issuer -dates -pubkey -modulus -fingerprint

clean:
	rm $(HTML)
	rm $(CERTIFICATE)

compile : $(OUT)


$(OUT) : $(FILE)
	$(CXX) $(CXXFLAGS) $(FILE)
