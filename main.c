#include <stdio.h>
#include <unistd.h>

// Deklaration der exakten, kleingeschriebenen PS5-Systemfunktionen
extern int sceShellUtilInit(void);
extern int sceShellUtilActivateHomeMenu(void);

int main() {
    // Initialisiert das Shell-Subsystem der PS5
    sceShellUtilInit();

    // Die Payload bleibt permanent als Hintergrund-Prozess aktiv
    while (1) {
        
        // Wir nutzen einen unschädlichen, passiven Timer:
        // Da die PS5 nach dem Aufwachen exakt 5 Sekunden braucht, 
        // bis das Netzwerk steht, schlafen wir hier. In dieser Zeit 
        // ueberschreibt dein Pi die app.db via FTP im laufenden Betrieb.
        sleep(5);

        // Nativer "Homebutton-Druck" ueber das PS5-Betriebssystem.
        // Das zwingt das Kachel-UI live zum Neueinlesen der app.db!
        sceShellUtilActivateHomeMenu(); 

        // 10 Sekunden schlafen, um doppeltes Feuern beim Aufwachen zu verhindern
        sleep(10);
    }

    return 0;
}
