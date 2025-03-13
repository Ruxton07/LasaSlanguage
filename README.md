<img style="width:100%;" src="docs/lasabanner.png">

[![GitHub Project](https://img.shields.io/badge/GitHub_Projects_Page-0066ff?style=for%2Dthe%2Dbadge&logo=github)](https://github.com/users/Ruxton07/projects/1)
![Windows Status](https://img.shields.io/badge/windows-working-33EE33?style=for%2Dthe%2Dbadge&logo=git%20for%20windows)
![Linux Status](https://img.shields.io/badge/linux-not_tested-ffff00?style=for%2Dthe%2Dbadge&logo=linux)

# LasaSlanguage

LasaSlanguage is a project aimed at creating a custom programming language. This repository contains the source code, tests, and documentation for the language.

Arithmetic and logic expressions obey the `ID BNBABXBO PEMDAS NEAXO` version of PEMDAS I made up for LasaSlanguage (from first to last):

```
++ (Incrementation)        [1] | -- first
-- (Decrementation)        [1] |
                               |
~ (Bitwise Negation)       [2] |
& (Bitwise AND)            [3] |
$ (Bitwise XOR)            [4] |
| (Bitwise OR)             [5] |
                               |
() (Parentheses)           [6] |
^ (Exponentiation)         [7] |
* (Multiplication)         [8] |
/ (Division)               [8] |
+ (Addition)               [9] |
- (Subtraction)            [9] |
                               |
! (Logical Negation)      [10] |
== (Logical Equivalence)  [11] |
&& (Logical AND)          [12] |
$$ (Logical XOR)          [13] |
|| (Logical OR)           [14] v -- last
```

## Project Structure

- **.github/**: GitHub-specific files and workflows.
- **.vscode/**: Visual Studio Code settings.
- **build/**: Build artifacts, logs, and test results.
- **dev/**: Development-related files and resources.
- **docs/**: Documentation and images.
- **examples/**: Example programs written in LasaSlanguage.
- **prototypes/**: Prototypes and experimental code.
- **src/**: Source code for the LasaSlanguage compiler and interpreter.
- **test/**: Unit tests and test support files.
- **tools/**: Tools and utilities for development.

## License

This project is licensed under the terms of the [LICENSE](LICENSE) file.

## Contributing

Contributions are welcome! Please see the [project.yml](project.yml) file for guidelines on how to contribute.

## Contact

If you have any questions, please let the author (rt.kellar@gmail.com) know via email or by opening an issue.

## Documentation for Comments

- The format of something like `<INTEGER-CO>` serves as a placeholder for an INTEGER-Compatible-Operator as a shorthand reference.
- Some operators are set to specific compound literals for a reason specified in the comments.