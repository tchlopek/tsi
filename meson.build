project(
    'tsi',
    'cpp',
    default_options: [
        'cpp_std=c++17',
        'warning_level=3'
    ])

inc = include_directories('include')
tsi_dep = declare_dependency(include_directories: inc)

if get_option('build_utest')
    subdir('test')
endif
