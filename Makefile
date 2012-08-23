dirs = src tests

.PHONY: all clean $(dirs)

all: $(dirs)

clean: $(dirs)

$(dirs):
	$(MAKE) -j2 -C $@ $(MAKECMDGOALS)
