# Aklatan

A Library Management program using Qt and C++.

## Objective of the Aklatan Project
The original Library Management System Project (LMS) came from our college thesis written in VB and used Microsoft Access as it's database backend.
It tracks books and users using RFID tags and barcodes. This project aims to rewrite most of the original LMS program for cross-platform support for Windows and Linux. And this time it's going to be open-source. 


### Specific Objectives
*   Rewrite the program with the Qt libraries and frameworks.
*   Compatibility with the hardware used in the original LMS project.
    * Obtain information given by the RFID reader running on an Arduino Uno.
*   Separate programs for Users and the Library Admins.
*   Change the database backend to SQLite.
*   Make it easier to setup for multiple computers.

## Install
These instructions are for how Aklatan is currently setup. 
1. Download the binary file from the [releases page](https://github.com/AJigsawnHalo/Aklatan/releases) with everything included or you can build it yourself.

2. For Aklatan to work, you would need to have a sqlite database named `aklatan.db` located in `~/.local/share`. This would be changed in the future to allow you to setup a database yourself.
   *  There's a pre-made database included in the release. Just copy the `aklatan.db` file to your `~/.local/share` folder.

3. Run the program using the following.
   *  Open a terminal and go to the folder where the Aklatan binary is located.
   *  Run using `./Aklatan`.


## Build
### Dependencies
*  Git
*  C++ compiler
*  [Qt5](https://doc.qt.io/qt-5/index.html) (`qmake`)
*  [Sqlite v3](https://www.sqlite.org/index.html) (Not needed in building. Only for normal operation)

### Building in Linux
1. Clone this repo and go to the `Aklatan` directory.
```
git clone https://github.com/AJigsawnHalo/Aklatan.git
cd Aklatan
```
2. To build the Main Library Window, change directory to `library-window`.
```
cd library-window
```
3. Run `qmake` and `make`.
```
qmake && make
```
4. Run the program.
```
./Aklatan
```

## Contribute
If you would like to contribute, please go to the [Github repo](https://github.com/AJigsawnHalo/aklatan) and open an [issue](https://github.com/AJigsawnHalo/Aklatan/issues) or submit a [pull request](https://github.com/AJigsawnHalo/Aklatan/pulls).
I'm a begginer at both Qt and C++ and I'm still learning so the code might be a bit inefficient and messy some times. 

### Things being worked on.
*   User-facing Windows
    * Login Window
    * Search Window

### Things to be done in the future
*   Original LMS hardware support

## License
Aklatan is licensed under [GNU General Public License v3.0](https://www.gnu.org/licenses/gpl.txt).

## Related Links
*	[GitHub Repo](https://github.com/AJigsawnHalo/aklatan "Aklatan GitHub repo")
*	[GitLab Repo.](https://gitlab.com/AJigsawnHalo/aklatan "Aklatan Gitlab repo") (for redundancy)
*  [Project Homepage](https://ajigsawnhalo.github.io/Aklatan)
