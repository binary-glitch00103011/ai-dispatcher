#                                                                          =
#`1010101010                                                       `10101010101.                                                      
#                                                                     `10    `10.                                                     
#  101010                                      =                      `10  =   10                                     `101`   0       
#  10`       `10      10 `10  10`     10   ,1010101,  .1010101"       `10  =  :10  10.  .10101010. `10 ,010101010'   10101` 10        
#  1010101010 `10    10` `10  1010`   10   10  _  10                  `10      01  10.  10         `10     10       10` 10  10        
#              `10  10`       10 101` 10   10  =      .10101:         `10101010'        10   10101         10      10   10  10        
#               .1010.   `10  10   10101   10     10  .10             '            10.  10      10 `10     10     ;1    10  10        
#                .10,    `10  10     101   101010101  .10101010`                   10.  1010101010 `10     10     10  0101  10101010. 
#,°º¤ø,¸¸,ø¤º°`°º¤ø,¸,ø¤°`10,¸¸,ø¤º°`°º¤ø,¸¸,ø¤º°`°º¤ø,¸,ø¤°º¤ø,¸¸,ø¤º°`°º¤ø,¸,ø¤°º10.¸¸,ø¤º°`°º¤ø,`10ø¤º°`°º¤ø,¸¸,ø¤º°`°º¤ø,¸,ø¤°º¤ø,¸¸,ø¤,
#`.                      `10                                                       10.             `10                                     ;
#  ¤                                              _(¯`·._.·(¯`·._.·COVENANT·._.·´¯)·._.·´¯)_                                              ¤ 
#  ø                                                                                                                                      ø
# '                                               EvinceDigital Ethical Open Source Covenant:                                              ' 
#:                                                                                                                                          :
#:           This source code is open source; you can redistribute it and/or modify it under the terms of the EvinceDigital                 : 
# °           OpenWeb Covenant as published by the EvinceDigital.                                                                           °
#  ¤                                                                                                                                      ¤     
#  ø         This source code is distributed in the hope that it will be useful,but without any assurance or guarantee or                 ø         
# '           any implied fitness for any purpos. This is not a legal document, but rather it is an ethical appeal to one's                '  
#:            sense of moral obligation. It is a request to uphold the commonly known standards of Open Source coding & some                :
#:            hard earned lessons outlined in the rest of the EvinceDigital Ethical Open Source Covenant.                                   :
# °                                                                                                                                        °
#  ¤         You should have received a copy of the EvinceDigital Ethical Open Source Covenant along with this source code; if not,        ¤
#  ø          write to the EvinceDigital leader, @ binary.glitch@gmail.com.                                                               ø
#.°                                                                                                                                        ° 
#°º¤ø,¸¸,ø¤º°`°º¤ø,¸,ø¤°º¤ø,¸¸,ø¤º°`°º¤ø,¸¸,ø¤º°`°º¤ø,¸,ø¤°º¤ø,¸¸,ø¤º°`°º¤ø,¸,ø¤°º¤ø,¸¸,ø¤º°`°º¤ø,¸¸,ø¤º°`°º¤ø,¸¸,ø¤º°`°º¤ø,¸,ø¤°º¤ø,¸¸,ø¤º' 

CXX = g++
CXXFLAGS = -O3 -Wall
TARGET = ai
SRC = ai_dispatcher.cpp
REAL_HOME = $(shell eval echo ~$(SUDO_USER))
PREFIX = /usr/local/bin
CONFIG_DIR = $(REAL_HOME)/.config/ai
CONFIG_FILE = $(CONFIG_DIR)/ai.config
SRC_CONFIG = $(CURDIR)/config/ai.config

all: $(TARGET)

$(TARGET): $(SRC)
	$(CXX) $(CXXFLAGS) $(SRC) -o $(TARGET)

install: $(TARGET)
	@echo "Installing binary to $(PREFIX)..."
	install -d $(PREFIX)
	install -m 755 $(TARGET) $(PREFIX)/$(TARGET)
	
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
	@echo "Installation complete. You can now colaberate with your AIs by running the 'ai' command with your flags"

clean:
	rm -f $(TARGET)

uninstall:
	rm -f $(PREFIX)/$(TARGET)
	@echo "Note: Configuration file at $(CONFIG_FILE) was left intact."

.PHONY: all install clean uninstall
