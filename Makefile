run: clearsrc compile exec clean
.PHONY: run

compile: objects.cpp utils.cpp
	@echo "\033[1;94mCOMPILING FILES...\033[0m\n"
	g++ -c utils.cpp -lm
	g++ -c main.cpp -lm
	g++ -o run utils.o main.o

exec: compile
	@echo "\033[1;94mSTARTING...\033[0m\n"
	./run

clean:
	@echo "\033[1;94mDELETING COMPILED FILES...\033[0m\n"
	rm -rf *.o *.out
	rm -rf run

clearsrc:
	clear
