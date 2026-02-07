from conan import ConanFile

required_conan_version = ">=2.0.14"


class demos(ConanFile):
    python_requires = "libhal-bootstrap/[>=4.3.0 <5]"
    python_requires_extend = "libhal-bootstrap.demo"

    def requirements(self):
        self.requires("libhal-util/[^5.8.1]", transitive_headers=True)
        self.requires("libhal-arm-mcu/latest")
        self.requires("libhal-actuator/1.2.3")
        self.requires("minimp3/cci.20211201")
