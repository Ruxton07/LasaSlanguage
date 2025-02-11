unityincl += include_directories('.')
unitysrc += files('unity.c')

if not meson.is_subproject()
  install_headers(
    'unity.h',
    'unity_internals.h',
    subdir: meson.project_name()
  )
endif

unity_proj = subproject('unity')
runner_gen = unity_proj.get_variable('gen_test_runner')
test_runner = meson.source_root() / 'test/test_intops.c'