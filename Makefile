IMNEEDS := $(shell Magick++-config --cppflags --cxxflags --ldflags --libs)

main:
	g++ main.cpp -o build/pixicog $(IMNEEDS)

clean:
	rm -rf build/*
	rm -rf output/*
