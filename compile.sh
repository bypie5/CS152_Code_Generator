[ -e parser ] && rm parser
[ -e symbol_table_test ] && rm symbol_table_test
[ -e gen_code_test ] && rm gen_code_test


flex mini_l.lex
bison -v -d --file-prefix=y mini_l.y
gcc -o parser y.tab.c lex.yy.c -ll
