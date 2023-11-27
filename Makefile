CFLAGS = -std=c++17 -O2
LDFLAGS = -lglfw -lvulkan -ldl -lpthread -lX11 -lXxf86vm -lXrandr -lXi

FPP: src/main.cpp
	g++ $(CFLAGS) -o fpp -g src/*.cpp $(LDFLAGS)

.PHONY: test clean

test: FPP
	./fpp

clean:
	rm -f fpp