MAIN = main
TEST = test
FILES = main.cpp stack.cpp ../dynamic_array/dynamic_array.cpp
TEST_FILES = test_stack.cpp stack.cpp ../dynamic_array/dynamic_array.cpp

CXXFLAGS = -std=c++98 -Wall -Wextra -O0 -g -fno-omit-frame-pointer
VALGRIND = valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes

all: $(MAIN) $(TEST)

$(MAIN): $(FILES)
	g++ $(CXXFLAGS) $(FILES) -o $(MAIN)

$(TEST): $(TEST_FILES)
	g++ $(CXXFLAGS) $(TEST_FILES) -o $(TEST)

release: clean
	g++ -std=c++98 -O2 -o $(MAIN) $(FILES)

debug: $(MAIN)

test: $(TEST)

run: $(MAIN)
	./$(MAIN)

run-test: $(TEST)
	./$(TEST)

valgrind-main: $(MAIN)
	$(VALGRIND) ./$(MAIN)

valgrind-test: $(TEST)
	$(VALGRIND) ./$(TEST)

clean:
	rm -f $(MAIN) $(TEST)

.PHONY: all release debug test run run-test valgrind-main valgrind-test clean