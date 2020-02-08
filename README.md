# stm32dev

### STM32 Development in VS Code:

#### Prerequisites
- Install the following programs and add them to your system PATH
  - [arm-none-eabi-gcc toolchain](https://developer.arm.com/tools-and-software/open-source-software/developer-tools/gnu-toolchain/gnu-rm/downloads)
  - [OpenOCD](https://gnutoolchains.com/arm-eabi/openocd/)
  - (Windows) [Make for Windows](http://gnuwin32.sourceforge.net/packages/make.htm)

#### Creating a Project
- Generate a project from [STM32CubeMX](https://www.st.com/en/development-tools/stm32cubemx.html) with the Toolchain / IDE option in the Project Manager set to Makefile.

#### VS Code Configuration
- Install the Cortex-Debug extension
- Create a `C_Cpp_properties` configuration
  - Add the following `defines`:
    - `DEBUG`
    - `USE_HAL_DRIVER`
    - `STM32...` where **STM32...** is defined by the **`STM32...`**`_HAL_Driver` folder name under `Drivers/`
  - Set the compiler path to the `arm-none-eabi-gcc` executable location
  - Set the include path to `${workspaceFolder}/**` for recursive inclusion
- Create a `tasks` configuration
  - Create a task with the following parameters:
    - `"label": "build",`
    - `"type": "shell",`
    - `"command": "make",`
- Create a `launch` configuration from the Cortex-Debug template
  - Modify the following parameters:
    - `executable` to the appropriate executable location  `${workspaceFolder}/build/`**project_name**`.elf`
    - `servertype` to `openocd`
  - Add the parameter `configFiles` and specify the following two .cfg files:
    - `interface/`**x**`.cfg` where **x** is the debugger type (i.e. stlink)
    - `target/`**y**`.cfg` where **y** is the target type (i.e. stm32f4x)
    - Refer to `OpenOCD_install_directory/share/openocd/scripts` to find the correct file names for your platform
  - Add the parameter `"preLaunchTask": "build",`