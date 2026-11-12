# Lab 3 — Wildcards, Hard Links and Symbolic Links: individual report

Copy this template to `lab3/README.md` in your own course repository. Follow [the instructions](lab3-instruction.md). Your prediction, debrief and checkpoint answers are already saved by `oslab`; do not copy them here. The marks come from those records and your evidence files; this report is your own record of the lab.

- Student name: TEAV Encheng 
- ID: e20230138
- Ubuntu username: gic-teav-encheng
- My values (`oslab values lab3`): name = silver, tag = old, v1 = 107, v2 = 114
- Files: `evidence/wildcards.txt`, `evidence/links.txt`, `evidence/replacement.txt`, `evidence/checkpoint.txt`

## What I Saw

| State | What `cat` printed for the hard link | What `cat` printed for the symbolic link | What `readlink` printed |
|---|---|---|---|
| Before the rename | version 107 | version 107 | silver.txt |
| After the rename, before the repair | version 107 | No such file or directory (dangling error) | silver.txt |
| After a new file took the old name | version 107 | version 114 | silver.txt |
| After my repair | version 107 | version 107 | silver-old.txt |

My repair (the two commands I wrote):
```bash
rm -- silver-soft.txt
ln -s silver-old.txt silver-soft.txt