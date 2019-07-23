TARGET_BUILD_DIR?=./

.PHONY: make-markers

all-markers : markers/d10-w400-1.jpg markers/d10-w400-2.jpg markers/d10-w400-3.jpg markers/d10-w400-4.jpg

markers :
	mkdir -p markers

markers/d10-w400-%.jpg : markers
	$(TARGET_BUILD_DIR)/create-marker -d=10 --ms=400 --id=$* $@
