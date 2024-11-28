/*

************************************************************
**
** Created by: Amiga4ever with StormC5 ED/gcc
**
** Project: PWGen
**
** File:
**
** Date: 19-04-2024
**
************************************************************

*/

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>
#include <unistd.h>
#include <sys/ioctl.h>
#include <termios.h>


void neuesPW();

// struct my_winsize{
// 	unsigned short ws_row;
// 	unsigned short ws_col;
// 	unsigned short ws_xpixel;
// 	unsigned short ws_ypixel;
// };

int main() {

	// struct my_winsize w;
	// ioctl(STDOUT_FILENO, IOC_IN, &w);
	// w.ws_row = 25;
	// w.ws_col = 80;
	// ioctl(STDOUT_FILENO, IOC_IN, &w);

    int h = 80; // Neue Höhe des Terminals
    int w = 80; // Neue Breite des Terminals

    // Konstruiere den Befehl mit den Variablen h und w
    char command[100];
    sprintf(command, "echo -ne \"\\e[8;%d;%dt\"", h, w);

    // Führe den Befehl aus, um die Fenstergröße zu setzen
    system(command);


    printf(".---------------------------------.\n");
    printf("|  .---------------------------.  |\n");
    printf("|[]|                           |[]|\n");
    printf("|  |  P A S S W O R T -     _  |  |\n");
    printf("|  |                     _ //  |  |\n");
    printf("|  |  G E N E R A T O R  \\X/   |  |\n");
    printf("|  |                           |  |\n");
    printf("|  |                           |  |\n");
    printf("|  |  enter the desired        |  |\n");
    printf("|  |  password length          |  |\n");
    printf("|  |  (max. 512)               |  |\n");
    printf("|  `---------------------------'  |\n");
    printf("|      __________________ _____   |\n");
    printf("|     |   ___            |     |  |\n");
    printf("|     |  |   |           |     |  |\n");
    printf("|     |  |   |           |     |  |\n");
    printf("|     |  |   |           |     |  |\n");
    printf("|     |  |___|           |     |  |\n");
    printf("\\_____|__________________|_____|__|\n");
    printf("\n");

    neuesPW();
    printf("\n");
    printf("#############################################\n");

    int input = 0;

    do {
        printf("#     [1] - weiteres Passwort erstellen\t    #\n");
        printf("#     [0] - Programm beenden\t\t    #\n");
        printf("#############################################\n");
        scanf("%d", &input);

        if (input == 1) {
            neuesPW();
            printf("\n");
        } else if (input == 0) {
            printf("Danke fuer die Benutzung des PW-Generators!\n");
            break;
        } else {
            printf("Ungueltige Eingabe. Nur 0 oder 1!\n");
        }

    } while (input != 1 || input != 0);
}

void neuesPW() {
    int pwLaenge = 0;

    int mitSonderzeichen = 0; // Flag, um zu ueberpruefen, ob Sonderzeichen gewuenscht sind
    printf("# Gewuenschte Zeichenlaenge des Passworts: #\n");
    scanf("%d", &pwLaenge);

	//printf("Sollen Sonderzeichen enthalten sein? (1 = Ja, 0 = Nein): ");
    //scanf("%d", &mitSonderzeichen);


	while(1){
	    bool sonderZ = false;

	    printf("Sollen Sonderzeichen enthalten sein? (1 = Ja, 0 = Nein): ");
    	scanf("%d", &mitSonderzeichen);

    	if (mitSonderzeichen == 1 || mitSonderzeichen == 0){
    	    sonderZ = (mitSonderzeichen == 1);
    	    break; // Schleife verlassen, wenn die Eingabe gueltig war
    	    }
		else{
		    printf("Ungueltige Eingabe. Nur 0 oder 1!\n");
		    }
	    }

    if (pwLaenge <= 512) {
        char pw[513] = {0}; // Array fuer das Passwort

        const char upperCase[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
        const char lowerCase[] = "abcdefghijklmnopqrstuvwxyz";
        const char numbers[] = "0123456789";
        const char sSigns[] = "!@#$%&.*";

        srand((unsigned int)time(NULL));

        for (int i = 0; i < pwLaenge; i++) {
            int r = rand() % (mitSonderzeichen ? 4 : 3); // Beruecksichtigt Sonderzeichen oder nicht
            int k = 0;

            switch (r) {
                case 0:
                    k = rand() % 26;
                    pw[i] = upperCase[k];
                    break;
                case 1:
                    k = rand() % 26;
                    pw[i] = lowerCase[k];
                    break;
                case 2:
                    k = rand() % 10;
                    pw[i] = numbers[k];
                    break;
                case 3:
                    if (mitSonderzeichen) {
                        k = rand() % 8;
                        pw[i] = sSigns[k];
                    } else {
                        // ueberspringe den Sonderzeichen-Teil und generiere erneut einen Zufallswert
                        i--; // Dekrementiere i, um die Schleife fuer diesen Durchlauf zu wiederholen
                    }
                    break;
                default:
                    break;
            }
        }

        pw[pwLaenge] = '\0'; // Null-Zeichen am Ende des Passworts setzen

        printf("Dein neues Passwort: \n\n");
        printf("%s\n", pw);
    } else {
        printf("Ungueltige Eingabe, keine Buchstaben!\n");
        printf("Nur maximal 512 Zeichen moeglich!\n");
    }
}
