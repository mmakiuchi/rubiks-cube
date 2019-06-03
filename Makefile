
CXX = g++
CXXFLAGS = -std=c++11 `pkg-config --cflags opencv4 glfw3`
LDFLAGS = `pkg-config --libs opencv4 glfw3` -framework Cocoa -framework OpenGL -framework IOKit -framework CoreVideo
RM = rm

MAIN = main

.PHONY: default
default: $(MAIN).o
	./$<

$(MAIN).o: Cube.cpp PoseEstimation.cpp MarkerTracker.cpp main.cpp 
	$(CXX) $(CXXFLAGS) $(LDFLAGS) $^ -o $@

.PHONY: clean
clean:
	$(RM) -rf $(MAIN).o
