# projects
PA := polynomialAnalyzer
rrLL := rightRecursiveLL
MP := multiplicationPolynomials
STACK := stack

all: makeDirs $(PA) $(rrLL) $(MP) $(STACK)

makeDirs:
	mkdir -p bin lib

$(PA):
	cd $(PA) && $(MAKE)

$(rrLL):
	cd $(rrLL) && $(MAKE)

$(MP):
	cd $(MP) && $(MAKE)

$(STACK):
	cd $(STACK) && $(MAKE)

.PHONY: all $(PA) $(rrLL) $(MP) $(STACK)
