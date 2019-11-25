flex mini_l.lex
bison -v -d --file-prefix=y mini_l.y
gcc -o parser y.tab.c lex.yy.c -ll
gcc -o symbol_table_test symbol_table.c