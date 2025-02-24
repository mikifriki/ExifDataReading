main: main.c filemethods.c
	cc -o main main.c filemethods.c exif.c -lexif -g
asm: main.c filemethods.c
	cc -S main.c filemethods.c -lexif  -fverbose-asm
clean:
	rm -f main