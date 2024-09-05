%.data: %.png
	python ../res/binary_image_palette.py $< $@

%.data.pal: %.png
	python ../res/binary_image_palette.py $< $@

%.data.h: %.data
	$(BUILD_BINARY_H)

%.data.pal.h: %.data.pal
	$(BUILD_BINARY_H)
