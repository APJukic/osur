POCETNI_DIREKTORIJ = $(shell pwd)
export POCETNI_DIREKTORIJ 

include $(POCETNI_DIREKTORIJ)/config.ini

all: $(PROGRAM)

CURR_DIR := \"$(shell pwd)\"
CFLAGS += -D VAR1=$(VAR1) -D VAR2=$(VAR2) -D CURR_DIR=$(CURR_DIR)

OBJEKTI = main.o
MODULI = Zagreb/mod-Zagreb.o Split/mod-Split.o Nadoknada/mod-Nadoknada.o

$(PROGRAM): $(OBJEKTI) $(MODULI)
	$(CC) $(LDFLAGS) $^ $(LDLIBS) -o $@


main.o: main.c $(POCETNI_DIREKTORIJ)/include/postavke.h
	$(CC) $(CFLAGS) -o $@ -c $<

.PHONY: $(MODULI)
$(MODULI):
	$(MAKE) -C $(dir $@)


.PHONY: brisi
brisi:
	$(MAKE) -C Zagreb brisi
	$(MAKE) -C Split brisi
	$(MAKE) -C Nadoknada brisi
	rm -f $(OBJEKTI) $(PROGRAM)

.PHONY: pokreni
pokreni: primjer
	./primjer
