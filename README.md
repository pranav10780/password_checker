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
  - Xml supported(coming soon)

## Installation
1. Clone the repo:
```bash
git clone http://github.com/pranav10780/password_checker.git
cd password_checker
```

2. Compiling:
```bash
gcc password_checker.c -o password_checker
```
## Usage
```bash
usage: ./password_checker password
  options:
    -h print this screen
    -f file.txt Use a file to check if the password already exists eg:rockyou.txt
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

4. Take the output in json format
```bash
./password_checker -f abc.txt -o json helo
```

3. Printing the help screen
```bash
./password_checker -h
```
