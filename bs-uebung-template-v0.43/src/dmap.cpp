#include "macros.h"

#include "dmap.h"

#undef DEBUG

//Standardkonstruktor
DMap::DMap() { 
	// Initialisierung wenn alle Blöcke frei sein sollen.
	// Beim Mounten des FS müssen diese Werte aus Containerdatei gelesen werden -> Dafür neue Methode
	for(int i = 0; i < NUMBER_OF_FIELD_ELEMENTS; i++){ 
		// Frei = 0; Belegt != 0;
		allocated[i] = 0; // Entspricht Zustand frei für 32 Blöcke
	}
}

void DMap::setBlockAllocated(int blocknr){
	// In welchem Feldelement befinden sich der Belegungsindikator
	int elementnr = blocknr / 32;
	// An welcher Stelle des uInt befindet sich der Belegungsindikator
	int bitposition = blocknr % 32;
	// Setzen des Bits an der richtigen Stelle
	allocated[elementnr] = allocated[elementnr] | (1 << bitposition);
	
}

bool DMap::isBlockAllocated(int blocknr){
	// In welchem Feldelement befinden sich der Belegungsindikator
	int elementnr = blocknr / 32;
	// An welcher Stelle des uInt befindet sich der Belegungsindikator
	int bitposition = blocknr % 32;
	// Prüfen des Bits an der richtigen Stelle
	return (0 != (allocated[elementnr] & (1 << bitposition))); // Siehe Softwareprojekt Sem. 2 Aufg. 1
}

uint32_t* DMap::getDMap(){
	return allocated;
}

// BESPRECHEN:
/*
 * Anmerkung zur derzeitigen DMap: 4bit werden verschenkt da mit ganzen 32bit uInt gerechnet wird (letzter uInt nicht ganz gefüllt).
 * Schreiben in Containerdatei global? Wenn ja: Einheitlicher Getter für alle funktionalen Abschnitte 
 * -> Datentypvorschlag (hier implementiert): 
 *  
 */

// DOKUMENTATION:
/*
 * Im Folgenden wird der Ausdruck Block synonym zu dem eigentlich präziseren Ausdruck virtueller Block benutzt.
 * Um 62500 Blöcke adressieren zu können werden 1954 uint32_t benötigt. 
 * Ein uint32_t benötigt dabei 4 Bytes. Für 1954 uint32_t werden folglich 7816 Byte benötigt.
 * Dies ergibt bei einer Blockgröße von 512 Bytes einen Bedarf an 16 Blöcken. 
 * Daher sind im letzten Block 136 Bytes unbelegt. 
 * Im ungünstigsten Fall blieben (bei anderer Größe der DMap) 508 Byte ungenutzt.
 * Folglich ist unsere Größenwahl überdurchschnittlich speichersparsam.
 */
