main: main.cpp BloomFilter.h ArraySet.h
	g++ main.cpp -o main -Ofast

.PHONY:
data: data.cpp
	g++ data.cpp -o data -Ofast

check: check.cpp
	g++ check.cpp -o check -Ofast

clean:
	rm data
	rm main
	rm check