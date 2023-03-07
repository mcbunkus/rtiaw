CXX 	:= g++
CFLAGS 	:= -Wall -Wpedantic -MMD -MP -O3 -pg

SRC 	:= $(wildcard *.cpp)
OBJ 	:= $(SRC:%.cpp=%.o)
DEP 	:= $(SRC:%.cpp=%.d)

TARGET 	:= rtiaw

$(TARGET): $(OBJ)
	$(CXX) $(CFLAGS) $^ -o $@

%.o: %.cpp
	$(CXX) $(CFLAGS) -c $< -o $@

clean:
	$(RM) $(OBJ) $(DEP) $(TARGET)

-include $(DEP)
