import importlib, os, sys, re, types, ast, dill
from unreal_engine_tools import *
from unreal_engine import FVector, FRotator, FTransform

PROJECT_SCRIPT_PATH = os.path.join(os.path.abspath(ue.get_content_dir()), "Scripts")

# Always reload these, even if not detected automatically
MANUAL_MODULES = []

# Always star-import these
STAR_MODULES = ["unreal_engine_tools", "languages", "cli", "hotreload"]

# Skip these modules entirely during reload
SKIP_MODULES = ["hotreload", "unreal_engine", "cli", "languages"]

def detect_star_imports_from_main():
    """Detect 'from <module> import *' statements in main.py."""
    detected = []
    main_path = os.path.join(PROJECT_SCRIPT_PATH, "main.py")
    if not os.path.exists(main_path):
        return detected

    try:
        with open(main_path, "r") as f:
            for line in f:
                line = line.split("#")[0].strip()
                if line.startswith("from ") and " import *" in line:
                    module_name = line.split("from")[1].split("import")[0].strip()
                    if module_name and module_name not in SKIP_MODULES:
                        detected.append(module_name)
    except Exception as e:
        print(f"[HotReload] Could not parse star imports in main.py: {e}")

    return detected


def detect_manual_imports_from_main():
    """Detect 'import x as y' statements in main.py."""
    detected = []
    main_path = os.path.join(PROJECT_SCRIPT_PATH, "main.py")
    if not os.path.exists(main_path):
        return detected

    try:
        with open(main_path, "r") as f:
            for line in f:
                line = line.split("#")[0].strip()
                if line.startswith("import ") and " as " in line:
                    parts = line.replace("import", "", 1).split(" as ")
                    module_name = parts[0].strip()
                    alias = parts[1].strip()
                    if module_name and module_name not in SKIP_MODULES:
                        detected.append((module_name, alias))
    except Exception as e:
        print(f"[HotReload] Could not parse manual imports in main.py: {e}")

    return detected


def reload_module(module):
    """Reload a module safely."""
    try:
        importlib.reload(module)
        print(f"[HotReload] Reloaded module: {module.__name__}")
        return True
    except Exception as e:
        print(f"[HotReload] Could not reload module {module}: {e}")
        return False


def star_import(module_name, target_globals):
    """Perform a star import of a module into given globals."""
    try:
        module = importlib.import_module(module_name)
        names = getattr(module, "__all__", dir(module))
        for name in names:
            if name.startswith("_"):
                continue
            target_globals[name] = getattr(module, name)
        print(f"[HotReload] Star-imported: {module_name}")
        return True
    except Exception as e:
        print(f"[HotReload] Could not star-import {module_name}: {e}")
        return False


# The goal was to use this when you want to edit any imports while using the editor, but it doesn't seem to do that
def reload_all_modules():
    print("[HotReload] Reload start...")
    # Reload project modules
    for name, module in list(sys.modules.items()):
        try:
            spec = getattr(module, "__spec__", None)
            if spec is None or spec.origin is None or not isinstance(spec.origin, str):
                continue

            origin = os.path.normpath(spec.origin)

            # Only reload real Python files in Scripts/, skip main.py
            if not origin.endswith(".py") or origin.endswith("main.py"):
                continue
            if not origin.startswith(PROJECT_SCRIPT_PATH):
                continue

            if module.__name__ in SKIP_MODULES:
                print(f"[HotReload] Skipping module in SKIP_MODULES: {module.__name__}")
                continue

            reload_module(module)

        except Exception as e:
            print(f"[HotReload] Skipped {name}: {e}")

    # Handle star imports
    _star_imported = set()

    for module_name in detect_star_imports_from_main():
        if module_name not in _star_imported:
            star_import(module_name, globals())
            _star_imported.add(module_name)

    for module_name in STAR_MODULES:
        if module_name not in SKIP_MODULES and module_name not in _star_imported:
            star_import(module_name, globals())
            _star_imported.add(module_name)

    # Handle manual imports with 'as'
    for module_name, alias in detect_manual_imports_from_main():
        if alias not in globals():
            try:
                module = importlib.import_module(module_name)
                globals()[alias] = module
                print(f"[HotReload] Imported {module_name} as {alias}")
            except Exception as e:
                print(f"[HotReload] Could not import {module_name} as {alias}: {e}")

    # Reload manual modules
    for module_name in MANUAL_MODULES:
        try:
            module = importlib.import_module(module_name)
            reload_module(module)
        except Exception as e:
            print(f"[HotReload] Could not reload manual module {module_name}: {e}")

    print("[HotReload] Reload complete.")


def dump_module(module):
    pickled_module = dill.dumps(module)
    return pickled_module


def dump_session(session = 'session_backup.pkl'):
    dill.dump_module(session)


def load_session(session = 'session_backup.pkl'):
    dill.load_module(session)


def rebuild_generated_modules():
    libraries_to_build = [ # languages.py self builds
        os.path.join(os.path.abspath(ue.get_content_dir()), "Scripts", "unreal_engine", "gen_autocomplete_stub.py"),
        os.path.join(os.path.abspath(ue.get_content_dir()), "Scripts", "gen_cli.py")
    ]
    print("Building libraries:", libraries_to_build)
    try:
        for library in libraries_to_build:
            print("Building library:", library)
            ue.py_exec(library)
        print("Finished building libraries")
    except Exception as e:
        print("Building libraries failed", e)

    # from pickle import picklequotes
    # picklequotes.pickle_quotes()


def reset_pyactor(py_actor_name = "BP_PyActor"):
    # TODO: maybe match old pyactors settings to new, like transform, module, and class
    print("World", world)
    # print_all_actors()
    py_actor = find_actor(py_actor_name)
    print("PyActor Found", py_actor)
    old_py_actor_name = py_actor.get_name()
    py_actor_class = py_actor.get_class().get_name()
    py_actor.actor_destroy()
    print("PyActor Destroyed", old_py_actor_name)
    py_actor = world.actor_spawn(ue.find_class(py_actor_class), FVector(0,0,0), FRotator(0,0,0)) # .set_actor_transform(FTransform(location=FVector(0,0,0), rotation=FRotator(0,0,0), scale=FVector(1,1,1)))
    py_actor.set_actor_label(old_py_actor_name)
    py_actor.set_property("PythonModule", "main")
    py_actor.set_property("PythonClass", "Main")
    print("PyActor Spawned", py_actor)
    # print_all_actors()