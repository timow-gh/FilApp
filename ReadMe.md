## meshler

[![Ubuntu](https://github.com/timow-gh/meshler/actions/workflows/ubuntu.yml/badge.svg)](https://github.com/timow-gh/meshler/actions/workflows/ubuntu.yml)
[![Windows](https://github.com/timow-gh/meshler/actions/workflows/windows.yml/badge.svg)](https://github.com/timow-gh/meshler/actions/workflows/windows.yml)

![](media/ubuntu_meshler.png)

This is a project is meant to be a playground to test a CMake project structure, experiment with a clean architecture
andThis is a project is meant to be a playground to test a CMake project structure, experiment with a clean architecture
and some OOP design patterns.

This project is meant to be a playground for me to test some things I have encountered.

* See how to build a project with CMake, how would development look like if all libraries are independent and not in a
  monorepo
    * This allows to have a clean separation of concerns
    * It has a significant overhead, the libraries must be versioned
        * Devs must be aware of the version of the library they are using
        * Devs must be aware whether they are introducing a breaking change
        * Refactoring becomes much more difficult.
* See how a core project with common types could be used
    * This would allow to change out types application wide and measure the change
* Test how some OOP design patterns use cases.
* Testing how to use the MVC (smalltalk) design pattern with clean architecture
