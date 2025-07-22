# 🔐 Secure Pass – Qt & C++ Password Manager

**Secure Pass** is a fast, secure, and offline-first password manager built with **C++** and **Qt**. It uses AES encryption to keep your credentials safe, fully offline. Organize your logins, generate strong passwords, and stay in control of your data.

![Screenshot](app_preview/login_screenshot.png)

---

## 🚀 Features

- ✅ **Offline-Only Storage** – No internet access required; all data stays local.
- 🔒 **AES-256 Local Encryption** – Your passwords are encrypted securely on disk using the Advanced Encryption Standard.
- 🔑 **Built-in Password Generator** – Easily create strong, random passwords.
- ⚡ **Auto Password Suggestion** – Automatically generates a password when adding new entries.
- 🗂️ **Category-Based Sorting** – Organize credentials by categories like Email, Social Media, Work, etc.
- 💻 **Cross-Platform UI** – Seamless experience across Windows, Linux, and macOS with Qt.

---

## 📸 Preview

![Dashboard](app_preview/dashboard_screenshot.png)
![PasswordGenerator](app_preview/password_generator_screenshot)

---

## 🛠️ Tech Stack

- **Language:** C++
- **UI Framework:** Qt 6 / Qt 5 (Widgets or QML)
- **Encryption:** AES-256
- **Build System:** CMake

---

## 🔧 Getting Started

### Prerequisites

- C++17 or higher
- Qt 5.x or 6.x
- OpenSSL development libraries (if using OpenSSL for AES)
- CMake or Qt Creator

### Build Instructions (CMake)

```bash
git clone https://github.com/yourusername/secure-pass.git
cd secure-pass
mkdir build && cd build
cmake ..
make
./SecurePass
