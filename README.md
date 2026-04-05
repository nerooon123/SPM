# Space Password Manager

A lightweight password manager built with **C++** and **OpenSSL**.  
Encrypts and stores your passwords locally using strong AES encryption.

## Getting Started

These instructions will get you a copy of the project up and running on your local machine for development and testing purposes. See deployment for notes on how to deploy the project on a live system.

### Prerequisites

What things you need to install the software and how to install them

- **Visual Studio 2022** (Community Edition is free) with the following workloads:
	* ``` Desktop development with C++ ```
- **OpenSSL 3.4.x** (full version, not Light)
	* Download from [click link](https://slproweb.com/products/Win32OpenSSL.html)
	* Install to ``` C:\Program Files\OpenSSL-Win64 ``` (default)
	* During installation select: "Copy OpenSSL DLLs to /bin directory" (or to Windows system directory)
- **Git** (optional, for cloning the repository)

### Installing

A step by step series of examples that tell you how to get a development env running

1. **Clone or download the project**
```bash
git clone https://github.com/nerooon123/SPM.git
cd SPM
```
2. **Open the solution in Visual Studio**
	* Double-click ```SPM.slnx``` (if provided) or create a new Console App project and add the source files manually.
3. **Configure C++ and OpenSSL paths in Visual Studio**
	* Right-click on the project → Properties
	* Go to C/C++ → General → Additional Include Directories
	   > Add: ``` $(ProjectDir)include; ```
	   > Add: ``` C:\Program Files\OpenSSL-Win64\include ```
	* Go to Linker → General → Additional Library Directories
	   > Add: ``` C:\Program Files\OpenSSL-Win64\lib\VC\x64\MTd ```
	* Go to Linker → Input → Additional Dependencies
	   > Add: ``` libssl.lib; libcrypto.lib ```
4. **Build the solution**
	* Select Build → Build Solution (or press ``` Ctrl+Shift+B ```).
5. **Run the application**
	* Press ```F5``` to start debugging or ```Ctrl+F5``` to run without debugging.

## Built With

* [Visual Studio Comunity](https://visualstudio.microsoft.com/vs/community/) - A fully-featured, extensible, free IDE for creating modern applications
* [OpenSLL](https://openssl-library.org/community/) - A full-featured toolkit for general-purpose cryptography and secure communication

## Contributing

Please read [CONTRIBUTING.md](https://github.com/nerooon123/SPM/CONTRIBUTING.md) for details on our code of conduct, and the process for submitting pull requests to us.

## Versioning

We use [SemVer](http://semver.org/) for versioning. For the versions available, see the [tags on this repository](https://github.com/nerooon123/SPM/tags). 

## Authors

* **Timur Alisherovich** - *Initial work* - [nerooon123](https://github.com/nerooon123)

See also the list of [contributors](https://github.com/nerooon123/SPM/contributors) who participated in this project.

## License

This project is licensed under the MIT License - see the [LICENSE.txt](https://github.com/nerooon123/SPM/LICENSE.txt) file for details

## Acknowledgments

* Hat tip to anyone whose code was used
* Inspiration
* etc
