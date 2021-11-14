CXX = g++
CXXFLAGS = -Wall -lcrypto
FILE = lab3.cpp
OUT = ./a.out
IMG1 = homer-simpson.bmp
IMG2 = Mad_scientist.bmp
IMG1_ECB_DEC = homer-simpson_ecb_dec.bmp
IMG1_CBC_DEC = homer-simpson_cbc_dec.bmp
IMG2_ECB_DEC = Mad_scientist_ecb_dec.bmp
IMG2_CBC_DEC = Mad_scientist_cbc_dec.bmp


clean:
	rm homer-simpson_ecb.bmp
	rm homer-simpson_cbc.bmp
	rm Mad_scientist_ecb.bmp
	rm Mad_scientist_cbc.bmp
	rm $(IMG1_ECB_DEC)
	rm $(IMG1_CBC_DEC)
	rm $(IMG2_ECB_DEC)
	rm $(IMG2_CBC_DEC)

compile : $(OUT)

run : $(OUT)
	$(OUT)
	if diff $(IMG1) $(IMG1_ECB_DEC) ;then echo "\n \"$(IMG1)\" & \"$(IMG1_ECB_DEC)\" MATCH\n\n";fi
	if diff $(IMG1) $(IMG1_CBC_DEC) ;then echo "\n \"$(IMG1)\" & \"$(IMG1_CBC_DEC)\" MATCH\n\n";fi
	if diff $(IMG2) $(IMG2_ECB_DEC) ;then echo "\n \"$(IMG2)\" & \"$(IMG2_ECB_DEC)\" MATCH\n\n";fi
	if diff $(IMG2) $(IMG2_CBC_DEC) ;then echo "\n \"$(IMG2)\" & \"$(IMG2_CBC_DEC)\" MATCH\n\n";fi


$(OUT) : $(FILE)
	$(CXX) $(CXXFLAGS) $(FILE)
