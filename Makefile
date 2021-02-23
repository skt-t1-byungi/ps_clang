CC=gcc
CFLAGS=-Wall
LDFLAGS=./libtap/tap.c -I./ -lm
test:
	$(if $(f),,$(error c파일주소 없음))
	@${CC} $(f) $(CFLAGS) $(LDFLAGS) -o test && ./test && rm ./test 
.PHONY:test