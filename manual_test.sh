#!/bin/bash

echo "=== MANUAL EXPANSION AND EXPORT TESTS ==="
echo

# Make the script executable
chmod +x test_expansion.sh

echo "1. Testing basic expansion:"
echo "Input: echo \$HOME"
echo "Expected: $HOME"
echo "Running..."
echo "echo \$HOME" | ./minishell
echo

echo "2. Testing export with expansion:"
echo "Input: export a='a b c'; export \$a=test"
echo "Expected: Error about invalid identifier"
echo "Running..."
cat > test_export.txt << EOF
export a='a b c'
export \$a=test
exit
EOF
./minishell < test_export.txt
rm -f test_export.txt
echo

echo "3. Testing your specific case:"
echo "Input: export a='a b c'; export d='c v b'; export \$a=\$d"
echo "Expected: Error about invalid identifier 'a b c=c v b'"
echo "Running..."
cat > test_specific.txt << EOF
export a='a b c'
export d='c v b'
export \$a=\$d
export
exit
EOF
./minishell < test_specific.txt
rm -f test_specific.txt
echo

echo "4. Testing expansion in echo:"
echo "Input: echo \$USER"
echo "Expected: $USER"
echo "Running..."
echo "echo \$USER" | ./minishell
echo

echo "5. Testing undefined variable:"
echo "Input: echo \$UNDEFINED_VAR"
echo "Expected: (empty line)"
echo "Running..."
echo "echo \$UNDEFINED_VAR" | ./minishell
echo

echo "6. Testing valid export:"
echo "Input: export TEST_VAR=hello; echo \$TEST_VAR"
echo "Expected: hello"
echo "Running..."
cat > test_valid.txt << EOF
export TEST_VAR=hello
echo \$TEST_VAR
exit
EOF
./minishell < test_valid.txt
rm -f test_valid.txt
echo

echo "=== INTERACTIVE TESTING ==="
echo "You can now test interactively:"
echo "1. Run: ./minishell"
echo "2. Try these commands:"
echo "   - export a='a b c'"
echo "   - export d='c v b'"
echo "   - export \$a=\$d"
echo "   - export (to see the list)"
echo "   - echo \$a"
echo "   - echo \$d"
echo

echo "=== DEBUGGING TIPS ==="
echo "To debug expansion issues:"
echo "1. Add printf statements in your expand function"
echo "2. Check what tokens are being created"
echo "3. Verify the export_var function is called with correct arguments"
echo "4. Test the is_valid function separately"
echo

echo "=== EXPECTED BEHAVIOR ==="
echo "For export \$a=\$d where a='a b c' and d='c v b':"
echo "1. Expansion should result in: 'a b c=c v b'"
echo "2. get_key_and_value should extract key: 'a b c'"
echo "3. is_valid should return 1 (invalid) because key contains spaces"
echo "4. pr_error should be called with the original argument"
echo "5. No variables should be created"
echo 