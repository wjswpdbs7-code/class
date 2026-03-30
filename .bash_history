man sudo_root
ㅣㄴ
ls
git clone https://github.com/freshmea/kuBig2026.git
ls
lsusb
make
lsusb
aads
lsusb
cd /home/jjy2026/build/atmega128-build
make
lsusb
ls -l /dev/bus/usb/001/002
sudo chmod 666 /dev/ttyUSB0
ls -l /dev/bus/usb/001/002
sudo chmod 666 
ls -l /dev/bus/usb/001/002
ls -l /dev/bus/usb/001/002
sudo tee /etc/udev/rules.d/99-usb-permissions.rules > /dev/null <<'RULES'
SUBSYSTEM=="usb", ATTR{idVendor}=="03eb", ATTR{idProduct}=="2104", MODE="0666"
SUBSYSTEM=="usb", ATTR{idVendor}=="0403", ATTR{idProduct}=="6001", MODE="0666"
RULES

sudo udevadm control --reload-rules && sudo udevadm trigger
ls -l /dev/bus/usb/001/002
ls -l /usr/lib/avr/include/avr/interrupt.h || true
ls -l /usr/lib/gcc/avr/7.3.0/include-fixed || true
ls -l /usr/lib/gcc/avr/7.3.0/include || true
echo "PWD: $PWD"
cmake --build . --target pwmservo.elf -- -j 4
cmake --build . --target upload_pwmservo
cd /home/jjy2026/build/atmega128-build
make
cd /home/jjy2026/build
rm -rf atmega128-build
cmake -S /home/jjy2026/kuBig2026 -B atmega128-build -DCMAKE_TOOLCHAIN_FILE=/home/jjy2026/kuBig2026/atmega128/avr-toolchain.cmake
cmake --build atmega128-build -- -j
make_upload_pwmservo
cd /home/jjy2026/build/atmega128-build
PROGRAM=pwmservo make upload
make
make_upload_cds
make upload_cds
make upload_cds
make
make upload_cds
ls -l /dev/ttyACM* /dev/ttyUSB* || echo 'no serial devices'
avrdude -c stk500v2 -p m128 -P usb -v
lsusb
make 
make upload_pwmservo
make
make
make upload_pwmServoSwitch
make
make upload_pwmServoSwitch
make
make upload_pwmservo
make
make upload_pwmservo
cd /home/jjy2026/build/atmega128-build
make
make
make
make
make
make
make
ㅡ맏
make
cd /home/jjy2026/build/atmega128-build
cmake ..   # 또는 cmake -S /home/jjy2026/kuBig2026/atmega128 -B /home/jjy2026/build/atmega128-build
make -j$(nproc)
make
make upload_pwmServoSwitch
make
make upload_pwmServoSwitch
make
make
make
python
make
make
make
make
git status
git init
git add .
git commit -m "Initial commit"
git config --global user.email "


git config --global user.email "
git config --global user.email
git remote add origin https://github.com/wjswpdbs7-code/class.git
git remote -v
git push
git push -u origin master
git branch
git remote -v
git rev-parse --abrev-ref HEAD
git branch
cd ..
cd ..
ls
git branch
git push -u origin main
cd ..
ls
cd jjy2026/
cd pico/
git submodule add https://github.com/raspberrypi/pico-sdk.git deps/pico-sdk
cd ~
la -al
ls -al
cd /root
ls
cd /
ls
cd root
sudo cd root
sudo cd root
 git remote -v 
ls
git clone  https://github.com/wjswpdbs7-code/class.git
cd /home/jjy2026/class-main/class-main/build
make
cd /home/jjy2026/class-main/class-main
rm -rf build
mkdir build
cd build
ㅡ맏
make
cmake .. -G "Ninja"
cmake --build . --parallel
cd /home/jjy2026/class-main/class-main/pico_project
rm -rf build
mkdir build
cd build
# PICO_SDK_PATH 환경이 올바르지 않다면 명시
cmake -D PICO_SDK_PATH=/home/jjy2026/pico/pico-sdk ..
cmake --build . --parallel
pwd
ls -la
if [ -f CMakeCache.txt ]; then rg "^CMAKE_HOME_DIRECTORY|^CMAKE_SOURCE_DIR" CMakeCache.txt || true; fi
cd /home/jjy2026/class-main/class-main/pico_project/build_pico2w
pwd
ls -la | head -n 40
if [ -f CMakeCache.txt ]; then rg "^CMAKE_HOME_DIRECTORY|^CMAKE_SOURCE_DIR" CMakeCache.txt || true; fi
pwd
ls -la
if [ -f CMakeCache.txt ]; then rg "^CMAKE_HOME_DIRECTORY|^CMAKE_SOURCE_DIR" CMakeCache.txt || true; fi
cd /home/jjy2026/class-main/class-main/pico_project/build_pico2w
pwd
ls -la | head -n 40
if [ -f CMakeCache.txt ]; then rg "^CMAKE_HOME_DIRECTORY|^CMAKE_SOURCE_DIR" CMakeCache.txt || true; fi
cd /home/jjy2026/class-main/class-main/pico_project
cmake -S . -B build_pico2w
cd /home/jjy2026/class-main/class-main/pico_project/build_pico2w
make
command -v arm-none-eabi-gcc || true
arm-none-eabi-gcc --version | head -n 1 || true
arm-none-eabi-gcc -print-file-name=nosys.specs || true
find /usr -name nosys.specs 2>/dev/null | head -n 20
dpkg -s libstdc++-arm-none-eabi-newlib >/dev/null 2>&1; echo libstdcppnewlib:$?
dpkg -s gcc-arm-none-eabi >/dev/null 2>&1; echo gccarm:$?
dpkg -s libnewlib-arm-none-eabi >/dev/null 2>&1; echo libnewlib:$?
dpkg -s libstdc++-arm-none-eabi-newlib >/dev/null 2>&1; echo libstdcppnewlib:$?
dpkg -s gcc-arm-none-eabi >/dev/null 2>&1; echo gccarm:$?
cd /home/jjy2026/class-main/class-main/pico_project
printf "PWD: %s\n" "$PWD"
if git rev-parse --is-inside-work-tree >/dev/null 2>&1; then   echo "INSIDE_GIT_REPO=yes";   git rev-parse --show-toplevel; else   echo "INSIDE_GIT_REPO=no"; fi
git -C /home/jjy2026/class-main/class-main rev-parse --show-toplevel 2>/dev/null || echo "NO_GIT_IN_CLASS_MAIN"
cd /home/jjy2026
git fetch origin main --tags
git merge --allow-unrelated-histories --no-edit origin/main || true
git status -sb
ls
git clone https://github.com/freshmea/kuBig2026.git
cd /home/jjy2026/class-main/class-main/pico_project && cmake -S . -B build_pico2w && cmake --build build_pico2w -j && ls -1 build_pico2w/*.uf2
cd /home/jjy2026/class-main/class-main/pico_project && cmake -S . -B build_pico2w && cmake --build build_pico2w -j && ls -1 build_pico2w/*.uf2
git status
cd /home/jjy2026/class-main/class-main/pico_project
if [ ! -d .git ]; then   git init; fi
git config pull.rebase false
git config user.name "jjy2026"
git config user.email "jjy2026@users.noreply.github.com"
git add .
if ! git diff --cached --quiet; then   git commit -m "chore: initialize independent pico_project repo"; fi
git status -sb
