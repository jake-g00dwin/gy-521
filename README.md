# CMOCKA/CMAKE template

## Purporse

- Streamline the setup of new C projects
- Make it easy to setup a develoment enviroment
- Allow TDD for embedded systems
- Provide easy LSP usage via compile_commands.json
- correctly use the CTEST command.
- Avoid having to setup ruby/ceedling with it's dependency hell

## Organization

```
.
├── CMakeLists.txt
├── LICENSE
├── README.md
├── build
├── cmake
│   └── cmocka
│       ├── AddCCompilerFlag.cmake
│       ├── AddCMockaTest.cmake
│       ├── COPYING-CMAKE-SCRIPTS
│       ├── CheckCCompilerFlagSSP.cmake
│       ├── DefineCMakeDefaults.cmake
│       ├── DefineCompilerFlags.cmake
│       ├── DefinePlatformDefaults.cmake
│       ├── FindNSIS.cmake
│       └── MacroEnsureOutOfSourceBuild.cmake
├── compile_commands.json -> ./build/compile_commands.json
├── git_modules
├── src
│   ├── CMakeLists.txt
│   ├── led_driver
│   │   ├── CMakeLists.txt
│   │   ├── led_driver.c
│   │   └── led_driver.h
│   ├── main.c
│   └── main.h
└── tests
    ├── CMakeLists.txt
    ├── led_driver
    │   ├── CMakeLists.txt
    │   └── test_led_driver.c
    └── simple_test
        ├── CMakeLists.txt
        └── simple_test.c

10 directories, 24 files
```

The actual code is all stored inside the src direcotry with any libs/submodules
stored inside their own subdirectories.

The code we use to test stuff gets stored inside the dir "tests" in the 
projects root.

The compile_commands.json file in the project root is actaully a symlink to
the generated compile_commands.json file inside the build directory. So if
you notice your LSP isn't working correctly it probably means that you haven't
ran cmake yet.


## Running and building the project

```sh
# change into the build dir
cd ./build

# generate the make files and make everything.
cmake ../ -DUNIT_TESTING=ON; make all;

# Run the tests
ctest

```

# Adding tests

To actually add tests to the project create a new directory inside the
"tests" dir. From there it will need a source.c and CMAKELists.txt file.

You will also need to include it inside the tests/CMakeLists.txt file as well.

```cmake
add_subdirectory(new_test)
```

## RoadMap

Things I want to add in the future:

- Automatic module creation
- template generation
- header --> mocking
- report generation
- embedded specific scripts for common hardware items




##TDD stuff

- what does a struct typedef <name_struct> \*struct actually mean?




