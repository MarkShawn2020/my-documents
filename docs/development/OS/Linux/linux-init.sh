
" 
version: 0.0.3
features:
    1. disable sudo password so running commands faster
    2. disable apt password so installing packages faster 
    3. enable arrow up/down to backward/forward search prefix command
    4. auto change deb(apt) source
    5. auto install zsh, config oh-my-zsh, set as the default shell, you may need to switch to bash when build android in case of errors, it's easy just to input `bash` in terminal
    6. re-login to make these changes work
"

# !IMPORTANT: config global variables
PASSWORD=" "

# --- step 1.0 ---
echo "alias logout='sudo pkill -u $USER'" >> ~/.bash_aliases
source ~/.bash_aliases

# --- step 1 ---
# write password variable into bash_profile

echo "export PASSWORD=$PASSWORD" >> ~/.bash_profile
source ~/.bash_profile

# !WARNING 这一步可能会把`\n`写入文件（要删除，否则无效），建议检查
# disable sudo password, ref: https://askubuntu.com/a/878705
echo "$PASSWORD\n$USER ALL=(ALL:ALL) NOPASSWD: ALL" | sudo -S tee /etc/sudoers.d/$USER # skip confirm based on -S

# --- step 1.5 ---
# enable backward/forward prefix commands search
echo '"\e[A": history-search-backward     # arrow up      --> backward
"\e[B": history-search-forward      # arrow down    --> forward' >> ~/.inputrc

# --- step 1.7 ---

# change timezone, so that time display ok
echo "export TZ='Asia/Shanghai'" >> ~/.profile # need relogin

# --- step 2 ---
# update apt and install packages

# change apt source
APT_SOURCE="http://mirrors.yun-idc.com/ubuntu/"
APT_SOURCES_LIST_FILE=/etc/apt/sources.list
sudo sed -i.bak -r  "s|deb \S+|deb $APT_SOURCE|g" $APT_SOURCES_LIST_FILE

echo "Y" | sudo apt update # need confirm but skipped since configured
echo "Y" | sudo apt upgrade

INSTALLED_PACKAGES="vim git htop zsh terminator wget curl python"
echo $INSTALLED_PACKAGES | xargs sudo apt install -y

# --- step 4 ---
# configure zsh (installed in \$INSTALLED_PACKAGES) / oh-my-zsh

# install oh-my-zsh (built-in backward search)
wget https://raw.githubusercontent.com/ohmyzsh/ohmyzsh/master/tools/install.sh
yes | sh install.sh

# --- step 5 ---
# diy zsh based on 'oh-my-zsh'

# add dynamical time display
echo "setopt PROMPT_SUBST
PROMPT='%B%F{yellow}[%D{%L:%M:%S}]%f:%F{green}\${\${(%):-%~}}%f$ %b'
" >> ~/.zshrc

# set zsh as the default terminal (need relogin!)
sudo chsh -s $(which zsh) # after configed sudo, no need to input password

# enable zsh changes
exec zsh

# --- step 6 ---
# re-login/logout
sudo pkill -u $USER
