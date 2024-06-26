#!/bin/fish
if test (count $argv) -ne 2
echo "The script must be called from the vscode task."
exit 1
end
set Username (cat ./Username)
set Password (cat ./Password)
set OJ (pwd | sed 's/.*\///g')
cd ./OJTool
./Run.sh
./Build/OJTool -u $Username -p $Password -oj $OJ -o $argv[1] -pr $argv[2]
