#!/bin/bash

SCRIPT_DIR="$(dirname "$0")"
source "${SCRIPT_DIR}/color_codes.sh"

SIGNALS=(2 3 4 6 8 11 15)

echo -e "${COLOR_BOLD_GREEN}\ntesting signal handler in backtrace.c${COLOR_RESET}"

#create processes in background
for SIGNAL in "${SIGNALS[@]}"
do
	ASAN_OPTIONS=handle_sigfpe=false:allow_user_segv_handler=true ./backtrace&
done

sleep 1

#kill background processes
for SIGNAL in "${SIGNALS[@]}"
do
	echo -e "${COLOR_MESSAGE}\ntesting Signal $SIGNAL:${COLOR_RESET}"
	pkill -$SIGNAL -n backtrace
	sleep 1
done
echo -e "${COLOR_BOLD_GREEN}\ncleaning up all remaining test processes...${COLOR_RESET}"
while true
do 
	pkill backtrace || exit 0 
done
