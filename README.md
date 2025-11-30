# LazyKey 🚀

**LazyKey** is a lightweight, modern Windows utility that transforms your keyboard into a productivity powerhouse. With a single toggle, it rebinds standard keys into essential shortcuts (Copy, Paste, Cut, Undo, Redo), allowing for rapid-fire editing without holding down the `Ctrl` key.

## ✨ Features

- **One-Key Shortcuts:** Perform common commands with a single keystroke.
    
- **Visual Status:** A modern, glowing GUI indicates whether the tool is Active or Inactive.
    
- **Toggle System:** Easily switch between "Shortcut Mode" and "Typing Mode" using the 'S' key or the GUI button.
    
- **Background Operation:** Works globally across all Windows applications.
    
- **Lightweight:** Built with native C++ and Windows API (No heavy frameworks).
    

## 🎮 How to Use

When LazyKey is **Active** (Purple Glow), the following keys are remapped:

|     |     |     |
| --- | --- | --- |
| **Key Press** | **Action Performed** | **Function** |
| **C** | `Ctrl` + `C` | Copy |
| **V** | `Ctrl` + `V` | Paste |
| **X** | `Ctrl` + `X` | Cut |
| **Z** | `Ctrl` + `Z` | Undo |
| **A** | `Ctrl` + `Y` | Redo |
| **S** | Toggle Off | Returns keyboard to normal |

**To Close the App:** Click the standard `X` button on the window title bar.

## 📥 Installation (For Users)

1.  Go to the \[suspicious link removed\] page.
    
2.  Download `LazyKey_Setup_v1.exe`.
    
3.  Run the installer and follow the "Next" prompts.
    
4.  Launch **LazyKey** from your Desktop or Start Menu.
    

## 🛠️ Development (For Developers)

If you want to modify the code or build it from source, follow these steps.

### Prerequisites

- **OS:** Windows 10 or 11.
    
- **Compiler:** MinGW-w64 (GCC).
    
- **Installer Builder:** [Inno Setup](https://jrsoftware.org/isdl.php "null") (optional, for packaging).
    
- **Editor:** Visual Studio Code (recommended).
    

### 1\. Environment Setup (MinGW)

1.  Install **MSYS2** from [msys2.org](https://www.msys2.org/ "null").
    
2.  Open the MSYS2 terminal and run:
    
    ```
    pacman -S mingw-w64-ucrt-x86_64-toolchain
    ```
    
3.  Add the binary path to your Windows Environment Variables:
    
    - Path: `C:\msys64\ucrt64\bin`

### 2\. Build from Source

1.  Clone this repository:
    
    ```
    git clone [https://github.com/YourUsername/LazyKey.git](https://github.com/YourUsername/LazyKey.git)
    cd LazyKey
    ```
    
2.  Run the automated build script:
    
    ```
    .\build.bat
    ```
    
3.  This will compile `lazykey.cpp` and generate `KeyboardTool.exe`.
    

### 3\. Create Installer

To generate a professional `setup.exe` like the one in Releases:

1.  Install **Inno Setup**.
    
2.  Open `installer_config.iss` in Inno Setup.
    
3.  Click **Build** > **Compile**.
    
4.  The installer will be generated in the `Output` folder.
    

## 📂 Project Structure

- `lazykey.cpp` - Main C++ source code (Logic + GUI).
    
- `build.bat` - Automates the compilation process with GDI+ linking.
    
- `installer_config.iss` - Configuration file for Inno Setup.
    

## 🤝 Contributing

Pull requests are welcome. For major changes, please open an issue first to discuss what you would like to change.

## 📄 License

[MIT](https://www.google.com/search?q=LICENSE "null")
