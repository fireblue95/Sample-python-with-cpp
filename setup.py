from distutils.core import setup, Extension

import subprocess
import numpy as np

def pkgconfig(package, kw):
    flag_map = {'-I': 'include_dirs', '-L': 'library_dirs', '-l': 'libraries'}
    output = subprocess.getoutput(
        'pkg-config --cflags --libs {}'.format(package))
    for token in output.strip().split():
        kw.setdefault(flag_map.get(token[:2]), []).append(token[2:])
    return kw

example_src = ['task.cpp']
example_inc = ['include', np.get_include()]
extension_kwargs = {
    'sources': example_src,
    'include_dirs': example_inc,
}

extension_kwargs = pkgconfig('opencv', extension_kwargs)
# print(extension_kwargs)

example_ext = Extension('task', **extension_kwargs)

setup (name = 'PackageName',
       version = '1.0',
       description = 'This is a demo package',
       ext_modules = [example_ext])