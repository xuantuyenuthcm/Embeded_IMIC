# Makefile for Embedded IMIC Project
# Alternative build system for advanced users

# Project configuration
PROJECT_NAME = embedded_imic
BOARD = arduino:avr:uno
PORT = /dev/ttyUSB0
BAUD = 9600

# Directories
SRC_DIR = src
INCLUDE_DIR = include
LIB_DIR = lib
BUILD_DIR = build
DOCS_DIR = docs

# Source files
MAIN_FILE = $(SRC_DIR)/main.ino
SOURCES = $(wildcard $(SRC_DIR)/*.cpp) $(wildcard $(SRC_DIR)/*.c)
HEADERS = $(wildcard $(INCLUDE_DIR)/*.h)

# Arduino CLI settings (if available)
ARDUINO_CLI = arduino-cli
FQBN = $(BOARD)
SKETCH = $(SRC_DIR)/main.ino

# PlatformIO settings (alternative)
PIO = platformio

.PHONY: all compile upload monitor clean install-deps help

# Default target
all: compile

# Compile the project using Arduino CLI
compile:
	@echo "Compiling $(PROJECT_NAME)..."
	@if command -v $(ARDUINO_CLI) > /dev/null; then \
		$(ARDUINO_CLI) compile --fqbn $(FQBN) $(SRC_DIR); \
	elif command -v $(PIO) > /dev/null; then \
		$(PIO) run; \
	else \
		echo "Error: Neither Arduino CLI nor PlatformIO found."; \
		echo "Please install one of them or use Arduino IDE."; \
		exit 1; \
	fi

# Upload to Arduino board
upload: compile
	@echo "Uploading to board on $(PORT)..."
	@if command -v $(ARDUINO_CLI) > /dev/null; then \
		$(ARDUINO_CLI) upload -p $(PORT) --fqbn $(FQBN) $(SRC_DIR); \
	elif command -v $(PIO) > /dev/null; then \
		$(PIO) run --target upload; \
	else \
		echo "Error: Neither Arduino CLI nor PlatformIO found."; \
		exit 1; \
	fi

# Monitor serial output
monitor:
	@echo "Starting serial monitor on $(PORT) at $(BAUD) baud..."
	@if command -v $(ARDUINO_CLI) > /dev/null; then \
		$(ARDUINO_CLI) monitor -p $(PORT) -c baudrate=$(BAUD); \
	elif command -v $(PIO) > /dev/null; then \
		$(PIO) device monitor; \
	else \
		echo "Error: Neither Arduino CLI nor PlatformIO found."; \
		echo "You can use any serial terminal at $(BAUD) baud."; \
	fi

# Install dependencies
install-deps:
	@echo "Installing dependencies..."
	@if command -v $(ARDUINO_CLI) > /dev/null; then \
		$(ARDUINO_CLI) lib install "DHT sensor library"; \
		$(ARDUINO_CLI) lib install "LiquidCrystal I2C"; \
		$(ARDUINO_CLI) lib install "Adafruit Unified Sensor"; \
	elif command -v $(PIO) > /dev/null; then \
		$(PIO) lib install; \
	else \
		echo "Please install libraries manually:"; \
		echo "- DHT sensor library"; \
		echo "- LiquidCrystal I2C"; \
		echo "- Adafruit Unified Sensor"; \
	fi

# Test the project (if PlatformIO is available)
test:
	@if command -v $(PIO) > /dev/null; then \
		$(PIO) test; \
	else \
		echo "Testing requires PlatformIO. Install it or run tests manually."; \
	fi

# Clean build files
clean:
	@echo "Cleaning build files..."
	@rm -rf $(BUILD_DIR)
	@if command -v $(PIO) > /dev/null; then \
		$(PIO) run --target clean; \
	fi
	@echo "Clean complete."

# Setup Arduino CLI (for first-time users)
setup-arduino-cli:
	@echo "Setting up Arduino CLI..."
	@if ! command -v $(ARDUINO_CLI) > /dev/null; then \
		echo "Arduino CLI not found. Please install it from:"; \
		echo "https://arduino.github.io/arduino-cli/installation/"; \
		exit 1; \
	fi
	$(ARDUINO_CLI) core update-index
	$(ARDUINO_CLI) core install arduino:avr
	@echo "Arduino CLI setup complete."

# Setup PlatformIO (alternative)
setup-platformio:
	@echo "Setting up PlatformIO..."
	@if ! command -v $(PIO) > /dev/null; then \
		echo "PlatformIO not found. Installing via pip..."; \
		pip install platformio; \
	fi
	@echo "PlatformIO setup complete."

# List available ports
list-ports:
	@echo "Available serial ports:"
	@if command -v $(ARDUINO_CLI) > /dev/null; then \
		$(ARDUINO_CLI) board list; \
	else \
		ls /dev/tty* | grep -E "(USB|ACM)"; \
	fi

# Generate documentation (if Doxygen is available)
docs:
	@if command -v doxygen > /dev/null; then \
		doxygen Doxyfile; \
	else \
		echo "Doxygen not found. Documentation generation skipped."; \
	fi

# Check code style (if available)
lint:
	@echo "Code style checking..."
	@if command -v cppcheck > /dev/null; then \
		cppcheck --enable=all --std=c++11 $(SRC_DIR)/ $(INCLUDE_DIR)/; \
	else \
		echo "cppcheck not found. Code style checking skipped."; \
	fi

# Show project information
info:
	@echo "Project: $(PROJECT_NAME)"
	@echo "Board: $(BOARD)"
	@echo "Port: $(PORT)"
	@echo "Baud rate: $(BAUD)"
	@echo ""
	@echo "Source files:"
	@echo "  Main: $(MAIN_FILE)"
	@echo "  Headers: $(HEADERS)"
	@echo ""
	@echo "Directories:"
	@echo "  Source: $(SRC_DIR)"
	@echo "  Include: $(INCLUDE_DIR)"
	@echo "  Library: $(LIB_DIR)"
	@echo "  Documentation: $(DOCS_DIR)"

# Help target
help:
	@echo "Available targets:"
	@echo "  all              - Compile the project (default)"
	@echo "  compile          - Compile the project"
	@echo "  upload           - Upload to Arduino board"
	@echo "  monitor          - Start serial monitor"
	@echo "  install-deps     - Install required libraries"
	@echo "  test             - Run unit tests (PlatformIO only)"
	@echo "  clean            - Remove build files"
	@echo "  setup-arduino-cli- Setup Arduino CLI"
	@echo "  setup-platformio - Setup PlatformIO"
	@echo "  list-ports       - List available serial ports"
	@echo "  docs             - Generate documentation"
	@echo "  lint             - Check code style"
	@echo "  info             - Show project information"
	@echo "  help             - Show this help message"
	@echo ""
	@echo "Configuration:"
	@echo "  PORT=$(PORT)     - Set serial port"
	@echo "  BAUD=$(BAUD)     - Set baud rate"
	@echo ""
	@echo "Example usage:"
	@echo "  make compile"
	@echo "  make upload PORT=/dev/ttyACM0"
	@echo "  make monitor BAUD=115200"