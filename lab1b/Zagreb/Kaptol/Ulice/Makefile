include $(POCETNI_DIREKTORIJ)/config.ini

VAR1 = 111
VAR2 = 3
CURR_DIR := \"$(shell pwd)\"
CFLAGS += -D VAR1=$(VAR1) -D VAR2=$(VAR2) -D CURR_DIR=$(CURR_DIR)

OBJEKTI = Medvedgradska.o Radiceva.o Jurjevska.o
MODUL = mod-Ulice.o

$(MODUL): $(OBJEKTI)
	$(LD) -r $^ $(LDFLAGS) -o $@

Medvedgradska.o: Medvedgradska.c $(POCETNI_DIREKTORIJ)/include/postavke.h
	$(CC) $(CFLAGS) -o $@ -c $<
Radiceva.o: Radiceva.c $(POCETNI_DIREKTORIJ)/include/postavke.h
	$(CC) $(CFLAGS) -o $@ -c $<
Jurjevska.o: Jurjevska.c $(POCETNI_DIREKTORIJ)/include/postavke.h
	$(CC) $(CFLAGS) -o $@ -c $<

# brisanje
.PHONY: brisi
brisi:
	rm -f $(OBJEKTI) $(MODUL)
