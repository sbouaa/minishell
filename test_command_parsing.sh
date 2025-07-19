#!/bin/bash

echo "=== TESTING COMMAND PARSING ==="
echo

echo "Test 1: Empty double quotes"
echo "Input: \"\""
echo "Expected: command not found"
echo "Running..."
echo '""' | ./minishell
echo

echo "Test 2: Empty single quotes"
echo "Input: ''"
echo "Expected: command not found"
echo "Running..."
echo "''" | ./minishell
echo

echo "Test 3: Just spaces"
echo "Input: '   '"
echo "Expected: command not found"
echo "Running..."
echo "   " | ./minishell
echo

echo "Test 4: Empty string as argument"
echo "Input: echo \"\""
echo "Expected: (empty line)"
echo "Running..."
echo 'echo ""' | ./minishell
echo

echo "Test 5: Command with empty argument"
echo "Input: ls \"\""
echo "Expected: ls error or empty directory"
echo "Running..."
echo 'ls ""' | ./minishell
echo

echo "=== ANALYSIS ==="
echo "If Test 1 and 2 give 'command not found', your fix is working correctly."
echo "If they give no output, we need to check the command name parsing."
echo 