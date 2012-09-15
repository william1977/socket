dirs = src tests

.PHONY: all clean $(dirs)

all: $(dirs)

clean: $(dirs)

$(dirs):
	$(MAKE) -C $@ $(MAKECMDGOALS)
