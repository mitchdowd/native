# Project Native

Project Native is a developer-friendly, light-weight, native C++ library for
basic client applications.

## Overview

The goal of Project Native is to provide a clean, developer-friendly library
for the creation of native client applications. Initial scope is for Android
and Windows platforms, with other platforms to be incorporated once stable.

## Guiding Principles

The following principles describe what Project Native stands for, and how
decisions are made regarding its design.

 - Code should always be clean, readable, object-oriented code. Steer clear
   of things like unnecessary macros, and confusing template meta-programming.
 - Refrain from leaky abstractions, allowing underlying OS types to leak
   through to the library's API.
 - Native platform constructs should be used to implement things where
   feasible. For example, different Component types.
 - Resist unnecessary bloat. This is a light-weight library for efficient
   client applications. It should run in low memory situations easily.
 - Do not force developers to allocate everything onto the heap. C++ has an
   excellent memory management facility in stack-based object lifecycles. Let
   the developer use it.
