IMNEEDS := $(shell Magick++-config --cppflags --cxxflags --ldflags --libs)

squares:
	g++ squares.cpp -o build/squares $(IMNEEDS)

clean:
	rm -rf build/*
	rm -rf output/*
