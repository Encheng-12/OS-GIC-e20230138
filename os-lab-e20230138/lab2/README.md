Student name/ID: TEAV Encheng
Ubuntu username: gic-teav-encheng
My values (oslab values lab2): file1 = sales north.txt, file2 = audit nots.txt , owner = Legal, reader = Marketing, third = Engineering
Files: evidence/paths.txt, evidence/tree.txt, evidence/checkpoint.txt
            Step                                                           My command                                                       Current folder when I ran it
Move the first file (relative destination)                          mv "$file1" ../reports/                                                     incoming
Move the second file (absolute paths)                               cd ..                                                                       lab2
                                                                    pwd
                                                                    mv "$OSLAB_WORKSPACE/lab2/incoming/$file2" "$OSLAB_WORKSPACE/lab2/reports/"  
Read the report from my reader department (relative path)           cat "reports/$file1"                                                         Marketing
The path error I made on purpose, and its message                   