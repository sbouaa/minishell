#!/bin/bash

# Test script for heredoc syntax error handling
# This script tests various heredoc syntax error cases

echo "🧪 Testing Heredoc Syntax Error Handling"
echo "========================================"

# Colors for output
RED='\033[0;31m'
GREEN='\033[0;32m'
YELLOW='\033[1;33m'
NC='\033[0m' # No Color

# Function to test a command and check for expected error
test_heredoc_error() {
    local test_name="$1"
    local command="$2"
    local expected_error="$3"
    
    echo -e "\n${YELLOW}Test: $test_name${NC}"
    echo "Command: $command"
    echo "Expected: $expected_error"
    
    # Run the command and capture output
    output=$(echo "$command" | ./minishell 2>&1)
    exit_code=$?
    
    # Check if we got the expected error
    if echo "$output" | grep -q "$expected_error"; then
        echo -e "${GREEN}✅ PASS${NC}"
    else
        echo -e "${RED}❌ FAIL${NC}"
        echo "Actual output:"
        echo "$output"
        echo "Exit code: $exit_code"
    fi
}

# Test cases for heredoc syntax errors

echo -e "\n${YELLOW}1. Missing delimiter tests:${NC}"
test_heredoc_error "Missing delimiter" "echo hello <<" "expected delimiter after \`<<'"
test_heredoc_error "Missing delimiter with pipe" "echo hello << | cat" "expected delimiter after \`<<'"

echo -e "\n${YELLOW}2. Empty delimiter tests:${NC}"
test_heredoc_error "Empty delimiter" "echo hello << \"\"" "empty heredoc delimiter"
test_heredoc_error "Empty delimiter single quotes" "echo hello << ''" "empty heredoc delimiter"

echo -e "\n${YELLOW}3. Invalid delimiter tests:${NC}"
test_heredoc_error "Delimiter with <" "echo hello << <EOF" "invalid heredoc delimiter"
test_heredoc_error "Delimiter with >" "echo hello << >EOF" "invalid heredoc delimiter"
test_heredoc_error "Delimiter with |" "echo hello << |EOF" "invalid heredoc delimiter"
test_heredoc_error "Delimiter with multiple invalid chars" "echo hello << <|>EOF" "invalid heredoc delimiter"

echo -e "\n${YELLOW}4. Consecutive heredoc tests:${NC}"
test_heredoc_error "Consecutive heredocs" "echo hello << << EOF" "unexpected token \`<<'"
test_heredoc_error "Consecutive heredocs with delimiter" "echo hello << EOF << EOF" "unexpected token \`<<'"

echo -e "\n${YELLOW}5. Valid heredoc tests (should work):${NC}"
echo -e "\n${YELLOW}Test: Valid heredoc${NC}"
echo "Command: echo hello << EOF"
echo "Expected: Should work without errors"
output=$(echo -e "echo hello << EOF\nworld\nEOF" | ./minishell 2>&1)
if [ $? -eq 0 ]; then
    echo -e "${GREEN}✅ PASS${NC}"
else
    echo -e "${RED}❌ FAIL${NC}"
    echo "Output: $output"
fi

echo -e "\n${YELLOW}6. Edge cases:${NC}"
test_heredoc_error "Heredoc at end of line" "echo hello <<" "expected delimiter after \`<<'"
test_heredoc_error "Heredoc with space after" "echo hello << " "expected delimiter after \`<<'"
test_heredoc_error "Heredoc with tab after" "echo hello <<	" "expected delimiter after \`<<'"

echo -e "\n${YELLOW}7. Mixed error cases:${NC}"
test_heredoc_error "Heredoc after pipe error" "| << EOF" "unexpected token \`|'"
test_heredoc_error "Heredoc before pipe error" "<< EOF |" "unexpected end after \`|'"

echo -e "\n${GREEN}🎉 Heredoc Syntax Error Testing Complete!${NC}" 