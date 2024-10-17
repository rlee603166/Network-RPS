
# Compiler
CXX = g++

# Source files
SRCS_SERVER = rpsserver.cpp game.cpp player.cpp
SRCS_CLIENT = rpsclient.cpp game.cpp player.cpp

# Executables
EXECUTABLES = rpsserver rpsclient

# Rule to build both executables
all: $(EXECUTABLES)

# Rule to build rpsserver
rpsserver: $(SRCS_SERVER)
	$(CXX) $(CXXFLAGS) $(SRCS_SERVER) -o rpsserver

# Rule to build rpsclient
rpsclient: $(SRCS_CLIENT)
	$(CXX) $(CXXFLAGS) $(SRCS_CLIENT) -o rpsclient

# Clean rule to remove the binaries
clean:
	rm -f $(EXECUTABLES)

