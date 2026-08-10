# C++ Tuition-Centre-Management-System

> **Note:** This project was originally built as a half (my group member part is half done) functional tuition management system. Due to curriculum limitations (we explored some concepts and multi-file structures slightly beyond the official syllabus), this specific version wasn't used for our final submission and became an archived project. However, since we put a lot of effort into it, we are open-sourcing it here for sharing and reference.
> 
> ⚠️ **Disclaimer / 免责声明:** This repository is intended **strictly for learning and reference purposes only**. Any forms of plagiarism, cheating, or direct submission of this code for academic assignments are **strictly prohibited**. The authors assume no liability for any academic integrity violations resulting from the misuse of this code.
> 
> 本仓库的代码仅供学习和参考使用。严禁将本代码用于任何形式的抄袭、作弊或直接提交作为课程作业。因滥用本代码而导致的任何学术诚信问题, 作者概不负责。

---

# 🌟 Key Features

- **Secure Authentication System**: Supports role-based login (Administrator and standard User) with input validation, error handling, and cancellation options (`auth.cpp`).
- **Administrative Control (`Admin/`)**: Comprehensive tools for administrators to manage course menus, generate reports, update user functions, and control system workflows.
- **User Management (`User/`)**: Dedicated interfaces for users and students to handle packages, navigate course options, and interact with the system seamlessly.
- **Robust Storage & Utilities (`Utils/`)**: Built-in data storage handlers, custom data models, input sanitization tools, and helper menus to ensure smooth data persistence and navigation.

---

# 📂 Project Structure

```text
├── Admin/
│   ├── adminmenu.cpp / .h
│   ├── adminUserFunctions.cpp / .h
│   └── report.cpp / .h
├── User/
│   ├── usermenu.cpp
│   └── userpackage.cpp / .h
├── Utils/
│   ├── menu.h
│   ├── models.cpp / .h
│   ├── storage.cpp / .h
│   └── tools.cpp / .h
├── auth.cpp / .h
├── main.cpp
└── LICENSE
```
# 🚀 Getting Started
## Option 1: Download Pre-compiled Executable (Recommended)
If you just want to run and test the program quickly without compiling:
1. Head over to the [Releases page](https://github.com/xiaokuai0915/Tuition-Centre-Management-System/releases).
2. Download the latest compiled .exe file.
3. Run it directly on your Windows machine.

## Option 2: Compile from Source
If you prefer to build it yourself:
1. Clone the repository:
```
git clone [https://github.com/xiaokuai0915/Tuition-Centre-Management-System.git](https://github.com/xiaokuai0915/Tuition-Centre-Management-System.git)
```
2. Navigate into the project directory:
```
cd Tuition-Centre-Management-System
```
3. Compile the source files:
```
g++ -o tuition_system main.cpp auth.cpp Admin/adminUserFunctions.cpp Admin/adminmenu.cpp Admin/report.cpp User/usermenu.cpp User/userpackage.cpp Utils/models.cpp Utils/storage.cpp Utils/tools.cpp
```
4. Run the executable:
```
./tuition_system
```

# 📝 License
This project is open-source and available under the terms of the [LICENSE](LICENSE) file.
