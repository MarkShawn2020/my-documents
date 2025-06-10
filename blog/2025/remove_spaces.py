#!/usr/bin/env python3
# -*- coding: utf-8 -*-
"""
移除文件和文件夹名称中的空格脚本
作者：南川
日期：2025-06-10
"""

import os
import re
import logging
from pathlib import Path

# 配置日志
logging.basicConfig(
    level=logging.INFO,
    format='%(asctime)s - %(levelname)s - %(message)s',
    handlers=[
        logging.FileHandler('remove_spaces.log', encoding='utf-8'),
        logging.StreamHandler()
    ]
)
logger = logging.getLogger(__name__)

class SpaceRemover:
    def __init__(self, target_dir: str):
        self.target_dir = Path(target_dir)
        self.changes = []
        self.errors = []
    
    def clean_name(self, name: str) -> str:
        """
        清理文件/文件夹名称，去除空格和规范化
        """
        # 保存文件扩展名
        path_obj = Path(name)
        stem = path_obj.stem
        suffix = path_obj.suffix
        
        # 去除多余空格，替换为单个空格
        cleaned_stem = re.sub(r'\s+', ' ', stem.strip())
        
        # 去除所有空格
        cleaned_stem = cleaned_stem.replace(' ', '')
        
        # 特殊字符规范化
        replacements = {
            '·': '-',
            '—': '-',
            '–': '-',
            '－': '-',
            '（': '(',
            '）': ')',
            '：': '-',
            '，': ',',
            '。': '.',
        }
        
        for old, new in replacements.items():
            cleaned_stem = cleaned_stem.replace(old, new)
        
        # 移除连续的分隔符
        cleaned_stem = re.sub(r'[-_]+', '-', cleaned_stem)
        cleaned_stem = re.sub(r'^[-_]+|[-_]+$', '', cleaned_stem)
        
        return cleaned_stem + suffix
    
    def should_rename(self, original: str, cleaned: str) -> bool:
        """
        判断是否需要重命名
        """
        return original != cleaned and ' ' in original
    
    def rename_item(self, old_path: Path, new_name: str) -> bool:
        """
        重命名文件或文件夹
        """
        try:
            new_path = old_path.parent / new_name
            
            # 检查目标路径是否已存在
            if new_path.exists():
                logger.warning(f"目标路径已存在，跳过: {new_path}")
                return False
            
            # 执行重命名
            old_path.rename(new_path)
            self.changes.append((str(old_path), str(new_path)))
            logger.info(f"重命名: {old_path.name} -> {new_name}")
            return True
            
        except Exception as e:
            error_msg = f"重命名失败 {old_path}: {str(e)}"
            logger.error(error_msg)
            self.errors.append(error_msg)
            return False
    
    def process_directory(self, directory: Path) -> None:
        """
        递归处理目录中的所有文件和文件夹
        """
        if not directory.exists():
            logger.error(f"目录不存在: {directory}")
            return
        
        try:
            # 获取所有项目并按深度排序（深度优先，避免重命名父目录后子目录路径失效）
            all_items = []
            for root, dirs, files in os.walk(directory):
                root_path = Path(root)
                
                # 添加文件
                for file in files:
                    file_path = root_path / file
                    all_items.append((file_path, len(file_path.parts)))
                
                # 添加目录
                for dir_name in dirs:
                    dir_path = root_path / dir_name
                    all_items.append((dir_path, len(dir_path.parts)))
            
            # 按深度降序排序（先处理深层的文件）
            all_items.sort(key=lambda x: x[1], reverse=True)
            
            # 处理每个项目
            for item_path, _ in all_items:
                if not item_path.exists():  # 可能已被重命名
                    continue
                    
                original_name = item_path.name
                cleaned_name = self.clean_name(original_name)
                
                if self.should_rename(original_name, cleaned_name):
                    self.rename_item(item_path, cleaned_name)
                    
        except Exception as e:
            error_msg = f"处理目录时出错 {directory}: {str(e)}"
            logger.error(error_msg)
            self.errors.append(error_msg)
    
    def generate_report(self) -> None:
        """
        生成处理报告
        """
        logger.info("\n" + "="*60)
        logger.info("处理完成报告")
        logger.info("="*60)
        
        if self.changes:
            logger.info(f"\n成功重命名 {len(self.changes)} 个项目:")
            for old, new in self.changes:
                logger.info(f"  {Path(old).name} -> {Path(new).name}")
        else:
            logger.info("\n没有找到需要重命名的项目")
        
        if self.errors:
            logger.error(f"\n发生 {len(self.errors)} 个错误:")
            for error in self.errors:
                logger.error(f"  {error}")
        
        logger.info("="*60)

def main():
    target_directory = "/Users/mark/projects/my-docusaurus/my-website/my-documents/blog/2025"
    
    logger.info(f"开始处理目录: {target_directory}")
    
    remover = SpaceRemover(target_directory)
    remover.process_directory(remover.target_dir)
    remover.generate_report()
    
    logger.info("脚本执行完成")

if __name__ == "__main__":
    main()
