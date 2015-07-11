all:
	gcc -o frommem frommem.c
	gcc -o tomem tomem.c
clean:
	rm -f frommem tomem file.out out
md:
	md5sum 1mb_file
	md5sum out
ex:
	./tomem & ./frommem
