- #server #init #ubuntu
  ```shell
  ##------------
  ## mac local config (ensure remote ok)
  ##------------
  # ref: https://askubuntu.com/a/1347849/1629991
  
  
  ##------------
  ## init server
  ##------------
  
  sudo apt update
  sudo apt upgrade -y
  
  sudo apt install zsh
  # install oh-my-zsh
  sh -c "$(curl -fsSL https://raw.githubusercontent.com/ohmyzsh/ohmyzsh/master/tools/install.sh)"
  
  sudo apt install tmux
  # install oh-my-tmux
  git clone https://github.com/gpakosz/.tmux.git
  ln -s -f .tmux/.tmux.conf
  cp .tmux/.tmux.conf.local .
  
  
  # install nvm/node/npm, ref: https://github.com/nvm-sh/nvm
  curl -o- https://raw.githubusercontent.com/nvm-sh/nvm/v0.39.4/install.sh | bash
  export NVM_DIR="$([ -z "${XDG_CONFIG_HOME-}" ] && printf %s "${HOME}/.nvm" || printf %s "${XDG_CONFIG_HOME}/nvm")"
  [ -s "$NVM_DIR/nvm.sh" ] && \. "$NVM_DIR/nvm.sh" # This loads nvm
  
  nvm install 18
  nvm use 18
  
  npm install -g yarn
  
  # ssh/rsync no-secret login (from local to server)
  username="xxx"
  server="xxxxx"
  file="~/.ssh/id_rsa.pub"
  cat $file | ssh $username@$server "cat - >> ~/.ssh/authorized_keys"
  
  # config git in server (server to github)
  rsync -ravP ~/.ssh/id_ed25519* ubuntu@54.254.215.39:~/.ssh/
  # test
  ssh -vT git@github.com
  
  ##------------
  ## mongodb
  ##------------
  
  # install mongodb / postgresql
  # from official at https://www.mongodb.com/docs/manual/tutorial/install-mongodb-on-ubuntu/
  sudo apt-get install gnupg curl
  curl -fsSL https://pgp.mongodb.com/server-7.0.asc | \
   sudo gpg -o /usr/share/keyrings/mongodb-server-7.0.gpg \
   --dearmor
  sudo apt-get update
  
  # if error, resolve the invalid signature problem from official,  https://chrisjean.com/fix-apt-get-update-the-following-signatures-couldnt-be-verified-because-the-public-key-is-not-available/
  sudo apt-key adv --keyserver keyserver.ubuntu.com --recv-keys 160D26BB1785BA38 # replace the code from update error
  
  sudo systemctl start mongod
  sudo systemctl enable mongod
  sudo systemctl status mongod
  # 用户名、密码、端口啥的不需要，直接localhost:27017即可，通过我们的ssh登录（包括在 mongodb compass）
  
  ##------------
  ## postgresql
  ##------------
  sudo apt update
  sudo apt install postgresql postgresql-contrib
  
  sudo systemctl start postgresql 
  sudo systemctl status postgresql
  # change password for our database connection, ref: https://stackoverflow.com/a/57997449/9422455
  # there is no need to change user, since the `postgres` is default
  sudo -u postgres psql -c "ALTER ROLE postgres WITH PASSWORD 'postgres';"
  
  ### install pg-vector, ref: https://github.com/pgvector/pgvector#apt
  psql --version # check postgresql version
  ## ubuntu
  sudo apt install -y postgresql-common
  sudo /usr/share/postgresql-common/pgdg/apt.postgresql.org.sh
  
  ## ubuntu
  sudo apt install postgresql-14-pgvector # support 14/15
  ## mac
  brew install pgvector # only supports 14
  
  ### init server
  cd scripts && yarn && -
  # 需要先装好 pgvector-14
  npx prisma migrate dev && npm prisma db push
  npx tsx scripts/init-flowgpt-data.ts
  npx tsx scripts/init-pg-vector.ts
  
  
  ##------------
  ## nginx
  ##------------
  # 1. 参考这篇配置基本的nginx ssl： https://gist.github.com/jjsquady/5399d6e1b23f501083a9c262d806e248
  # 2. 参考这个配置 子域名 ssl：https://community.letsencrypt.org/t/you-may-need-to-use-a-different-authenticator-plugin/115026/4
  sudo certbot certonly --manual --preferred-challenges=dns --email cto@cs-magic.com --server https://acme-v02.api.letsencrypt.org/directory -d poketto.ai -d '*.poketto.ai'
  # 3. 并同步配置域名内的 DNS 记录： https://dcc.godaddy.com/control/portfolio/poketto.ai/settings?tab=dns&itc=mya_vh_buildwebsite_domain
  # 4. 如果要配置多个域名的话，要把 default-server 去掉
  sudo systemctl start nginx
  
  
  ##------------
  ## source code (poketto #js)
  ##------------
  mkdir @cs-magic && cd @cs-magic 
  mkdir coding && cd coding
  git clone git@github.com:cs-magic/poketto.git
  yarn
  npx prisma migrate dev
  
  # test dev
  yarn dev
  # visit 54.254.215.39:3000 to see if website ok
  
  # run prod
  yarn update
  
  
  ##------------
  ## source code (scrapy-flowgpt, #py)
  ##------------
  # install py 3.11 (since we used, while default is 3.10), https://iohk.zendesk.com/hc/en-us/articles/16724475448473-Install-Python-3-11-on-ubuntu
  sudo apt update && sudo apt upgrade
  sudo apt install wget build-essential libncursesw5-dev libssl-dev \  
  libsqlite3-dev tk-dev libgdbm-dev libc6-dev libbz2-dev libffi-dev zlib1g-dev
  sudo add-apt-repository ppa:deadsnakes/ppa
  sudo apt install python3.11
  
  # ref: https://python-poetry.org/docs/
  curl -sSL https://install.python-poetry.org | python3 -
  echo 'export PATH="/home/ubuntu/.local/bin:$PATH"' >> ~/.zshrc
  poetry install
  poetry shell
  
  
  # ------------------
  # pm2 serve
  # ------------------
  script='
  cd ~/@cs-magic/coding/poketto
  pm2 start --name "poketto" "yarn start -p 30817"
  pm2 start "npx tsx scripts/reset-quota-daily.ts" --name "reset-quota-daily" -c "20 3 * * *" --no-autorestart
  '
  npm i -g pm2
  eval $script
  # startup 会让你手动复制粘贴运行最后一句输出，以启用重启，我们可以自动化
  eval $(pm2 startup | tail -n 1)
  ```