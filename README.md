# Sprocket Obj
Imports .obj files to sprocket .blueprint

## Installation
### Requirements
 - CMake 3.5 and above

### Installing
1. Create cmake files
```
mkdir build
cmake -B ./build
```

2. Compile the program 
```
cmake --build ./build
```

3. Run the program
```
cd ./build
sprocket-obj -h
```

## Usage
### Arguments
| Option | Description |
|--------|-------------|
| `-i [file path]` | Import OBJ to blueprint |
| `-o [out directory]` | Specifies the output directory |
| `-h` | Show help |

### Examples
1. Importing an object
```
./sprocket-obj -i model.obj
```

2. Specifying a directory
```
./sprocket-obj -i model.obj -o ~/models
```

