from conan import ConanFile
from conan.tools.cmake import CMakeToolchain, CMake
from conan.tools.cmake import cmake_layout, CMakeDeps
from conan.tools.build import check_min_cppstd


class TestCPPRecipe(ConanFile):
    name = "testcpp"
    version = "0.1.1-beta.2"
    package_type = "library"

    license = "Unlicense"
    author = "Jonathan Hyry el.jonny@gmail.com"
    url = "https://github.com/eljonny/TestCPP"
    description = "A very simple programmatic C++ testing framework."
    topics = ("testing", "unit-testing")

    settings = "os", "compiler", "build_type", "arch"
    options = {"shared": [True, False], "fPIC": [True, False]}
    default_options = {"shared": False, "fPIC": True}

    exports_sources = "CMakeLists.txt", "src/Test.cpp", "include/Test.h"
    exports_sources += "cmake/*", "LICENSE", "README.md", "WAIVER"

    generators = "CMakeDeps"

    def config_options(self):
        if self.settings.os == "Windows":
            self.options.rm_safe("fPIC")

    def configure(self):
        if self.options.shared:
            self.options.rm_safe("fPIC")

    def layout(self):
        cmake_layout(self)

    def generate(self):
        deps = CMakeDeps(self)
        deps.generate()
        tc = CMakeToolchain(self)
        tc.generate()

    def validate(self):
        check_min_cppstd(self, "11")

    def build(self):
        cmake = CMake(self)
        cmake.configure()
        cmake.build()

    def package(self):
        cmake = CMake(self)
        cmake.install()

    def package_info(self):
        self.cpp_info.libs = ["TestCPP"]
