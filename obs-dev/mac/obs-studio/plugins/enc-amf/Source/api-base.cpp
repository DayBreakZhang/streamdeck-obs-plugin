/*
MIT License

Copyright (c) 2016 Michael Fabian Dirks

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
*/

#pragma once
//////////////////////////////////////////////////////////////////////////
// Includes
//////////////////////////////////////////////////////////////////////////
#include "api-base.h"

#include "api-d3d9.h"
#include "api-d3d11.h"

#if defined(_WIN32) || defined(_WIN64)
#include <windows.h>
#include <VersionHelpers.h>
#endif

//////////////////////////////////////////////////////////////////////////
// Code
//////////////////////////////////////////////////////////////////////////

Plugin::API::Device::Device() {
	this->Name = "Default";
	this->UniqueId = "";
}

Plugin::API::Device::Device(std::string Name, std::string UniqueId) {
	this->Name = Name;
	this->UniqueId = UniqueId;
}

Plugin::API::Device::~Device() {
}

bool Plugin::API::operator<(const Plugin::API::Device & left, const Plugin::API::Device& right) {
	return left.UniqueId < right.UniqueId;
}

bool Plugin::API::operator>(const Plugin::API::Device & left, const Plugin::API::Device& right) {
	return right < left;
}

bool Plugin::API::operator<=(const Plugin::API::Device & left, const Plugin::API::Device& right) {
	return !(right < left);
}

bool Plugin::API::operator>=(const Plugin::API::Device & left, const Plugin::API::Device& right) {
	return !(left < right);
}

bool Plugin::API::operator==(const Plugin::API::Device & left, const Plugin::API::Device& right) {
	return left.UniqueId == right.UniqueId;
}

bool Plugin::API::operator!=(const Plugin::API::Device & left, const Plugin::API::Device& right) {
	return !(left == right);
}

std::vector<Plugin::API::Device> Plugin::API::APIBase::EnumerateDevices() {
	// Build a list of Devices
	#if defined(_WIN32) || defined(_WIN64)
	if (IsWindows8OrGreater()) {
		return Plugin::API::Direct3D11::EnumerateDevices();
	} else if (IsWindowsXPOrGreater()) {
		//return Plugin::API::Direct3D9::EnumerateDevices();
	} else
		#endif 
	{ // OpenGL
		//return Plugin::API::OpenGL::EnumerateDevices();
	}
	return std::vector<Plugin::API::Device>();
}

Plugin::API::Device Plugin::API::APIBase::GetDeviceForUniqueId(std::string uniqueId) {
	auto devices = EnumerateDevices();
	for (auto device : devices) {
		if (device.UniqueId == uniqueId)
			return device;
	}
	return Plugin::API::Device();
}

std::unique_ptr<Plugin::API::APIBase> Plugin::API::APIBase::CreateBestAvailableAPI(Plugin::API::Device device) {
	std::unique_ptr<Plugin::API::APIBase> retVal = std::make_unique<Plugin::API::APIBase>();
	#if defined(_WIN32) || defined(_WIN64)
	if (IsWindows8OrGreater()) {
		retVal = std::make_unique<Plugin::API::Direct3D11>(device);
	} else if (IsWindowsXPOrGreater()) {
		//retVal = std::make_unique<Plugin::API::Direct3D9>(device);
	} else
		#endif 
	{ // OpenGL
	  //return Plugin::API::OpenGL::OpenGL(device);
	}
	return retVal;
}

Plugin::API::APIType Plugin::API::APIBase::GetBestAvailableAPI() {
	#if defined(_WIN32) || defined(_WIN64)
	if (IsWindows8OrGreater()) {
		return APIType_Direct3D11;
	} else if (IsWindowsXPOrGreater()) {
		return APIType_Direct3D9;
	} else
		#endif 
	{ // OpenGL
		return APIType_OpenGL;
	}
	return APIType_Base;
}

Plugin::API::APIBase::APIBase() {
	myDevice = Plugin::API::Device();
}

Plugin::API::APIBase::APIBase(Device device) {
	myDevice = device;
}

Plugin::API::APIBase::~APIBase() {
}

Plugin::API::APIType Plugin::API::APIBase::GetType() {
	return myType;
}

void* Plugin::API::APIBase::GetContext() {
	return nullptr;
}

Plugin::API::Device Plugin::API::APIBase::GetDevice() {
	return myDevice;
}
