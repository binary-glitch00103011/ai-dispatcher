CXX = g++
CXXFLAGS = -O3 -Wall
TARGET = ai
SRC = ai_dispatcher.cpp
REAL_HOME = $(shell eval echo ~$(SUDO_USER))
PREFIX = /usr/local/bin
CONFIG_DIR = $(REAL_HOME)/.config
CONFIG_FILE = $(CONFIG_DIR)/ai.conf
SRC_CONFIG = $(CURDIR)/config/ai.conf.example

all: $(TARGET)

$(TARGET): $(SRC)
	$(CXX) $(CXXFLAGS) $(SRC) -o $(TARGET)

install: $(TARGET)
	@echo "Installing binary to $(PREFIX)..."
	install -d $(DESTDIR)$(PREFIX)
	install -m 755 $(TARGET) $(DESTDIR)$(PREFIX)/$(TARGET)
	
	@echo "Ensuring config directory exists..."
	install -d $(CONFIG_DIR)
	
	@echo "Checking for existing configuration..."
	@if [ ! -f $(CONFIG_FILE) ]; then \
		echo "Installing default config to $(CONFIG_FILE)..."; \
		cp $(SRC_CONFIG) $(CONFIG_FILE); \
		chmod 644 $(CONFIG_FILE); \
		if [ -n "$(SUDO_USER)" ]; then chown $(SUDO_USER):$(SUDO_USER) $(CONFIG_FILE); fi; \
	else \
		echo "Existing config detected. Skipping overwrite to protect your settings."; \
	fi
	@echo "Installation complete. You can now run the 'ai' command with your flags"

clean:
	rm -f $(TARGET)

uninstall:
	rm -f $(PREFIX)/$(TARGET)
	@echo "Note: Configuration file at $(CONFIG_FILE) was left intact."

.PHONY: all install clean uninstall
