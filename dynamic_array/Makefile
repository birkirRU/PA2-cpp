MAIN = main
FILES = main.cpp dynamic_array.cpp

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
	@for f in tests/test*.in; do \
		n=$$(basename "$$f" .in); \
		./$(MAIN) < "$$f" > /tmp/$$n.got; \
		if diff -q "tests/$$n.out" /tmp/$$n.got > /dev/null; then \
			echo "$$n PASS"; \
		else \
			echo "$$n FAIL"; \
			diff -u "tests/$$n.out" /tmp/$$n.got; \
		fi; \
	done

clean:
	rm -f $(MAIN)
	rm -rf *.dSYM

.PHONY: all run test valgrind-main clean