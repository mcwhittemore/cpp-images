
main:
	g++ test.cpp -o build/unit-test

test: main
	./build/unit-test ./output/5-5.png 5 5
	./build/unit-test ./output/10-10.png 10 10

clean:
	rm -rf build/*
	rm -rf output/*
