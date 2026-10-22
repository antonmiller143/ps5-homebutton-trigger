// Wir deklarieren die PS5-Systemfunktion manuell als nacktes Symbol
extern int sceShellUtilActivateHomeMenu(void);

// Eine eigene, reine Hardware-Warteschleife ueber die CPU-Zyklen der PS5
// Verhindert die Abhaengigkeit von "sleep()" oder externen Bibliotheken
void hardware_delay(unsigned int loops) {
    volatile unsigned int i;
    for (i = 0; i < loops; i++) {
        __asm__ volatile("nop"); // Nackter CPU-Leerlaufbefehl
    }
}

int main() {
    // Endlosschleife, damit die Payload dauerhaft im Hintergrund-RAM verweilt
    while (1) {
        
        // 1. Wartezeit (entspricht ca. 5-8 Sekunden auf der PS5 CPU-Architektur)
        // In diesem Zeitfenster schiebt dein Pi die app.db via FTP rueber
        hardware_delay(90000000);

        // 2. Den nackten UI-Refresh an die PS5 senden
        sceShellUtilActivateHomeMenu(); 

        // 3. Sicherheits-Verzoegerung, um mehrfaches Feuern beim Aufwachen zu verhindern
        hardware_delay(150000000);
    }

    return 0;
}
