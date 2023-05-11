# CLIMP
CLIMP stands for **C**ommand-**L**ine **I**nterface for **M**-**P**lane. It runs
on O-RUs and exposes/executes HAL (hardware abstraction layer) functions to
monitor and modify radio operations. CLIMP provides a simple entry point for
executing HAL functions.

## Requirements
* [LuaJIT](https://luajit.org/) based on Lua 5.1
* [Penlight](https://github.com/lunarmodules/Penlight)
* [Argparse](https://github.com/luarocks/argparse)
* [LuaUnit](https://github.com/bluebird75/luaunit) (for unit tests only)

Refer to [climp.bb](../meta-mplane/recipes-mplane/climp/climp.bb) for full details.

## Usage
Run `climp <command>`, or `--help` to view available commands/options.

## Testing
Unit tests can be run with `climp_test`, which invokes
`climp/tests/climp_test.lua`.

## Implementation
Refer to [IMPLEMENTATION.md](IMPLEMENTATION.md).
