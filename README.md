# Starcel
Hi, I'm Nick Maleki. I'm the owner of Recursion Computing and the developer of Starcel. 

## What is it? 
A Python controlled 3D spreadsheet. A full Unreal Engine 4 instance with Chaos physics. Support for Client and Server. It can be used as a visualization or education tool.
Currently, Starcel is an Unreal Engine 4.27Chaos Client and Server which can be controlled with Python 3.9. There is 3D spreadsheet functionality, a Python calculation engine, everything Unreal engine offers, and there are many more features planned. It is very powerful. 

This project is intended for content creators, hobbyists, developers, spreadsheet users, gamers, and more. 


## Price? 
Currently, free! In the future, as more features are added we will switch to a paid model. 


## Quickstart
The current releases include the client, the server, and the no editor for Windows. Each compiled source is ~1GB each. 
The full Unreal Engine Starcel source project folder is quite a large download, ~50GB. The project files on github are ~200MB, check the .gitignore to see what is missing. 

You need to use Visual Studio 2019 for compiling ([download community edition](https://aka.ms/vs/16/release/vs_community.exe)). I recommend [PyCharm Community](https://www.jetbrains.com/pycharm/download/?section=windows) for editing until IDE support is added.

Compiled versions of Python 3.9 can be downloaded from here https://www.python.org/downloads/release/python-3913/, newer versions of Python 3.9 should work, but need to be compiled from Python source. The unreal_engine package is not installed to Python permanently, but it is installed at runtime, so it does not need to be pip-installed. The Content/Scripts/unreal_engine folder includes all necessary stubs and empty classes for intellisense. 
You can install the necessary packages directly using python.exe -m pip install numpy sympy cmdix fast-autocomplete fast-autocomplete[levenshtein] numba kingdon matplotlib scikit-image scikit-learn dill. If any of these fails, you may need to re-run the command. 
The default Unreal Engine map contains a PyActor which loads main.py and the class Main when the map starts up. Both the server and the client will run this file separately. The line ``if KismetSystemLibrary.IsDedicatedServer():`` lets you define client and server specific code. You can create more PyActors or even use Python from the UE console by clicking ` and typing "py.". 
Create a Text object by double clicking Enter. Once created, you can use =py() to run any Python command. 
The state of the world is not saved in main.py or elsewhere, you will need to make changes there directly or copy your changes from the world elsewhere to save. This will be changed in the future.


## Please Donate to keep this project running
You can donate on [Paypal](https://www.paypal.com/paypalme/RecursionIs) or [Patreon](https://www.patreon.com/RecursionIs)


## Questions, Issues, and Support
Most everything you need will be covered in this readme. 
Python support can be found at r/LearnPython, YouTube, other forums, and chats.
Unreal Engine support can be found on YouTube, their Discord, and their forum. 
UnrealEnginePython examples, Starcel examples, and the unreal_engine folder in Content/Scripts which has the class and function info should cover just about everything you can do with the plugin. If you are certain there is an issue with the https://github.com/20tab/UnrealEnginePython plugin you can post on their issues tab on GitHub. I will check this every so often. The UE4.27 port of the plugin can be found at https://github.com/HaiyiMei/UnrealEnginePython. I made minor changes to this source to make it work on my computer. Issues with the Starcel code and new features can be posted here. I will occasionally merge new features and fixes. Feel free to contribute. Anything else can be asked in our Discord. We are a community of volunteers so we may not have answers and may not get back to you, but we will try our best. 


## Are public Starcel servers safe? 
Not yet. Local use is completely safe: as safe as local Python. 

Treat this project as if you were downloading and running unsigned code from the internet or as if you were giving someone remote desktop access to your computer. Utilize the whitelist system to stay safe. 


## How do I use a server? 
You can connect to a server by running the client_travel()/connect() Python function or by changing the _StartClient.bat file. 
If you want to run a local server, LAN, you can use ipconfig to find your IP, and the server console should also list an IP and port. You can share this IP and port with other users on your network. You can port forward this local port in your router to have it available online. You can share your public IP and port with whoever and they will be able to connect. Be very careful sharing your IP and use the whitelist system. Treat this project as downloading and running unsigned code from the internet or giving someone remote desktop access. 

Python functions can run on the client and server, this is clear from the Python code and can be easily changed. This opens up great possibilities of collaboration using tools like PyCharm's "Code With Me" or by sharing your folders in Windows Explorer's built in OneDrive implementations. 

Unreal's replication system can be confusing. Clients cannot directly invoke functions on other clients, they must first invoke a call to the server and then the server can run a Multicast RPC. 

I recommend starting a fresh UE C++ project and getting familiar with Blueprints and maybe also C++ to get a feel for how to use Unreal and its editor. 

If you want to manually build the dedicated server source, you cannot use UE4.27Chaos from the launcher, you must download the Engine directly from [EpicGame's github branch](https://github.com/EpicGames/UnrealEngine/tree/4.27-chaos), which requires signing up for their developer program. My UE Source folder is ~150GB, whereas the download from the Epic Games Launcher is ~45GB. I needed to add the following lines to my "C:\Program Files\Epic Games\UE_4.27Chaos_Source\Engine\Config\BaseEngine.ini" among a few other fixes for compiling this project. 
```
[PlatformPaths]
UnrealBuildTool=Engine/Binaries/DotNET/UnrealBuildTool.exe
```
You will also need to cook the content from the editor or use the included .bat file.


## Linux and Mac? 
Starcel is currently Windows only. It can be compiled on these Operating Systems. However, this is currently untested. To start, UE, Python, and the UnrealEnginePython plugin are supported in Linux and MacOS. If the project receives support and requests I will port it myself. Feel free to submit a pull request if you upgrade it yourself. 


## Is the program stable? 
Not currently, expect crashes and lost work. Eventually we will release a stable update. 


## AR/VR integration? 
[Starcel-Panda3D](https://github.com/thejasonfisher/starcel-panda3d/) had some [integration for AR glasses](https://github.com/nickmaleki/TCLRayneoAir2SDK). This functionality will return and there will be more functionality for VR soon. 


## Can I make a 2D UI? 
It is not recommended to control any elements in Starcel with a 2D UI. You can build a UI out of 3D elements in the 3D space and make it always display flat on the screen. However, if you need, you could use Tkinter, QT, etc. to make a 2D UI outside the game window. UnrealEnginePython has built in support for QT in Engine using Slate. This would render directly on top of the existing Starcel viewport. 


## UE5 and Python upgrade? 
The latest edition of Starcel is written in Python 3.9 and Unreal Engine 4.27Chaos. This likely will not change for a while as Python cannot be upgraded as its C++ bindings have been deprecated and changed in Python 3.10. This will take a month or few to upgrade. An Unreal Engine 5 upgrade of the UnrealEnginePython plugin will require header, module, and api changes. This could take a month to upgrade. If you plan on working on this, message me for some info that should help you begin. 
I do not plan on upgrading the project myself unless this project receives a lot of support and use. 


## What happened to the last Starcel and its features? 
The last Starcel release was written, at the time, in the newest Python, Python 3.8, and the newest unreal engine release, UE5.1. Any Python build could be used, but I was using PyPy for its performance with the GARAMON 10 dimensional geometric algebra, which has now been replaced with the much more feature-rich Kingdon library. I will release those files at request, but I have not tried compiling the code after one failed test. I did, however, manage to copy the content folder into an empty project and view and use the map and blueprints from there. Many of the plugins and features in the last Starcel are not supported in this version, however there are plans to upgrade as much of it as possible. I will return to all the features showcased in the original video, with many features and new functionality added. 


## What new features are planned
- Tables and spreadsheet. 
- Hotkey editor.
- Multi-language IDE.
- Symbols with varying sizes replacement, highlighting, and reduction: code translation. Rotating symbol replacement so you don't get used to random letters and symbols. https://github.com/codereport/jello.
- File explorer and desktop environment.
- CLI, SSH, and SCP. 
- API for the Reals.
- Units and text editing.
- Math, algebra, calculus, LaTeX.
- Geometric algebra rendering: PGA, VGA, CGA, STA.
- Full Excel, Google Sheets, HDF5, and FOAM3 importer.
- Multidimensional graphing.
- Plotting, charts, digraphs, nodes. Most of what is available in OriginLab Pro. 
- VRChat/Helios features.
- Dynamic graphing and variables. With reverse order calculation engine support. 
- Advanced search and multiple histories with transactions and rollbacks. 
- Google sheets/docs edit functionality. 
- Academic hall and learning center: history, math, physics, particles, physical matter.


## Why Unreal? 
Unreal is great! It is industry-leading for developing games and in cinema. The Python bindings are the icing on the cake, making this a fully featured engine with quick scripting potential. The rendering system is unmatched, beautiful, and the engine itself is quite fast.
Unity has limited Python support with Unity-PythonNet. 
Panda3D and RenderPipeline had issues with speed, server support, and windows. 
Blender's UPBGE and NVIDIA Omniverse were not ready for a server capable game with the features I was looking for. 


## Where does the name "Starcel" come from?
- In software, the * character is used as a wildcard which could represent literally anything. One of the goals of Starcel is to allow you to run any conceivable command and represent any format of data.
- If you leave the axiomatically set area you will see your space and actions from a third person view - a single star, or dot, suspended in the void.
- Starcel runs inside the cells of a spreadsheet.
- "cel" relates to our player acceleration function. It is intended that Starcel accelerates users and development around the world. 
- We built a function that spawns basis of various dimensions within a spatial dimension. These basis look like stars.
![Commands and Features](/Images/StarcelUE5-old/DimSelectorOverride3.png)
- You, the user, are a Star! *


## Need to contact me?
I prefer to be reached via the Discord, but if you need or if you are looking to donate or sponsor the project, you can contact me by email, nick@recursion.is. 
