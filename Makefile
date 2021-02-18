CC=gcc

test:
	$(if $(f),,$(error c파일주소 없음))
	@${CC} $(f) -o test && ./test && rm ./test
.PHONY:test