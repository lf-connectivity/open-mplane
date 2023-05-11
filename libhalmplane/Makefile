.PHONY: all
all: clean build install

build/%:
	-mkdir build; \
	cd build && cmake .. -DCONTEXT=STANDALONE -DBUILD=$* && $(MAKE)

install/%: build/%
	cd build && sudo $(MAKE) install

.PHONY: clean
clean: 
	sudo rm -r build

.PHONY: docs
docs:
	doxygen
