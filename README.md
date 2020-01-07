# STM32DEV

### Debugging STM32 in VS Code (Windows):

#### Prerequisites
- Install [MinGW](http://www.mingw.org/) and [MSYS2](https://www.msys2.org/)
- Install [arm-none-eabi-gcc](https://developer.arm.com/tools-and-software/open-source-software/developer-tools/gnu-toolchain/gnu-rm/downloads) toolchain and add it to your system PATH
- Install OpenOCD and add it to your system PATH:
  - In MSYS2, enter `pacman -S mingw-w64-x86_64-openocd-git`

#### VS Code Configuration
- Open `C_Cpp_properties.json` configuration
  - Add the following `defines`:
    - `DEBUG`
    - `USE_HAL_DRIVER`
    - `STM32`**abc**`xx` where **abc** is the model of the target (i.e. F429)
  - Set the C standard to `c99`
  - Set the compiler path to the `arm-none-eabi-gcc.exe` location
  - Set the include path to `${workspaceFolder}/**` for recursive inclusion
- Install the Cortex-Debug extension, and use it to create the `launch.json` debug configuration
  - Change `executable` to the appropriate executable location  (./build/\<project_name\>.elf)'
  - Change `servertype` to `openocd`
  - Add the field `configFiles` and specify the following two .cfg files:
    - `interface/`**x**`.cfg` where **x** is the debugger type (i.e. stlink)
    - `target/`**y**`.cfg` where **y** is the target type (i.e. stm32f4x)

#### Building
The MCU configuration can be generated using [STM32CubeMX](https://www.st.com/en/development-tools/stm32cubemx.html) with the Toolchain / IDE option in the Project Manager set to Makefile. The project can then be built with `mingw32-make`.

