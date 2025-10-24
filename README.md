# Rae

![C++23](https://img.shields.io/badge/C%2B%2B-23-blue.svg?style=flat&logo=c%2B%2B)
![License](https://img.shields.io/badge/license-MIT-green.svg)
![Status](https://img.shields.io/badge/status-in%20development-orange.svg)

[![CodeFactor](https://www.codefactor.io/repository/github/krish2882005/rae/badge)](https://www.codefactor.io/repository/github/krish2882005/rae)
[![Quality Gate Status](https://sonarcloud.io/api/project_badges/measure?project=Krish2882005_Rae&metric=alert_status)](https://sonarcloud.io/summary/new_code?id=Krish2882005_Rae)

> **A Modern C++23 Application Framework**  
> *Zero overhead. Zero bloat. Zero compromise.*

## What is Rae?

Rae is a modern C++ framework for building graphics applications, tools, editors, and visualizations. The name embodies the philosophy: **RAII** (Resource Acquisition Is Initialization), **Ray** (light, direction, and rendering), and **Rei** (零 - Japanese for zero).

## The Goal

Create a clean, extensible framework that leverages the latest C++23 features while maintaining an understandable architecture. Rae aims to be both a practical foundation for real applications and a reference for modern C++ design patterns.

## What's Inside

Rae is built around a pluggable graphics backend system, starting with SDL3 for cross-platform windowing and rendering. The framework uses RAII principles throughout for automatic resource management, and includes ImGui with docking support for building developer tools and UI. EnTT provides the entity-component-system architecture, spdlog handles async logging, and GLM powers the math operations.

The design emphasizes clean separation of concerns with a layer-based application structure for organizing code.

## Status

🚧 **In Active Development** - Core architecture and systems are being implemented.
