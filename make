# --- Variables ---
PREFIX = /usr/local/bin
# This anchors the 'Home' to the actual user home, even if running as sudo
REAL_HOME = $(shell eval echo ~$(SUDO_USER))
CONFIG_DIR = $(REAL_HOME)/.config/ai
# This anchors the 'Source' to wherever you currently are
SRC_DIR = $(CURDIR)/config

# --- Targets ---
install:
	@echo "Installing to $(PREFIX)..."
	install -d $(DESTDIR)$(PREFIX)
	install -m 755 ai $(DESTDIR)$(PREFIX)/ai
	
	@echo "Setting up config in $(CONFIG_DIR)..."
	install -d $(DESTDIR)$(CONFIG_DIR)
	# Fixed Line 24: Points directly to the local config folder
	cp $(SRC_DIR)/ai.conf.example $(DESTDIR)$(CONFIG_DIR)/ai.conf
	
	@echo "Installation complete."

.PHONY: install


************************************************


CXX = g++
CXXFLAGS = -O3 -Wall
TARGET = ai
SRC = ai_dispatcher.cpp
PREFIX = /usr/local/bin
CONFIG_DIR = $(HOME)/.config
CONFIG_FILE = $(CONFIG_DIR)/ai.conf

all: $(TARGET)

$(TARGET): $(SRC)
	$(CXX) $(CXXFLAGS) $(SRC) -o $(TARGET)

install: $(TARGET)
	@echo "Installing binary to $(PREFIX)..."
	sudo cp $(TARGET) $(PREFIX)/
	sudo chmod 755 $(PREFIX)/$(TARGET)
	
	@echo "Checking for config directory..."
	mkdir -p $(CONFIG_DIR)
	
	@if [ ! -f $(CONFIG_FILE) ]; then \
		echo "Installing default config to $(CONFIG_FILE)..."; \
		cp config/ai.conf.example $(CONFIG_FILE); \
		chmod 644 $(CONFIG_FILE); \
	else \
		echo "Config file already exists. Skipping overwrite to protect your settings."; \
	fi
	@echo "Done. You can now run 'ai -g hello'"

clean:
	rm -f $(TARGET)

uninstall:
	sudo rm -f $(PREFIX)/$(TARGET)
	@echo "Note: Configuration file at $(CONFIG_FILE) was left intact."

.PHONY: all install clean uninstall
