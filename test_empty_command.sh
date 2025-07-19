#!/bin/bash

echo "=== TESTING EMPTY COMMAND HANDLING ==="
echo

echo "Test 1: Empty double quotes"
echo "Expected: minishell: command not found"
echo "Running..."
echo '""' | ./minishell
echo

echo "Test 2: Empty single quotes"
echo "Expected: minishell: command not found"
echo "Running..."
echo "''" | ./minishell
echo

echo "Test 3: Just spaces"
echo "Expected: minishell: command not found"
echo "Running..."
echo "   " | ./minishell
echo

echo "Test 4: Empty string as argument (should work)"
echo "Expected: (empty line)"
echo "Running..."
echo 'echo ""' | ./minishell
echo

echo "Test 5: Empty string with spaces"
echo "Expected: (empty line)"
echo "Running..."
echo 'echo " "' | ./minishell
echo

echo "=== SUMMARY ==="
echo "Empty commands should now give 'command not found' errors"
echo "Empty strings as arguments should work normally"
echo 