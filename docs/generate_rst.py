import os

# Get the directory where this script lives
script_dir = os.path.dirname(os.path.abspath(__file__))

# Directories containing your code (absolute paths)
code_dirs = [
    os.path.join(script_dir, "../include"),
    os.path.join(script_dir, "../src")
]

# Output directory for .rst files
output_dir = os.path.join(script_dir, "source\\api")
os.makedirs(output_dir, exist_ok=True)

found = False
for code_dir in code_dirs:
    if not os.path.exists(code_dir):
        print(f"Directory not found: {code_dir}")
        continue

   # Only list files directly in the folder (no recursion)
    for f in os.listdir(code_dir):
        full_path = os.path.join(code_dir, f)
        if os.path.isfile(full_path) and f.endswith((".cpp", ".h", ".hpp")):
            found = True
            rst_name = f.replace(".", "_") + ".rst"
            rst_path = os.path.join(output_dir, rst_name)
            print(f"Generating {rst_path}")
            with open(rst_path, "w") as rst_file:
                title = f"{f}"
                rst_file.write(f"{title}\n{'=' * len(title)}\n\n")
                rst_file.write(f".. doxygenfile:: {f}\n")
                rst_file.write("   :project: MyProject\n")

if not found:
    print("No files found to generate .rst!")
else:
    print("RST files generated successfully!")

# api_dir = os.path.join(os.path.dirname(__file__), "source/api")
# files = [f[:-4] for f in os.listdir(api_dir) if f.endswith(".rst")]

# with open(os.path.join(os.path.dirname(__file__), "source/index.rst"), "a") as index_file:
#    index_file.write("\n.. toctree::\n   :maxdepth: 2\n\n")
#    for f in files:
#       index_file.write(f"   api/{f}\n")