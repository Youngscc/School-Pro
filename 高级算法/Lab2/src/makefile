quickSort: main.cpp
	g++ main.cpp -Wall -o quickSort


.PHONY:
data:
	g++ data.cpp -Wall -o makedata
	./makedata $(shell date "+%Y%m%d%H%M%S")

test1:
	./quickSort -N 1 $(shell date "+%Y%m%d%H%M%S")

test2:
	./quickSort -N 2 $(shell date "+%Y%m%d%H%M%S")
	
test3:
	./quickSort -N 3