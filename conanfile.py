from conan import ConanFile
from conan.tools.cmake import cmake_layout, CMake

class Package(ConanFile):
    name = "tsi"
    version = "1.0.0"
    license = "MIT"
    author = "Tomasz Chlopek (tomasz.chlopek.dev@gmail.com)"
    url = ""
    description = ""
    topics = ("C++", "functional", "range")

    generators = "CMakeDeps", "CMakeToolchain"
    settings = "os", "compiler", "build_type", "arch"
    options = {"shared": [True, False], "fPIC": [True, False]}
    default_options = {"shared": False, "fPIC": False}

    exports_sources = (
        "cmake/*",
        "include/*",
        "CMakeLists.txt")

    def layout(self):
        cmake_layout(self)

    def build(self):
        cmake = CMake(self)
        cmake.configure()
        cmake.build()

    def package(self):
        cmake = CMake(self)
        cmake.install()
