all: conv caeser

conv: enc_dec/all_conv.cpp
	g++ -o ../bin/conv enc_dec/all_conv.cpp -I../include

caeser: cipher/caeser/caeser_cipher.c
	gcc -o ../bin/caeser cipher/caeser/caeser_cipher.c 

clean:
	rm -rf ../bin/conv ../bin/caeser
