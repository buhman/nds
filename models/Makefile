all: $(patsubst %.obj,%.h,$(wildcard *.obj))

%.h: %.obj
	python render_obj_fixed_point_c_source.py $< $(basename $<) > $@
