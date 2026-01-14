#!/usr/bin/env python3
# -*- coding: utf-8 -*-

import re

def convert_table_to_list(file_path):
    with open(file_path, 'r', encoding='utf-8') as f:
        content = f.read()
    
    # Find the table section (lines 76-83)
    lines = content.split('\n')
    
    # Extract table data
    table_data = []
    in_table = False
    
    for i, line in enumerate(lines):
        if '|     |' in line and '预期' in line:  # Header row
            in_table = True
            continue
        elif in_table and line.strip() and line.startswith('|'):
            # Parse table row
            cells = [cell.strip() for cell in line.split('|')[1:-1]]
            if len(cells) == 4 and cells[0] and cells[0] not in ['---', ' ---', '']:
                table_data.append({
                    'category': cells[0],
                    'expectation': cells[1].replace('<br>', '\n').replace('<br />', '\n'),
                    'reality': cells[2].replace('<br>', '\n').replace('<br />', '\n'), 
                    'plan': cells[3].replace('<br>', '\n').replace('<br />', '\n')
                })
        elif in_table and (not line.strip() or not line.startswith('|')):
            break
    
    # Convert to list format
    result = []
    categories = {
        '外在': '01',
        '学业': '02', 
        '事业': '03',
        '财富': '04',
        '情感': '05',
        '精神': '06'
    }
    
    def format_content(content):
        """Format multi-line content with proper indentation"""
        lines = content.strip().split('\n')
        if len(lines) == 1:
            return lines[0]
        
        # If first line starts with '-', handle as list
        if lines[0].strip().startswith('-'):
            formatted = []
            for line in lines:
                if line.strip():
                    formatted.append('\n  ' + line.strip())
            return ''.join(formatted)
        else:
            # Normal text followed by list items
            formatted = [lines[0]]
            for line in lines[1:]:
                if line.strip():
                    formatted.append('\n  ' + line.strip())
            return ''.join(formatted)
    
    for item in table_data:
        cat_num = categories.get(item['category'], '00')
        result.append(f"\n### {cat_num}. {item['category']}\n")
        result.append(f"- 预期：{format_content(item['expectation'])}")
        result.append(f"- 现实：{format_content(item['reality'])}")
        result.append(f"- 计划：{format_content(item['plan'])}")
    
    return '\n'.join(result)

if __name__ == "__main__":
    file_path = "/Users/mark/__core__/my-docusaurus/my-website/my-documents/30岁，终于可以慢一点.md"
    converted_text = convert_table_to_list(file_path)
    
    # Save to output file
    output_path = "/Users/mark/__core__/my-docusaurus/my-website/my-documents/table_converted_to_list.txt"
    with open(output_path, 'w', encoding='utf-8') as f:
        f.write(converted_text)
    
    print("转换完成！")
    print(f"输出文件：{output_path}")
    print("\n转换结果预览：")
    print(converted_text)