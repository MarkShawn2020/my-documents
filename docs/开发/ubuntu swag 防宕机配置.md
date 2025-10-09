> /think-ultra
  我的ubuntu Mem 2G，Swp 0，我希望修改我的Swp让它有更好的性能，否则容易宕机
  （请直接给出一步步的指引，但不要实施，因为你可能会被命令杀掉）

✻ Thinking…

  用户想要在Ubuntu系统上配置swap分区来提高性能，防止因内存不足导致的宕机。他们有2G内存，0
  swap，希望我给出配置swap的步骤指引，但不要实际执行。

  我需要给出创建swap文件的步骤指引，这是一个系统管理任务。我应该提供详细的步骤但不执行它们。

● 以下是配置swap的步骤指引：

  1. 检查当前swap状态

  free -h
  swapon --show

  2. 创建swap文件（建议4G，2倍内存大小）

  sudo fallocate -l 4G /swapfile

  3. 设置文件权限

  sudo chmod 600 /swapfile

  4. 设置为swap文件

  sudo mkswap /swapfile

  5. 启用swap

  sudo swapon /swapfile

  6. 验证swap已启用

  free -h

  7. 设置开机自动挂载

  echo '/swapfile none swap sw 0 0' | sudo tee -a /etc/fstab

  8. 优化swap性能（可选）

  # 设置swappiness值（建议10-60）
  echo 'vm.swappiness=10' | sudo tee -a /etc/sysctl.conf

  # 设置cache pressure
  echo 'vm.vfs_cache_pressure=50' | sudo tee -a /etc/sysctl.conf

  这样配置后，你的系统将有4G swap空间，大大降低宕机风险。

![](https://poketto.oss-cn-hangzhou.aliyuncs.com/2561ae6b5e963cf152ec4625d269c717.png?x-oss-process=image/resize,w_800/quality,q_100/rotate,0)
