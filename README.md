# w3x\_t

W3X is a file format used by WarCraft III. The file format consists of a header of 512 bytes followed by an MPQ Archive.

This library can interpret the various (raw binary) files in the MPQ Archive as easily digestible data structures. It's meant to be used together with [StormLib](https://github.com/ladislav-zezula/StormLib), but is decoupled from it.

## Build

Instructions for building the library will come when there's a first release.

Instructions for the testing environment is as follows.

1. Install [StormLib](https://github.com/ladislav-zezula/StormLib),
2. Install [CascLib](https://github.com/ladislav-zezula/CascLib),
3. `sudo apt install libbz2-dev` 
4. Clone this repository and build with CMake:
    ```c++
    $ cmake -S . -B cmake-build-debug
    $ cmake --build cmake-build-debug/
    ```

## Example Usage

All structs exists in `lib/structs/` and are mostly self explanatory. Functions to interpret into and write from these structs exists in `lib/`.

```cpp
int main(int argc, char* argv[]) {
    // Read the contents of the file "war3map.doo" in the MPQ Archive into a std::string using StormLib
    
    // Interpret as a struct
    doo_type doo = doo_to_struct(file_contents);
    
    // Change some values
    doo.doodads[5].rotation_angle = 50.0;
    
    // Write struct as string
    std::string modified_doo = struct_to_doo(doo);
    
    // Write to MPQ Archive using StormLib
}
```
