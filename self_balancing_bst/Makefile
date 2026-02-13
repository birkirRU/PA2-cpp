MAIN = main
FILES = main.cpp avl_tree.cpp

CXXFLAGS = -std=c++98 -Wall -Wextra -O0 -g3 -fno-omit-frame-pointer -D_GLIBXX_DEBUG
VALGRIND = valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes

all: $(MAIN)

$(MAIN): $(FILES)
	g++ $(CXXFLAGS) $(FILES) -o $(MAIN)

run: $(MAIN)
	./$(MAIN)

valgrind-main: $(MAIN)
	$(VALGRIND) ./$(MAIN)

test: $(MAIN)
	@echo "Running tests..."
	@i=1; \
	while [ -f "tests/test$$i.txt" ]; do \
		./$(MAIN) < "tests/test$$i.txt" > "/tmp/test$$i.got"; \
		if diff -q "tests/eout$$i.txt" "/tmp/test$$i.got" > /dev/null; then \
			echo "test$$i PASS"; \
		else \
			echo "test$$i FAIL"; \
			diff -u "tests/eout$$i.txt" "/tmp/test$$i.got"; \
		fi; \
		i=$$((i+1)); \
	done

clean:
	rm -f $(MAIN)
	rm -rf *.dSYM

.PHONY: all run test valgrind-main clean