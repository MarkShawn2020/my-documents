#!/bin/bash
# 移除文件和文件夹名称中的空格脚本
# 作者：南川
# 日期：2025-06-10

set -euo pipefail

# 目标目录
TARGET_DIR="/Users/mark/projects/my-docusaurus/my-website/my-documents/blog/2025"

# 日志文件
LOG_FILE="remove_spaces_bash.log"

# 初始化日志
echo "开始执行空格移除脚本 - $(date)" > "$LOG_FILE"

# 计数器
RENAMED_COUNT=0
ERROR_COUNT=0

# 日志函数
log_info() {
    echo "[INFO] $(date '+%Y-%m-%d %H:%M:%S') - $1" | tee -a "$LOG_FILE"
}

log_error() {
    echo "[ERROR] $(date '+%Y-%m-%d %H:%M:%S') - $1" | tee -a "$LOG_FILE"
}

# 清理名称函数
clean_name() {
    local name="$1"
    
    # 去除空格
    name=$(echo "$name" | tr -d ' ')
    
    # 替换中文标点
    name=$(echo "$name" | sed 's/·/-/g; s/—/-/g; s/–/-/g; s/－/-/g')
    name=$(echo "$name" | sed 's/（/(/g; s/）/)/g; s/：/-/g')
    
    # 去除连续的分隔符
    name=$(echo "$name" | sed 's/[-_]\+/-/g; s/^[-_]*//; s/[-_]*$//')
    
    echo "$name"
}

# 重命名函数
rename_item() {
    local old_path="$1"
    local old_name=$(basename "$old_path")
    local dir_path=$(dirname "$old_path")
    
    # 检查是否包含空格
    if [[ "$old_name" != *" "* ]]; then
        return 0
    fi
    
    local new_name=$(clean_name "$old_name")
    local new_path="$dir_path/$new_name"
    
    # 如果名称没有变化，跳过
    if [[ "$old_name" == "$new_name" ]]; then
        return 0
    fi
    
    # 检查目标文件是否存在
    if [[ -e "$new_path" ]]; then
        log_error "目标路径已存在，跳过: $new_path"
        ((ERROR_COUNT++))
        return 1
    fi
    
    # 执行重命名
    if mv "$old_path" "$new_path" 2>/dev/null; then
        log_info "重命名: $old_name -> $new_name"
        ((RENAMED_COUNT++))
        return 0
    else
        log_error "重命名失败: $old_path"
        ((ERROR_COUNT++))
        return 1
    fi
}

# 主处理函数
process_directory() {
    local target_dir="$1"
    
    if [[ ! -d "$target_dir" ]]; then
        log_error "目录不存在: $target_dir"
        return 1
    fi
    
    log_info "开始处理目录: $target_dir"
    
    # 使用 find 命令获取所有文件和目录，按深度倒序排列
    find "$target_dir" -type f -o -type d | sort -r | while IFS= read -r item; do
        # 跳过根目录
        if [[ "$item" == "$target_dir" ]]; then
            continue
        fi
        
        # 检查文件/目录是否仍然存在（可能已被重命名）
        if [[ ! -e "$item" ]]; then
            continue
        fi
        
        rename_item "$item"
    done
}

# 生成报告
generate_report() {
    echo "" | tee -a "$LOG_FILE"
    echo "============================================================" | tee -a "$LOG_FILE"
    echo "处理完成报告" | tee -a "$LOG_FILE"
    echo "============================================================" | tee -a "$LOG_FILE"
    echo "成功重命名: $RENAMED_COUNT 个项目" | tee -a "$LOG_FILE"
    echo "发生错误: $ERROR_COUNT 个" | tee -a "$LOG_FILE"
    echo "详细日志请查看: $LOG_FILE" | tee -a "$LOG_FILE"
    echo "============================================================" | tee -a "$LOG_FILE"
}

# 主函数
main() {
    log_info "脚本开始执行"
    
    # 切换到脚本所在目录
    cd "$(dirname "$0")"
    
    # 处理目录
    process_directory "$TARGET_DIR"
    
    # 生成报告
    generate_report
    
    log_info "脚本执行完成"
}

# 执行主函数
main "$@"
