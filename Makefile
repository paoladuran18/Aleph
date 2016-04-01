# Pon en esta variable el camino hacia aleph-w
ALEPH = /home/paoladuran/Bibliotecas/Aleph/aleph

# pon en esta variable el camino hacia clang
#CLANGPATH = clang++

CXX = clang++

OPTIMIZATION = -g -O0

WARN = -Wall -Wextra -Wcast-align -Wno-sign-compare -Wno-write-strings \
       -Wno-parentheses -Wno-invalid-source-encoding

FLAGS = $(OPTIMIZATION) -std=c++11 $(WARN)

INCLUDE = -I. -I $(ALEPH) 

LIBS = -L $(ALEPH) \
       -lAleph -lnana -lm -lgsl -lgslcblas -lgmp -lmpfr -lasprintf -lpthread -lc

all: word-find 

clean:
	rm -f word-find 

word-find: tpl_tree_node.H word-find.C word-find.H dictnode.o 
	$(CXX) $(FLAGS) $(INCLUDE) $@.C -g -O0 -o $@ dictnode.o $(LIBS)

