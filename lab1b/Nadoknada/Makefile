include $(POCETNI_DIREKTORIJ)/config.ini

VAR1 = 12
VAR2 = 2
CURR_DIR := \"$(shell pwd)\"
CFLAGS += -D VAR1=$(VAR1) -D VAR2=$(VAR2) -D CURR_DIR=$(CURR_DIR)

OBJEKTI = Nadoknada.o
MODUL = mod-Nadoknada.o

$(MODUL): $(OBJEKTI)
	$(LD) -r $^ $(LDFLAGS) -o $@

Nadoknada.o: lab1xx.c $(POCETNI_DIREKTORIJ)/include/postavke.h
	$(CC) $(CFLAGS) -o $@ -c $<

# brisanje
.PHONY: brisi
brisi:
	rm -f $(OBJEKTI) $(MODUL)

