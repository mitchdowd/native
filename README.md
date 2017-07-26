# Project Native

Project Native is a developer-friendly, light-weight, native C++ library for
basic client applications. It is currently in pre-alpha stage, as features
are gradually implemented.

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

## Feature Status

This library is still in relatively early development, and many features are
not yet implemented. Below is a guide as to the status of each feature.

### Core Functionality

Various classes for basic, core functionality, used all throughout the library.

- [x] Collection classes
- [x] DateTime
- [x] Exception
- [x] Flags
- [x] Function
- [x] Mutex
- [x] Signal
- [x] Singleton
- [x] String
- [x] Task
- [x] Thread
- [x] Variant

### IO Classes

Classes for IO operations across various channels. These are minimal implementations
to be expanded upon once they are stable.

- [x] File
- [x] MemoryStream
- [ ] ServerSocket
- [x] TcpSocket
- [ ] TextStream
- [ ] UdpSocket

### Minimal Control Implementations

This is for minimal implementation only. Once each component is working well
in its minimal state, then each control will be fleshed out with all of the
relevant features for that control.

- [x] Button
- [x] CheckBox
- [ ] DatePicker
- [x] GroupBox
- [x] InputComponent
- [x] Label
- [ ] ListView
- [ ] NumberPicker
- [x] ProgressBar
- [x] RadioButton
- [ ] SliderComponent
- [ ] TableView
- [ ] TabView
- [x] TextArea
- [ ] ToolBar
- [x] WebView
- [x] Window

### Layouts

Components whose task is to lay out their child Components in a specific
format.

- [ ] FlowLayout
- [ ] GridLayout
- [x] LinearLayout

### Graphics

These are basic, minimal implementations of various drawing classes. Once they
are all working as intended, features will be added.

- [x] Brush
- [x] Canvas
- [x] Color
- [x] Font
- [ ] Image
- [ ] Menu
- [x] Pen

### Data Handling

Various classes used to structure and handle data in various formats.

- [ ] JsonConverter
- [ ] ListModel
- [ ] SqlClient
- [ ] TableModel
- [ ] ValueModel
- [ ] XmlConverter
