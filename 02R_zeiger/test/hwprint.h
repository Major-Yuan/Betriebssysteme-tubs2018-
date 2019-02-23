#ifndef H_BS_HWPRINT
#define H_BS_HWPRINT
#define BS_HWPRINT_WIDTH 39
#define BS_HWPRINT_MANUAL_PREFIX "MANUAL"

#define BS_SUCCESS "\e[32merfolgreich\e[0m\n"
#define BS_FAILURE "\e[31mfehlgeschlagen\e[0m\n"

#define BS_HW_FORMATSTRING \
"\n    \e[30;47;1m╔═════════════════════════════════════════╗\e[0m\n"\
"    \e[30;47;1m║             Zusammenfassung             ║█\e[0m\n"\
"    \e[30;47;1m╟─────────────────────────────────────────╢█\e[0m\n"\
"    \e[30;47;1m║ Aufgabe: %30s ║█\e[0m\n"\
"    \e[30;47;1m║                                         ║█\e[0m\n"\
"    \e[30;47;1m║ automatisch verteilte Punkte: %4d / %2d ║█\e[0m\n"\
"    \e[30;47;1m║ manuell zu bestimmende Punkte:      %3d ║█\e[0m\n"\
"    \e[30;47;1m║                                         ║█\e[0m\n"\
"    \e[30;47;1m║ %39s ║█\e[0m\n"\
"    \e[30;47;1m╚═════════════════════════════════════════╝█\e[0m\n"\
"     \e[30;47;1m███████████████████████████████████████████\e[0m\n\n"

#include <stdio.h>

// in case the implementation gets moved to its own file
void bs_hw_print(int, int, int, char*);
void bs_hw_manual(char*, char*);
void bs_hw_next();

void bs_hw_print(int erreicht, int automatisch, int manuell, char* aufgabenname) {
    float percent = (float)erreicht/(float)automatisch;
    float width = BS_HWPRINT_WIDTH;
    float fill_level = width * percent;
    fill_level += 0.5;
    char progress[BS_HWPRINT_WIDTH+1];
    progress[0] = '[';
    for (int i = 0; i < BS_HWPRINT_WIDTH-2; i++) {
	progress[i+1] = (i < fill_level) ? '#' : ' ';
    }
    progress[BS_HWPRINT_WIDTH-1] = ']';
    progress[BS_HWPRINT_WIDTH] = 0;
    printf(BS_HW_FORMATSTRING,
	    aufgabenname,
	    erreicht, automatisch,
	    manuell,
	    progress
    );
}

void bs_hw_manual(char* title, char* target) {
    printf("\e[30;1;47m[%s]\e[0m\e[33;1m %s\n\e[30;8;1;47m[%s]\e[0m \e[0m\e[33m>> \e[0;1m%s\e[0m\n", BS_HWPRINT_MANUAL_PREFIX, title, BS_HWPRINT_MANUAL_PREFIX, target);
}

void bs_hw_next() {
    printf("\e[0m\n=======================================================\n\n");
}

#endif
