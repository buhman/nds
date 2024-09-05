all: ../include/graphics_engine_a.h ../include/graphics_engine_b.h ../include/bits.h

%.csv: %.ods
	libreoffice --headless --convert-to csv:"Text - txt - csv (StarCalc)":44,34,76,,,,true --outdir $(dir $@) $<

../include/graphics_engine_a.h: 0x04000000.txt
       python format.py $< graphics_engine_a 0x1000 > $@

../include/graphics_engine_b.h: 0x04001000.txt
       python format.py $< graphics_engine_b 0 > $@

../include/bits.h: graphics_engine_bits.csv
       python format_bits.py $< > $@
