main: main.o Scheduling.o Simulated_Annealing.o DAG.o
 
    g++ -o main main.o Scheduling.o Simulated_Annealing.o DAG.o

main.o: main.cpp

	g++ -c main.cpp

Scheduling.o: Scheduling.cpp

	g++ -c Scheduling.cpp
 
Simulated_Annealing.o: Simulated_Annealing.cpp

    g++ -c Simulated_Annealing.cpp
 
DAG.o: DAG.cpp
 
    g++ -c DAG.cpp
 
clean:
 
    rm -rf *.o