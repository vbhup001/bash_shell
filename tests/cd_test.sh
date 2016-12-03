#!/bin/bash
cd ..
bin/rshell << 'EOF'
mkdir dir1
mkdir dir2
ls
cd dir1
ls
cd ..
ls
cd dir2 && echo a
cd .. || echo b #should not print b
cd -
cd -
cd dir1/../dir2
(cd ..)
(echo a && cd dir1)
(echo b && cd ../dir2); cd;
exit
EOF