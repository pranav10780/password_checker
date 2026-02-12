# Password Strength Checker

A simple cli tool which takes password from command line and assess its strength

## Features

- **Take password directly**: Unlike most password checkers it takes the password directly form the command line arguments
- **Wordlist checking**: Provides an option to the user to wheather to use a wordlist to check if the password already exists
- **Comprehensive checks**:
  - Prioritied lenght of password as main source of strength
  - Checks for uppercase, lowercase, digits, special characters, etc
- **Output formats**:
  - Json supported
  - Xml supported
- Uses heap instead of vlas with proper freeing of memory

## Installation
1. Clone the repo:
```bash
git clone http://github.com/pranav10780/password_checker.git
cd password_checker
```

2. Compiling:
```bash
make
```
## Usage
```bash
usage: ./password_checker password
  options:
    -h print this screen
    -f file.txt Use a file to check if the password already exists eg:rockyou.txt
    -o json|xml Output format
```

## Examples
1. Check password strength
```bash
./password_checker helo
```

2. Check password is in a wordlist
```bash
./password_checker helo -f rockyou.txt
```

3. Take the output in json format
```bash
./password_checker -o json helo
```

4. Take the output in xml format
```bash
./password_checker -o xml helsai
```
5. Printing the help screen
```bash
./password_checker -h
```
