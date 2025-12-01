# LazyKey ⌨️🚀

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

1.  Go to the [Download](https://github.com/yottajunaid/LazyKey/releases/download/EXE_File/LazyKey_Setup_v1.exe) page.
    
2.  Download `LazyKey_Setup_v1.exe`.
    
3.  Run the installer and follow the "Next" prompts. It may say **Unknown publisher**, just click on **more info** and click **Install Anyway**

4.  Create Desktop Shortcut
   
5.  Launch **LazyKey** from your Desktop or Start Menu or from wherever you downloaded the file.
    

## 🛠️ Development (For Developers)

If you want to modify the code or build it from source, follow these steps.

### Prerequisites

- **OS:** Windows XP, 7, 8, 10 or 11.
    
- **Compiler:** MinGW-w64 (GCC).
    
- **Installer Builder:** [Inno Setup](https://jrsoftware.org/isdl.php "null") (optional, for packaging).
    
- **Editor:** Visual Studio Code (recommended).
    

### 1\. Environment Setup (MinGW)

1.  Install **MSYS2** from [msys2.org](https://www.msys2.org/ "null").
    
2.  It will Open the MSYS2 terminal. Run this command and click enter to install all setups:
    
    ```
    pacman -S mingw-w64-ucrt-x86_64-toolchain
    ```
    
3.  Add the binary path to your Windows Environment Variables:
    
    - Press the Windows Key and search "Edit environment variables".

    - Click the result. In the window, click "Environment Variables...".

    - In the "System variables" list (bottom half), find "Path", select it, and click "Edit".

    - Click "New" and paste this path: C:\msys64\ucrt64\bin

    - Click OK on all windows.

4.  Verify Restart VS Code. Open a terminal and type g++ --version. If you see text describing the version, you are ready to run build.bat.

### 2\. Build from Source

1.  Clone this repository:
    
    ```
    git clone https://github.com/yottajunaid/LazyKey.git
    cd LazyKey
    ```
    
2.  Run the automated build script:
    
    ```
    .\build.bat
    ```
    
3.  This will compile `lazykey.cpp` and generate `Lazykey.exe`.
    

### 3\. Create Installer

To generate a professional `setup.exe` like the one in Releases:

1.  Install **Inno Setup**.
    
2.  Open `installer_config.iss` in Inno Setup.
    
3.  Click **Build** > **Compile** or simply click run.
    
4.  The installer will be generated in the `Output` folder or `Selected` folder.
    

## 📂 Project Structure

- `lazykey.cpp` - Main C++ source code (Logic + GUI).
    
- `build.bat` - Automates the compilation process with GDI+ linking.
    
- `installer_config.iss` - Configuration file for Inno Setup.
    

## 🤝 Contributing

Pull requests are welcome. For major changes, please open an issue first to discuss what you would like to change.

## 📄 License

[MIT](https://github.com/yottajunaid/LazyKey/blob/main/LICENSE)
