MAIN = main
FILES = main.cpp doubly_linked_list.cpp

CXXFLAGS = -std=c++98 -Wall -Wextra -O0 -g -fno-omit-frame-pointer
VALGRIND = valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes

all: $(MAIN)

$(MAIN): $(FILES)
	g++ $(CXXFLAGS) $(FILES) -o $(MAIN)

run: $(MAIN)
	./$(MAIN)

valgrind: $(MAIN)
	$(VALGRIND) ./$(MAIN)

clean:
	rm -f $(MAIN)

.PHONY: all run valgrind clean