Set WshShell = CreateObject("WScript.Shell" ) 
WshShell.Run """C:\Users\nicho\Documents\Unreal Projects\Starcel9\Content\CLITools\Everything-1.4.1.1030.x64\everything.exe""", 0 'Must quote command if it has spaces; must escape quotes
Set WshShell = Nothing