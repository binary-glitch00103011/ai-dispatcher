CXX = g++
CXXFLAGS = -O3 -Wall
TARGET = ai
SRC = ai_dispatcher.cpp
SRC_DIR = $(CURDIR)/config
PREFIX = /usr/local/bin
REAL_HOME = $(shell eval echo ~$(SUDO_USER))
CONFIG_DIR = $(HOME)/.config
CONFIG_FILE = $(CONFIG_DIR)/ai.conf

all: $(TARGET)

$(TARGET): $(SRC)
	$(CXX) $(CXXFLAGS) $(SRC) -o $(TARGET)

install: $(TARGET)
	@echo "Installing binary to $(PREFIX)..."
	sudo install -d $(DESTDIR)$(PREFIX)
	sudo chmod 755 ai $(DESTDIR)$(PREFIX)/ai
	
	@echo "Setting up config in $(CONFIG_DIR)..."
	install -d $(DESTDIR)$(CONFIG_DIR)
	
	@if [ ! -f $(CONFIG_FILE) ]; then \
		echo "Installing default config to $(CONFIG_FILE)..."; \
		cp $(SRC_DIR)/ai.conf.example $(DESTDIR)$(CONFIG_DIR)/ai.conf
		chmod 644 $(CONFIG_FILE); \
	else \
		echo "Config file already exists. Skipping overwrite to protect your settings."; \
	fi
	@echo "Installation complete. You can now run the ai command with your flags"

clean:
	rm -f $(TARGET)

uninstall:
	sudo rm -f $(PREFIX)/$(TARGET)
	@echo "Note: Configuration file at $(CONFIG_FILE) was left intact."

.PHONY: all install clean uninstall
