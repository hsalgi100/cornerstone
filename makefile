PROJECT_NAME=cornerstone-cpp

.PHONY: run
run:
	[[ -d build ]] || mkdir build
	cd build; cmake ..; make
	cd build; ./${PROJECT_NAME}

.PHONY: build
build:
	@[[ -d build ]] || mkdir build
	@cd build; cmake ..; make

.PHONY: test
test: build
	build/${PROJECT_NAME} < ../backbone-test/base/hello-world.bb

.PHONY: clean
clean:
	rm -rf build