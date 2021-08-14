# mere-lock #
`mere-lock` is a utility program to lock screen ( and system wise locking is in
the plan). When the user invoked the program, it locks the screen and wais for 
user interaction - any key press or mouse activity. The program then prompts 
for the secret, usually the user's password, to unlock the screen. When the 
program is invoked without `--password` argument, it will match the password 
with the logged-in user password using the *pam* service. 

User may wish to NOT using the system's user password, instead using a
different one to unlock the screen - it can be done using `--password` argument.

The lock screen is quite configurable, such as
- change the background of the screen
  - color code
  - image path
- change or hide the logo used on the screen
  - image path
- change the background of the password prompt screen
  - color code or image path can
- change or hide the logo used in the password prompt screen
  - image path

TODOs:
- Restrict on wrong attempts (but why and how?)
  - Record the person who made false attemps? maybe capturing the face using webcam? 
- VT locking
- System locking

### Screenshots
<img src="screenshots/screen.png" height="225px"> <img src="screenshots/prompt.png" height="225px">

more screenshots are available [here](screenshots).

### Usage
Simply invoke the 'mere-lock' command. To get out of it, enter your password.

```shell
$ mere-lock --strict
```

If the user wishes to use a temporary password, then the invocation command 
would be:

```shell
$ mere-lock --strict --password secret
```

Tips: you can generate a password while invoking, and pass it using xargs!

### Build

```shell
$ git clone https://github.com/merelabs/mere-lock.git
$ cd mere-lock
$ qmake
$ make release
```

### Install

```shell
$ make install
```

## License
All the code in this repository is licensed under a [BSD-2-Clause License](LICENSE).
