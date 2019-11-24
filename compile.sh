
flex mini_l.lex
bison -v -d --file-prefix=y mini_l.y
gcc -o parser y.tab.c lex.yy.c -lfl
gcc -o test_table symbol_table.c

