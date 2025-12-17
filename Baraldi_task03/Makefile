.PHONY: all generate daxpy clean

all: generate daxpy

generate:
	python generate_vectors.py

daxpy:
	python daxpy_from_config.py

clean:
	rm -f output/*.dat