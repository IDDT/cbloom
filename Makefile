NAME := cbloom

build: clean
	python3 setup.py build \
		&& mv build/lib.*/$(NAME)*.so $(NAME).so

test: build
	python3 -m unittest tests

clean:
	rm -rf build/ $(NAME).egg-info/ dist/ *.so

sdist:
	python3 setup.py build sdist
