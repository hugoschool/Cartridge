# Cartridge

Bare metal compilation of Game Boy Advance cartridges

Creation of our own "kernel" (`src`, `include` folders)

Example available in `example`

## Build

### Compiling our own SDK

```sh
cd sdk
make
make move
```

### Compiling the kernel

You're going to need `arm-none-eabi-gcc` and `arm-none-eabi-newlib`.

Nix flake available with all tools using `nix develop`

```sh
cd src
make
```

### Compiling the example

```sh
cd example/menus
make
```

## Launching the example

The emulator is available [here](https://github.com/YannMagnin/ayyboy-advance)

Download and compile it using the instructions given.

Create a file in `~/.config/cartridge/emulator_path` with the full path to the emulator:

`<...>/ayyboy-advance/target/release/ayydbg`

Then go to the example folder and run `cartridge emu --rom ./<game>.rom`

## Useful resources

- https://problemkaputt.de/gbatek.htm
- https://users.ece.utexas.edu/~mcdermot/arch/articles/ARM/arm7tdmi_instruction_set_reference.pdf
- https://www.cs.rit.edu/~tjh8300/CowBite/CowBiteSpec.htm

More available in the code comments ;)
