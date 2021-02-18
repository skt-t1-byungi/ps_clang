CC=gcc

test:
	$(if $(f),,$(error c파일주소 없음))
	@${CC} $(f) ./libtap/tap.c -I./ -o test && ./test && rm ./test
.PHONY:test