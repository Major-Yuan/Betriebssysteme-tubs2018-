#!/bin/bash
echo -e "\n\033[1;32mTesting Reading Input:\033[0m"
tests/test-input
echo -e "\n\033[1;32mTesting Processes:\033[0m"
tests/test-foreground
echo -e "\n\033[1;32mTesting Background Processes:\033[0m"
tests/test-background
echo -e "\n\033[1;32mTesting Collecting Terminated Background Processes:\033[0m"
tests/test-zombies
echo -e "\n\033[1;32mTesting Changing Directories:\033[0m"
tests/test-cd
ls
echo -e "\n\033[1;32mTesting Listing Background Processes:\033[0m"
tests/test-walklist
