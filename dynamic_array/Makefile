TARGET = myvector
FILES = main.cpp vector.cpp

$(TARGET): $(FILES)

release:
	g++ -std=c++98 -O2 -o $(TARGET)

debugg:
	g++ -std=c++98 -Wall -O0 -fsanitize=address -fsanitize=undefined -Fsat $(FILES) -o $(TARGET)

clean:
	rm -f $(TARGET)

run: $(TARGET)
	./$(TARGET)