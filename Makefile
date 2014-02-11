all: arpinfo.c
	gcc -o arpinfo arpinfo.c && chmod 755 arpinfo
install:
	cp arpinfo ~/bin/
clean:
	[ -e arpinfo ] && rm arpinfo
