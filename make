# AI Dispatcher Makefile
# The 'Architect's' build script

CXX = g++
CXXFLAGS = -O3 -Wall
TARGET = ai
SRC = ai_dispatcher.cpp
PREFIX = /usr/local/bin

all: $(TARGET)

$(TARGET): $(SRC)
	$(CXX) $(CXXFLAGS) $(SRC) -o $(TARGET)

install: $(TARGET)
	@echo "Installing $(TARGET) to $(PREFIX)..."
	sudo cp $(TARGET) $(PREFIX)/
	sudo chmod 755 $(PREFIX)/$(TARGET)
	@echo "Done. Create your config at ~/.config/ai.conf"

clean:
	rm -f $(TARGET)

uninstall:
	sudo rm -f $(PREFIX)/$(TARGET)

.PHONY: all install clean uninstall
