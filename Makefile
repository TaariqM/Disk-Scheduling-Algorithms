projf: Proj_F.c
	gcc -o projf Proj_F.c -I.
	./projf
all: run

run: projf
	./projf

.PHONY: all run