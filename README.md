# mere-lock #
`mere-lock` is a utility program to lock screen ( and system - in plan). In this versio, only screen To unnlock it user need to press any key or move/click mouse - program then open prompt window for the password to unlock the screen.

Usually program with math password with the logged-in user's credential using *pam* service. If user do not wish to enter his/her logged in password, can pass temporary password for the screen lock program.

Lock screen is quite configurable, such as
- change background of the screen
  - color code or imgae file path can be set as background
- change the logo used in screen 
- change the background of the passowrd prompt screen
  - color code or imgae file path can be set as background
- change the logo used in password prompt screen

TODO:
- Restrict the number of failure attempts
- Vertual terminal locking
- System locking

### Usage
Simply invoke the 'mere-lock' command. To get out of it, enter your password.
```
$ mere-lock
```
If user wish to use temporary password, then invokation command would be
```shell
$ mere-lock --password secret
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
