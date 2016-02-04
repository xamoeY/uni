.PHONY: clean all oneside twoside

all: oneside twoside presentation

oneside:
	rubber --unsafe -d oneside.tex

twoside:
	rubber --unsafe -d twoside.tex

presentation:
	rubber --unsafe -d presentation.tex

clean:
	rubber --clean -d oneside.tex
	rubber --clean -d twoside.tex
	rubber --clean -d presentation.tex
