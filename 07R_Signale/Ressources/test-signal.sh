#!/bin/bash

SCRIPT_DIR="$(dirname "$0")"
source "${SCRIPT_DIR}/color_codes.sh"

SIGNALS=(2 3 4 6 8 11 15)


# testing input
echo -e "${COLOR_BOLD_GREEN}Testing input variants and error handling${COLOR_RESET}"

echo -e "${COLOR_MESSAGE}No Parameter:${COLOR_RESET}"
./send-signal

echo -e "${COLOR_MESSAGE}Only 1 Parameter:${COLOR_RESET}"
./send-signal -p 42
./send-signal -s 23

echo -e "${COLOR_MESSAGE}Wrong  Parameter:${COLOR_RESET}"
./send-signal -x -p 123 -s 123
echo -e "${COLOR_MESSAGE}Error Handling:${COLOR_RESET}"
./send-signal -p 123 -s 123


# create processes in background
for SIGNAL in "${SIGNALS[@]}"
do
	# ASAN_OPTIONS=handle_sigfpe=false:allow_user_segv_handler=true ./backtrace/backtrace > /dev/null &
	./print-signal &
done

sleep 1

# kill background processes
echo -e "${COLOR_MESSAGE}testing signal sending${COLOR_RESET}"
for SIGNAL in "${SIGNALS[@]}"
do
	echo -e "${COLOR_MESSAGE}testing Signal $SIGNAL:${COLOR_RESET}"
	COMMAND="./send-signal -s $SIGNAL -p $(pgrep -n print-signal)"
	# echo $COMMAND
	eval $COMMAND
	sleep 1
done
echo -e "${COLOR_MESSAGE}cleaning up all remaining processes...${COLOR_RESET}"
while true
do 
	pkill print-signal || exit 0 
done
