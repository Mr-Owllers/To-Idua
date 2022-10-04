# To-Idua: a TODO list like Idea-manager:tm: (lol) for the command line.

## Installation
### Requirements
- g++ (installed with gcc)
- [nlohmann/json](https://github.com/nlohmann/json)
### Unix:
```bash
git clone https://github.com/Mr-Owllers/To-Idua
cd To-Idua
make install
make clean
```
### Windows:
> NOTE- Run terminal as administrator, also the bat file might not add the path to the environment variables, so you might have to do that manually. 
```
git clone https://github.com/Mr-Owllers/To-Idua
cd To-Idua
install.bat
```

## Usage
```bash
To-Idua:
help - shows this page
list - lists your ideas
add "name" "note" - adds an idea
remove <id> - removes an idea
status <id> "open" || "in progress" || "done" - changes status of an idea

Examples:
toidua list
toidua add "This is an idea" "Idea description"
toidua remove 11
toidua status 11 "done"
```

## Uninstallation
### Unix:
```bash
make uninstall
```
### Windows:
```
uninstall.bat
```

## License
[MIT](LICENSE)
