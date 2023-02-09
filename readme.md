# PluginLoader_DefaultPlugin
*A simple way to integrate Plugin support*</br>

---
## What is this?
An example plugin for my [PluginLoader](https://github.com/sam-k0/PluginLoader). <br>

This can be used as a quickstart as it already includes all necessary files to build a plugin.

---
## Prerequisites
- GNU GCC Compiler

## Setup
Easiest is to download this repo. <br>
You *need* all the header files in order for this to work.<br>

---
**In-IDE-Setup**<br>
The plugin DLL files should be built for the same architecture as the Loader. This defaults to **x86**. <br>

You should also **statically link the standard library**<br>
*This can be done by using these linker flags*:<br>
`-static-libgcc -static-libstdc++`

