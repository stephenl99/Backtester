import sys
import os

# Get the absolute path to the project root directory (where this script is)
project_root = os.path.dirname(os.path.abspath(__file__))

# Add all possible build directory locations to Python path
possible_build_dirs = [
    os.path.join(project_root, "build"),
    os.path.join(project_root, "cmake-build-debug"),  # CLion's default build directory
]

for build_dir in possible_build_dirs:
    if build_dir not in sys.path and os.path.exists(build_dir):
        sys.path.append(build_dir)
        print(f"Added {build_dir} to Python path")

try:
    import PythonBinding
    # Call the function
    result = PythonBinding.add()
    print(f"Result from C++: {result}")
except ImportError as e:
    print(f"Error importing PythonBinding: {e}")
    print("Current Python path:")
    for path in sys.path:
        print(f"  {path}")
    print("\nCurrent working directory:", os.getcwd()) 