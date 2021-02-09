FROM silkeh/clang:latest

WORKDIR /usr
CMD clang ${file} -o test && ./test
