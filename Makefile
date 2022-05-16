NAME = mypy

LLVM_CONFIG = /usr/bin/llvm-config-13

NO_WARNING =  -Wno-return-type \
	-Wno-c++11-compat-deprecated-writable-strings \
	-Wno-deprecated-register \
	-Wno-switch \

CXXFLAGS = `$(LLVM_CONFIG) --cppflags` -std=c++14 $(NO_WARNING) -fpermissive 
LDFLAGS = `$(LLVM_CONFIG) --ldflags`
LIBS = `$(LLVM_CONFIG) --libs --system-libs`

OBJS = parser.o tokenizer.o ast.o  main.o CodeGenerator.o

all : $(NAME)

parser.hpp: ./src/parser.y
	bison -d -o ./src/parser.hpp ./src/parser.y

lex.cpp: ./src/lex.l
	flex -o ./src/lex.cpp ./src/lex.l
# parser.hpp: ./src/parser.cpp

%.o: %.cpp ./src/%.cpp ./src/%.hpp
	g++ -c $(CXXFLAGS) -g -o $@ $< 

$(NAME): ./src/$(OBJS)
	g++ -o $@ ./src/$(OBJS) $(LIBS) $(LDFLAGS)

.PHONY: clean
clean:
	-rm -f *.o ./src/*.o
	-rm -f ./src/parser.hpp ./src/parser.hpp ./src/lex.cpp ./mypy
	-rm -f *.s
	-rm -f *.ll
