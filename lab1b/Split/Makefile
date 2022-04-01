include $(POCETNI_DIREKTORIJ)/config.ini

VAR1 = 2
VAR2 = 1
CURR_DIR := \"$(shell pwd)\"
CFLAGS += -D VAR1=$(VAR1) -D VAR2=$(VAR2) -D CURR_DIR=$(CURR_DIR)

OBJEKTI = Split.o
MODUL = mod-Split.o

$(MODUL): $(OBJEKTI)
	$(LD) -r $^ $(LDFLAGS) -o $@

Bol.o: Bol.c $(POCETNI_DIREKTORIJ)/include/postavke.h
	$(CC) $(CFLAGS) -o $@ -c $<

# brisanje
.PHONY: brisi
brisi:
	rm -f $(OBJEKTI) $(MODUL)
