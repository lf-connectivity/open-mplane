# CLIMP Implementation

## LuaJIT FFI
CLIMP uses LuaJIT's FFI (Foreign Function Interface) library to load the shared
library containing HAL functions and make the subsequent function calls. The FFI
library allows the Lua program to directly call external C functions and access
C data structures.

The code block below demonstrates the basic steps:
```lua
-- 1. Load the FFI library
local ffi = require "ffi"

-- 2. Load the shared library containing the HAL functions
ffi.load("libhalmplane.so")

-- 3. Add C function declarations for the HAL functions
ffi.cdef(halmplane_error_t halmplane_get_io_value(external_io_t *io))

-- 4. Call the HAL functions
ffi.halFunc.halmplane_get_io_value(external_io)
```

## Error Codes
Each HAL function returns an enum `halmplane_error_t` representing the error
code. A full list with descriptions can be found in the CLIMP function
`logErrorWithContext()`.

To add a new error code:
1. Create a new `halmplane_error_t` enum value in `MplaneEnums.h`
2. Update the `halmplane_error_t` definition in `mplane/hal.lua`
3. Add a new error message in `logErrorWithContext()` in `climp.lua`

## Adding New Commands
To add a new CLI command, follow the steps below:

### 1. Include the New HAL Functions in `libhalmplane.so`
1. Create a header file containing HAL functions, typedefs, and any other
   definitions for the YANG model
2. Implement the HAL functions in the source file
3. Add the new header file to the list of files to install in
   `libhalmplane/CMakeLists.txt`
4. Add the source file to the `SRC` variable in
   `libhalmplane/<board>/CMakeLists.txt`

### 2. Make New HAL Functions Available in CLIMP
1. Add a new `ffi.cdef()` call in `mplane/hal.lua`
2. Add all the function definitions and typedefs in the `ffi.cdef()` block

### 3. Add New CLIMP Commands
1. Create a new function to add the desired command and subcommands to the CLI
   parser in `createParser()`
2. Implement a callback function (specified by `action`) for each command
