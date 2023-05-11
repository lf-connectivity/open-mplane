APP = i2cenv

CXXFLAGS += -std=gnu++11

# Add any other object files to this list below
APP_OBJS = \
	Crc.o \
	BootEnv.o \
	BootEnvDevice.o \
	I2cEnv.o \
	SingleBootEnv.o \
	Zcu111BootEnv.o

all: build

build: $(APP)

clean:


$(APP): $(APP_OBJS)
	$(CXX) $(LDFLAGS) -o $@ $(APP_OBJS) $(LDLIBS)
