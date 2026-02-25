from conan import ConanFile
from conan.tools.cmake import CMakeDeps

class ESP32Project(ConanFile):
    name = "esp32_app"
    version = "1.0"
    settings = "os", "compiler", "build_type", "arch"

    def generate(self):
        # We use CMakeDeps because PlatformIO's CMake integration 
        # will benefit from the generated config files.
        deps = CMakeDeps(self)
        deps.generate()