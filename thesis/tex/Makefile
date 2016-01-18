.PHONY: clean all oneside twoside

all: oneside twoside

oneside:
	rubber --unsafe -d oneside.tex

twoside:
	rubber --unsafe -d twoside.tex

clean:
	rubber --clean -d oneside.tex
	rubber --clean -d twoside.tex
