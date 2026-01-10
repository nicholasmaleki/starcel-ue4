import unreal_engine as ue
import os
from pathlib import Path

class Main:
    # this is called on game start
    def begin_play(self):
        self.gen_intellisense_stubs()
        self.gen_intellisense_stubs_classes()

    def gen_intellisense_stubs(self):
        import pystubgen
        import inspect
        # This only traverses objects defined in the module
        source = pystubgen.make_source(ue)

        # Need to manually get freeform functions in module
        functions_list = [o[1] for o in inspect.getmembers(ue) if inspect.isroutine(o[1])]
        funcDefs = '\n'.join([pystubgen.make_source(funcObj) for funcObj in functions_list])

        # Output
        stubFilePath = Path('C:/Users/nicho/Documents/Unreal Projects/Starcel9/Content/Scripts/unreal_engine/__init__.py')
        print(os.getcwd())
        if not os.access(str(stubFilePath), os.W_OK):
            print(f"p4 edit {str(stubFilePath)}")
            os.system(f"p4 edit {str(stubFilePath)} && pause>nul")

        with open( str(stubFilePath), 'w', encoding='utf8') as outputFile:
            outputFile.write('# Freeform Methods')
            outputFile.write(funcDefs)
            outputFile.write('\n\n\n')
            outputFile.write(source)

    def gen_intellisense_stubs_classes(self):
        class_def_list = []
        for _class in ue.all_classes():
            class_def = [f'class {_class.get_name()}:']
            for function in _class.functions():
                class_def.append(f'    def {function}(__unknown_params__):')
                class_def.append(f'        pass\n')

            for _property in _class.properties():
                class_def.append(f'    {_property} = "__unknown__"\n')

            class_def_list.append('\n'.join(class_def))

        stubFilePath = Path('C:/Users/nicho/Documents/Unreal Projects/Starcel9/Content/Scripts/unreal_engine/classes.py')
        with open( str(stubFilePath), 'w', encoding='utf8') as outputFile:
            outputFile.write('\n'.join(class_def_list))

