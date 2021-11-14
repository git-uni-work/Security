CXX = g++
CXXFLAGS = -Wall -lcrypto
FILE1 = lab2.1.cpp
FILE2 = lab2.2.cpp
OUT1 = ./lab21
OUT2 = ./lab22

all :
	make compile

compile : $(OUT1) $(OUT2)

run : $(OUT1) $(OUT2)
	$(OUT1)
	$(OUT2)

$(OUT1) : $(FILE1)
	$(CXX) $(CXXFLAGS) $(FILE1) -o $(OUT1)

$(OUT2) : $(FILE2)
	$(CXX) $(CXXFLAGS) $(FILE2) -o $(OUT2)
