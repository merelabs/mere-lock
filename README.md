# mere-lock #
`mere-lock` is a utility program to lock screen ( and system - in plan). In this versio, only screen To unnlock it user need to press any key or move/click mouse - program then open prompt window for the password to unlock the screen.

Lock screen is quite configurable, such as
- change background of the screen
  - color code or imgae file path can be set as background
- change the logo used in screen 
- change the background of the passowrd prompt screen
  - color code or imgae file path can be set as background
- change the logo used in password prompt screen

TODO:
- Temporary password support
- Restrict the number of failure attempts
- Vertual terminal locking
- System locking

### Usage
Simply invoke the 'mere-lock' command. To get out of it, enter your password.
```
$ mere-lock
```

### Build

```shell
$ git clone https://github.com/merelabs/mere-lock.git
$ cd mere-lock
$ qmake
$ make
```

### Install

```shell
$ make install
```
## License
All the code in this repository is licensed under a [BSD-2-Clause License](LICENSE).
