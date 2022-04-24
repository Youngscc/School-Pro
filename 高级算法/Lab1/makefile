a : main.o naive.o minhash.o lsh.o
	g++ main.o naive.o minhash.o lsh.o -o a -Ofast

main.o : main.cpp
	g++ main.cpp -c -o main.o -Ofast

naive.o : naive.cpp
	g++ naive.cpp -c -o naive.o -Ofast

minhash.o : minhash.cpp
	g++ minhash.cpp -c -o minhash.o -Ofast

lsh.o : lsh.cpp
	g++ lsh.cpp -c -o lsh.o -Ofast

.PHONY: clean
clean:
	@rm -rf *.o
	@rm a
