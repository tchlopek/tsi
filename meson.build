project(
    'cpprange',
    'cpp',
    default_options: [
        'buildtype=debug',
        'cpp_std=c++17',
])

cmake = import('cmake')
cmake_opt = cmake.subproject_options()
cmake_opt.add_cmake_defines({'INSTALL_GTEST': false})
gtest = cmake.subproject('googletest', options: cmake_opt)

ut_deps = [
    gtest.dependency('gtest'),
    gtest.dependency('gtest_main'),
    gtest.dependency('gmock'),
    gtest.dependency('gmock_main')
]

range_incl = include_directories('cppiter')

subdir('test')