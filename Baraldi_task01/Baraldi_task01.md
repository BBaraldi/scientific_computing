# Installing AlmaLinux 9 on Docker (macOS & Windows)

**Authors:** Beatrice Baraldi & Giacomo Guastella  

This short guide explains how to install Docker and set up an **AlmaLinux 9** container on **macOS (Apple Silicon)** and **Windows 10/11**.  
We wrote it because we struggled a bit at first and thought it might save others some time.

---

## 1. Installing AlmaLinux 9 on Docker with macOS (Apple Silicon)

### 1.1 Prerequisites
Before starting, make sure you have:
- A Mac with an Apple Silicon chip (M1, M2, or M3)
- Internet connection
- A terminal (Terminal.app or iTerm2)
- Homebrew (not mandatory, but very useful)

---

### 1.2 Step 1: Install Docker on macOS (Apple Silicon)
If you already use **Homebrew**, the fastest way is:
```bash
brew install --cask docker
````

Otherwise, you can download the Apple Silicon version of Docker Desktop from the [official website](https://www.docker.com/products/docker-desktop/) and install it manually.

* **Homebrew install:** faster, cleaner, automatically updated.
* **Manual install:** works fine, but you’ll need to update it yourself.

After installing, check that everything works:

```bash
docker --version
docker run hello-world
```

---

### 1.3 Step 2: Pull the AlmaLinux 9 Image

```bash
docker pull almalinux:9
```

---

### 1.4 Step 3: Create an AlmaLinux 9 Container

```bash
docker run -it --name almalinux9-container almalinux:9 /bin/bash
```

This gives you a **bash shell** inside the container.

---

### 1.5 Step 4: Update & Install Packages

Inside the container:

```bash
dnf update -y
dnf groupinstall -y "Development Tools"
```

If you want SSH access (not always necessary, but handy):

```bash
dnf install -y openssh-server
systemctl enable sshd
systemctl start sshd
```

---

### 1.6 Step 5: Exit & Manage the Container

Check OS release info:

```bash
cat /etc/os-release
```

List containers:

```bash
docker ps
```

Exit:

```bash
exit
```

Restart later:

```bash
docker start -ai almalinux9-container
```

Remove it completely:

```bash
docker rm almalinux9-container
```

---

### 1.7 Conclusion

That’s it! 🎉 You now have **AlmaLinux 9 running on Docker** on your Mac with Apple Silicon.

---

## 2. Installing Docker and AlmaLinux 9 on Windows

### 2.1 Prerequisites

* Windows 10/11 (64-bit) or Windows Server 2019/2022
* WSL 2 enabled (recommended for speed)
* Virtualization enabled in BIOS
* Administrator rights
* Internet connection

---

### 2.2 Step 1: Install Docker Desktop

1. Download Docker Desktop from the [official website](https://www.docker.com/products/docker-desktop/).
2. Run the installer and follow the steps.
3. Enable **WSL 2 integration** in the settings (if available).
4. Restart if asked.
5. Check installation with:

   ```powershell
   docker --version
   ```
6. Run a test:

   ```powershell
   docker run hello-world
   ```

✅ Done! Docker is running. Time for a coffee ☕.

---

### 2.3 Step 2: Enable WSL 2 (Optional but Recommended)

Open **PowerShell as Administrator**:

```powershell
wsl --install
wsl --set-default-version 2
```

Restart if needed, then check:

```powershell
wsl -l -v
```

---

### 2.4 Step 3: Pull and Run AlmaLinux 9

```powershell
docker pull almalinux:9
docker images
docker run -it --name almalinux9_container almalinux:9 /bin/bash
```

Now you’re inside AlmaLinux 🎉

---

### 2.5 Step 4: Basic Configuration Inside Container

Update system:

```bash
sudo dnf update -y
```

Install packages:

```bash
sudo dnf install <package-name> -y
```

Exit:

```bash
exit
```

---

### 2.6 Step 5: Manage the Container

List running containers:

```powershell
docker ps
```

Start/stop:

```powershell
docker start almalinux9_container
docker stop almalinux9_container
```

Re-enter:

```powershell
docker exec -it almalinux9_container /bin/bash
```

Remove container:

```powershell
docker rm almalinux9_container
```

Remove the AlmaLinux image:

```powershell
docker rmi almalinux:9
```

---

### 2.7 Conclusion

You now have **Docker + AlmaLinux 9** running on Windows.
Perfect for testing, development, or just playing with Linux in a safe environment.

---

## 3. Quick Reference Cheat Sheet

### Common Commands (macOS & Windows)

```bash
# Pull AlmaLinux 9
docker pull almalinux:9

# Run new container
docker run -it --name almalinux9-container almalinux:9 /bin/bash

# List containers
docker ps

# Exit container
exit

# Restart container
docker start -ai almalinux9-container

# Re-enter an existing container
docker exec -it almalinux9-container /bin/bash

# Remove container
docker rm almalinux9-container

# Remove image
docker rmi almalinux:9
```
