project(
    'remote_controller', 'cpp',
    default_options: ['cpp_std=c++20'],
    version: '0.0.1',
    license: 'BSD-3'
)


sdl2_dep = dependency(
                'sdl2',
                fallback: ['sdl2', 'sdl2_dep']
)
cppzmq_dep = dependency(
                'cppzmq',
                fallback: ['cppzmq', 'cppzmq_dep']
)

subdir('server')
subdir('client')
