#!/bin/bash

echo "=== TESTING YOUR SPECIFIC EXPORT EXPANSION ISSUE ==="
echo

echo "Step 1: Setting up variables"
echo "export a='a b c'"
echo "export d='c v b'"
echo

echo "Step 2: Testing the problematic command"
echo "export \$a=\$d"
echo

echo "Expected behavior:"
echo "- Expansion should result in: 'a b c=c v b'"
echo "- Key extraction should be: 'a b c'"
echo "- is_valid('a b c') should return 1 (invalid)"
echo "- Error message should be printed"
echo "- No variables should be created"
echo

echo "Running test..."
cat > test_case.txt << 'EOF'
export a='a b c'
export d='c v b'
echo "Before export \$a=\$d:"
export
echo
echo "Running: export \$a=\$d"
export $a=$d
echo
echo "After export \$a=\$d:"
export
echo
echo "Testing echo \$a and \$d:"
echo "a: '$a'"
echo "d: '$d'"
exit
EOF

./minishell < test_case.txt
rm -f test_case.txt

echo
echo "=== ANALYSIS ==="
echo "If you see variables like 'b', 'c', 'v' being created, it means:"
echo "1. The expansion is working but creating multiple tokens"
echo "2. The export function is processing each token separately"
echo "3. The word splitting is happening incorrectly"
echo
echo "If you see an error message about invalid identifier, that's correct behavior."
echo
echo "If you see no error and no variables created, that's also correct."
echo 