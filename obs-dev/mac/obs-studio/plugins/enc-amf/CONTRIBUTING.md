# Reporting Issues

Before you report an issue, please read the [Troubleshooting Guide](https://github.com/Xaymar/obs-studio_amf-encoder-plugin/wiki/Troubleshooting-Guide).
It contains a step-by-step guide on how to solve your issue and even includes a FAQ for you to read through.

# Git and the Project

## Committing Changes

Read [this wiki page for information](https://github.com/Xaymar/obs-studio_amf-encoder-plugin/wiki/Contributing) and please follow it. Rebasing a bunch of pushed commits is terrible for anyone involved.

## Pull Requests

Pull Request titles should follow the guidelines for committing changes and also have a short description of what the change does.

# Building

## Step 1: Get the pre-requisites
This plugin is included in the Open Broadcaster Studio project itself. This is only necessary if you wish to verify functionality with a standalone build.

### Pre-Requisites
* [Visual Studio� 2013 or Visual Studio� 2015 (Community or better)](http://visualstudio.com/)
* Windows 10 SDK (Version 10586 or better, bundled with Visual Studio)
* [OBS Studio](https://github.com/jp9000/obs-studio)
* [AMF SDK](https://github.com/GPUOpen-LibrariesAndSDKs/AMF)
* [InnoSetup](http://www.jrsoftware.org/isinfo.php)
* CMake

## Step 2: Configure with CMake
Point CMake at the source code and use either /build32 for 32-bit or /build64 for 64-bit as the binaries path.

The following variables are needed to be set for a successful build:

* PATH_AMDAMFSDK - Path to the cloned AMF SDK repository.
* PATH_OBSStudio - Path to the cloned OBS Studio repository.

Once you have set these, you can generate the project files.

## Step 3: Build with CMake
1. Open the project file 
2. Build

Binaries will be located in /#Build and in the chosen binary path. An Installer can be created using the package.bat in /#Resources.

## Step 3: Verify Functionality

*[You can only do this with an AMD APU or GPU installed](https://github.com/Xaymar/obs-studio_amf-encoder-plugin/wiki/Hardware,-GCN-and-VCE-Limits)*.  
Install the plugin into your OBS Studio installation or test environment and select it in either Simple Output Mode or Advanced Output Mode. It should encode fine without crashing at any point.

# Coding Standard

The entire Project is written in C++ and as such follows common C++ writing practices.

## Namespaces

Namespaces should be named in *Pascal Case*. You may create a nested namespace that is 3 levels deep, not more.

## Enumerations

Enumerations should be named in *Pascal Case* and be inside a namespace or class.  
Enumeration Constants should always be prefixed by the enumeration name so no ambiguity exists.

## Functions

Functions should be named in *Pascal Case* and should always be inside a namespace or class.
Ideally your function should be either inlinable or have parameters passed by reference for optimization.

## Classes

Classes should be named in *Pascal Case* and should always be inside a namespace - a class not in a namespace must be really important to everything.

### Methods (Class-specific Functions)

Methods should be named in *Pascal Case* and always reside in the class it belongs to.

### Members (Class-specific Variables)

Members should be prefixed by 'm_' and then use a *Pascal Case* name. There is no special prefix per-type, per-usage or per-source.

## Variables

Variables should be named in *camel Case*

