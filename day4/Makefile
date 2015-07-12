all:
	gcc -o frommem frommem.c bin_sem.c
	gcc -o tomem tomem.c bin_sem.c
clean:
	rm -f frommem tomem file.out out
md:
	md5sum 100mb_file
	md5sum out
ex:
	./tomem & ./frommem
