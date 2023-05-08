main: main.c filemethods.c
	cc -o main main.c filemethods.c -lexif
asm: main.c filemethods.c
	cc -S main.c filemethods.c -lexif  -fverbose-asm
clean:
	rms -f main