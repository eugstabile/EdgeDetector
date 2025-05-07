from conan import ConanFile
from conan.tools.cmake import CMakeToolchain, CMake, cmake_layout, CMakeDeps
from conan.tools.files import copy

import os


class EdgeDetector(ConanFile):

    name = "edgedetector"
    description= "Edge detector library for image processing" 
    
    settings = "os", "compiler", "build_type", "arch"
    exports_sources = "CMakeLists.txt", "EdgeDetector/*", "cmake/*", "Test/*", "Resources/*"
    generators = "CMakeDeps"
    
    options = {
        "shared": [True, False], 
        "fPIC": [True, False],
        "build_tests": [True, False]
    }
    
    default_options = {
        "shared": True, 
        "fPIC": True,
        "build_tests": True
    }


    def requirements(self):

        self.requires("gtest/1.15.0",  options={"no_main": True})
        self.requires("opencv/4.11.0", options={"imgproc": True, "highgui": True, "with_png": True})
    
        
    def config_options(self):
        
        if self.settings.os == "Windows":
        
            del self.options.fPIC
        

    def layout(self):
        
        cmake_layout(self)


    def generate(self):
        
        tc = CMakeToolchain(self)
        tc.variables["BUILD_TESTS"] = True if self.options.build_tests else False
        tc.variables["BUILD_SHARED_LIBS"] = True if self.options.shared else False
        tc.generate()


    def build(self):
        
        cmake = CMake(self)
        cmake.configure()
        cmake.build()


    def package(self):

        copy(self, pattern="*.hpp", src=os.path.join(self.source_folder, "EdgeDetector", "include"), dst=os.path.join(self.package_folder, "include"))

        if self.settings.os == "Windows":

            copy(self, pattern="*.dll", src=self.build_folder, dst=os.path.join(self.package_folder, "lib"), keep_path=False)
            copy(self, pattern="*.lib", src=self.build_folder, dst=os.path.join(self.package_folder, "lib"), keep_path=False)

        else:

            copy(self, pattern="*.so", src=self.build_folder, dst=os.path.join(self.package_folder, "lib"), keep_path=False)
            copy(self, pattern="*.a", src=self.build_folder, dst=os.path.join(self.package_folder, "lib"), keep_path=False)
      
            
    def package_info(self):
        self.cpp_info.libs = ["edgedetector"] 
        self.cpp_info.set_property("cmake_find_mode", "both")
