build: snake

snake: snake.c 
	gcc -Wall snake.c -o snake -lcurses

clean:
	rm -f snake

run:
	./snake