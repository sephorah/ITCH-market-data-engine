#!/usr/bin/env bash

install() {
    echo "Installing packages..."
    conan install . --build=missing
    cmake --preset conan-release
}

build() {
    echo "Building ITCH Market Data Engine with CMake..."
    cmake --build --preset conan-release
    make -C build/Release
}

clean() {
    echo "Cleaning ITCH Market Data Engine..."
    cmake --build --target clean --preset conan-release
    rm -f MarketDataSimulatorServer
    echo "Done."
}

case "$1" in
    install)
        install
        ;;
    build)
        build
        ;;
    clean)
        clean
        ;;
    *)
        echo "Usage: $0 {install|build|clean}"
        exit 1
        ;;
esac