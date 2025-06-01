#!!/opt/homebrew/bin/python3
import sys
import os

# Get the absolute path to the project root directory (where this script is)
project_root = os.path.dirname(os.path.abspath(__file__))

print("Looking for PythonBinding module...")
print("Current working directory:", os.getcwd())

# Add all possible build directory locations to Python path
possible_build_dirs = [
    os.path.join(project_root, "build"),
    os.path.join(project_root, "cmake-build-debug"),  # CLion's default build directory
]

for build_dir in possible_build_dirs:
    if build_dir not in sys.path and os.path.exists(build_dir):
        print(f"Adding {build_dir} to Python path")
        sys.path.append(build_dir)
        # List contents of build directory
        print(f"Contents of {build_dir}:")
        for item in os.listdir(build_dir):
            print(f"  {item}")

print("\nPython path:")
for path in sys.path:
    print(f"  {path}")

try:
    print("\nTrying to import PythonBinding...")
    import PythonBinding
    print("Successfully imported PythonBinding")
    print(f"Available functions: {dir(PythonBinding)}")
    
    result = PythonBinding.run()
    print(f"Result: {result}")
except Exception as e:
    print(f"\nError: {type(e).__name__}: {str(e)}")
    print("Python version:", sys.version)

