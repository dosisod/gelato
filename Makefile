PLUGIN_INCLUDE_DIR=$(shell gcc -print-file-name=plugin)/include

CXXFLAGS += \
	-std=c++11 \
	-fno-rtti \
	-I $(PLUGIN_INCLUDE_DIR)

all: gelato.so

gelato.so: gelato.cpp
	$(CXX) $(CXXFLAGS) $^ -fPIC -shared -o gelato.so
