# C setup
CC ?= gcc


all: test

hot:
	find

test:
	@echo "testing..."

build:
	@echo "building"

.PHONY: test build hot
