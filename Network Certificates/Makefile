CXX = g++
CXXFLAGS = -Wall -lcrypto -lssl
FILE = lab6.cpp
OUT = ./a.out | less
HTML = htmlpage.txt
CERTIFICATE = certf.pem

run : $(OUT)
	$(OUT)
	openssl s_client -connect fit.cvut.cz:443 -showcerts | less

clean:
	rm $(HTML)
	rm $(CERTIFICATE)

compile : $(OUT)


$(OUT) : $(FILE)
	$(CXX) $(CXXFLAGS) $(FILE)
