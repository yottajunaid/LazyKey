; Script for Inno Setup Compiler
; This creates a professional "Next, Next, Finish" installer for your app.

[Setup]
; NOTE: The value of AppId uniquely identifies this application.
; Do not use the same AppId value in installers for other applications.
AppId={{A34C1E12-9F12-4242-9999-ABC123456789}
AppName=LazyKey
AppVersion=1.0
AppPublisher=yottajunaid
DefaultDirName={autopf}\LazyKey
DefaultGroupName=LazyKey
; This is the file you give to your users:
OutputBaseFilename=LazyKey_Setup_v1
Compression=lzma
SolidCompression=yes
; Modern visual style for the installer
WizardStyle=modern

[Languages]
Name: "english"; MessagesFile: "compiler:Default.isl"

[Tasks]
Name: "desktopicon"; Description: "{cm:CreateDesktopIcon}"; GroupDescription: "{cm:AdditionalIcons}"; Flags: unchecked

[Files]
; IMPORTANT: Ensure 'LazyKey.exe' exists in the same folder before running this!
Source: "LazyKey.exe"; DestDir: "{app}"; Flags: ignoreversion

[Icons]
Name: "{group}\LazyKey"; Filename: "{app}\LazyKey.exe"
Name: "{commondesktop}\LazyKey"; Filename: "{app}\LazyKey.exe"; Tasks: desktopicon

[Run]
; Option to launch the app after installation finishes
Filename: "{app}\LazyKey.exe"; Description: "{cm:LaunchProgram,LazyKey}"; Flags: nowait postinstall skipifsilent

[Code]
// You can add custom pascal script logic here if needed, 
// but the default is perfect for a simple tool.