include $(POCETNI_DIREKTORIJ)/config.ini

VAR1 = 11
VAR2 = 2
CURR_DIR := \"$(shell pwd)\"
CFLAGS += -D VAR1=$(VAR1) -D VAR2=$(VAR2) -D CURR_DIR=$(CURR_DIR)

OBJEKTI = Kaptol.o
MODULI = Ulice/mod-Ulice.o
MODUL = mod-Kaptol.o

$(MODUL): $(OBJEKTI) $(MODULI)
	$(LD) -r $^ $(LDFLAGS) -o $@

Kaptol.o: Kaptol.c $(POCETNI_DIREKTORIJ)/include/postavke.h
	$(CC) $(CFLAGS) -o $@ -c $<

.PHONY: $(MODULI)
$(MODULI):
	$(MAKE) -C $(dir $@)

# brisanje
.PHONY: brisi
brisi:
	$(MAKE) -C Ulice  brisi
	rm -f $(OBJEKTI) $(MODUL)

