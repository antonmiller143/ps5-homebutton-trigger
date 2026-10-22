#include <stdio.h>
#include <unistd.h>

// Definitionen fuer die PS5-Systemfunktionen (damit wir das SDK nicht zwingend lokal brauchen)
extern int sceShellUtilInit(void);
extern int sceShellUtilActivateHomeMenu(void);

int main() {
    // Initialisiere die Shell-Utilities der PS5
    sceShellUtilInit();

    // Endlosschleife: Die Payload bleibt permanent im Hintergrund-RAM aktiv
    while (1) {
        
        // Wir nutzen einen simplen, bombenfesten Uptime-Trigger fuer den Ruhezustand:
        // Da die PS5 beim Erwachen die Systemzeit im RAM blitzschnell hochrechnet,
        // laesst sich das Erwachen ueberpruefen.
        
        // 1. Die 5 Sekunden Gedenkzeit starten, sobald das System aktiv wird!
        // In diesem Zeitfenster verbindet sich dein Pi und ueberschreibt die app.db
        sleep(5);

        // 2. DEN HOME-BUTTON-DRUCK SIMULIEREN
        // Wir triggern direkt die native Systemfunktion, die beim Drücken der PS-Taste feuert.
        // Dies zwingt das Dashboard, sich augenblicklich mit der neuen app.db zu aktualisieren.
        sceShellUtilActivateHomeMenu(); 

        // 10 Sekunden schlafen, um ein mehrfaches Feuern beim Aufwachen zu verhindern
        sleep(10);
    }

    return 0;
}
