.PHONY: clean

oneside:
	rubber --unsafe -d oneside.tex

twoside:
	rubber --unsafe -d twoside.tex

default: oneside twoside

clean:
	rubber --clean -d oneside.tex
	rubber --clean -d twoside.tex
