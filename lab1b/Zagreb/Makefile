include $(POCETNI_DIREKTORIJ)/config.ini

VAR1 = 1
VAR2 = 1
CURR_DIR := \"$(shell pwd)\"
CFLAGS += -D VAR1=$(VAR1) -D VAR2=$(VAR2) -D CURR_DIR=$(CURR_DIR)

OBJEKTI = Zagreb.o
MODULI = Kaptol/mod-Kaptol.o Sopot/mod-Sopot.o
MODUL = mod-Zagreb.o

$(MODUL): $(OBJEKTI) $(MODULI)
	$(LD) -r $^ $(LDFLAGS) -o $@ 

Zagreb.o: Zagreb.c $(POCETNI_DIREKTORIJ)/include/postavke.h
	$(CC) $(CFLAGS) -o $@ -c $<

.PHONY: $(MODULI)
$(MODULI):
	$(MAKE) -C $(dir $@)

# brisanje
.PHONY: brisi
brisi:
	$(MAKE) -C Kaptol brisi
	$(MAKE) -C Sopot brisi
	rm -f $(OBJEKTI) $(MODUL)

