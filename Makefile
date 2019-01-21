.PHONY: xcode clean
xcode:
	mkdir -p build && cd build && cmake -G Xcode ..

clean:
	rm -rf build