#include "symbol_table.h"

int main() {
	init_table(Table, SIZE);

	insert(Table, "i");
	insert(Table, "j");
	insert(Table, "size");
	insert(Table, "temp");

	print(Table, SIZE);
}

