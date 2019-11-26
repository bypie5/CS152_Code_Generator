./compile.sh

echo "custom.min:"
./parser test_files/custom.min
echo

echo "errors.min:"
./parser test_files/errors.min
echo

echo "fib.min:"
./parser test_files/fib.min
echo

echo "fibonacci.min:"
./parser test_files/fibonacci.min
echo

echo "mini.min:"
./parser test_files/mini.min
echo

echo "mytest.min:"
./parser test_files/mytest.min
echo

echo "semantic_error.min:"
./parser test_files/semantic_error.min
echo

echo "syntax_error_1.min:"
./parser test_files/syntax_error_1.min
echo

echo "syntax_error_2.min:"
./parser test_files/syntax_error_2.min
