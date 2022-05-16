NAME = mypy

LLVM_CONFIG = /usr/bin/llvm-config-13

NO_WARNING =  -Wno-return-type \
	-Wno-c++11-compat-deprecated-writable-strings \
	-Wno-deprecated-register \
	-Wno-switch \

CXXFLAGS = `$(LLVM_CONFIG) --cppflags` -std=c++14 $(NO_WARNING) -fpermissive 
LDFLAGS = `$(LLVM_CONFIG) --ldflags`
LIBS = `$(LLVM_CONFIG) --libs --system-libs`

OBJS = parser.o lex.o ast.o main.o code_gen.o

all : $(NAME)

parser.cpp: parser.ypp
	bison -d -o parser.cpp parser.ypp

parser.hpp: parser.cpp

lex.cpp: lex.l
	flex -o lex.cpp lex.l

%.o: %.cpp ast.hpp code_gen.hpp
	g++ -c $(CXXFLAGS) -o $@ $<

$(NAME): $(OBJS)
	g++ -o $@ $(OBJS) $(LIBS) $(LDFLAGS)

.PHONY: clean
clean:
	-rm -f *.o
	-rm -f parser.hpp parser.cpp lex.cpp mypy
	-rm -f *.s
	-rm -f *.ll
