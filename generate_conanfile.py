# import os
# import subprocess
# from SCons.Script import Import, COMMAND_LINE_TARGETS

# # 1. Pull the environment from SCons
# Import("env")

# def run_conan(source, target, item, env):
#     # Skip running Conan if we are just updating IDE metadata/IntelliSense
#     if set(["_idedata", "idedata"]) & set(COMMAND_LINE_TARGETS):
#         return
    
#     print("\n--- Generating Conanfile.py ---")

#     print("\n--- Running Conan to install dependencies ---")
    
#     cmd = [
#         "conan", "install", ".",
#         "--build=missing",
#         "-s", "arch=xtensa", 
#         "-s", "compiler=gcc",
#         "-s", "compiler.version=12", 
#         "-s", "compiler.libcxx=libstdc++11",
#         "-s", "build_type=MinSizeRel"
#     ]
    
#     try:
#         subprocess.run(cmd, check=True)
#         # 2. Correctly append the include path using the passed env
#         env.Append(CPPPATH=[os.path.abspath("build/Release/generators")])
#         print("--- Conan Dependencies Linked Successfully ---")
#     except Exception as e:
#         print(f"Conan failed: {e}")

# # 3. Register the action. 
# # Note: We pass 'env' as a positional argument to the callback
# env.AddPreAction("buildprog", lambda source, target, item: run_conan(source, target, item, env))

# ===================================================================================
# import os
# import subprocess
# from SCons.Script import Import, COMMAND_LINE_TARGETS, DefaultEnvironment

# Import("env")

# def run_conan(env):
#     # 1. Skip if it's just IntelliSense or metadata cleaning
#     if set(["_idedata", "idedata", "clean"]) & set(COMMAND_LINE_TARGETS):
#         return

#     print("\n--- [CONAN] Starting Installation ---")
    
#     # IMPORTANT: Ensure build directory matches your generators path
#     build_dir = os.path.join(env.subst("$PROJECT_DIR"), "build", "MinSizeRel")
    
#     cmd = [
#         "conan", "install", ".",
#         "--build=missing",
#         "-s", "arch=xtensa", 
#         "-s", "compiler=gcc",
#         "-s", "compiler.version=12", 
#         "-s", "compiler.libcxx=libstdc++11",
#         "-s", "build_type=MinSizeRel",
#         f"--output-folder={build_dir}"
#     ]
    
#     try:
#         # 2. Run Conan immediately
#         subprocess.run(cmd, check=True, shell=True)
        
#         # 3. Inject the generated paths so the compiler finds the headers
#         # Conan 2.0 uses 'generators' subfolder
#         gen_path = os.path.join(build_dir, "generators")
#         env.Append(CPPPATH=[gen_path])
        
#         print(f"--- [CONAN] Success! Headers at: {gen_path} ---")
#     except Exception as e:
#         print(f"--- [CONAN] Failed: {e} ---")

# # 4. CALL THE FUNCTION IMMEDIATELY
# # Instead of AddPreAction, we just run it because this is a 'pre:' script.
# run_conan(env)
# ===================================================================================

import os
import subprocess
from SCons.Script import Import, DefaultEnvironment

# Pull the PIO environment
try:
    Import("env")
except Exception:
    env = DefaultEnvironment()

# def get_conan_package_path(package_ref):
#     """ Fetches the absolute path of a package in the Conan cache """
#     try:
#         # Runs: conan cache path llvm-toolchain/20
#         result = subprocess.check_output(
#             ["conan", "cache", "path", package_ref], 
#             stderr=subprocess.STDOUT, 
#             shell=True
#         ).decode().strip()
#         return result
#     except subprocess.CalledProcessError as e:
#         print(f"--- [CONAN] Error: Could not find {package_ref} in cache. Did you run 'conan install'? ---")
#         return None

# def get_conan_package_path(package_ref):
#     """
#     Fetches the absolute path of a package in the Conan 2.x cache.
#     Uses 'conan list' which is more reliable for automation than 'cache path'.
#     """
#     # 1. We'll try to find the path using the 'conan list' command with JSON output
#     # This is the safest way to get machine-readable data in Conan 2.0
#     cmd = f'conan list "{package_ref}:*" --format=json'
    
#     try:
#         print(f"--- [CONAN] Searching for {package_ref} in cache... ---")
#         output = subprocess.check_output(cmd, shell=True, stderr=subprocess.STDOUT).decode().strip()
#         data = json.loads(output)
        
#         # Conan 2.x JSON structure: {"Local Cache": {"ref": {"revisions": {...}}}}
#         # This is a bit nested, so we drill down to find the 'package_folder'
#         local_cache = data.get("Local Cache", {})
#         for ref, content in local_cache.items():
#             revisions = content.get("revisions", {})
#             for rev, rev_content in revisions.items():
#                 packages = rev_content.get("packages", {})
#                 for pkg_id, pkg_content in packages.items():
#                     # If the package is found, return its folder
#                     path = pkg_content.get("info", {}).get("package_folder")
#                     if not path: 
#                         # Fallback for different Conan versions: check 'path' directly
#                         path = pkg_content.get("path")
#                     if path:
#                         return path
                        
#         # 2. If the JSON search fails, try the direct 'cache path' command as a backup
#         backup_cmd = f'conan cache path {package_ref}'
#         return subprocess.check_output(backup_cmd, shell=True).decode().strip()

#     except Exception as e:
#         print(f"--- [CONAN] ERROR: Could not find path for {package_ref} ---")
#         print(f"--- [CONAN] Details: {e} ---")
#         print(f"--- [CONAN] TIP: Try running 'conan install --requires={package_ref}' manually first. ---")
#         return None

import os
import subprocess
from SCons.Script import Import, DefaultEnvironment

try:
    Import("env")
except Exception:
    env = DefaultEnvironment()

def get_conan_package_path(package_ref, folder=None):
    """
    Fetches the path for a given package reference.
    :param package_ref: Reference like 'llvm-toolchain/20' or 'llvm-toolchain/20:id'
    :param folder: Optional subfolder like 'build', 'source', or 'export_source'
    """
    # 1. Prepare the command
    cmd = ["conan", "cache", "path", package_ref]
    if folder:
        cmd.append(f"--folder={folder}")
    
    cmd_str = " ".join(cmd)
    
    try:
        # Try direct path command (Works if ref is exact or is a recipe ref)
        path = subprocess.check_output(cmd_str, shell=True, stderr=subprocess.DEVNULL).decode().strip()
        if os.path.exists(path):
            return path
    except Exception:
        # 2. Fallback: Search the cache for a specific binary if only recipe was provided
        try:
            # We search for any package ID belonging to this recipe
            search_cmd = f'conan list "{package_ref}:*" --format=json'
            output = subprocess.check_output(search_cmd, shell=True).decode().strip()
            data = json.loads(output)
            
            # Navigate Conan 2 JSON to find the first available package_folder
            cache = data.get("Local Cache", {})
            for recipe in cache.values():
                for rev in recipe.get("revisions", {}).values():
                    for pkg in rev.get("packages", {}).values():
                        # We found a package ID. Now we ask for ITS specific folder.
                        pkg_id = pkg.get("info", {}).get("package_id")
                        if pkg_id:
                            full_ref = f"{package_ref}:{pkg_id}"
                            return get_conan_package_path(full_ref, folder)
        except Exception as e:
            print(f"--- [CONAN DEBUG] Deep search failed for {package_ref}: {e} ---")
    return None

def apply_llvm_toolchain(env):
    # Getting LLVM path from conan cache
    llvm_path = "~/.conan2/p/b/llvm-7e3e93141da1e/p"
    print(llvm_path)

    if llvm_path:
        # LLVM binaries are usually in the /bin subfolder of the package
        llvm_bin = os.path.join(llvm_path, "bin")

        # 2. Override the PlatformIO Compiler variables
        # Note: Adjust 'clang'/'clang++' names if your package uses prefixes
        env.Replace(
            CC=os.path.join(llvm_bin, "clang"),
            CXX=os.path.join(llvm_bin, "clang++"),
            AS=os.path.join(llvm_bin, "clang"),
            AR=os.path.join(llvm_bin, "llvm-ar"),
            RANLIB=os.path.join(llvm_bin, "llvm-ranlib")
        )



        print(os.path.join(llvm_bin, "clang++"))
        
        # 3. Add LLVM bin to the system PATH for this build session
        env.PrependENVPath("PATH", llvm_bin)
        
        print("--- [CONAN] PlatformIO is now using LLVM/Clang ---")

# Run the logic
apply_llvm_toolchain(env)
