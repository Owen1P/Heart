.PHONY: clean run
.SILENT:

heart.o: heart.c
	gcc -o $@ $< -lm

run: heart.o
	./$<

clean:
	rm -rf heart.o
