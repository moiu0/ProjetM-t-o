all:mainC

mainC.o: mainC.c Header.h
	gcc -c $< -o $@

ABR.o: ABR.c Header.h
	gcc -c $< -o $@

AVL.o: AVL.c Header.h
	gcc -c $< -o $@

TAB.o: TAB.c Header.h
	gcc -c $< -o $@

mainC: mainC.o ABR.o AVL.o TAB.o
	gcc $^ -o $@

clear:
	rm *.o