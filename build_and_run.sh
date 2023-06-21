rm -rf build task.*.so

python3 setup.py build_ext --inplace

rm -rf build

python3 run.py