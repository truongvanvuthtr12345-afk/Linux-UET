#!/bin/bash
# Ho ten: Vu Van Truong
# Ten tap lenh: greeting.sh
# Muc dich: Thuc hien cac thao tac thong tin he thong va loi chao nguoi dung

echo "Hello + $USER"
uname -a
id -g
date
ls -la ~
echo "TERM=$TERM"
echo "PATH=$PATH"
echo "HOME=$HOME"
echo "Goodbye + $(date)"
