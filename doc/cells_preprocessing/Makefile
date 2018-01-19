# set latexfile to the name of the main file without the .tex
latexfile = paper

all :
	rm bin/$(latexfile).pdf -rf
	pdflatex $(latexfile).tex

	cp $(latexfile).pdf bin/.
